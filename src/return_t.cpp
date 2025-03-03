#include "headers/return_t.hpp"
/**
 * @file return_t.cpp
 * @author Ray Richter
 * @brief Function definitions for VReturn_t.
 * @note If any operation involves a PERFECT or FAIL value, return PERFECT or FAIL. If both PERFECT and FAIL are involved, return FAIL. 
 * Maybe PERFECT should be returned?
 * 
 * Special Value Check Operators: !return = true | false;
 * Table:
 * Op | Special Value | Description
 * !  | FAIL          | Returns true if score = FAIL
 * +  | PASS          | Returns true if score = PASS
 * *  | PERFECT       | Returns true if score = PERFECT
 * ~  | PASS or score | Returns true if score != PERFECT or FAIL
 * -  | PERFECT | FAIL| Returns true if score == PERFECT or FAIL
 * ++ | any           | Returns true if score == any special value
 * -- | score         | Returns true if score != any special value
 */

using namespace Validspace;

/// @section Unary Operator Overrides

/// @brief Is VReturn_t == FAIL
bool VReturn_t::operator! () const { return score == FAIL;    }
/// @brief Is VReturn_t == PASS
bool VReturn_t::operator+ () const { return score == PASS;    }
/// @brief Is VReturn_t == PERFECT
bool VReturn_t::operator* () const { return score == PERFECT; }
/// @brief Is VReturn_t a special value
bool VReturn_t::operator~ () const { return  (score == FAIL || score == PERFECT); }
/// @brief Is VReturn_t not a special value
bool VReturn_t::operator- () const { return !(score == FAIL || score == PERFECT); }
/// @brief Is VReturn_t a special value
bool VReturn_t::operator++() const { return  (score == FAIL || score == PASS || score == PERFECT); }
/// @brief Is VReturn_t not a special value
bool VReturn_t::operator--() const { return !(score == FAIL || score == PASS || score == PERFECT); }

/// @section Assignment Operator Overloads

/// @brief Assigns a score to `VReturn_t`
VReturn_t& VReturn_t::operator= (const    uint_t &rhs) { score = rhs; return *this; }
/// @brief Assigns a score to `VReturn_t`
VReturn_t& VReturn_t::operator= (const VReturn_t &rhs) { 
    if (this == &rhs)  { return *this; }
    score =  rhs.score;  return *this; }

/// @section Arithmatic Operator Overloads
/// @note FAIL always returns FAIL, PERFECT returns PERFECT if neither is FAIL. 

/// @brief Creates a new VReturn_t with the combined scores, FAIL, or PERFECT
const VReturn_t VReturn_t::operator+(const VReturn_t &rhs) const {
    if (!(*this) || !rhs) { return VReturn_t(   FAIL); }
    if (*(*this) || *rhs) { return VReturn_t(PERFECT); }
    return               VReturn_t(score + rhs.score); }
/// @brief Creates a new VReturn_t with the subtracted scores, FAIL, or PERFECT
const VReturn_t VReturn_t::operator-(const VReturn_t &rhs) const {
    if (!(*this) || !rhs) { return VReturn_t(   FAIL); }
    if (*(*this) || *rhs) { return VReturn_t(PERFECT); }
    return               VReturn_t(score - rhs.score); }
/// @brief Adds the right score to this score or sets this score to FAIL or PERFECT
VReturn_t& VReturn_t::operator+=(const VReturn_t &rhs) { 
    if (!rhs) { score  =        FAIL; return *this; }
    if (~(*this))                   { return *this; }
    if (*rhs) { score  =     PERFECT; return *this; }
                score +=   rhs.score; return *this; }
/// @brief Subtracts the right score from this score or sets this score to FAIL or PERFECT
VReturn_t& VReturn_t::operator-=(const VReturn_t &rhs) { 
    if (!rhs) { score  =        FAIL; return *this; }
    if (~(*this))                   { return *this; }
    if (*rhs) { score  =     PERFECT; return *this; }
                score -=   rhs.score; return *this; }

/// @section Boolean Operator Overloads

/// @brief Equality check. If either value == FAIL, return false. Then if either value == PERFECT, return true. Then if both 
/// have the same score, return true. Otherwise return false.
bool VReturn_t::operator==(const VReturn_t &rhs) const {
    if (!(*this) || !rhs)           { return false; } // Either == FAIL
    if (*(*this) || *rhs)           { return  true; } // Either == PERFECT
    return score == rhs.score;                      }
/// @brief Inequality check
bool VReturn_t::operator!=(const VReturn_t &rhs) const {
    return !(*this == rhs); }
/// @brief Comparison check. Treat FAIL as -1, and PERFECT as infinity
bool VReturn_t::operator< (const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return !(*this); } // Either == FAIL, return (LHS == FAIL)
    return score <  rhs.score;                      }
/// @brief Comparison check. Treat FAIL as -1, and PERFECT as infinity
bool VReturn_t::operator> (const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return     !rhs; } // Either == FAIL, return (RHS == FAIL)
    return score >  rhs.score;                      }
/// @brief Comparison check. Treat FAIL as -1, and PERFECT as infinity
bool VReturn_t::operator<=(const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return !(*this); } // Either == FAIL, return (LHS == FAIL)
    return score <= rhs.score;                      }
/// @brief Comparison check. Treat FAIL as -1, and PERFECT as infinity
bool VReturn_t::operator>=(const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return     !rhs; } // Either == FAIL, return (RHS == FAIL)
    return score >= rhs.score;                      }

/// @brief Adds `VReturn_t` info to an Out Stream
std::ostream& Validspace::operator<< (std::ostream &os, const VReturn_t &ret) {
    if      (ret() == VReturn_t::PASS     ) { os << "PASS";      }
    else if (ret() == VReturn_t::FAIL     ) { os << "FAIL";      }
    else if (ret() == VReturn_t::PERFECT  ) { os << "PERFECT";   }
    else    { os << ret(); } return os; }
    
/// @brief Adds detailed `VReturn_t` info to an Out Stream
std::ostream& Validspace::operator<<=(std::ostream &os, const VReturn_t &ret) {
    os << "{Return value: " << ret() << ", Tag: ";
    if      (ret() == VReturn_t::PASS     ) { os << "PASS";      }
    else if (ret() == VReturn_t::FAIL     ) { os << "FAIL";      }
    else if (ret() == VReturn_t::PERFECT  ) { os << "PERFECT";   }
    else    { os << "score"; } return os << "}"; }