#include "supervisedvar.h"

template<class T>
SupervisedVar<T>::SupervisedVar(): m_var(0) {}

template<class T>
SupervisedVar<T>::SupervisedVar(const T &val): m_var(val) {}

template<class T>
T SupervisedVar<T>::get()
{
  return m_var;
}

template<class T>
void SupervisedVar<T>::set(const T &val)
{
    m_var = val;
}

template<class T>
SupervisedVar<T>::~SupervisedVar() {}
