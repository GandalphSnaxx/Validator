#pragma once
/**
 * @file src/Validator_core.hpp
 * @author Ray Richter
 * @brief Internal header for Validator declarations.
 */

/// @section Required stdlib Includes
#include <cstdlib>
#include <cstdint>
#include <ostream>
#include <map>
#include <type_traits>
#include <vector>

/// @section Debug Macros
#ifdef  VALIDATOR_DEBUG
#define V_DEBUG_MSG(msg)      std::cout << msg << std::endl
#define V_DEBUG_NO_ENDL(msg)  std::cout << msg
#define V_DEBUG_ENDL          std::cout << std::endl
#else
#define V_DEBUG_MSG(msg)
#define V_DEBUG_NO_ENDL(msg)
#define V_DEBUG_ENDL
#endif

/// @section Type Trait Functions

#define HAS_OP(op, op_name)                                                                     \
template <typename T>                                                                           \
auto _has_##op_name(int) -> decltype(std::declval<T>() op std::declval<T>(), std::true_type{}) {\
    return std::true_type{};                                                                    \
}                                                                                               \
template <typename T>                                                                           \
std::false_type _has_##op_name(...) {                                                           \
    return std::false_type{};                                                                   \
}                                                                                               \
template <typename T>                                                                           \
constexpr bool has_##op_name = decltype(_has_##op_name<T>(0))::value;                           \

// Equality operators
HAS_OP(==, eq_op);
HAS_OP(!=, ineq_op);
// Comparison operators
HAS_OP(< , lt_op);
HAS_OP(> , gt_op);
HAS_OP(<=, lteq_op);
HAS_OP(>=, gteq_op);
// Arithmatic operators
HAS_OP(+ , add_op);
HAS_OP(- , sub_op);
HAS_OP(+=, add_eq_op);
HAS_OP(-=, sub_eq_op);
// COUT Operators
template <typename T>
auto _has_cout_op(int) -> decltype(std::cout << std::declval<T>(), std::true_type{}) {
    return std::true_type{};
}
template <typename T>
std::false_type _has_cout_op(...) {
    return std::false_type{};
}
template <typename T>
constexpr bool has_cout_op = decltype(_has_cout_op<T>(0))::value;

constexpr enum TFlags {
    EQUALITY_OP     = 1u,
    INEQUALITY_OP   = 2u,
    COMPARISON_OP   = 4u,
    ARITHMATIC_OP   = 8u,
    PRINTABLE_OP    = 16u,
    // UNUSED          = 32u,
    // UNUSED          = 64u,
    // UNUSED          = 128u,
};

template <typename T>
constexpr size_t type_flags = 
//  op flag       |  required operators
    EQUALITY_OP   *  has_eq_op<T>   |
    INEQUALITY_OP *  has_ineq_op<T> |
    COMPARISON_OP * (has_eq_op<T>  && has_ineq_op<T> && has_lt_op<T>     && has_gt_op<T> && has_lteq_op<T> && has_gteq_op<T>) |
    ARITHMATIC_OP * (has_add_op<T> && has_sub_op<T>  && has_add_eq_op<T> && has_sub_eq_op<T>) |
    PRINTABLE_OP  *  has_cout_op<T>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @subsection Internal Data Type Declaration
//  Set the number of bits to use for internal use
#if   defined(USE_8_BIT_MODE)
using  uint_t =     uint8_t;
#define V_UINT_MAX  UINT8_MAX
#elif defined(USE_16_BIT_MODE)
using  uint_t =     uint16_t;
#define V_UINT_MAX  UINT16_MAX
#elif defined(USE_32_BIT_MODE)
using  uint_t =     uint32_t;
#define V_UINT_MAX  UINT32_MAX
#elif defined(USE_64_BIT_MODE)
using  uint_t =     uint64_t;
#define V_UINT_MAX  UINT64_MAX
#else // Default to size_t
using  uint_t =     size_t;
#define V_UINT_MAX  SIZE_MAX
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////