#pragma once
/**
 * @file src/return_t.hpp
 * @author Ray Richter
 * @brief VReturn_t Class declaration. 
 */
#include "Validator_core.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief A class of enums, operators, and one variable for labeling, handling, and storing Validator return data
class VReturn_t {
    public:
    enum : uint_t {               // Enumeration labels for return values
        PASS    = 0,              // Pass label
    //  scores  = [1, 2, 3, 4..], // Score points
        PERFECT = V_UINT_MAX - 1, // Perfect label
        FAIL    = V_UINT_MAX   }; // Fail label

    /// @brief Constructor from uint
    VReturn_t(const uint_t&);
    /// @brief Constructor from another `VReturn_t`.
    VReturn_t(const VReturn_t&);
    /// @brief Default constructor. Initalizes to `PASS` aka `0`.
    VReturn_t();

    /// @subsection Conversion Overloads

    /// @brief Explicit conversion operator to uint
    explicit operator uint_t() const { return score; }
    /// @brief Explicit conversion operator to bool. Returns `true` if `score` is not `FAIL`.
    explicit operator   bool() const { return score != FAIL; }

    /// @subsection Unary Prefix Operator Overloads for Special Value Checks

//  ret | op        | const | ret | funcName   | const | return calculation

    /// @brief Checks if `score` is `FAIL`.
    bool operator! () const ; bool  isFAIL    () const { return  !(*this); }
    /// @brief Checks if `score` is `PASS`.
    bool operator+ () const ; bool  isPASS    () const { return  +(*this); }
    /// @brief Checks if `score` is `PERFECT`.
    bool operator* () const ; bool  isPERFECT () const { return  *(*this); }
    /// @brief Checks if `score` is not `FAIL`, `PASS`, or `PERFECT`.
    bool operator~ () const ; bool  isScore   () const { return  ~(*this); }
    /// @brief Checks if `score` is `FAIL`, `PASS`, or `PERFECT`.
    bool operator- () const ; bool  isNScore  () const { return  -(*this); }
    /// @brief Checks if `score` is `FAIL`, `PASS`, or `PERFECT`.
    bool operator++() const ; bool  isSpecial () const { return ++(*this); }
    /// @brief Checks if `score` is not `FAIL`, `PASS`, or `PERFECT`.
    bool operator--() const ; bool  isNSpecial() const { return --(*this); }

    /// @subsection Operator overloads

    /// @brief Assigns a value from a uint.
    VReturn_t& operator= (const uint_t&);
    /// @brief Assigns a value from another `VReturn_t`.
    VReturn_t& operator= (const VReturn_t&);
    /// @brief Adds points if `score` is not `FAIL` or `PERFECT`.
    const  VReturn_t  operator+ (const VReturn_t&) const;
    /// @brief Subtracts points if `score` is not `FAIL` or `PERFECT`.
    const  VReturn_t  operator- (const VReturn_t&) const;
    /// @brief Adds points if `score` is not `FAIL` or `PERFECT`.
    VReturn_t& operator+=(const VReturn_t&);
    /// @brief Subtracts points if `score` is not `FAIL` or `PERFECT`.
    VReturn_t& operator-=(const VReturn_t&);
    // VReturn_t& operator+=(const    VKey_t&)       ; // Add key to return
    // VReturn_t& operator-=(const    VKey_t&)       ; // Sub key from return

    /// @brief Returns `true` if `score` is equal to the other `VReturn_t` and neither is `FAIL`.
    bool operator==(const VReturn_t&) const;
    /// @brief Returns `true` if `score` is not equal to the other `VReturn_t` or either is `FAIL`.
    bool operator!=(const VReturn_t&) const;
    /// @brief Returns `true` if the left `score` is less than the right `score` or left = `FAIL`.
    bool operator< (const VReturn_t&) const;
    /// @brief Returns `true` if the left `score` is greater than the right `score` or right = `FAIL`.
    bool operator> (const VReturn_t&) const;
    /// @brief Returns `true` if the left `score` is less than or equal to the right `score` or left = `FAIL`.
    bool operator<=(const VReturn_t&) const;
    /// @brief Returns `true` if the left `score` is greater than or equal to the right `score` or right = `FAIL`.
    bool operator>=(const VReturn_t&) const;
    /// @brief Gets the score as a uint.
    const uint_t operator()() const { return score; }

    // template<class T> VReturn_t& operator+=(const VKeyedData_t<T> &rhs) { (*this) += VKey_t(rhs.first); return *this; }
    // template<class T> VReturn_t& operator-=(const VKeyedData_t<T> &rhs) { (*this) -= VKey_t(rhs.first); return *this; }

    friend std::ostream& operator<< (std::ostream&, const VReturn_t&);
    friend std::ostream& operator<<=(std::ostream&, const VReturn_t&);

    private:
    uint_t score;
};

/// @brief Adds `VReturn_t` info to an Out Stream
std::ostream& operator<< (std::ostream&, const VReturn_t&);
/// @brief Adds detailed `VReturn_t` info to an Out Stream
std::ostream& operator<<=(std::ostream&, const VReturn_t&);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////