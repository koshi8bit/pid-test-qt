#include "varscontainer.h"


QList<NetVarBase*> VarsContainer::localVars;

VarsContainer::VarsContainer(QObject *parent) : QObject(parent)
{

}

VarsContainer::~VarsContainer()
{

}

bool VarsContainer::localVarsContains(NetVarBase *var)
{
    for(int i = 0; i < localVars.count(); i++){
        if(var->name == localVars.at(i)->name)
            return true;
    }
    return false;
}

int VarsContainer::localVarsIdByName(QString name)
{
    for(int i = 0; i < localVars.count(); i++){
        if(name == localVars.at(i)->name)
            return i;
    }
    return -1;
}


void VarsContainer::updateLocalVar(QString name, QVariant value)
{
    int id = localVarsIdByName(name);
    if(id == -1){
#ifndef KOSHI8BIT_LIB_SV_HIDE_MESSAGES
        nvDebug << "update an unknown variable" << name;
#endif
        return;
    }
    localVars.at(id)->updateNewValue(value);
}
