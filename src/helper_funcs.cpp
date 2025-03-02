// #include "Validator_core.hpp"
// /**
//  * @file src/helper_funcs.cpp
//  * @author Ray Richter
//  * @brief Helper functions for Validator
//  */
// using namespace Validspace;

// /// @section cout Operator Overloads

// /// @brief VKey_t print
// /// @param os 
// /// @param k 
// /// @return 
// inline std::ostream& Validspace::operator<< (std::ostream &os, const VKey_t &k) {
//          if (k == VKey_t::WHITELIST) { os << "WHITELIST"; }
//     else if (k == VKey_t::BLACKLIST) { os << "BLACKLIST"; }
//     else if (k == VKey_t::  MAXIMUM) { os <<   "MAXIMUM"; }
//     else if (k == VKey_t::  MINIMUM) { os <<   "MINIMUM"; }
//     else if (k == VKey_t::  PERFECT) { os <<   "PERFECT"; }
//     else { os << k(); } return os; }

// /// @brief Out Stream operator overload for printing detailed VKey_t info
// /// @param os Out Stream
// /// @param k Key
// /// @return Out Stream
// inline std::ostream& Validspace::operator<<=(std::ostream &os, const VKey_t &k) {
//     os << "[ value: " << k() << ", tag: ";
//          if (k == VKey_t::WHITELIST) { os << "WHITELIST"; }
//     else if (k == VKey_t::BLACKLIST) { os << "BLACKLIST"; }
//     else if (k == VKey_t::  MAXIMUM) { os <<   "MAXIMUM"; }
//     else if (k == VKey_t::  MINIMUM) { os <<   "MINIMUM"; }
//     else if (k == VKey_t::  PERFECT) { os <<   "PERFECT"; }
//     else { os << "score"; } os << " ]"; return os; }

// /// @brief Out Stream operator overload for printing a Config_t's state.
// /// @note Usage: cout << config << endl;
// ///
// /// Output example: [  Initalized , Whitelist, ~Arithmatic, ~Minimum, ~Maximum,  Perfect, ~Range, ~Ex Range ]
// /// @param os Out Stream
// /// @param r Queried Config_t
// /// @return Out Stream
// inline std::ostream& Validspace::operator<< (std::ostream &os, const Config_t &r) {
//     os 
// //  Formatting  | Flag checks                    | Flag set      | Flag not set
//     << "[ " << ((r && Config_t::INITALIZED_FLAG) ? " Initalized" : "~Initalized" )
//     << ", " << ((r && Config_t::BLACKLIST_FLAG ) ?  "Blacklist"  :  "Whitelist"  )
//     << ", " << ((r && Config_t::ARITHMATIC_FLAG) ? " Arithmatic" : "~Arithmatic" )
//     << ", " << ((r && Config_t::MINIMUM_FLAG   ) ? " Minimum"    : "~Minimum"    )
//     << ", " << ((r && Config_t::MAXIMUM_FLAG   ) ? " Maximum"    : "~Maximum"    )
//     << ", " << ((r && Config_t::PERFECT_FLAG   ) ? " Perfect"    : "~Perfect"    )
//     << ", " << ((r && Config_t::RANGE_FLAG     ) ? " Range"      : "~Range"      )
//     << ", " << ((r && Config_t::EX_RANGE_FLAG  ) ? " Ex Range"   : "~Ex Range"   )
//     << " ]";
//     return os;
// }

// /// @brief Out stream operator overload for printing detailed information about a Config_t
// /// @note Usage: cout << "MSG " <<= config << endl;
// /// @param os Out Stream
// /// @param r Queried Config_t
// /// @return Out Stream
// inline std::ostream& Validspace::operator<<=(std::ostream &os, const Config_t &r) {
//     os
//     << "\n\tFlag name       | Set | Description"
//     << "\n\tINITALIZED_FLAG | " 
//     << ((r && Config_t::INITALIZED_FLAG) ? "1" : "0") 
//     << "   | Validator is initalized when set."
//     << "\n\tBLACKLIST_FLAG  | " 
//     << ((r && Config_t::BLACKLIST_FLAG ) ? "1" : "0") 
//     << "   | Validator contains only BLACKLIST keys when set. Queried data returns PASS if it does not match any blacklisted value."
//     << "\n\tARITHMATIC_FLAG | " 
//     << ((r && Config_t::ARITHMATIC_FLAG) ? "1" : "0") 
//     << "   | Validator data type is an arithmatic data type when set. Queried data can return a score."
//     << "\n\tMINIMUM_FLAG    | " 
//     << ((r && Config_t::MINIMUM_FLAG   ) ? "1" : "0") 
//     << "   | Validator contains one MINIMUM keyed value when set. Cannot be set if MAXIMUM_FLAG is set."
//     << "\n\tMAXIMUM_FLAG    | " 
//     << ((r && Config_t::MAXIMUM_FLAG   ) ? "1" : "0") 
//     << "   | Validator contains one MAXIMUM keyed value when set. Cannot be set if MINIMUM_FLAG is set."
//     << "\n\tPERFECT_FLAG    | " 
//     << ((r && Config_t::PERFECT_FLAG   ) ? "1" : "0") 
//     << "   | Validator contains at least one PERFECT keyed value when set."
//     << "\n\tRANGE_FLAG      | " 
//     << ((r && Config_t::RANGE_FLAG     ) ? "1" : "0") 
//     << "   | Validator contains at least one range of acceptable values when set. Cannot be set if ARITHMATIC_FLAG is not set."
//     << "\n\tEX_RANGE_FLAG   | " 
//     << ((r && Config_t::EX_RANGE_FLAG  ) ? "1" : "0") 
//     << "   | Validator contains an exclusive range when set. Cannot be set if RANGE_FLAG is not set."
//     << "\n";
//     return os; }
// /* Example: cout << "ERROR: cannot add an exclusive range! Validator configuration: " <<= _config << endl;
// ERROR: cannot add an exclusive range! Validator configuration: 
//     Flag name       | Set | Description
//     INITALIZED_FLAG | 1   | Validator is initalized when set.
//     BLACKLIST_FLAG  | 0   | Validator contains only BLACKLIST keys when set. Queried data returns PASS if it does not match any blacklisted value.
//     ARITHMATIC_FLAG | 1   | Validator data type is an arithmatic data type when set. Queried data can return a score.
//     MINIMUM_FLAG    | 0   | Validator contains one MINIMUM keyed value when set. Cannot be set if MAXIMUM_FLAG is set.
//     MAXIMUM_FLAG    | 1   | Validator contains one MAXIMUM keyed value when set. Cannot be set if MINIMUM_FLAG is set.
//     PERFECT_FLAG    | 0   | Validator contains at least one PERFECT keyed value when set.
//     RANGE_FLAG      | 1   | Validator contains at least one range of acceptable values when set. Cannot be set if ARITHMATIC_FLAG is not set.
//     EX_RANGE_FLAG   | 0   | Validator contains an exclusive range when set. Cannot be set if RANGE_FLAG is not set.
// */

