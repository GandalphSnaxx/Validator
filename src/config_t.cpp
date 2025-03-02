#include "headers/config_t.hpp"
/**
 * @file config_t.cpp
 * @author Ray Richter
 * @brief Config_t class member function definitions.
 */
using namespace Validspace;

#define   CAST(i) static_cast<underlying_config_t>(i)
#define UNCAST(i) static_cast<Config_t>(i)

// return | op to overload    | right hand side   | const | return calculation

/// @brief Sets `Config_t` flags from another `Config_t`
Config_t& Config_t::operator= (const Config_t &rhs)       { _cfg = -rhs;               return *this; }
/// @brief Sets `Config_t` flags from a `uint`
Config_t& Config_t::operator= (const   uint_t &rhs)       { _cfg =  rhs;               return *this; }
/// @brief `Config_t` `INITALIZED_FLAG` check @return Returns `true` if `INITALIZED_FLAG` is set
bool      Config_t::operator! ()                    const { return (_cfg &   INITALIZED_FLAG)  != 0; }
/// @brief Sets `INITALIZED_FLAG`
void      Config_t::operator+ ()                          {        (_cfg &=  INITALIZED_FLAG)      ; }
/// @brief `Config_t` flag check @return Returns `true` if every rhs flag is set
bool      Config_t::operator&&(const Config_t &rhs) const { return (_cfg &  -rhs) != 0             ; }
/// @brief `Config_t` flag check @return Returns `true` if every rhs flag is set
bool      Config_t::operator()(const Config_t &rhs) const { return (_cfg &  -rhs) != 0             ; }
/// @brief `Config_t` flag check @return Returns `true`  if both `Config_t`s have the same flags set
bool      Config_t::operator==(const Config_t &rhs) const { return (_cfg == -rhs)                  ; }
/// @brief `Config_t` flag check @return Returns `false` if both `Config_t`s have the same flags set
bool      Config_t::operator!=(const Config_t &rhs) const { return (_cfg &  -rhs) == 0             ; }
/// @brief `FLAG` filter. Keeps rhs flags
Config_t& Config_t::operator&=(const Config_t &rhs)       { _cfg &=  (-rhs);           return *this; }
/// @brief `FLAG` adder. Adds rhs flags
Config_t& Config_t::operator+=(const Config_t &rhs)       { _cfg |=  (-rhs);           return *this; }
/// @brief Makes a new `Config_t` with combined flags.
Config_t  Config_t::operator| (const Config_t &rhs) const { return            Config_t(_cfg | -rhs); }
/// @brief `FLAG` adder. Adds rhs flags
Config_t& Config_t::operator|=(const Config_t &rhs)       { _cfg |=  (-rhs);           return *this; }
/// @brief `FLAG` remover. Clears rhs flags
Config_t& Config_t::operator-=(const Config_t &rhs)       { _cfg &= !(-rhs);           return *this; }
/// @brief `FLAG` toggle. Toggles rhs flags
Config_t& Config_t::operator^=(const Config_t &rhs)       { _cfg ^=  (-rhs);           return *this; }
/// @brief Conditional clear. Removes every flag if `TRUE`.
Config_t& Config_t::operator()(const     bool &rhs)       { if(!rhs) { _cfg = EMPTY; } return *this; }
/// @brief Conditional clear. Removes every flag if `TRUE`.
Config_t& Config_t::operator*=(const     bool &rhs)       { if(!rhs) { _cfg = EMPTY; } return *this; }
/// @brief Conditional clear. Creates a new `Config_t` with the same flags if `TRUE` or no flags if `FALSE`.
Config_t  Config_t::operator* (const     bool &rhs) const { return     Config_t(rhs ? _cfg : EMPTY); }