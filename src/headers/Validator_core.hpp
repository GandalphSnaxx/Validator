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
#ifdef  NDEBUG
#define V_DEBUG_MSG(msg)
#define V_DEBUG_NO_ENDL(msg)
#define V_DEBUG_ENDL
#else
#define V_DEBUG_MSG(msg)      std::cout << msg << std::endl
#define V_DEBUG_NO_ENDL(msg)  std::cout << msg
#define V_DEBUG_ENDL          std::cout << std::endl
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
constexpr uint8_t type_flags = 
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
using  uint_t =    uint8_t;
#define V_UINT_MAX    UINT8_MAX
#elif defined(USE_16_BIT_MODE)
using  uint_t =    uint16_t;
#define V_UINT_MAX    UINT16_MAX
#elif defined(USE_32_BIT_MODE)
using  uint_t =    uint32_t;
#define V_UINT_MAX    UINT32_MAX
#elif defined(USE_64_BIT_MODE)
using  uint_t =    uint64_t;
#define V_UINT_MAX    UINT64_MAX
#else // Default to 32 bit mode
using  uint_t =    uint32_t;
#define V_UINT_MAX    UINT32_MAX
#endif

/// @subsection Internal VKey_t Dependant Type Definitions
// With subtype T |using|    New type | Complex type | Sub type(s)

// template <class T> using VKeyedList_t = std::multimap<VKey_t,  T >;
// template <class T> using VKeyedData_t = std::pair    <VKey_t,  T >;
// template <class T> using     VRange_t = std::pair    <     T,  T >;
// template <class T> using      VList_t = std::vector  <         T >;
// template <class T> using VRangeList_t = std::vector  <VRange_t<T>>;

// template <class T> const bool operator==(const VKeyedData_t<T> &lhs, const VKey_t &rhs) { return lhs.first == rhs; }
// template <class T> const bool operator==(const VKey_t &lhs, const VKeyedData_t<T> &rhs) { return rhs.first == lhs; }
// template <class T> const bool operator!=(const VKeyedData_t<T> &lhs, const VKey_t &rhs) { return lhs.first != rhs; }
// template <class T> const bool operator!=(const VKey_t &lhs, const VKeyedData_t<T> &rhs) { return rhs.first != lhs; }

// /// @subsection ValidList_t Internal Class Declaration and Definition
// /// @brief A class containing a keyed list of validation info and functions for configuring the list, initalizing the validator,
// /// querying data, and scoring queried data
// /// @tparam Data_t Data type
// /// TODO: Is init needed?
// /// TODO: Add range validation
// template <class Data_t> class ValidList_t {
//     public:
//     /// TODO: Add additional constructors?

//     ValidList_t();  // Default constructor
//     ~ValidList_t(); // Deconstructor

//     void add(const VKey_t&, const VList_t<Data_t>&);
//     void add(const VKey_t&, const Data_t&);
//     void add(const  VKeyedList_t<Data_t>&);
//     void add(const  VKeyedData_t<Data_t>&);
//     void add(const       VList_t<Data_t>&);
//     void add(const               Data_t &);
//     void add(const  VRangeList_t<Data_t>&);
//     void add(const      VRange_t<Data_t>&);

//     VReturn_t validate(const Data_t&) const;

//     ValidList_t<Data_t>& operator+=(const VKeyedList_t<Data_t> &rhs) { this->_addkl(rhs); return *this; }
//     ValidList_t<Data_t>& operator+=(const VKeyedData_t<Data_t> &rhs) { this->_addkd(rhs); return *this; }
//     ValidList_t<Data_t>& operator+=(const VRangeList_t<Data_t> &rhs) { this->_addrl(rhs); return *this; }
//     ValidList_t<Data_t>& operator+=(const     VRange_t<Data_t> &rhs) { this->_addrg(rhs); return *this; }

