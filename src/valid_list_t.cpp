// #include "Validator_core.hpp"
// /**
//  * @file src/valid_list_t.cpp
//  * @author Ray Richter
//  * @brief Function definitions for ValidList_t class. 
//  */
// using namespace Validspace;

// /// @section Constructors

// template <class Data_t> ValidList_t<Data_t>::ValidList_t() {
//     static_assert(std::is_arithmetic<Data_t>::value, "ValidList_t requires an arithmetic type for Data_t");
//     DEBUG_MSG("Called ValidList_t default constructor with type: " << typeid(Data_t).name());
//     // Setup config based on Data_t
//     _config  =  Config_t::INITALIZED_FLAG;
//     _config +=  Config_t:: BLACKLIST_FLAG;
//     _config.setIf(Config_t::ARITHMATIC_FLAG, std::is_arithmetic<Data_t>::value);
//     // _config += (Config_t::ARITHMATIC_FLAG * std::is_arithmetic<Data_t>::value);
//     DEBUG_MSG("Initalized with config: " << _config);
// }

// template <class Data_t> ValidList_t<Data_t>::~ValidList_t() {
//     DEBUG_MSG("Called ValidList_t deconstructor with type: " << typeid(Data_t).name());
// }

// /// @section External Add Functions

// /// @brief Adds a list with the same key to the Validator
// /// @tparam Data_t Data type of the Validator
// /// @param key Data key as `VKey_t`
// /// @param list List of valid data as `VList_t<Data_t>`
// template <class Data_t> void ValidList_t<Data_t>::add(const VKey_t &key, const VList_t<Data_t> &list) {
//     for (const auto &data : list) {
//         _addkd({key, data});
//     }
// }

// /// @brief Adds keyed data to a Validator
// /// @tparam Data_t Data type of the Validator
// /// @param key Data key as `VKey_t`
// /// @param data Data as `Data_t`
// template <class Data_t> void ValidList_t<Data_t>::add(const VKey_t &key, const Data_t &data) {
//     _addkd({key, data});
// }

// /// @brief Adds a list of keyed data to a Validator
// /// @tparam Data_t Data type of the Validator
// /// @param keyedList A keyed list of data as `VKeyedList_t<Data_t>`
// template <class Data_t> void ValidList_t<Data_t>::add(const VKeyedList_t<Data_t> &keyedList) {
//     for (const auto &keyedData : keyedList) {
//         _addkd(keyedData);
//     }
// }

// /// @brief Adds keyed data to a Validator
// /// @tparam Data_t Data type of the Validator
// /// @param keyedData Keyed data as `VKeyedData_t<Data_t>`
// template <class Data_t> void ValidList_t<Data_t>::add(const VKeyedData_t<Data_t> &keyedData) {
//     _addkd(keyedData);
// }

// /// @brief Adds a list of data ranges to a Validator
// /// @tparam Data_t Data type of the Validator
// /// @param rangeList A list of ranges as `VRangeList_t<Data_t>`
// template <class Data_t> void ValidList_t<Data_t>::add(const VRangeList_t<Data_t> &rangeList) {
//     for (const auto &range : rangeList) {
//         /// TODO: Add range
//         // _addRange(range);
//     }
// }

// /// @brief Adds a data range to a Validator
// /// @tparam Data_t Data type of the Validator
// /// @param range A range as `VRange_t<Data_t>`
// template <class Data_t> void ValidList_t<Data_t>::add(const VRange_t<Data_t> &range) {
//     _addrg(range);
// }

// /// @brief Adds a list of values to a Validator as `WHITELIST`
// /// @tparam Data_t Data type of the Validator
// /// @param list A list of whitelisted data
// template <class Data_t> void ValidList_t<Data_t>::add(const VList_t<Data_t> &list) {
//     for (const auto &data : list) {
//         _addkd({VKey_t::WHITELIST, data});
//     }
// }

// /// @brief Adds data to a Validator as `WHITELIST`
// /// @tparam Data_t Data type of the Validator
// /// @param data Data to add to a whitelist
// template <class Data_t> void ValidList_t<Data_t>::add(const Data_t &data) {
//     _addkd({VKey_t::WHITELIST, data});
// }

// /// @section Validate Function

// /// @brief Queries the validity of queried data. 
// /// @tparam Data_t Data type of the Validator and queried data.
// /// @param qData Queried data to be validated and/or scored.
// /// @return `VReturn_t` as PASS, FAIL, PERFECT, or score. 
// template <class Data_t> VReturn_t ValidList_t<Data_t>::validate(const Data_t &qData) const {
//     // If the list is empty, pass everything
//     if (_keyedList.size() == 0) { return VReturn_t::PASS; }

//     // Initalize a score as 0 and dataFound as false
//     VReturn_t score = 0;
//     bool dataFound = false;

//     // Iterate through the internal list...
//     for (const VKeyedData_t<Data_t> &listData : _keyedList) {
//         // If qData is found...
//         if (qData == listData.second) {
//             dataFound = true;
//             // Adding VKeyedData_t to VReturn_t does not pass if either is a special value
//             score += listData;
//         }
//     }

//     // No data found section
//     if (!dataFound) {
//         // If Validator is in blacklist mode, return PASS
//         if (_config && Config_t:: BLACKLIST_FLAG) { return    VReturn_t::PASS; }
//         // If Validator is in arithmatic mode, return value based score
//         if (_config && Config_t::ARITHMATIC_FLAG) { return _valueScore(qData); }
//         // No data found, not BLACKLIST, not ARITHMATIC
//         return VReturn_t::FAIL;
//     }

//     // Data found in list
//     return score;
// }

// /// @section Internal Functions

// template <class Data_t> void ValidList_t<Data_t>::_addData(const VKeyedData_t<Data_t> &keyedData) {
//     // Update config depending on the key
//     if (keyedData != VKey_t::BLACKLIST) { _config -= Config_t::BLACKLIST_FLAG; }
//     if (keyedData == VKey_t::  PERFECT) { _config += Config_t::  PERFECT_FLAG; }
//     if (keyedData == VKey_t::  MINIMUM) { _config += Config_t::  MINIMUM_FLAG;
//         /// TODO: Handle minimum
//     }
//     if (keyedData == VKey_t::  MAXIMUM) { _config += Config_t::  MAXIMUM_FLAG;
//         /// TODO: Handle maximum
//     }

//     _keyedList.insert(keyedData);
// }

// template <class Data_t> void ValidList_t<Data_t>::_add2(const VKey_t &key, const VList_t<Data_t> &list) {
//     for (const auto &data : list) {
//         _addData({key, data});
//     }
// }

// template <class Data_t> void ValidList_t<Data_t>::_add2(const VKey_t &key, const Data_t &data) {
//     _addData({key, data});
// }

// template <class Data_t> void ValidList_t<Data_t>::_addkl(const VKeyedList_t<Data_t> &list) {
//     for (const auto &data : list) {
//         _addData(data);
//     }
// }

// template <class Data_t> void ValidList_t<Data_t>::_addkd(const VKeyedData_t<Data_t> &data) {
//     _addData(data);
// }

// /// TODO: Add Ranges
// template <class Data_t> void ValidList_t<Data_t>::_addrg(const VRange_t<Data_t> &range) {}
// template <class Data_t> void ValidList_t<Data_t>::_addrl(const VRangeList_t<Data_t> &list) {}

// template <class Data_t> VReturn_t ValidList_t<Data_t>::_valueScore(const Data_t &qData) {
//     /// TODO: Calculate value based score
//     return VReturn_t::FAIL;
// }