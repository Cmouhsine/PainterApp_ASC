#include "redoundo.h"

RedoUndo::RedoUndo(QObject *parent)
    : QObject(parent)
{
}

void RedoUndo::addState(const QImage &state)
{
    undoStack.push(state);
    redoStack.clear();
}

QImage RedoUndo::undo()
{
    if (canUndo()) {
        redoStack.push(undoStack.pop());
        return undoStack.top();
    }
    return QImage();
}

QImage RedoUndo::redo()
{
    if (canRedo()) {
        undoStack.push(redoStack.pop());
        return undoStack.top();
    }
    return QImage();
}

bool RedoUndo::canUndo() const
{
    return undoStack.size() > 1;
}

bool RedoUndo::canRedo() const
{
    return !redoStack.isEmpty();
}
