#ifndef PRINTSCREENER_H
#define PRINTSCREENER_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>


#include <lib/koshi8bit/easyliving.h>



class PrintScreener
{
public:
    PrintScreener();
    static QString save(QWidget *widget, QString defaultFileName = "", bool autosave = false);
    static void copy(QWidget *widget);
};

#endif // PRINTSCREENER_H
