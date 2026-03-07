/// Talos Modules
#include "talos/type/builder.hpp"

//  PUBLIC METHODS  //

Talos::Type::Erased Talos::Type::Generic::instantiate(std::vector<Erased> arguments) const {
    // get the details about the incoming arguments and parameters
    auto adicity = m_parameters.size();

    // prepare the constraints cache to be used
    auto constraints = $::New().shared<Constraints::element_type>();

    // reconstruct the suitable cache now
    for (size_t ii = 0; ii < adicity; ++ii) {
        // get the incoming parameter
        auto* parameter = m_parameters.at(ii).get();

        // resolve our argument value now
        auto argument = ii < arguments.size() ? arguments.at(ii) : Builder::unset();

        // finally construct the necessary parameter typing
        (*constraints)[parameter] = parameter->coalesce(argument);
    }

    // and attempt instantiating the body now
    return m_target->infer(constraints);
}

//  PRIVATE METHODS  //

Talos::Type::Erased Talos::Type::Generic::m_infer(const Constraints& constraints) const {
    return Builder::generic(m_target->infer(constraints), m_parameters);
}

bool Talos::Type::Generic::m_unify(const Erased& candidate, const Constraints& constraints) const {
    // ignore if the other is not a suitable generic
    if (!candidate->is<Generic>()) return false;

    // cast the other generic now
    auto other = candidate->as<Generic>();

    // stop if the total parameters count is invalid
    if (m_parameters.size() != other->m_parameters.size()) return false;

    // now we attempt instantiating as necessary
    auto instantiated = other->instantiate({ m_parameters.cbegin(), m_parameters.cend() });

    // and finally we want to unify based on the target now
    return m_target->unify(instantiated, constraints);
}

void Talos::Type::Generic::m_print($::Stream::Output& os) const {
    // ignore if the underlying parameters are valid here
    if (m_parameters.empty() || !m_target->is<Callable>()) return void(os << *m_target);

    static constexpr $::String::View prefix = "fn ";  // prefix value
    auto suffix = fmt::to_string(*m_target).substr(prefix.size());

    // prepare the parameters to be output as well
    auto predicate = [](const auto& parameter) -> Erased { return parameter; };
    auto parameters = $::Ranges::To(m_parameters | std::views::transform(predicate));

    // and show the final result now as necessary
    os << prefix << '[' << $::Convert::join(parameters) << ']' << suffix;
}
