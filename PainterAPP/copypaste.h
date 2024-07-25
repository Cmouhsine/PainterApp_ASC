#ifndef COPYPASTE_H
#define COPYPASTE_H

#include <QObject>
#include <QTextEdit>

/**
 * @class CopyPaste
 * @brief The CopyPaste class provides functionality for copying, cutting, and pasting text in a QTextEdit.
 */
class CopyPaste : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a CopyPaste object.
     * @param textEdit A pointer to the QTextEdit to operate on.
     * @param parent The parent QObject.
     */
    explicit CopyPaste(QTextEdit *textEdit, QObject *parent = nullptr);

public slots:
    /**
     * @brief Copies the selected text from the QTextEdit to the clipboard.
     */
    void copy();

    /**
     * @brief Cuts the selected text from the QTextEdit to the clipboard.
     */
    void cut();

    /**
     * @brief Pastes the text from the clipboard to the QTextEdit.
     */
    void paste();

private:
    QTextEdit *textEdit; /**< A pointer to the QTextEdit widget. */
};

#endif // COPYPASTE_H