//     ValidList_t<Data_t>& operator+=(const VList_t<Data_t> &rhs) { this->_add2(VKey_t::WHITELIST, rhs); return *this; }
//     ValidList_t<Data_t>& operator+=(const         Data_t  &rhs) { this->_add2(VKey_t::WHITELIST, rhs); return *this; }
//     ValidList_t<Data_t>& operator-=(const VList_t<Data_t> &rhs) { this->_add2(VKey_t::BLACKLIST, rhs); return *this; }
//     ValidList_t<Data_t>& operator-=(const         Data_t  &rhs) { this->_add2(VKey_t::BLACKLIST, rhs); return *this; }
//     ValidList_t<Data_t>& operator*=(const VList_t<Data_t> &rhs) { this->_add2(VKey_t::  PERFECT, rhs); return *this; }
//     ValidList_t<Data_t>& operator*=(const         Data_t  &rhs) { this->_add2(VKey_t::  PERFECT, rhs); return *this; }
//     ValidList_t<Data_t>& operator>=(const         Data_t  &rhs) { this->_add2(VKey_t::  MINIMUM, rhs); return *this; }
//     ValidList_t<Data_t>& operator<=(const         Data_t  &rhs) { this->_add2(VKey_t::  MAXIMUM, rhs); return *this; }

//     VReturn_t operator()(const Data_t &qData) const { return validate(qData); } // Allows: score += validator(qData);

//     private:
//     VKeyedList_t<Data_t> _keyedList{};
//     // VRangeList_t<Data_t> _rangeList{};
//     Config_t                _config{};

//     void _addData(const VKeyedData_t<Data_t> &keyedData);   // Internal add keyed data function
//     void _add2 (const VKey_t&, const VList_t<Data_t>&);     // Internal add key and list
//     void _add2 (const VKey_t&, const         Data_t &);     // Internal add key and data
//     void _addkl(const VKeyedList_t<Data_t>&);               // Internal add keyed list
//     void _addkd(const VKeyedData_t<Data_t>&);               // Internal add keyed data
//     void _addrg(const     VRange_t<Data_t>&);               // Internal add range data
//     void _addrl(const VRangeList_t<Data_t>&);               // Internal add range list
//     VReturn_t _valueScore(const Data_t &qData);             // Internal evaluate score based on queried data's value
// };

/// @subsection Validator Member Functions

// inline std::ostream& operator<< (std::ostream&, const    VKey_t&); // Print key info
// inline std::ostream& operator<<=(std::ostream&, const    VKey_t&); // Print detailed key info
// inline std::ostream& operator<< (std::ostream&, const  Config_t&); // Print config info
// inline std::ostream& operator<<=(std::ostream&, const  Config_t&); // Print detailed config info
// inline std::ostream& operator<< (std::ostream&, const VReturn_t&); // Print return info
// inline std::ostream& operator<<=(std::ostream&, const VReturn_t&); // Print detailed return info
// template <class T> inline std::ostream& operator<< (std::ostream&, const VKeyedData_t<T>&); // Print keyed data info
// template <class T> inline std::ostream& operator<<=(std::ostream&, const VKeyedData_t<T>&); // Print detailed keyed data info
// template <class T> inline std::ostream& operator<< (std::ostream&, const VKeyedList_t<T>&); // Print keyed list info
// template <class T> inline std::ostream& operator<<=(std::ostream&, const VKeyedList_t<T>&); // Print detailed keyed list info
// template <class T> inline std::ostream& operator<< (std::ostream&, const      VList_t<T>&); // Print list info
// template <class T> inline std::ostream& operator<<=(std::ostream&, const      VList_t<T>&); // Print detailed list info
// template <class T> inline std::ostream& operator<< (std::ostream&, const     VRange_t<T>&); // Print range data info
// template <class T> inline std::ostream& operator<<=(std::ostream&, const     VRange_t<T>&); // Print detailed range data info
// template <class T> inline std::ostream& operator<< (std::ostream&, const VRangeList_t<T>&); // Print range list info
// template <class T> inline std::ostream& operator<<=(std::ostream&, const VRangeList_t<T>&); // Print detailed range list info
// template <class T> inline std::ostream& operator<< (std::ostream&, const  ValidList_t<T>&); // Print Validator info
// template <class T> inline std::ostream& operator<<=(std::ostream&, const  ValidList_t<T>&); // Print detailed Validator info

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////