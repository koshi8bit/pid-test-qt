#include "errorhandler.h"

const QString ErrorHandler::errorSave = tr("Возникла критическая ошибка!\nНевозможно сохранить файл.\nПокажи это окно Лехе (или сфотай и отправь через Telegram/WhatsApp)");
const QString ErrorHandler::errorSend = tr("Возникла критическая ошибка!\nОтправка логов не удалась, но логи сохранены в файл.\nСообщи Лехе!");
const QString ErrorHandler::okSend = tr("Возникла критическая ошибка!\nЛоги отправлены Лехе!");

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &ErrorHandler::timerTimeout);
}

void ErrorHandler::checkForErrors()
{
    checkForErrorsEmited = true;
    if(triggered)
    {
        timer->start();
    }
}

void ErrorHandler::showErrorMessage(QString messageToUser, QString error)
{
    QMessageBox mb;
    mb.setText(messageToUser);
    mb.setInformativeText(error);
    mb.setIcon(QMessageBox::Critical);
    mb.exec();
}

void ErrorHandler::processError(QString error)
{
    triggered = true;
    auto date = QDateTime::currentDateTime().toString(EasyLiving::formatDateTimeFile());
    auto fileName = QString("crash-%1.log").arg(date);
    auto file = new QFile(fileName);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qWarning() << "Error handled!" << error;
        showErrorMessage(errorSave, error);
        return;
    }

    auto stream = new QTextStream(file);
    *stream << error;
    stream->flush();
    file->close();

    if (file->size() == 0)
    {
        showErrorMessage(errorSave, error);
        return;
    }

    showErrorMessage(errorSend, file->fileName());

    if (checkForErrorsEmited)
        QCoreApplication::exit(-1);

}

void ErrorHandler::timerTimeout()
{
    QCoreApplication::exit(-1);
}

