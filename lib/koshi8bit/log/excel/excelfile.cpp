#include "excelfile.h"

//file->close();

ExcelFile::ExcelFile(QObject *parent) : QObject(parent)
{

}

ExcelFile::~ExcelFile()
{
    if (file != nullptr)
    {
        push();

        //stream->close();
        file->close();
    }
}

bool ExcelFile::configure(QDateTime dt, QString datePattern, QString folder, QString codepage)
{
    auto date = dt.toString(datePattern);
    this->codepage = codepage;

    auto dir = QDir();
    if (!dir.exists(folder))
    {
        if (!dir.mkpath(folder))
        {
            auto message = EL_FORMAT_ERR(QString("Error creating folder <%1>").arg(folder));
            qDebug() << message;
            emit errorOcurred(message);
            return false;
        }
    }

    auto fileName = QString("%1.xls").arg(date);
    fileName = QDir(folder).filePath(fileName);
    file = new QFile(fileName);

    if (!openFile())
    {
        auto message = QString("Error open file <%1>").arg(fileName);
        //qDebug() << message;
        emit errorOcurred(message);
        return false;
    }

    return true;
}

void ExcelFile::append(QString message)
{
    buffer.append(message);
}

bool ExcelFile::openFile()
{
    _isCreated = !file->exists();
    if (file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        stream = new QTextStream(file);
        if (!codepage.isEmpty()) {
#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 2))
            stream->setEncoding(codepage.toStdString().c_str());
#endif
        }
        return true;
    }
    return false;
}

long long ExcelFile::tryPush()
{
    auto sizeBefore = file->size();
    *stream << buffer;
    stream->flush();
    auto sizeAfter = file->size();
    return sizeAfter - sizeBefore;
}

bool ExcelFile::push()
{
    if(tryPush() > 0)
    {
        buffer.clear();
        return true;
    }
    file->close();
    openFile();
    if(tryPush() > 0)
    {
        buffer.clear();
        return true;
    }
    return false;
}

bool ExcelFile::isCreated()
{
    return _isCreated;
}

QString ExcelFile::fileName()
{
    return file->fileName();
}



