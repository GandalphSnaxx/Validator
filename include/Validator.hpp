#pragma once
/**
 * @file include/Validator.hpp
 * @author Ray Richter
 * @brief This is the header to include to use Validator. It exposes classes and data types to a main program.
 * 
 * @note Validator numberline example:
 * <-------------------------0--------------------------------------------->
 *     >        |   |   <    *     >     <   x    x  >    |            <
 * - `<`: Valid range start
 * - `>`: Valid range end
 * - `|`: Valid value
 * - `*`: Perfect value
 * - `x`: Invalid value
 * 
 * @note Standard Validator Operator Overloads:
 * Op     | Operator Description | Return Type     | Left Type    | Right Type | Description
 * Family |                      |                 |              |            |
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 * +a     | Gets pointers to or  | Data_t*         | VKeyedData_t | -          | Gets a pointer to data.
 *        | copies of internal   | VList_t<Data_t> | VKeyedList_t | -          | Gets a pointer to a data list.
 *        | data                 | uint_t          | VReturn_t    | -          | Casts to uint_t.
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 * -a     | Gets a copy of a key | VKey_t          | VKeyedData_t | -          | Gets a copy of a key.
 *        | or key data          | uint_t          | VKey_t       | -          | Gets a copy of a key's value.
 *        | or config data       | bool            | VReturn_t    | -          | PASS, PERFECT, score = true; FAIL = false.
 *        |                      | uint_t          | Config_t     | -          | Gets a copy of Config_t as uint
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 * !a     | Special value checks | bool            | VKey_t       | -          | ! - BLACKLIST, ~ - score
 * ~a     |                      | bool            | VKeyedData_t | -          | ! - BLACKLIST, ~ - score
 *        |                      | bool            | VReturn_t    | -          | ! - FAIL,      ~ - score
 *        |                      | bool            | Config_t     | -          | ! - INITALIZED_FLAG set
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 * a <  b | Compares keys or     | bool            | VKey_t       | VKey_t     | Compare with respect to special values.
 * a >  b | returns with respect | bool            | VReturn_t    | VReturn_t  | Compare with respect to special values.
 * a <= b | to special values    |                 |              |            |
 * a >= b |                      |                 |              |            |
 * a == b |                      |                 |              |            |
 * a != b |                      |                 |              |            |
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 * a += b | Does math to a with  | VReturn_t&      | VReturn_t&   | VReturn_t  | any   + (FAIL, BLACKLIST) = FAIL
 * a -= b | respect to special   | "        "      | "        "   | VKey_t     | PASS  + (WHITELIST, MINIMUM, MAXIMUM) = PASS
 *        | values               |                 |              |            | !FAIL +  PERFECT = PERFECT
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 * a +  b | Gets a copy after    | VReturn_t       | VReturn_t    | VReturn_t  | any   + (FAIL, BLACKLIST) = FAIL
 * a -  b | math with respect to | "       "       | "       "    | VKey_t     | PASS  + (WHITELIST, MINIMUM, MAXIMUM) = PASS
 *        | special values       | "       "       | "       "    | uint_t     | !FAIL + PERFECT = PERFECT
 * -------|----------------------|-----------------|--------------|------------|-----------------------------------------------
 *        |                      |                 |              |            |
 * TODO: Make a struct validator (a list of Validators)
 */

#include "../src/headers/Validator_core.hpp"
#include "../src/headers/config_t.hpp"
#include "../src/headers/keyed_data_t.hpp"
#include "../src/headers/keyed_list_t.hpp"
#include "../src/headers/key_t.hpp"
#include "../src/headers/range_t.hpp"
#include "../src/headers/return_t.hpp"

/// @section Type Definitions for External Use

//    External type | Internal type
using VReturn_t     = Validspace::VReturn_t;
using VKey_t        = Validspace::VKey_t;

// With subtype T |using| External type | Internal type
template <class T> using   VKeyedList_t = Validspace::VKeyedList_t<T>;
template <class T> using   VKeyedData_t = Validspace::VKeyedData_t<T>;
// template <class T> using       VRange_t = Validspace::    VRange_t<T>;
// template <class T> using        VList_t = Validspace::     VList_t<T>;
// template <class T> using   VRangeList_t = Validspace::VRangeList_t<T>;
// template <class T> using      Validator = Validspace:: ValidList_t<T>;