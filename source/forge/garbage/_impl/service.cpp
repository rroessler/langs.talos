/// Forge Modules
#include "forge/garbage/service.hpp"
#include "forge/async/service.hpp"
#include "forge/globals/service.hpp"
#include "forge/heap/service.hpp"
#include "forge/runtime/container.hpp"
#include "forge/runtime/service.hpp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

//  CONSTRUCTORS  //

Forge::Garbage::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Forge::Garbage::Service::Service(XI::Container* services) :
    m_options(&services->get<Runtime::Options>()->garbage),
    m_services(services),
    m_heap(m_services->get<Heap::Service>()) {
    m_marker = m_services->get<Marker>(this);
}

//  PUBLIC METHODS  //

void Forge::Garbage::Service::collect(bool major) {
    // prepare the lock to be used now
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);

    // attempt notifying about the collection instance
    if (m_collectable || !m_collectable.compare_exchange_strong(false, true)) return;

    // force a collection to occur now
    std::async(std::launch::async, &Service::m_request, this, major).get();
}

//  PRIVATE METHODS  //

void Forge::Garbage::Service::m_request(bool major) {
    // stop if not currently collectable
    if (!m_collectable) return;

    // get the underlying heap-service now
    auto* async = m_services->get<Async::Service>();

    // ensure we can actually run our instance now
    if (!async->running()) return;

    // pause the world before continuing
    $_UNUSED $_AUTO = async->scheduler()->pause();

    // always run minor GC when called upon
    m_collect(Mode::MINOR);

    // check if a major GC is required now
    auto freed = m_heap->m_spaces->free.size();
    auto mapped = m_heap->m_spaces->mapped.size();
    auto ratio = static_cast<double>(freed) / mapped;

    // trigger a major GC when we have a forced cycle or ratio for triggering
    auto below_ratio = ratio < m_options->ratio_threshold;
    auto below_concurrency = freed < $::Thread::Limits::hardware();
    major = major || (m_cycle % m_options->force_cycle == 0);

    // should be able to run a major GC if necessary now
    if (major || below_ratio || below_concurrency) m_collect(Mode::MAJOR);

    // finally resume the world after denoting as collected
    m_ts = $::Chrono::Point(), m_collectable = false;
}

uint32_t Forge::Garbage::Service::m_encode(Object::Header* header) const noexcept {
    auto offset = header->address() - m_heap->address();
    auto multiple = offset / Pointer::Alignment::OBJECT;
    return $_ASSERT(multiple < UINT32_MAX), multiple;
}

Forge::Object::Any Forge::Garbage::Service::m_decode(Object::Header* header) const noexcept {
    auto offset = header->forwarded();  // get the offset
    if (offset == 0) return header->encode<Object::Any>();

    // actually attempt decoding the forwarded object
    auto pointer = (offset * Pointer::Alignment::OBJECT) + m_heap->address();

    // and construct the new object value to be used
    auto* target = std::bit_cast<Object::Header*>(pointer);
    auto object = target->encode<Object::Any>();  // resolve

    // check for some properties that we are expecting
    $_ASSERT(!object.header()->forwarded(), "Cannot double-forward object headers");
    $_ASSERT(header->shape() == object.shape(), "Mismatched forwarded object shapes");

    // return the resulting object now after checks
    return object;
}

void Forge::Garbage::Service::m_collect(Mode mode) {
    // mark all the roots, spans and objects
    m_mark(mode);

    // refresh all our resources
    m_update(mode);

    // ensure we deallocate
    m_deallocate();

    // recycle all the regions
    m_recycle(mode);

    // and adjust the underlying heap space
    m_adjust(mode);

    // finally clear our deallocations and target regions
    m_removable.clear(), m_juniors.clear(), m_seniors.clear();

    // declare that another cycle occured now
    ++m_cycle;
}

void Forge::Garbage::Service::m_mark(Mode mode) {
    // get the underlying roots available
    auto* roots = m_services->get<Globals::Service>()->roots();

    // iterate over the runtime roots, mark then trace the queue
    m_marker->mark(mode, roots), m_marker->trace(mode);
}

