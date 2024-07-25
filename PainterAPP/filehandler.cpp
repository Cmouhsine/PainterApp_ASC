#include "FileHandler.h"

FileHandler::FileHandler(QObject *parent) : QObject(parent) {}

bool FileHandler::openFile(const QString &fileName)
{
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "Error", "Could not open file");
        return false;
    }
    return true;
}

bool FileHandler::saveFile(const QString &fileName, const QString &content)
{
    QFile outFile(fileName);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "Error", "Could not save file");
        return false;
    }

    QTextStream out(&outFile);
    out << content;
    outFile.close();
    return true;
}

QString FileHandler::readFile()
{
    if (!file.isOpen() || !file.isReadable())
    {
        QMessageBox::warning(nullptr, "Error", "File is not open for reading");
        return QString();
    }

    QTextStream in(&file);
    QString content = in.readAll();
    return content;
}

bool FileHandler::writeFile(const QString &content)
{
    if (!file.isOpen() || !file.isWritable())
    {
        QMessageBox::warning(nullptr, "Error", "File is not open for writing");
        return false;
    }

    QTextStream out(&file);
    out << content;
    return true;
}

QString FileHandler::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter)
{
    return QFileDialog::getOpenFileName(parent, caption, dir, filter);
}

QString FileHandler::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter)
{
    return QFileDialog::getSaveFileName(parent, caption, dir, filter);
}
