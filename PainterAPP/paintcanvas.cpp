#include "paintcanvas.h"
#include <QPainter>
#include <QMouseEvent>

/**
 * @brief Constructs a new PaintCanvas object.
 * @param parent The parent widget.
 */
PaintCanvas::PaintCanvas(QWidget *parent) : QWidget(parent),
    tool(Pen),
    fill(false),
    drawing(false),
    penWidth(1),
    fillColor(Qt::blue),
    penColor(Qt::black),
    lastRect(QRectF(0, 0, 0, 0)),
    lastEraserRect(QRectF(0, 0, 0, 0))
{
    image = QImage(400, 400, QImage::Format_RGB32);  // Initialize the image
    image.fill(Qt::white);  // Fill the image with white color
}

/**
 * @brief Gets the current tool type.
 * @return The current tool type.
 */
PaintCanvas::ToolType PaintCanvas::getTool() const
{
    return tool;
}

/**
 * @brief Sets the tool type.
 * @param value The new tool type.
 */
void PaintCanvas::setTool(const ToolType &value)
{
    tool = value;
}

/**
 * @brief Gets the fill property.
 * @return The fill property.
 */
bool PaintCanvas::getFill() const
{
    return fill;
}

/**
 * @brief Sets the fill property.
 * @param value The new fill property.
 */
void PaintCanvas::setFill(bool value)
{
    fill = value;
}

/**
 * @brief Gets the pen width.
 * @return The pen width.
 */
int PaintCanvas::getPenWidth() const
{
    return penWidth;
}

/**
 * @brief Sets the pen width.
 * @param value The new pen width.
 */
void PaintCanvas::setPenWidth(int value)
{
    penWidth = value;
}

/**
 * @brief Gets the fill color.
 * @return The fill color.
 */
QColor PaintCanvas::getFillColor() const
{
    return fillColor;
}

/**
 * @brief Sets the fill color.
 * @param value The new fill color.
 */
void PaintCanvas::setFillColor(const QColor &value)
{
    fillColor = value;
}

/**
 * @brief Gets the pen color.
 * @return The pen color.
 */
QColor PaintCanvas::getPenColor() const
{
    return penColor;
}

/**
 * @brief Sets the pen color.
 * @param value The new pen color.
 */
void PaintCanvas::setPenColor(const QColor &value)
{
    penColor = value;
}

/**
 * @brief Gets the image.
 * @return The image.
 */
QImage PaintCanvas::getImage() const
{
    return image;
}

/**
 * @brief Sets the image.
 * @param newImage The new image.
 */
void PaintCanvas::setImage(const QImage &newImage)
{
    image = newImage;
    update();
    emit imageChanged();  // Emit signal whenever the image is set
}

/**
 * @brief Draws a line to the specified end point.
 * @param endPoint The end point of the line.
 */
void PaintCanvas::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(lastPoint, endPoint);
    int adjustment = penWidth + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-adjustment, -adjustment, +adjustment, +adjustment));
    lastPoint = endPoint;
    emit imageChanged();  // Emit signal when the image changes
}

/**
 * @brief Draws a rectangle or ellipse to the specified end point.
 * @param endPoint The end point of the shape.
 * @param elipse Whether to draw an ellipse instead of a rectangle.
 */
void PaintCanvas::drawRectTo(const QPoint &endPoint, bool elipse)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if (fill)
        painter.setBrush(fillColor);
    else
        painter.setBrush(Qt::NoBrush);

    if (!elipse)
        painter.drawRect(QRect(lastPoint, endPoint));
    else
        painter.drawEllipse(QRect(lastPoint, endPoint));

    if (drawing) {
        painter.setPen(QPen(Qt::white, penWidth + 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        if (fill)
            painter.setBrush(Qt::white);
        else
            painter.setBrush(Qt::NoBrush);

        if (!elipse)
            painter.drawRect(lastRect);
        else
            painter.drawEllipse(lastRect);

        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(fillColor);
    }

    lastRect = QRectF(lastPoint, endPoint);
    update();
    emit imageChanged();  // Emit signal when the image changes
}

/**
 * @brief Erases the area under the specified top-left point.
 * @param topLeft The top-left point of the eraser.
 */
void PaintCanvas::eraseUnder(const QPoint &topLeft)
{
    QPainter painter(&image);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::white);
    painter.drawRect(lastEraserRect);

    QRect currentRect(topLeft, QSize(100, 100));
    painter.drawRect(currentRect);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);
    painter.drawRect(currentRect);

    lastEraserRect = currentRect;

    if (!drawing) {
        painter.setBrush(Qt::white);
        painter.setPen(Qt::white);
        painter.drawRect(lastEraserRect);
        lastEraserRect = QRect(0, 0, 0, 0);
    }

    update();
    emit imageChanged();  // Emit signal when the image changes
}

/**
 * @brief Resizes the image to the specified size.
 * @param image The image to resize.
 * @param newSize The new size.
 */
void PaintCanvas::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
    emit imageChanged();  // Emit signal when the image changes
}

/**
 * @brief Handles mouse press events.
 * @param event The mouse event.
 */
void PaintCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

/**
 * @brief Handles mouse move events.
 * @param event The mouse event.
 */
void PaintCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        if (tool == Pen) {
            drawLineTo(event->pos());
        } else if (tool == Rect) {
            drawRectTo(event->pos());
        } else if (tool == Ellipse) {
            drawRectTo(event->pos(), true);
        } else if (tool == Eraser) {
            eraseUnder(event->pos());
        }
    }
}

/**
 * @brief Handles mouse release events.
 * @param event The mouse event.
 */
void PaintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        if (tool == Pen) {
            drawLineTo(event->pos());
        } else if (tool == Rect) {
            drawRectTo(event->pos());
        } else if (tool == Ellipse) {
            drawRectTo(event->pos(), true);
        } else if (tool == Eraser) {
            eraseUnder(event->pos());
        }
        lastRect = QRect(0, 0, 0, 0);
    }
}

/**
 * @brief Paints the widget.
 * @param event The paint event.
 */
void PaintCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rectToDraw = event->rect();
    painter.drawImage(rectToDraw, image, rectToDraw);
}

/**
 * @brief Handles resize events.
 * @param event The resize event.
 */
void PaintCanvas::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}
