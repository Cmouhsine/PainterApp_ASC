#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintcanvas.h"
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include "copypaste.h"
#include "redoundo.h"
#include <QDropEvent>
#include <QMenu>

#include "FileHandler.h" // Include FileHandler

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class represents the main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new MainWindow object.
     * @param parent The parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Creates the menus for the main window.
     */
    void createMenus();

    /**
     * @brief The file menu in the menu bar.
     */
    QMenu *fileMenu;

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot to handle changes in pen width.
     * @param width The new pen width.
     */
    void penWidthChanged(int width);

    /**
     * @brief Slot to change the pen color.
     */
    void changePenColor();

    /**
     * @brief Slot to change the fill color.
     */
    void changeFillColor();

    /**
     * @brief Slot to change the fill property.
     */
    void changeFillProperty();

    /**
     * @brief Slot to save the current state.
     */
    void saveState();

    /**
     * @brief Handles the drag enter event.
     * @param event The drag enter event.
     */
    void dragEnterEvent(QDragEnterEvent* event);

    /**
     * @brief Handles the drop event.
     * @param event The drop event.
     */
    void dropEvent(QDropEvent* event);

    /**
     * @brief Slot to open a file.
     */
    void openFile();

    /**
     * @brief Slot to save a file.
     */
    void saveFile();

    /**
     * @brief Slot to close a file.
     */
    void closeFile();

    /**
     * @brief Slot to handle action triggered for programmeurs.
     */
    void on_actionProgrammeurs_triggered();

private:
    Ui::MainWindow *ui;                /**< The UI object for the main window. */
    PaintCanvas *canvas;               /**< The paint canvas widget. */
    QPushButton *penColorButton;       /**< The button to change pen color. */
    QPushButton *fillColorButton;      /**< The button to change fill color. */
    QCheckBox *fillCheckBox;           /**< The checkbox to toggle fill property. */
    QTextEdit *textEdit;               /**< The text edit widget. */

    CopyPaste *copyPaste;              /**< The copy-paste handler. */
    RedoUndo *redoUndo;                /**< The redo-undo handler. */

    FileHandler fileHandler;           /**< The file handler. */
};

#endif // MAINWINDOW_H
