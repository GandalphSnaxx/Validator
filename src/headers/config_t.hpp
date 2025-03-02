#pragma once
/**
 * @file src/config_t.hpp
 * @author Ray Richter
 * @brief Config_t class declaration
 */
#include "Validator_core.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using underlying_config_t = uint8_t;

/// @brief A class for storing the configuration bytefield of a Validator
class Config_t {
    public:
    enum : underlying_config_t {
        EMPTY           = 0,
        INITALIZED_FLAG = 1 << 0,
        BLACKLIST_FLAG  = 1 << 1,
        ARITHMATIC_FLAG = 1 << 2,
        MINIMUM_FLAG    = 1 << 3,
        MAXIMUM_FLAG    = 1 << 4,
        PERFECT_FLAG    = 1 << 5,
        RANGE_FLAG      = 1 << 6,
        EX_RANGE_FLAG   = 1 << 7};

    Config_t(const   uint_t &cfg) : _cfg( cfg) {} // Constructor from uint
    Config_t(const Config_t &cfg) : _cfg(-cfg) {} // Constructor from uint
    Config_t()                    : _cfg(   0) {} // Default constructor

    // operator uint_t() const { return _cfg; }   // Allows implicit casting Config_t to uint

    operator bool() const { return _cfg != 0; }   // Allows implicit casting Config_t to bool
    const underlying_config_t operator-() const { return _cfg; } // Use ~ prefix to cast to uint
    Config_t& setIf(const Config_t &flags, const bool &b) { if (b) { _cfg |= -flags; } return *this; }

//  return   | op to    | right hand    | const |    Description
//  type     | overload | side type     | func? |

    Config_t& operator= (const Config_t&)       ; // Sets config from config
    Config_t& operator= (const   uint_t&)       ; // Sets config from uint
    bool      operator! ()                const ; // Returns true if init flag is not set
    void      operator+ ()                      ; // Sets INITALIZED_FLAG
    bool      operator&&(const Config_t&) const ; // Returns true if every qFlag is set
    bool      operator()(const Config_t&) const ; // Returns true if every qFlag is set
    bool      operator==(const Config_t&) const ; // Returns true if both have the same flags
    bool      operator!=(const Config_t&) const ; // Returns false if every qFlag is set
    Config_t& operator&=(const Config_t&)       ; // Keeps only qFlags
    Config_t& operator+=(const Config_t&)       ; // Sets flags
    Config_t  operator| (const Config_t&) const ; // Combines flags
    Config_t& operator|=(const Config_t&)       ; // Sets flags
    Config_t& operator-=(const Config_t&)       ; // Removes flags
    Config_t& operator^=(const Config_t&)       ; // Flips flags
    Config_t& operator()(const     bool&)       ; // Sets config to EMPTY if false
    Config_t& operator*=(const     bool&)       ; // Sets config to EMPTY if false
    Config_t  operator* (const     bool&) const ; // Returns a new Config_t if true, else return EMPTY

    // Config_t  setIf(const Config_t &c, const bool &b) const { return b? c : EMPTY; }

    private:
    underlying_config_t _cfg;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////