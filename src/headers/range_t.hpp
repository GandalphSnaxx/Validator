#pragma once
/**
 * @file src/keyed_data_t.hpp
 * @author Ray Richter
 * @brief VRange_t Class declaration. 
 * @note Operator overrides: 
 * op | return_t | other_t | Description
 * !  | bool     | -       | Returns true if range is invalid   (min == max)
 * ~  | bool     | -       | Returns true if range is exclusive (min >  max)
 * () | bool     | Data_t  | Returns true if queried data is within the range
 */
#include <flagfield.hpp>
#include "Validator_core.hpp"
#include "keyed_data_t.hpp"
#include "key_t.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Data_t> class VRange_t {
    // static_assert(std::is_arithmetic<Data_t>::value, "VRange_t ERROR: Data_t must be an arithmetic type.");
    static_assert((type_flags<Data_t> & COMPARISON_OP) != 0, "VRange_t ERROR: Data_t must have comparison operators.");
private:
    Data_t min;
    Data_t max;
    enum : uint8_t { // Config flags
        INVALID = 0, 
        HAS_MIN, 
        HAS_MAX, 
        EXCLUSIVE, 
        MAX_FLAG };
    FlagField<MAX_FLAG> cfg; // Range configuration flags
public:
    /// @brief Constructor from minimum and maximum data.
    VRange_t(const Data_t &min, const Data_t &max) { addMin(min); addMax(max); }
    /// @brief Constructor from keyed data.
    VRange_t(const VKeyedData_t<Data_t> &kd) { addKeyedData(kd); }
    /// @brief Copy constructor.
    VRange_t(const VRange_t<Data_t> &other) : min(other.min), max(other.max), cfg(other.cfg) {}
    /// @brief Default constructor.
    VRange_t(){}

    bool operator! () const { return min == max; }
    bool operator~ () const { return cfg(EXCLUSIVE); }
    bool operator()(const Data_t &data) const { return query(data); }

    bool addMin(const Data_t &data) {
        if (cfg(HAS_MIN) || cfg(INVALID)) return false;
        if (cfg(HAS_MAX) && data == max) { cfg += INVALID; return false; }
        if (cfg(HAS_MAX) && data >  max) { cfg += EXCLUSIVE; }
        min = data; cfg += HAS_MIN; return true; }
    bool addMax(const Data_t &data) {
        if (cfg(HAS_MAX) || cfg(INVALID)) return false;
        if (cfg(HAS_MIN) && data == min) { cfg += INVALID; return false; }
        if (cfg(HAS_MIN) && data <  min) { cfg += EXCLUSIVE; }
        max = data; cfg += HAS_MAX; return true; }
    /// @brief Adds keyed data to the range. Returns `false` if the key is invalid and no data is added.
    bool addKeyedData(const VKeyedData_t<Data_t> &kd) {
        switch (kd.getKey()) {
        case VKey_t::MINIMUM: return addMin(kd.getData());
        case VKey_t::MAXIMUM: return addMax(kd.getData());
        default: return false; }}
    /// @brief Checks if queried data is within the range.
    bool query(const Data_t &data) const {
        if (cfg(INVALID  )) return false;
        if (cfg(EXCLUSIVE)) return data < min || data > max;
        return data >= min && data <= max; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////