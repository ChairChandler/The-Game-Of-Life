#ifndef SUPERVISEDVAR_H
#define SUPERVISEDVAR_H

//Class used for creating getter and setter, the aim is to control the flow of access to the variable
template<class T>
class SupervisedVar
{
public:
    explicit SupervisedVar();
    explicit SupervisedVar(const T &val);
    virtual ~SupervisedVar();

    virtual void set(const T &val);
    virtual T get();

protected:
    T m_var;
};

#include "supervisedvar.tpp"

#endif // SUPERVISEDVAR_H
