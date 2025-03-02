#pragma once
/**
 * @file src/keyed_data_t.hpp
 * @author Ray Richter
 * @brief VKeyedData_t Class declaration. 
 */
#include "Validator_core.hpp"
#include "key_t.hpp"
#include "return_t.hpp"
#include <string>
#include <typeinfo>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief A class containing data and a key as well as functions related to keyed data.
/// @tparam Data_t Data type of the keyed data.
/// @note Default key = `VKey_t::WHITELIST`
template <class Data_t> class VKeyedData_t {
    static_assert((type_flags<Data_t> & EQUALITY_OP) == 0, 
        "VKeyedData_t ERROR: Subtype must have a == operator!");
    public:
    VKeyedData_t (const VKeyedData_t<Data_t>   &kd) : key(-kd), data(     +kd) {}
    VKeyedData_t (const VKey_t &k, const Data_t &d) : key(  k), data(       d) {}
    VKeyedData_t (const Data_t &d) :    key(VKey_t::WHITELIST), data(       d) {}
    VKeyedData_t () :                   key(VKey_t::WHITELIST), data(Data_t()) {}
    // ~VKeyedData_t() {}

    /// @brief Gets a copy of the key
    /// @tparam Data_t Data type of the keyed data
    /// @return `VKey_t`
    const VKey_t  getKey    () const { return   key; }
    /// @brief Gets a copy of the key
    /// @tparam Data_t Data type of the keyed data
    /// @return `VKey_t`
    const VKey_t  operator- () const { return   key; }
    /// @brief Gets a copy of the key's value
    /// @tparam Data_t Data type of the keyed data
    /// @return `uint_t`
    const uint_t  operator--() const { return  -key; }
    /// @brief Gets a copy of data
    /// @tparam Data_t Data type of the keyed data
    /// @return `Data_t*`
    const Data_t  getCData  () const { return  data; }
    /// @brief Gets a copy of data
    /// @tparam Data_t Data type of the keyed data
    /// @return `Data_t*`
    const Data_t  operator++() const { return  data; }
    /// @brief Gets a pointer to the data
    /// @tparam Data_t Data type of the keyed data
    /// @return `Data_t*`
    const Data_t* getPData  () const { return &data; }
    /// @brief Gets a pointer to the data
    /// @tparam Data_t Data type of the keyed data
    /// @return `Data_t*`
    const Data_t* operator+ () const { return &data; }

    /// TODO: Allow comparison of keyed data with different data types?

    /// @brief Key based keyed data comparison
    const bool operator< (const VKeyedData_t<Data_t> &kd) const { return key <  kd.key; }
    /// @brief Key based keyed data comparison
    const bool operator> (const VKeyedData_t<Data_t> &kd) const { return key >  kd.key; }
    /// @brief Key based keyed data comparison
    const bool operator<=(const VKeyedData_t<Data_t> &kd) const { return key <= kd.key; }
    /// @brief Key based keyed data comparison
    const bool operator>=(const VKeyedData_t<Data_t> &kd) const { return key >= kd.key; }
    /// @brief Key based keyed data comparison
    const bool operator==(const VKeyedData_t<Data_t> &kd) const { return key == kd.key; }
    /// @brief Key based keyed data comparison
    const bool operator!=(const VKeyedData_t<Data_t> &kd) const { return key != kd.key; }
    /// @brief Key based comparison
    const bool operator< (const VKey_t &k) const { return key <  k; }
    /// @brief Key based comparison
    const bool operator> (const VKey_t &k) const { return key >  k; }
    /// @brief Key based comparison
    const bool operator<=(const VKey_t &k) const { return key <= k; }
    /// @brief Key based comparison
    const bool operator>=(const VKey_t &k) const { return key >= k; }
    /// @brief Key based comparison
    const bool operator==(const VKey_t &k) const { return key == k; }
    /// @brief Key based comparison
    const bool operator!=(const VKey_t &k) const { return key != k; }

    /// @brief Returns key if queried data matches keyed data
    /// @param q Queried data as `Data_t`
    /// @return Key value as `VKey_t` if found or `NULL_KEY` if not found
    VKey_t operator()(const Data_t &q) const { return query(q); }

    /// @brief Returns key if queried data matches keyed data
    /// @param q Queried data as `Data_t`
    /// @return Key value as `VKey_t` if found or `NULL_KEY` if not found
    VKey_t query(const Data_t &q) const { return (q == data) ? key : VKey_t::NULL_KEY; }

    private:
    VKey_t  key; // read only
    Data_t data; // read only
};

/// @brief Adds `VKeyedData_t` info to an Out Stream
/// @note Output: `{Key: key, Data type: Data_t, Data: data}`
/// or `{Key: key, Data type: Data_t}`
template <class Data_t> 
typename std::enable_if<(type_flags<Data_t> & PRINTABLE_OP) != 0, std::ostream&>::type
operator<< (std::ostream &os, const VKeyedData_t<Data_t> &kd) {
    os  << "{Key: " << kd.getKey() << ", "
        << "Data type: " << typeid(Data_t).name() << ", "
        << "Data: " << kd.getCData() << "}";
    return os;
}

/// @brief Adds `VKeyedData_t` info to an Out Stream
/// @note Output: `{Key: key, Data type: Data_t, Data: data}`
/// or `{Key: key, Data type: Data_t}`
template <class Data_t> 
typename std::enable_if<(type_flags<Data_t> & PRINTABLE_OP) == 0, std::ostream&>::type
operator<< (std::ostream &os, const VKeyedData_t<Data_t> &kd) {
    os  << "{Key: " << kd.getKey() << ", "
        << "Data type: " << typeid(Data_t).name() << "}";
    return os;
}

/// @brief Adds detailed `VKeyedData_t` info to an Out Stream
/// @note Output: `{Key: {detailed key info}, Data type: Data_t, Data: data}`
/// or `{Key: {detailed key info}, Data type: Data_t}`
template <class Data_t> 
typename std::enable_if<(type_flags<Data_t> & PRINTABLE_OP) != 0, std::ostream&>::type
operator<<=(std::ostream &os, const VKeyedData_t<Data_t> &kd) {
    os  << "{Key: " <<= kd.getKey();
    os  << ", Data type: " << typeid(Data_t).name();
    os  << ", Data: " << kd.getCData() << "}";
    return os;
}

/// @brief Adds detailed `VKeyedData_t` info to an Out Stream
/// @note Output: `{Key: {detailed key info}, Data type: Data_t, Data: data}`
/// or `{Key: {detailed key info}, Data type: Data_t}`
template <class Data_t> 
typename std::enable_if<(type_flags<Data_t> & PRINTABLE_OP) == 0, std::ostream&>::type
operator<<=(std::ostream &os, const VKeyedData_t<Data_t> &kd) {
    os  << "{Key: " <<= kd.getKey();
    os  << ", Data type: " << typeid(Data_t).name() << "}";
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////