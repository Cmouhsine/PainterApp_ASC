#ifndef PAINTCANVAS_H
#define PAINTCANVAS_H

#include <QWidget>
#include <QImage>
#include <QStack>

/**
 * @brief The PaintCanvas class represents a widget for painting.
 */
class PaintCanvas : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Enum representing different tool types.
     */
    enum ToolType { Pen, Rect, Ellipse, Eraser };

    /**
     * @brief Constructs a new PaintCanvas object.
     * @param parent The parent widget.
     */
    explicit PaintCanvas(QWidget *parent = nullptr);

    /**
     * @brief Gets the current tool.
     * @return The current tool.
     */
    ToolType getTool() const;

    /**
     * @brief Sets the current tool.
     * @param value The new tool to set.
     */
    void setTool(const ToolType &value);

    /**
     * @brief Gets the fill property.
     * @return True if fill is enabled, false otherwise.
     */
    bool getFill() const;

    /**
     * @brief Sets the fill property.
     * @param value The new fill value.
     */
    void setFill(bool value);

    /**
     * @brief Gets the pen width.
     * @return The pen width.
     */
    int getPenWidth() const;

    /**
     * @brief Sets the pen width.
     * @param value The new pen width.
     */
    void setPenWidth(int value);

    /**
     * @brief Gets the fill color.
     * @return The fill color.
     */
    QColor getFillColor() const;

    /**
     * @brief Sets the fill color.
     * @param value The new fill color.
     */
    void setFillColor(const QColor &value);

    /**
     * @brief Gets the pen color.
     * @return The pen color.
     */
    QColor getPenColor() const;

    /**
     * @brief Sets the pen color.
     * @param value The new pen color.
     */
    void setPenColor(const QColor &value);

    /**
     * @brief Gets the current image.
     * @return The current image.
     */
    QImage getImage() const;

    /**
     * @brief Sets the current image.
     * @param value The new image.
     */
    void setImage(const QImage &value);

    /**
     * @brief Undoes the last action.
     */
    void undo();

    /**
     * @brief Redoes the last undone action.
     */
    void redo();

signals:
    /**
     * @brief Signal emitted when the image changes.
     */
    void imageChanged();

protected:
    /**
     * @brief Handles the mouse press event.
     * @param event The mouse press event.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handles the mouse move event.
     * @param event The mouse move event.
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief Handles the mouse release event.
     * @param event The mouse release event.
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * @brief Handles the paint event.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Handles the resize event.
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief Draws a line to the specified end point.
     * @param endPoint The end point of the line.
     */
    void drawLineTo(const QPoint &endPoint);

    /**
     * @brief Draws a rectangle or ellipse to the specified end point.
     * @param endPoint The end point of the rectangle or ellipse.
     * @param ellipse True to draw an ellipse, false to draw a rectangle.
     */
    void drawRectTo(const QPoint &endPoint, bool ellipse = false);

    /**
     * @brief Erases the area under the specified top-left point.
     * @param topLeft The top-left point of the area to erase.
     */
    void eraseUnder(const QPoint &topLeft);

    /**
     * @brief Resizes the image to the specified new size.
     * @param image The image to resize.
     * @param newSize The new size of the image.
     */
    void resizeImage(QImage *image, const QSize &newSize);

    /**
     * @brief Saves the current state for undo.
     */
    void saveStateForUndo();

    ToolType tool;             /**< The current tool. */
    bool fill;                 /**< The fill property. */
    bool drawing;              /**< Whether drawing is currently in progress. */
    int penWidth;              /**< The pen width. */
    QColor fillColor;          /**< The fill color. */
    QColor penColor;           /**< The pen color. */
    QPoint lastPoint;          /**< The last point drawn to. */
    QRectF lastRect;           /**< The last rectangle drawn. */
    QRectF lastEraserRect;     /**< The last eraser rectangle. */
    QImage image;              /**< The current image. */
    QStack<QImage> undoStack;  /**< The stack of images for undo. */
    QStack<QImage> redoStack;  /**< The stack of images for redo. */
};

#endif // PAINTCANVAS_H
