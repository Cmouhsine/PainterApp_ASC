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
#include<QMenu>

#include "FileHandler.h" // Include FileHandler

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void createMenus();
    QMenu *fileMenu;

    ~MainWindow();

private slots:
    void penWidthChanged(int width);
    void changePenColor();
    void changeFillColor();
    void changeFillProperty();
    void saveState(); // Add this line

//------------------------------------------------------------------------------------------------sf ------------------------------------------
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);
    //------------------------------------------------------------------------------------------------sf ------------------------------------------

    void openFile();
    void saveFile();
    void closeFile();


    void on_actionProgrammeurs_triggered();

private:
    Ui::MainWindow *ui;
    PaintCanvas * canvas;
    QPushButton * penColorButton;
    QPushButton * fillColorButton;
    QCheckBox * fillCheckBox;
    QTextEdit *textEdit;

    CopyPaste *copyPaste;
    RedoUndo *redoUndo;

    FileHandler fileHandler; // Declare FileHandler
};

#endif // MAINWINDOW_H


