#pragma once
/**
 * @file src/keyed_data_t.hpp
 * @author Ray Richter
 * @brief VRange_t Class declaration. 
 * @note Operator overrides: 
 * op | return_t | other_t | Description
 * !  | bool     | -       | Returns true if range is invalid   (min == max)
 * ~  | bool     | -       | Returns true if range is exclusive (min >  max)
 * () | bool     | Data_t  | Returns true if queried data is within the range
 */
#include "Validator_core.hpp"
#include "config_t.hpp"
#include "keyed_data_t.hpp"
#include "key_t.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// @brief Internal Validator namespace.                                                                                  ////
namespace Validspace {                                                                                                     ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Data_t> class VRange_t {
    public:
    VRange_t(const Data_t&, const Data_t &);
    VRange_t(const VKeyedData_t  <Data_t>&);
    VRange_t(const VRange_t      <Data_t>&);
    VRange_t();
    ~VRange_t();

    bool operator! () const { return min == max; }
    bool operator~ () const { return min >  max; }
    bool operator()(const Data_t&) const;

    private:
    Data_t   min;
    Data_t   max;
    Config_t cfg;

    bool _init(const Data_t&, const Data_t&);
    bool _init(const  VKeyedData_t<Data_t>&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // END: namespace Validspace                                                                                             ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////