// /// @brief Prints VReturn_t info
// /// @param os Out Stream
// /// @param r Validator return as `VReturn_t`
// /// @return Out Stream
// inline std::ostream& Validspace::operator<< (std::ostream &os, const VReturn_t &r) {
//          if (!r) { os << "FAIL";    }
//     else if (+r) { os << "PASS";    }
//     else if (*r) { os << "PERFECT"; }
//     else { os << r(); } return os;  }

// /// @brief Prints detailed VReturn_t info
// /// @param os Out Stream
// /// @param r Validator return as `VReturn_t`
// /// @return Out Stream
// inline std::ostream& Validspace::operator<<=(std::ostream &os, const VReturn_t &r) {
//     os << "[ value: " << r() << ", key: ";
//          if (!r) { os << "FAIL";    }
//     else if (+r) { os << "PASS";    }
//     else if (*r) { os << "PERFECT"; }
//     else { os << "score"; } os << " ]";
//     return os; }

// /// @brief Prints VKeyedData_t info
// /// @tparam T Contained data type
// /// @param os Out Stream
// /// @param kd Keyed Data
// /// @return Out Stream
// template <class T> inline std::ostream& Validspace::operator<< 
// (std::ostream &os, const VKeyedData_t<T> &kd) {
//     os << "{ Key: " 
//     << VKey_t(kd.first ) << ", sizeof(Data_t): " 
//     << sizeof(kd.second) << " }";
//     return os; }

// /// @brief Prints detailed VKeyedData_t info
// /// @tparam T Contained data type
// /// @param os Out Stream
// /// @param kd Keyed Data
// /// @return Out Stream
// template <class T> inline std::ostream& Validspace::operator<<=
// (std::ostream &os, const VKeyedData_t<T> &kd) {
//     os << "VKeyedData_t{ Key: " 
//     <<=VKey_t(kd.first);
//     /// TODO: Print more data info
//     os << ", sizeof(Data): " 
//     << sizeof(kd.second) << " }";
//     return os; }

// /// @brief Prints VKeyedList_t info
// /// @tparam T Contained data type
// /// @param os Out Stream
// /// @param kl Keyed List
// /// @return Out Stream
// template <class T> inline std::ostream& Validspace::operator<< 
// (std::ostream &os, const VKeyedList_t<T> &kl) {
//     os << "{ ";
//     for (const VKeyedList_t<T> &kd : kl) { os << kd; }
//     os << " }";
//     return os; }

// /// @brief Prints detailed VKeyedList_t info
// /// @tparam T Contained data type
// /// @param os Out Stream
// /// @param kl Keyed List
// /// @return Out Stream
// template <class T> inline std::ostream& Validspace::operator<<=
// (std::ostream &os, const VKeyedList_t<T> &kl) {
//     os << "\nVKeyedList_t: { ";
//     for (const VKeyedList_t<T> &kd : kl) { os <<= kd; }
//     os << " } end list\n";
//     return os; }

// /// @brief Prints Validator information
// /// @tparam T Validator data type
// /// @param os Out Stream
// /// @param v Validator as `ValidList_t<T>`
// /// @return Out Stream
// template <class T> inline std::ostream& Validspace::operator<< (std::ostream &os, const ValidList_t<T> &v) {
//     return os; }

// /// @brief Prints detailed Validator information
// /// @tparam T Validator data type
// /// @param os Out Stream
// /// @param v Validator as `ValidList_t<T>`
// /// @return Out Stream
// template <class T> inline std::ostream& Validspace::operator<<=(std::ostream &os, const ValidList_t<T> &v) {
//     return os; }