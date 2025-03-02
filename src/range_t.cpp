#include "headers/range_t.hpp"
/**
 * @file src/range_t.cpp
 * @author Ray Richter
 * @brief VRange_t definitions
 */

using namespace Validspace;

/// @section Constructors

template <class Data_t> VRange_t<Data_t>::VRange_t(const Data_t &newMin, const Data_t &newMax) {
    static_assert(std::is_arithmetic<Data_t>::value, "Range data must use an arithmatic data type!");
    DEBUG_MSG("Called VRange_t constructor with type: " << typeid(Data_t).name());
    _init(newMin, newMax); }

template <class Data_t> VRange_t<Data_t>::VRange_t(const VRange_t<Data_t> &other) {
    static_assert(std::is_arithmetic<Data_t>::value, "Range data must use an arithmatic data type!");
    DEBUG_MSG("Called VRange_t copy constructor with type: " << typeid(Data_t).name());
    _init(other.min, other.max); }

template <class Data_t> VRange_t<Data_t>::VRange_t(const VKeyedData_t<Data_t> &keyedData) {
    static_assert(std::is_arithmetic<Data_t>::value, "Range data must use an arithmatic data type!");
    DEBUG_MSG("Called VRange_t keyed data constructor with type: " << typeid(Data_t).name());
    _init(keyedData); }

template <class Data_t> VRange_t<Data_t>::VRange_t() {
    static_assert(std::is_arithmetic<Data_t>::value, "Range data must use an arithmatic data type!");
    DEBUG_MSG("Called VRange_t default constructor with type: " << typeid(Data_t).name()); 
    // Set config to known state
    cfg = Config_t::ARITHMATIC_FLAG | Config_t::RANGE_FLAG;
}

template <class Data_t> VRange_t<Data_t>::~VRange_t() {
    static_assert(std::is_arithmetic<Data_t>::value, "Range data must use an arithmatic data type!");
    DEBUG_MSG("Called VRange_t deconstructor with type: " << typeid(Data_t).name());
}

/// @section Operator Overrides
/// @note Operator overrides: 
/// op | return_t | other_t | Description
/// !  | bool     | -       | Returns true if range is invalid   (min == max)
/// ~  | bool     | -       | Returns true if range is exclusive (min >  max)
/// () | bool     | Data_t  | Returns true if queried data is within the range 

template <class Data_t> bool VRange_t<Data_t>::operator()(const Data_t &qData) const {
    /// TODO: Check HAS_MIN and HAS_MAX
    return min < qData && qData < max;
}

/// @section Internal Functions

template <class Data_t> bool VRange_t<Data_t>::_init(const Data_t &newMin, const Data_t &newMax) {
    // Set config to a known state
    cfg  = Config_t::INITALIZED_FLAG;
    cfg += Config_t::ARITHMATIC_FLAG;
    cfg += Config_t::     RANGE_FLAG;

    bool isValid = true;

    if (newMin >  newMax) { DEBUG_MSG("\tThis range is an exclusive range");   cfg += Config_t::EX_RANGE_FLAG; }
    if (newMin == newMax) { DEBUG_MSG("\tWARNING: This range is a single value! min == max"); isValid = false; }

    min = newMin;
    max = newMax;
    return isValid;
}

template <class Data_t> bool VRange_t<Data_t>::_init(const VKeyedData_t<Data_t> &keyedData) {
    // Set config to a known state
    cfg  = Config_t::INITALIZED_FLAG;
    cfg += Config_t::ARITHMATIC_FLAG;
    if (-keyedData == VKey_t::MAXIMUM) { cfg += Config_t::MAXIMUM_FLAG; }
    if (-keyedData == VKey_t::MAXIMUM) { cfg += Config_t::MAXIMUM_FLAG; }
    if (-keyedData != VKey_t::MAXIMUM && -keyedData != VKey_t::MINIMUM) { cfg += Config_t::MAXIMUM_FLAG; }
}