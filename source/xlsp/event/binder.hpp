#ifndef _XLSP_EVENTS_BINDER_HPP
#define _XLSP_EVENTS_BINDER_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

/// XLSP Modules
#include "xlsp/event/storage.hpp"
#include "xlsp/message/error.hpp"
#include "xlsp/message/notification.hpp"
#include "xlsp/message/request.hpp"

namespace XLSP::Event {

    /// @brief Handles binding events to a cache.
    class Binder {
        //  PROPERTIES  //

        /// @brief Events Storage Reference.
        Storage* m_storage;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an events binder.
         * @param storage               Events storage.
         */
        explicit Binder(Storage* storage) : m_storage(storage) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Core binder for notifications.
         * @tparam P                    Parameters typing.
         * @param method                Notification method.
         * @param handler               Handler to be bound.
         */
        template <class P>
        inline void on_notify(const Message::Method& method, $::Functor::Unique<void(const P&)>&& handler) {
            m_storage->notifications[method] = [cb = std::move(handler)](
                                                   const $::Serde::Value& value) { cb($::Reflect::decode<P>(value)); };
        }

        /**
         * @brief Allows binding class methods to notifications.
         * @tparam T                    Type of instance.
         * @tparam B                    Base instance type.
         * @tparam P                    Parameters typing.
         * @param method                Notification method.
         * @param self                  Self instance value.
         * @param handler               Handler to be bound.
         */
        template <class T, std::derived_from<T> B, class P>
        inline void on_notify(const Message::Method& method, T* self, void (B::*handler)(const P&)) {
            on_notify(method, [self, handler](const auto& params) { return (self->*handler)(params); });
        }

        /**
         * @brief Handles binding notifications.
         * @tparam M                    Notification kind.
         * @param handler               Handler to be bound.
         */
        template <Message::Type M>
        inline void on_notify($::Functor::Unique<void(const Notification::Params<M>&)>&& handler) {
            on_notify<Notification::Params<M>>(Message::Channel<M>(), std::move(handler));
        }

        /**
         * @brief Allows binding class methods to notifications.
         * @tparam T                    Type of instance.
         * @tparam B                    Base instance type.
         * @tparam M                    Notification kind.
         * @param self                  Self instance value.
         * @param handler               Handler to be bound.
         */
        template <class T, std::derived_from<T> B, Message::Type M>
        inline void on_notify(T* self, void (B::*handler)(const Notification::Params<M>&)) {
            on_notify<M>([self, handler](const Notification::Params<M>& params) { return (self->*handler)(params); });
        }

        /**
         * @brief Handles generic requests.
         * @tparam P                    Parameters typing.
         * @param method                Request method.
         * @param handler               Handler to bind.
         */
        template <class P>
        inline void on_request(const Message::Method& method, $::Functor::Unique<void(const P&, Answer&&)>&& handler) {
            m_storage->requests[method] = [cb = std::move(handler)](const auto& value, Answer&& reply) {
                cb($::Reflect::decode<P>(value), std::move(reply));
            };
        }

        /**
         * @brief Handles generic requests.
         * @tparam T                    Type of instance.
         * @tparam B                    Base instance type.
         * @tparam P                    Parameters typing.
         * @param method                Request method.
         * @param self                  Instance self value.
         * @param handler               Handler to bind.
         */
        template <class T, std::derived_from<T> B, class P>
        inline void on_request(const Message::Method& method, T* self, void (B::*handler)(const P&, Answer&&)) {
            on_request(method, [self, handler](const $::Serde::Value& params, Answer&& reply) {
                (self->*handler)(params, std::move(reply));
            });
        }

        /**
         * @brief Handles binding typed requests.
         * @tparam M                    Request kind.
         * @param handler               Handler to be bound.
         */
        template <Message::Type M, class C>
        inline void on_request($::Functor::Unique<void(Request::Handle<M, C>)>&& handle) {
            // prepare a transformer callback to be used
            auto transformer = [cb = std::move(handle)](const auto& params, Answer&& reply) {
                // prepare a handle to be used now
                Request::Handle<M, C> request = Request::Handle<M, C>(params);

                if constexpr (std::is_same_v<C, Answer>) request.reply = std::move(reply);
                else request.reply = Binder::m_respond<M, C>(std::move(reply));

                // and trigger the result now
                cb(std::move(request));
            };

            // and bind it to the original requestor now
            on_request<Request::Params<M>>(Message::Channel<M>(), std::move(transformer));
        }

        /**
         * @brief Handles transforming typed requests.
         * @tparam T                    Type of instance.
         * @tparam B                    Base instance type.
         * @tparam P                    Parameters typing.
         * @param self                  Instance self value.
         * @param handler               Handler to bind.
         */
        template <class T, std::derived_from<T> B, Message::Type M, class C>
        inline void on_request(T* self, void (B::*handler)(Request::Handle<M, C>)) {
            on_request<M, C>([self, handler](auto handle) { (self->*handler)(std::move(handle)); });
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles binding responses.
         * @tparam M                        Message type.
         * @tparam C                        Callback type.
         * @param reply                     Response callback.
         */
        template <Message::Type M, class C>
        static inline Request::Callback<M> m_respond(Answer&& reply) {
            return [rp = std::move(reply)](const Message::Result<Response::Value<M>>& result) {
                auto* response = std::get_if<Response::Value<M>>(&result);
                if (response != nullptr) rp($::Reflect::encode(*response));
                else rp(Message::Error(std::get<Message::Error>(result)));
            };
        }
    };

}  // namespace XLSP::Event

#endif
