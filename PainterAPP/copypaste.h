#ifndef COPYPASTE_H
#define COPYPASTE_H

#include <QObject>
#include <QTextEdit>

class CopyPaste : public QObject
{
    Q_OBJECT

public:
    explicit CopyPaste(QTextEdit *textEdit, QObject *parent = nullptr);

public slots:
    void copy();
    void cut();
    void paste();

private:
    QTextEdit *textEdit;
};

#endif // COPYPASTE_H
