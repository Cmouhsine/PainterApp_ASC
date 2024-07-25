#ifndef REDOUNDO_H
#define REDOUNDO_H

#include <QObject>
#include <QStack>
#include <QImage>

/**
 * @class RedoUndo
 * @brief The RedoUndo class provides functionality for managing undo and redo operations for images.
 */
class RedoUndo : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a RedoUndo object.
     * @param parent The parent QObject.
     */
    explicit RedoUndo(QObject *parent = nullptr);

    /**
     * @brief Adds a new state to the undo stack.
     * @param state The image state to add.
     */
    void addState(const QImage &state);

    /**
     * @brief Performs an undo operation.
     * @return The previous image state if available, otherwise an empty QImage.
     */
    QImage undo();

    /**
     * @brief Performs a redo operation.
     * @return The next image state if available, otherwise an empty QImage.
     */
    QImage redo();

    /**
     * @brief Checks if an undo operation can be performed.
     * @return true if undo is possible, false otherwise.
     */
    bool canUndo() const;

    /**
     * @brief Checks if a redo operation can be performed.
     * @return true if redo is possible, false otherwise.
     */
    bool canRedo() const;

private:
    QStack<QImage> undoStack; /**< Stack for storing undo states. */
    QStack<QImage> redoStack; /**< Stack for storing redo states. */
};

#endif // REDOUNDO_H
