#pragma once
/**
 * @file src/keyed_list_t.hpp
 * @author Ray Richter
 * @brief VKeyedList_t Class declaration. 
 */
#include "Validator_core.hpp"
#include "config_t.hpp"
#include "keyed_data_t.hpp"
#include "key_t.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// TODO: Should this support containing multiple data types?

/// @brief A class containing a list of keyed data and functions for managing this list. Range data should be stored in a 
/// separate range list. 
/// @tparam Data_t Data type of the keyed data
/// @note Default key = `VKey_t::WHITELIST`
template<class Data_t> class VKeyedList_t {
    public:
    /// @brief Constructor from a constant key and a list of data.
    /// @param key Constant key as `VKey_t`
    /// @param list List of data as `std::vector<Data_t>`
    VKeyedList_t (const VKey_t&, const std::vector<Data_t>&);
    /// @brief Constructor from a raw list of keyed data.
    /// @param kl A list of keyed data as `std::vector<VKeyedData_t<Data_t>>`.
    VKeyedList_t (const std::vector<VKeyedData_t<Data_t>>&);
    /// @brief Constructor from keyed data.
    /// @param kd Keyed data as `VKeyedData_t<Data_t>`.
    VKeyedList_t (const VKeyedData_t<Data_t>&);
    /// @brief Constructor from another `VKeyedList_t<Data_t>`.
    /// @param kl Another keyed list as `VKeyedList_t<Data_t>`.
    VKeyedList_t (const VKeyedList_t<Data_t>&);
    /// @brief Constructor from a list of data given the dafault key.
    /// @param list A list of data as `std::vector<Data_t>`.
    VKeyedList_t (const std::vector<Data_t>&);
    /// @brief Constructor from a key and data.
    /// @param key A key for the data as `VKey_t`.
    /// @param data Data to add to the keyed list as `Data_t`.
    VKeyedList_t (const VKey_t&, const Data_t &);
    /// @brief Constructor from data given the default key.
    /// @param data Data to add as `Data_t`
    VKeyedList_t (const Data_t&);
    /// @brief Default constructor.
    VKeyedList_t ();
    /// @brief Deconstructor
    ~VKeyedList_t();

    /// @brief Adds a list of data with the same key to the keyed list
    /// @param  key as `VKey_t`
    /// @param  list as `std::vector<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKey_t&, const std::vector<Data_t>&);

    /// @brief Adds a raw list of keyed data to the keyed list
    /// @param rawList as `std::vector<VKeyedData_t<Data_t>>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const std::vector<VKeyedData_t<Data_t>>&);

    /// @brief Adds a list of keyed data to the keyed list.
    /// @param  keyedList as `VKeyedList_t<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKeyedList_t<Data_t>&);
    
    /// @brief Adds keyed data to the keyed list.
    /// @param  keyedData as `VKeyedData_t<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKeyedData_t<Data_t>&);

    /// @brief Adds a list of data to the keyed list with a default key.
    /// @param  list as `std::vector<Data_t>`
    /// @return Number of add fails as `uint_t`
    uint_t add(const std::vector<Data_t>&);

    /// @brief Adds keyed data to the list.
    /// @param  key as `VKey_t`
    /// @param  data as `Data_t`
    /// @return Number of add fails as `uint_t`
    uint_t add(const VKey_t&, const Data_t&);

    /// @brief Adds data to the keyed list with a default key.
    /// @param  data as `Data_t`
    /// @return Number of add fails as `uint_t`
    uint_t add(const Data_t&);

    /// @section Operator Overrides

    // MyClass& MyClass::operator=(const MyClass &rhs) {
    //     // Only do assignment if RHS is a different object from this.
    //     if (this != &rhs) {
    //       ... // Deallocate, allocate new space, copy values...
    //     }
    //     return *this;
    // }

    /// @section Private Members
    private:
    std::vector<VKeyedData_t<Data_t>> list{};
    Config_t config = Config_t::EMPTY;

    // using DefaultKey = VKey_t::WHITELIST;

    void _init(); // Internal initalize config
    bool _add(const VKeyedData_t<Data_t>&); // Internal add keyed data
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////