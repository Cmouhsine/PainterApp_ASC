#ifndef REDOUNDO_H
#define REDOUNDO_H

#include <QObject>
#include <QStack>
#include <QImage>

class RedoUndo : public QObject
{
    Q_OBJECT

public:
    explicit RedoUndo(QObject *parent = nullptr);
    void addState(const QImage &state);
    QImage undo();
    QImage redo();
    bool canUndo() const;
    bool canRedo() const;

private:
    QStack<QImage> undoStack;
    QStack<QImage> redoStack;
};

#endif // REDOUNDO_H
