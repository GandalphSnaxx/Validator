#pragma once
/**
 * @file src/keyed_list_t.hpp
 * @author Ray Richter
 * @brief VKeyedList_t Class declaration. 
 */
#include <flagfield.hpp>
#include "Validator_core.hpp"
#include "keyed_data_t.hpp"
#include "key_t.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// TODO: Should this support containing multiple data types?

/// @brief Keyed list config flag indicies
enum KLFlags : uint_t {
    INIT_FLAG,          // List initalized flag
    BLACKLIST_FLAG,     // List contains only BLACKLIST keys
    WHITELIST_FLAG,     // List contains only WHITELIST, PERFECT, or score keys
    ARITHMETIC_FLAG,    // List contains an arithmetic data type
    COMPARABLE_FLAG,    // List contains a comparable data type
    PERFECT_FLAG,       // List contains a PERFECT key
    MAXIMUM_FLAG,       // List contains a MAXIMUM key
    MINIMUM_FLAG,       // List contains a MINIMUM key
    MAX_FLAGS};         // Maximum number of flags

/// @brief A class containing a list of keyed data and functions for managing this list. Range data should be stored in a 
/// separate range list. 
/// @tparam Data_t Data type of the keyed data
/// @note Default key = `VKey_t::WHITELIST`
template<class Data_t> class VKeyedList_t {
    public:
    /// @brief Constructor from a constant key and a list of data.
    /// @param key Constant key as `VKey_t`
    /// @param list List of data as `std::vector<Data_t>`
    VKeyedList_t (const VKey_t &key, const std::vector<Data_t> &list) {
        V_DEBUG_MSG("Called VKeyedList_t key and list constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(key, list);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Constructor from a raw list of keyed data.
    /// @param kl A list of keyed data as `std::vector<VKeyedData_t<Data_t>>`.
    VKeyedList_t (const std::vector<VKeyedData_t<Data_t>> &rawList) {
        V_DEBUG_MSG("Called VKeyedList_t raw keyed data list constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(rawList);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Constructor from keyed data.
    /// @param kd Keyed data as `VKeyedData_t<Data_t>`.
    VKeyedList_t (const VKeyedData_t<Data_t> &kd) {
        V_DEBUG_MSG("Called VKeyedList_t keyed data constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(kd);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Constructor from another `VKeyedList_t<Data_t>`.
    /// @param kl Another keyed list as `VKeyedList_t<Data_t>`.
    VKeyedList_t (const VKeyedList_t<Data_t> &kl) {
        V_DEBUG_MSG("Called VKeyedList_t copy constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(kl);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Constructor from a list of data given the dafault key.
    /// @param list A list of data as `std::vector<Data_t>`.
    VKeyedList_t (const std::vector<Data_t> &list) {
        V_DEBUG_MSG("Called VKeyedList_t default list constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(list);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Constructor from a key and data.
    /// @param key A key for the data as `VKey_t`.
    /// @param data Data to add to the keyed list as `Data_t`.
    VKeyedList_t (const VKey_t &key, const Data_t &data) {
        V_DEBUG_MSG("Called VKeyedList_t default key and data constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(key, data);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Constructor from data given the default key.
    /// @param data Data to add as `Data_t`
    VKeyedList_t (const Data_t &data) {
        V_DEBUG_MSG("Called VKeyedList_t default data constructor with type: " << typeid(Data_t).name());
        _init();
        uint_t numFail = add(data);
        if (numFail != 0) { V_DEBUG_MSG("WARNING: Failed to add " << numFail << " element(s)!"); }
        else { V_DEBUG_MSG("Success!"); }}

    /// @brief Default constructor.
    VKeyedList_t () {
        V_DEBUG_MSG("Called VKeyedList_t default constructor with type: " << typeid(Data_t).name());
        _init(); V_DEBUG_MSG("Success!"); }

    /// @brief Deconstructor
    ~VKeyedList_t() {
        V_DEBUG_MSG("Called VKeyedList_t deconstructor with type: " << typeid(Data_t).name()); }

    /// @brief Adds a list of data with the same key to the keyed list
    /// @param  key as `VKey_t`
    /// @param  list as `std::vector<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKey_t &key, const std::vector<Data_t> &list) {
        uint_t failCount = 0;
        for (const auto &data : list) { failCount += _add({key, data}); }
        return failCount; }

    /// @brief Adds a raw list of keyed data to the keyed list
    /// @param rawList as `std::vector<VKeyedData_t<Data_t>>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const std::vector<VKeyedData_t<Data_t>> &rawList) {
        uint_t failCount = 0;
        for (const auto &kd : rawList) { failCount += _add(kd); }
        return failCount; }

    /// @brief Adds a list of keyed data to the keyed list.
    /// @param  keyedList as `VKeyedList_t<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKeyedList_t<Data_t> &kl) {
        uint_t failCount = 0;
        for (const auto &kd : kl.list) { failCount += _add(kd); }
        return failCount; }
    
    /// @brief Adds keyed data to the keyed list.
    /// @param  keyedData as `VKeyedData_t<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKeyedData_t<Data_t> &kd) { return _add(kd); }

    /// @brief Adds a list of data to the keyed list with a default key.
    /// @param list as `std::vector<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const std::vector<Data_t> &list) {
        uint_t failCount = 0;
        for (const auto &data : list) { failCount += _add({VKey_t::WHITELIST, data}); }
        return failCount; }

    /// @brief Adds keyed data to the list.
    /// @param  key as `VKey_t`
    /// @param  data as `Data_t`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKey_t &key, const Data_t &data) { return _add({key, data}); }

    /// @brief Adds data to the keyed list with a default key.
    /// @param  data as `Data_t`
    /// @return Number of add fails as `uint_t`
    uint_t add(const Data_t &data) { return _add({VKey_t::WHITELIST, data}); }

    /// @brief Queries data to get a score or key.
    /// @param qData The queried data as `Data_t`
    /// @return `VReturn_t`
    VReturn_t query(const Data_t &qData) const {
        // If not initalized, return FAIL
        if (!config_(INIT_FLAG)) return VReturn_t::FAIL;
        // Find qData in internal list. If found, cast to VReturn_t and return
        for (const auto &kd : list_) { if (kd(qData) != VKey_t::NULL_KEY) return -kd; }
    
        // If qData was not found in the list:
        //  If blacklist mode, return PASS
        if (config_(BLACKLIST_FLAG )) return VReturn_t::PASS;
        //  If whitelist mode, return FAIL
        if (config_(WHITELIST_FLAG )) return VReturn_t::FAIL;
        /// TODO: If arethmetic, get value based score
        if (config_(ARITHMETIC_FLAG)) return VReturn_t::FAIL;
        /// TODO: If comparable, check ranges
        if (config_(COMPARABLE_FLAG)) return VReturn_t::FAIL;
    
        // All pass conditions failed:
        return VReturn_t::FAIL;
    }

    /// @brief Gets the size of the list.
    size_t size() const { return list_.size(); }

    /// @section Operator Overrides

    /// @brief Operator overload to query data.
    VReturn_t operator()(const Data_t &qData) const { return query(qData); }
    /// @brief Operator overload to get a pointer to keyed data.
    VKeyedData_t<Data_t>* operator[](const size_t &index) const { if (index >= size()) { return nullptr; } return &list_[index]; }

    /// @brief Adds data to the list. 
    VKeyedList_t& operator+=(const std::vector<VKeyedData_t<Data_t>> &rhs) { add(rhs); return *this; }
    /// @brief Adds data to the list. 
    VKeyedList_t& operator+=(const VKeyedList_t<Data_t> &rhs) { add(rhs); return *this; }
    /// @brief Adds data to the list. 
    VKeyedList_t& operator+=(const VKeyedData_t<Data_t> &rhs) { add(rhs); return *this; }
    /// @brief Adds data to the list with WHITELIST key.
    VKeyedList_t& operator+=(const std::vector<Data_t> &rhs) { add(VKey_t::WHITELIST, rhs); return *this; }
    /// @brief Adds data to the list with WHITELIST key.
    VKeyedList_t& operator+=(const Data_t &rhs) { add(VKey_t::WHITELIST, rhs); return *this; }
    
    /// @brief Adds data to the list with BLACKLIST key.
    VKeyedList_t& operator-=(const std::vector<Data_t> &rhs) { add(VKey_t::BLACKLIST, rhs); return *this; }
    /// @brief Adds data to the list with BLACKLIST key.
    VKeyedList_t& operator-=(const Data_t &rhs) { add(VKey_t::BLACKLIST, rhs); return *this; }

    // MyClass& MyClass::operator=(const MyClass &rhs) {
    //     // Only do assignment if RHS is a different object from this.
    //     if (this != &rhs) {
    //       ... // Deallocate, allocate new space, copy values...
    //     }
    //     return *this;
    // }

    friend std::ostream& operator<< (std::ostream&, const VKeyedList_t<Data_t>&);
    friend std::ostream& operator<<=(std::ostream&, const VKeyedList_t<Data_t>&);

    /// @section Private Members
    private:
    std::vector<VKeyedData_t<Data_t>> list_{};
    FlagField<MAX_FLAGS> config_;

    /// @brief Initalizes the internal config based on `Data_t`'s capabilities.
    void _init() {
        // Setup config
        config_  = INIT_FLAG;
        config_ += BLACKLIST_FLAG;
        config_ += WHITELIST_FLAG;
        config_.setFlagIf(ARITHMETIC_FLAG, (type_flags<Data_t> & ARITHMATIC_OP) != 0);
        config_.setFlagIf(COMPARABLE_FLAG, (type_flags<Data_t> & COMPARISON_OP) != 0);
    }

    /// @brief Adds keyed data to the internal list and updates config.
    /// @param kd Keyed data as `VKeyedData_t<Data_t>`.
    /// @return `true` if data could not be added.
    bool _add(const VKeyedData_t<Data_t> &kd) {
        V_DEBUG_NO_ENDL("\t_add: " <<= kd); V_DEBUG_ENDL;
        /// TODO: Make sure key checks are working
        // Update config
        if (-kd != VKey_t::BLACKLIST) { config_ -= BLACKLIST_FLAG; }
        if (-kd == VKey_t::BLACKLIST) { config_ -= WHITELIST_FLAG; }
        // Range data is not stored here. Yet?
        if (-kd == VKey_t::MAXIMUM)   { 
            config_ -= WHITELIST_FLAG; 
            config_ += MAXIMUM_FLAG;
            return true; }
        if (-kd == VKey_t::MINIMUM)   { 
            config_ -= WHITELIST_FLAG; 
            config_ += MINIMUM_FLAG;
            return true; }
        if (-kd == VKey_t::PERFECT)   { config_ += PERFECT_FLAG; }
    
        // Add keyed data to the list
        list_.push_back(kd);
        return false;
    }
};

/// @brief Adds `VKeyedList_t` info to an Out Stream
template <class Data_t> 
std::ostream& operator<< (std::ostream &os, const VKeyedList_t<Data_t> &kl) {
    os << "[";
    for (const auto &kd : kl.list_) { os << kd; os << ", "; }
    return os << "\b\b]";
}

/// @brief Adds detailed `VKeyedList_t` info to an Out Stream
template <class Data_t> 
std::ostream& operator<<=(std::ostream &os, const VKeyedList_t<Data_t> &kl) {
    os << "{Keyed List: {";
    os << "Config: {";
    os << (kl.config(INIT_FLAG      ) ? " Initalized" : "!Initalized") << ", ";
    os << (kl.config(BLACKLIST_FLAG ) ? " Blacklist"  : "!Blacklist" ) << ", ";
    os << (kl.config(WHITELIST_FLAG ) ? " Whitelist"  : "!Whitelist" ) << ", ";
    os << (kl.config(ARITHMETIC_FLAG) ? " Arithmetic" : "!Arithmetic") << ", ";
    os << (kl.config(COMPARABLE_FLAG) ? " Comparable" : "!Comparable") << ", ";
    os << (kl.config(PERFECT_FLAG   ) ? " Perfect"    : "!Perfect"   ) << ", ";
    os << (kl.config(MAXIMUM_FLAG   ) ? " Maximum"    : "!Maximum"   ) << ", ";
    os << (kl.config(MINIMUM_FLAG   ) ? " Minimum"    : "!Minimum"   );
    os << "}, Data: [";
    for (const auto &kd : kl.list_) { os <<= kd; os << ", "; }
    return os << "\b\b], Size: " << kl.size() << "}";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////