#pragma once
/**
 * @file src/key_t.hpp
 * @author Ray Richter
 * @brief VKey_t Class declaration. 
 */
#include "Validator_core.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief A class for storing and labeling validation data. 
/// @note Default key = `VKey_t::NULL_KEY`
class VKey_t {
    public:
    /// @brief Special value labels
    enum : uint_t {
        WHITELIST   = 0,              // Data is marked as whitelisted
    //  [1, 2, 3...]                  // Data is marked with a score value
        MINIMUM     = V_UINT_MAX - 4, // Data is marked as a minimum
        MAXIMUM     = V_UINT_MAX - 3, // Data is marked as a maximum
        PERFECT     = V_UINT_MAX - 2, // Data is marked as perfect
        BLACKLIST   = V_UINT_MAX - 1, // Data is marked as blacklisted
        NULL_KEY    = V_UINT_MAX   }; // Data is marked as NULL

    /// @section Constructors

    VKey_t(const VKey_t &key) : score(    -key) {} // Constructor from VKey_t
    VKey_t(const uint_t &key) : score(     key) {} // Constructor from uint
    VKey_t()                  : score(NULL_KEY) {} // Default constructor

    /// @section Comparison Operator Overloads

    /// @brief Key equality check.
    bool operator==(const VKey_t &rhs) const { return score == -rhs; }
    /// @brief Key inequality check.
    bool operator!=(const VKey_t &rhs) const { return score != -rhs; }
    /// @brief Key comparison. `NULL_KEY` == -1
    bool operator< (const VKey_t &rhs) const { if (!(*this) || !rhs) { return score > -rhs; } return score < -rhs; }
    /// @brief Key comparison. `NULL_KEY` == -1
    bool operator> (const VKey_t &rhs) const { return   rhs < *this ; }
    /// @brief Key comparison. `NULL_KEY` == -1
    bool operator<=(const VKey_t &rhs) const { return !(rhs > *this); }
    /// @brief Key comparison. `NULL_KEY` == -1
    bool operator>=(const VKey_t &rhs) const { return !(rhs < *this); }
    /// @brief Key == NULL_KEY check
    bool operator! () const { return score == NULL_KEY; }

    /// @section Score Retrieval Operator Overloads

    /// @brief Gets score as `uint_t`
    const uint_t operator()() const { return score; }
    /// @brief Gets score as `uint_t`
    const uint_t operator- () const { return score; }
    /// @brief Gets score as `uint_t`
    const uint_t getScore  () const { return score; }
    
    private:
    uint_t score;
};

/// @section COUT Functions

/// @brief Adds `VKey_t` info to an Out Stream
/// @note Example outputs: `WHITELIST`, `10`, or `NULL_KEY`
inline std::ostream& operator<< (std::ostream &os, const VKey_t &key) {
    if      (key == VKey_t::WHITELIST) { os << "WHITELIST"; }
    else if (key == VKey_t::BLACKLIST) { os << "BLACKLIST"; }
    else if (key == VKey_t::MAXIMUM  ) { os << "MAXIMUM"  ; }
    else if (key == VKey_t::MINIMUM  ) { os << "MINIMUM"  ; }
    else if (key == VKey_t::PERFECT  ) { os << "PERFECT"  ; }
    else if (key == VKey_t::NULL_KEY ) { os << "NULL_KEY" ; }
    else    { os << -key; } return os; }

/// @brief Adds detailed `VKey_t` info to an Out Stream
/// @note Example output: `{Key value: 0, Tag: WHITELIST}`
inline std::ostream& operator<<=(std::ostream &os, const VKey_t &key) {
    os << "{Key value: " << -key << ", Tag: ";
    if      (key == VKey_t::WHITELIST) { os << "WHITELIST"; }
    else if (key == VKey_t::BLACKLIST) { os << "BLACKLIST"; }
    else if (key == VKey_t::MAXIMUM  ) { os << "MAXIMUM"  ; }
    else if (key == VKey_t::MINIMUM  ) { os << "MINIMUM"  ; }
    else if (key == VKey_t::PERFECT  ) { os << "PERFECT"  ; }
    else if (key == VKey_t::NULL_KEY ) { os << "NULL_KEY" ; }
    else    { os << "score"; } return os << "}"; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////