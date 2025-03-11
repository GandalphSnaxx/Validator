#pragma once
/**
 * @file src/validator_t.hpp
 * @author Ray Richter
 * @brief VKeyedList_t Class declaration. 
 */
#include <flagfield.hpp>
#include "Validator_core.hpp"
#include "keyed_list_t.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Validator class for base types.
/// TODO: Add range support to VKeyedList_t
template <class T, class = void>
class Validator_t {
    public:
    // Validator (const VKey_t &key, const std::vector<T> &list) : list_(key, list) {}
    // Validator (const std::vector<VKeyedData_t<T>>   &rawList) : list_(rawList  ) {}
    // Validator (const VKeyedData_t<T>   &kd)                   : list_(kd       ) {}
    // Validator (const VKeyedList_t<T>   &kl)                   : list_(kl       ) {}
    // Validator (const std::vector <T> &list)                   : list_(list     ) {}
    // Validator (const VKey_t &key, const T &data)              : list_(key, data) {}
    // Validator (const T &data)                                 : list_(data     ) {}
    Validator_t (...) : list_(...) { V_DEBUG_MSG("Called Validator base type constructor with args."); }
    Validator_t ()    : list_()    { V_DEBUG_MSG("Called Validator base type constructor."); }
    ~Validator_t()                 { V_DEBUG_MSG("Called Validator base type deconstructor."); }

    uint_t add(...) { return list_.add(...); }
    VReturn_t validate(const T &qData) const { return list_.query(qData); }

    private:
    VKeyedList_t<T> list_;
};

// /// @brief Validator class for comparable types. Has support for ranges.
// /// TODO: Add range support to VKeyedList_t
// template <class T>
// class Validator<T, std::enable_if_t<type_flags<T> & COMPARABLE_FLAG != 0>> {
//     public:
//     Validator (...) : list_(...) { V_DEBUG_MSG("Called Validator comparable type constructor with args."); }
//     Validator ()    : list_()    { V_DEBUG_MSG("Called Validator comparable type constructor."); }
//     ~Validator()                 { V_DEBUG_MSG("Called Validator comparable type deconstructor."); }

//     uint_t add(...) { return list_.add(...); }
//     VReturn_t validate(const T &qData) const { return list_.query(qData); }

//     private:
//     VKeyedList_t<T> list_;
//     std::vector<VRange_t<T>> ranges_;
// };

/// @brief Validator class for object types. Contains validators for subtypes.
template <class T>
class Validator_t<T, std::enable_if_t<std::is_object_v<T>>> {
    public:

    VReturn_t validate(const T::U &qData) const {}

    private:
    std::vector<Validator<T::U>> subValidators_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////