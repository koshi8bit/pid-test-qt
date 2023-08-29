#ifndef NETVAR_H
#define NETVAR_H

#include "netvarbase.h"
#include <QVariant>


template <class TypeName>
class NetVar : public NetVarBase
{
public:
    NetVar(QString varName) : NetVarBase(varName){

    }
    TypeName value(){
        return this->_value.template value<TypeName>();
    }
    void setValue(TypeName val){
        this->_value.setValue(val);
    }
};

#endif // NETVAR_H
