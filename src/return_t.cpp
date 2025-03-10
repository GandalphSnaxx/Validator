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

/// @section Constructors

VReturn_t::VReturn_t(const uint_t    &val) : score(val)       {}
VReturn_t::VReturn_t(const VReturn_t &ret) : score(ret.score) {}
VReturn_t::VReturn_t()                     : score(PASS)      {}

/// @section Unary Operator Overrides

bool VReturn_t::operator! () const { return score == FAIL;    }
bool VReturn_t::operator+ () const { return score == PASS;    }
bool VReturn_t::operator* () const { return score == PERFECT; }
bool VReturn_t::operator~ () const { return  (score == FAIL || score == PERFECT); }
bool VReturn_t::operator- () const { return !(score == FAIL || score == PERFECT); }
bool VReturn_t::operator++() const { return  (score == FAIL || score == PASS || score == PERFECT); }
bool VReturn_t::operator--() const { return !(score == FAIL || score == PASS || score == PERFECT); }

/// @section Assignment Operator Overloads

VReturn_t& VReturn_t::operator= (const    uint_t &rhs) { score = rhs; return *this; }
VReturn_t& VReturn_t::operator= (const VReturn_t &rhs) { 
    if (this == &rhs)  { return *this; }
    score =  rhs.score;  return *this; }

/// @section Arithmatic Operator Overloads
/// @note FAIL always returns FAIL, PERFECT returns PERFECT if neither is FAIL. 

const VReturn_t VReturn_t::operator+(const VReturn_t &rhs) const {
    if (!(*this) || !rhs) { return VReturn_t(   FAIL); }
    if (*(*this) || *rhs) { return VReturn_t(PERFECT); }
    return               VReturn_t(score + rhs.score); }

const VReturn_t VReturn_t::operator-(const VReturn_t &rhs) const {
    if (!(*this) || !rhs) { return VReturn_t(   FAIL); }
    if (*(*this) || *rhs) { return VReturn_t(PERFECT); }
    return               VReturn_t(score - rhs.score); }

VReturn_t& VReturn_t::operator+=(const VReturn_t &rhs) { 
    if (!rhs) { score  =        FAIL; return *this; }
    if (~(*this))                   { return *this; }
    if (*rhs) { score  =     PERFECT; return *this; }
                score +=   rhs.score; return *this; }

VReturn_t& VReturn_t::operator-=(const VReturn_t &rhs) { 
    if (!rhs) { score  =        FAIL; return *this; }
    if (~(*this))                   { return *this; }
    if (*rhs) { score  =     PERFECT; return *this; }
                score -=   rhs.score; return *this; }

/// @section Boolean Operator Overloads

bool VReturn_t::operator==(const VReturn_t &rhs) const {
    if (!(*this) || !rhs)           { return false; } // Either == FAIL
    if (*(*this) || *rhs)           { return  true; } // Either == PERFECT
    return score == rhs.score;                      }

bool VReturn_t::operator!=(const VReturn_t &rhs) const {
    return !(*this == rhs); }

bool VReturn_t::operator< (const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return !(*this); } // Either == FAIL, return (LHS == FAIL)
    return score <  rhs.score;                      }

bool VReturn_t::operator> (const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return     !rhs; } // Either == FAIL, return (RHS == FAIL)
    return score >  rhs.score;                      }

bool VReturn_t::operator<=(const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return !(*this); } // Either == FAIL, return (LHS == FAIL)
    return score <= rhs.score;                      }

bool VReturn_t::operator>=(const VReturn_t &rhs) const {
    if (!(*this) || !rhs)        { return     !rhs; } // Either == FAIL, return (RHS == FAIL)
    return score >= rhs.score;                      }

std::ostream& Validspace::operator<< (std::ostream &os, const VReturn_t &ret) {
    if      (ret() == VReturn_t::PASS     ) { os << "PASS";      }
    else if (ret() == VReturn_t::FAIL     ) { os << "FAIL";      }
    else if (ret() == VReturn_t::PERFECT  ) { os << "PERFECT";   }
    else    { os << ret(); } return os; }
    
std::ostream& Validspace::operator<<=(std::ostream &os, const VReturn_t &ret) {
    os << "{Return value: " << ret() << ", Tag: ";
    if      (ret() == VReturn_t::PASS     ) { os << "PASS";      }
    else if (ret() == VReturn_t::FAIL     ) { os << "FAIL";      }
    else if (ret() == VReturn_t::PERFECT  ) { os << "PERFECT";   }
    else    { os << "score"; } return os << "}"; }