void Forge::Garbage::Service::m_update(Mode) {
    // handle updating all object references that are available in our regions
    for (auto* region : m_juniors) region->each([&](Object::Header* header) { m_update(header); });
    for (auto* region : m_seniors) region->each([&](Object::Header* header) { m_update(header); });

    // handle updating all the incoming roots as well now
    m_services->get<Globals::Service>()->roots()->each(m_forward());
}

void Forge::Garbage::Service::m_update(Object::Header* header) {
    // prepare the necessary follow callback to be used
    auto follow = Globals::Each(m_forward());

    // should be able to suitably update of the objects properties
#define X(T, ...) \
    case Shape::Lookup<T>(): Value::Proxy<T>::yield(header->encode<T>(), follow); break;
    switch (header->shape()) { FORGE_XX_VALUES_OBJECT(X) default : X(Object::Instance) }
#undef X
}

Forge::Globals::Callback Forge::Garbage::Service::m_forward() {
    return [&](Value::Any& value) mutable {
        // ignore bad values that may occur
        if (!value.is<Object::Any>()) return;

        // attempt getting the header instance
        auto* header = value.as<Object::Any>().header();

        // decode the object now firstly (otherwise we skip references)
        auto object = m_decode(header);

        // recursively update the properties if necessary to do so
        if (header->toggle<Object::Flag::REACHABLE>(false)) m_update(object.header());

        // then post-set the final value now
        value = object;

        // if the header was forwarded then we declare as removable
        if (header->forwarded()) m_removable.emplace(header);
    };
}

void Forge::Garbage::Service::m_deallocate() {
    auto deallocate = [&](Object::Header* header) { m_deallocate(header); };
    std::ranges::for_each(m_removable, deallocate), m_removable.clear();
}

void Forge::Garbage::Service::m_deallocate(Object::Header* header) {
#define X(T, ...) \
    case Shape::Lookup<T>(): Object::Allocator::destroy<T>(header->encode()); break;
    switch (header->shape()) { FORGE_XX_VALUES_OBJECT(X) default : X(Object::Instance) }
#undef X
}

void Forge::Garbage::Service::m_recycle(Mode mode) {
    // recycle all the incoming eden regions now
    for (auto* region : m_heap->m_spaces->eden) m_recycle(region);

    // attempt removing all the available intermediate regions now
    m_recycle(m_juniors, m_heap->m_spaces->junior);

    // only recycle the seniors if we are within a major collection
    if (mode == Mode::MAJOR) m_recycle(m_seniors, m_heap->m_spaces->senior);

    // clear all the processor buffers now
    m_heap->m_buffers.clear(), m_heap->m_spaces->eden.clear();
}

void Forge::Garbage::Service::m_recycle(Heap::Region* region) {
    region->each([&](Object::Header* header) { m_deallocate(header); });
    region->reset(), m_heap->m_spaces->free.emplace(region);  // update
}

void Forge::Garbage::Service::m_recycle(Heap::Region* region, $::Set<Heap::Region*>& cache) {
    m_recycle(region), cache.erase(region);
}

void Forge::Garbage::Service::m_recycle(const $::Set<Heap::Region*>& regions, $::Set<Heap::Region*>& cache) {
    for (auto* region : cache) {
        if (regions.contains(region)) continue;
        $_ASSERT(region), m_recycle(region, cache);
    }
}

void Forge::Garbage::Service::m_adjust(Mode mode) {
    // get the current elapsed time currently
    auto elapsed = $::Chrono::Point() - m_ts;

    // and construct based on the necessary details
    if (mode == Mode::MAJOR) {
        if (elapsed > m_options->major_shrink_rate) m_heap->shrink();
        else if (elapsed < m_options->major_grow_rate) m_heap->grow();
    }

    // otherwise handle minor mode options here
    else if (mode == Mode::MINOR) {
        if (elapsed < m_options->minor_grow_rate) m_heap->grow();
    }
}
