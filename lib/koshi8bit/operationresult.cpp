
#include "operationresult.h"

OperationResult::OperationResult(bool isOk, QString message, void *value)
{
    this->isOk = isOk;
    this->message = message;
    this->value = value;
}

OperationResult::~OperationResult()
{
    if (value){
        //qDebug() << Q_FUNC_INFO << "delete" << isOk << message;
        free(value);
    } else {
        //qDebug() << Q_FUNC_INFO << "no delete" << isOk << message;
    }
}

QString OperationResult::toString()
{
    return QString("%1; %2").arg(isOk).arg(message);
}
