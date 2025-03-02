#include "headers/keyed_data_t.hpp"
#include <typeinfo>
/**
 * @file src/keyed_data_t.cpp
 * @author Ray Richter
 * @brief VKeyedData_t class member definitions.
 */

using namespace Validspace;

template <class Data_t> const VKey_t  VKeyedData_t<Data_t>::getKey    () const { return   key; }
template <class Data_t> const VKey_t  VKeyedData_t<Data_t>::operator- () const { return   key; }
template <class Data_t> const uint_t  VKeyedData_t<Data_t>::operator--() const { return  -key; } // -(-keyedData) = --keyedData => uint_t
template <class Data_t> const Data_t  VKeyedData_t<Data_t>::getCData  () const { return  data; }
template <class Data_t> const Data_t  VKeyedData_t<Data_t>::operator++() const { return  data; }
template <class Data_t> const Data_t* VKeyedData_t<Data_t>::getPData  () const { return &data; }
template <class Data_t> const Data_t* VKeyedData_t<Data_t>::operator+ () const { return &data; }

template <class Data_t> const bool VKeyedData_t<Data_t>::operator< (const VKeyedData_t<Data_t> &rhs) const { return key <  rhs.key; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator> (const VKeyedData_t<Data_t> &rhs) const { return key >  rhs.key; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator<=(const VKeyedData_t<Data_t> &rhs) const { return key <= rhs.key; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator>=(const VKeyedData_t<Data_t> &rhs) const { return key >= rhs.key; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator==(const VKeyedData_t<Data_t> &rhs) const { return key == rhs.key; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator!=(const VKeyedData_t<Data_t> &rhs) const { return key != rhs.key; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator< (const              VKey_t  &rhs) const { return key <  rhs    ; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator> (const              VKey_t  &rhs) const { return key >  rhs    ; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator<=(const              VKey_t  &rhs) const { return key <= rhs    ; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator>=(const              VKey_t  &rhs) const { return key >= rhs    ; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator==(const              VKey_t  &rhs) const { return key == rhs    ; }
template <class Data_t> const bool VKeyedData_t<Data_t>::operator!=(const              VKey_t  &rhs) const { return key != rhs    ; }
