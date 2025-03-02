#pragma once
/**
 * @file src/return_t.hpp
 * @author Ray Richter
 * @brief VReturn_t Class declaration. 
 */
#include "Validator_core.hpp"
// #include "key_t.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief A class of enums, operators, and one variable for labeling, handling, and storing Validator return data
class VReturn_t {
    public:
    enum : uint_t {              // Enumeration labels for return values
        PASS    = 0,              // Pass label
    //  scores  = [1, 2, 3...],   // Score points
        PERFECT = V_UINT_MAX - 1, // Perfect label
        FAIL    = V_UINT_MAX   }; // Fail label

    VReturn_t(const uint_t &val) : score(val) {} // Constructor from uint
    // VReturn_t(const VKey_t &key) ;               // Constructor from VKey_t
    VReturn_t()                  : score(  0) {} // Default constructor

    /// @subsection Conversion Overloads

    explicit operator uint_t() const { return score; }
    explicit operator   bool() const { return score != FAIL; }

    /// @subsection Unary Prefix Operator Overloads for Special Value Checks

//  ret | op        | const | ret | funcName   | const | return calculation
    bool operator! () const ; bool  isFAIL    () const { return  !(*this); }
    bool operator+ () const ; bool  isPASS    () const { return  +(*this); }
    bool operator* () const ; bool  isPERFECT () const { return  *(*this); }
    bool operator~ () const ; bool  isScore   () const { return  ~(*this); }
    bool operator- () const ; bool  isNScore  () const { return  -(*this); }
    bool operator++() const ; bool  isSpecial () const { return ++(*this); }
    bool operator--() const ; bool  isNSpecial() const { return --(*this); }

    /// @subsection Operator overloads
//  const | return_t | op       | rhs            | const | Description or return calculation
           VReturn_t& operator= (const    uint_t&)       ; // Assigns a value
           VReturn_t& operator= (const VReturn_t&)       ; // Assigns a value
    const  VReturn_t  operator+ (const VReturn_t&) const ; // Adds points if score != FAIL or PERFECT
    const  VReturn_t  operator- (const VReturn_t&) const ; // Subtracts points if score != FAIL or PERFECT
           VReturn_t& operator+=(const VReturn_t&)       ; // x = x + y using above op
           VReturn_t& operator-=(const VReturn_t&)       ; // x = x - y using above op
        //    VReturn_t& operator+=(const    VKey_t&)       ; // Add key to return
        //    VReturn_t& operator-=(const    VKey_t&)       ; // Sub key from return
           bool       operator==(const VReturn_t&) const ; // Equality check
           bool       operator!=(const VReturn_t&) const ; // Inequality check
           bool       operator< (const VReturn_t&) const ; // Comparison check
           bool       operator> (const VReturn_t&) const ; // Comparison
           bool       operator<=(const VReturn_t&) const ; // Comparison
           bool       operator>=(const VReturn_t&) const ; // Comparison
    const  uint_t     operator()() const { return score; } // Cast to uint

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