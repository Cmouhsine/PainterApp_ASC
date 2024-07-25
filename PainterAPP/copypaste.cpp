#include "copypaste.h"

CopyPaste::CopyPaste(QTextEdit *textEdit, QObject *parent)
    : QObject(parent), textEdit(textEdit)
{
}

void CopyPaste::copy()
{
    textEdit->copy();
}

void CopyPaste::cut()
{
    textEdit->cut();
}

void CopyPaste::paste()
{
    textEdit->paste();
}
