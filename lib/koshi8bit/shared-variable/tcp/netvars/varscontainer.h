#ifndef VARSCONTAINER_H
#define VARSCONTAINER_H

#include <QObject>
#include <QList>
#include "netvarbase.h"

class VarsContainer : public QObject
{
    Q_OBJECT

public:
    explicit VarsContainer(QObject *parent = nullptr);
    virtual ~VarsContainer();
    void updateLocalVar(QString name, QVariant value);

protected:
    static bool localVarsContains(NetVarBase* var);
    static int localVarsIdByName(QString name);
    static QList<NetVarBase*> localVars;
signals:

public slots:

friend class NetVarBase;
};

#endif // VARSCONTAINER_H
