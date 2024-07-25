#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

/**
 * @class FileHandler
 * @brief The FileHandler class provides functionality to handle file operations such as opening, reading, writing, and saving files.
 */
class FileHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a FileHandler object.
     * @param parent The parent QObject.
     */
    explicit FileHandler(QObject *parent = nullptr);

    /**
     * @brief Opens a file with the given file name.
     * @param fileName The name of the file to open.
     * @return true if the file is successfully opened, false otherwise.
     */
    bool openFile(const QString &fileName);

    /**
     * @brief Saves content to a file with the given file name.
     * @param fileName The name of the file to save.
     * @param content The content to save to the file.
     * @return true if the file is successfully saved, false otherwise.
     */
    bool saveFile(const QString &fileName, const QString &content);

    /**
     * @brief Reads the content of the opened file.
     * @return The content of the file as a QString.
     */
    QString readFile();

    /**
     * @brief Writes content to the opened file.
     * @param content The content to write to the file.
     * @return true if the content is successfully written, false otherwise.
     */
    bool writeFile(const QString &content);

    /**
     * @brief Gets the file name for opening a file using a file dialog.
     * @param parent The parent widget.
     * @param caption The caption of the file dialog.
     * @param dir The initial directory of the file dialog.
     * @param filter The file filter for the file dialog.
     * @return The selected file name as a QString.
     */
    QString getOpenFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString());

    /**
     * @brief Gets the file name for saving a file using a file dialog.
     * @param parent The parent widget.
     * @param caption The caption of the file dialog.
     * @param dir The initial directory of the file dialog.
     * @param filter The file filter for the file dialog.
     * @return The selected file name as a QString.
     */
    QString getSaveFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString());

private:
    QFile file; /**< The QFile object used for file operations. */
};

#endif // FILEHANDLER_H
