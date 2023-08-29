
#ifndef OPERATIONRESULT_H
#define OPERATIONRESULT_H

#include <QString>
#include <QDebug>

class OperationResult
{
public:
    OperationResult(bool isOk, QString message="", void *value=nullptr);
    ~OperationResult();

    QString toString();

    bool isOk;
    QString message;
    void *value;
};

#endif // OPERATIONRESULT_H
