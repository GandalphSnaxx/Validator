#include "headers/keyed_list_t.hpp"
/**
 * @file src/keyed_list_t.cpp
 * @author Ray Richter
 * @brief VRange_t definitions
 */

using namespace Validspace;

/// @section Constructors

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const VKey_t &key, const std::vector<Data_t> &list) {
    DEBUG_MSG("Called VKeyedList_t key and list constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(key, list);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const std::vector<VKeyedData_t<Data_t>> &rawList) {
    DEBUG_MSG("Called VKeyedList_t raw keyed list constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(rawList);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const VKeyedData_t<Data_t> &kd) {
    DEBUG_MSG("Called VKeyedList_t keyed data constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(kd);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const VKeyedList_t<Data_t> &kl) {
    DEBUG_MSG("Called VKeyedList_t keyed list constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(kl);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const std::vector<Data_t> &list) {
    DEBUG_MSG("Called VKeyedList_t default list constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(list);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const VKey_t &key, const Data_t &data) {
    DEBUG_MSG("Called VKeyedList_t key and data constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(key, data);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
(const Data_t &data) {
    DEBUG_MSG("Called VKeyedList_t default data constructor with type: " << typeid(Data_t).name());
    _init();
    uint_t numFail = add(data);
    if (numFail != 0) { DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
    else { DEBUG_MSG("Success!"); }
}

template <class Data_t> 
VKeyedList_t<Data_t>::VKeyedList_t
() {
    DEBUG_MSG("Called VKeyedList_t default constructor with type: " << typeid(Data_t).name());
    _init();
}

template <class Data_t> 
VKeyedList_t<Data_t>::~VKeyedList_t
() {
    DEBUG_MSG("Called VKeyedList_t deconstructor with type: " << typeid(Data_t).name());
    // delete(list);
}

/// @section External Functions

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const VKey_t &key, const std::vector<Data_t> &list) {
    uint_t failCount = 0;
    for (const auto &data : list) { failCount += _add({key, data}); }
    return failCount;
}

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const std::vector<VKeyedData_t<Data_t>> &kl) {
    uint_t failCount = 0;
    for (const auto &kd : kl) { failCount += _add(kd); }
    return failCount;
}

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const VKeyedList_t<Data_t> &keyedList) {
    uint_t failCount = 0;
    for (const auto &keyedData : keyedList) { failCount += _add(keyedData); }
    return failCount;
}

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const VKeyedData_t<Data_t> &keyedData) {
    return _add(keyedData);
}

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const std::vector<Data_t> &list) {
    uint_t failCount = 0;
    for (const auto &data : list) { failCount += _add({VKey_t::WHITELIST, data}); }
    return failCount;
}

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const VKey_t &key, const Data_t &data) {
    return _add({key, data});
}

template <class Data_t> 
uint_t VKeyedList_t<Data_t>::add
(const Data_t &data) {
    return _add({VKey_t::WHITELIST, data});
}

// template<typename T1, typename T2>
// auto Plus(T1&& t1, T2&& t2) ->
//    decltype(forward<T1>(t1) + forward<T2>(t2))
// {
//    return forward<T1>(t1) + forward<T2>(t2);
// }


/// @section Operator Overloads



/// @section Internal Functions

template <class Data_t> void VKeyedList_t<Data_t>::_init() {
    // Setup config
    config  =    Config_t::INITALIZED_FLAG;
    config +=    Config_t:: BLACKLIST_FLAG;
    config.setIf(Config_t::ARITHMATIC_FLAG, std::is_arithmetic<Data_t>::value);
}

template <class Data_t> bool VKeyedList_t<Data_t>::_add(const VKeyedData_t<Data_t> &kd) {
    // Returns TRUE if the data add failed

    /// TODO: Make sure key checks are working
    // Update config
    if (kd != VKey_t::BLACKLIST) { config -= Config_t::BLACKLIST_FLAG; }
    // Range data is not stored here
    if (kd == VKey_t::MAXIMUM)   { return true; }
    if (kd == VKey_t::MINIMUM)   { return true; }
    if (kd == VKey_t::PERFECT)   { config += Config_t::PERFECT_FLAG; }

    // Add keyed data to the list
    list.push_back(kd);
    return false;
}