#ifndef _TALOS_OBJECT_CLASS_HPP
#define _TALOS_OBJECT_CLASS_HPP

/// Talos Includes
#include "talos/member/reference.hpp"
#include "talos/object/mixin.hpp"
#include "talos/string/common.hpp"

/// Forward Definitions
$_FWD(Talos::Object, using Fields = $::Map::Base<Value::Symbol, $::Unique::Pointer<Member::Reference>>)

namespace Talos {

/// @brief Class Attributes.
template <> struct Object::Wrapper<Object::Class> {
  //  PROPERTIES  //

  Fields statics;          // Static fields.
  Value::Any parent;       // Ancestor value.
  String::Any name;        // Exposed class name.
  Shape::Underlying shape; // Bound shape value.

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a class prototype.
   * @param name                  Name of class.
   * @param shape                 Shape of class.
   * @param parent                Ancestor class.
   */
  explicit Wrapper(const String::Any &name, Shape::Underlying shape, const Value::Any &parent = {}) :
      parent(parent), name(name), shape(shape) {}

  /**
   * @brief Constructs a class prototype.
   * @param isolate               Runtime isolate.
   * @param name                  Name of class.
   */
  explicit Wrapper(Runtime::Isolate *isolate, const $::String::View &name, Shape::Underlying shape) :
      Wrapper(isolate, name, shape, {}) {}

  /**
   * @brief Constructs a class prototype.
   * @param isolate               Runtime isolate.
   * @param name                  Name of class.
   * @param parent                Ancestor class.
   */
  explicit Wrapper(
      Runtime::Isolate *isolate, const $::String::View &name, Shape::Underlying shape, const Value::Any &parent
  ) : Wrapper(String::Any(isolate, name), shape, parent) {}
};

/// @brief Class Interface.
struct Object::Class : public Object::Mixin<Object::Class> {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Mixin::Mixin;

  //  PUBLIC METHODS  /

  inline constexpr Fields &statics() const noexcept { return m_wrapper()->statics; }
  inline constexpr Value::Any &parent() const noexcept { return m_wrapper()->parent; }
  inline constexpr String::Any &name() const noexcept { return m_wrapper()->name; }

  /**
   * @brief Checks if a value extends this class.
   * @param value                 Value to check.
   */
  inline constexpr bool extends(const Value::Any &value) const noexcept { return extends(value.shape()); }
  inline constexpr bool extends(Shape::Underlying shape) const noexcept {
    if (m_wrapper()->shape == shape) return true;
    auto parent = m_wrapper()->parent; // parent
    if (!parent.is<Object::Class>()) return false;
    return parent.as<Object::Class>().extends(shape);
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handlers yielding classes safely.
   * @param self                          Class instance.
   * @param yield                         Yield callback.
   */
  static void m_yield(const Class &self, Globals::Each &yield);

  /**
   * @brief Handles printing values.
   * @param os                    Output stream.
   * @param self                  Class instance.
   */
  static inline void m_print(std::ostream &os, const Class &self) {
    os << $::Dye::cyan("<{0}: {1}>", self.brand(), self.name());
  }
};

} // namespace Talos

#endif
