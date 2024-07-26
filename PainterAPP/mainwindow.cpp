#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QSpinBox>
#include <QColorDialog>
#include <QMouseEvent>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QMessageBox>
#include <QMimeData>
#include <QPixmap>
#include <QHBoxLayout>
#include <QGridLayout>
#include <dragbutton.h>
#include <QMenu>
#include <QBuffer>
#include <QDialog>

/**
 * @brief Constructs a new MainWindow object.
 * @param parent The parent widget.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileHandler(this) // Initialize FileHandler
{
    ui->setupUi(this);

    canvas = new PaintCanvas(this);
    setCentralWidget(canvas);

    // Pen width
    QLabel *penWidthLabel = new QLabel("Pen Width", this);
    QSpinBox *penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setValue(2);
    penWidthSpinBox->setRange(1, 15);

    // Pen color
    QLabel *penColorLabel = new QLabel("Pen Color", this);
    penColorButton = new QPushButton(this);

    // Fill Color
    QLabel *fillColorLabel = new QLabel("Fill Color", this);
    fillColorButton = new QPushButton(this);

    // Fill
    fillCheckBox = new QCheckBox("Fill Shape", this);

    // Tool Buttons
    QPushButton *rectButton = new QPushButton(this);
    rectButton->setIcon(QIcon(":/images/rectangle.png"));

    QPushButton *penButton = new QPushButton(this);
    penButton->setIcon(QIcon(":/images/pen.png"));

    QPushButton *ellipseButton = new QPushButton(this);
    ellipseButton->setIcon(QIcon(":/images/circle.png"));

    QPushButton *eraserButton = new QPushButton(this);
    eraserButton->setIcon(QIcon(":/images/eraser.png"));

    QPushButton *copyButton = new QPushButton(this);
    copyButton->setIcon(QIcon(":/images/copyIcon.png"));

    QPushButton *pasteButton = new QPushButton(this);
    pasteButton->setIcon(QIcon(":/images/pasteIcon.png"));

    QPushButton *cutButton = new QPushButton(this);
    cutButton->setIcon(QIcon(":/images/cutIcon.png"));

    QPushButton *redoButton = new QPushButton(this);
    redoButton->setIcon(QIcon(":/images/redoIcon.png"));

    QPushButton *undoButton = new QPushButton(this);
    undoButton->setIcon(QIcon(":/images/undoIcon.png"));

    QPushButton *saveButton = new QPushButton(this);
    saveButton->setIcon(QIcon(":/images/save.png"));

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(QIcon(":/images/close.png"));

    QPushButton *openButton = new QPushButton(this);
    openButton->setIcon(QIcon(":/images/open.png"));

    DragButton *starButton = new DragButton(this);
    starButton->setIcon(QIcon(":/images/star.png"));
    starButton->setStyleSheet("background-color:red;padding:6px");

    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("Enter text here...");
    textEdit->setMaximumSize(100, 30);

    copyPaste = new CopyPaste(textEdit, this);

    connect(copyButton, &QPushButton::clicked, copyPaste, &CopyPaste::copy);
    connect(cutButton, &QPushButton::clicked, copyPaste, &CopyPaste::cut);
    connect(pasteButton, &QPushButton::clicked, copyPaste, &CopyPaste::paste);

    connect(rectButton, &QPushButton::clicked, [=]() {
        canvas->setTool(PaintCanvas::Rect);
        statusBar()->showMessage("Current tool: Rect");
    });

    connect(penButton, &QPushButton::clicked, [=]() {
        canvas->setTool(PaintCanvas::Pen);
        statusBar()->showMessage("Current tool: Pen");
    });

    connect(ellipseButton, &QPushButton::clicked, [=]() {
        canvas->setTool(PaintCanvas::Ellipse);
        statusBar()->showMessage("Current tool: Ellipse");
    });

    connect(eraserButton, &QPushButton::clicked, [=]() {
        canvas->setTool(PaintCanvas::Eraser);
        statusBar()->showMessage("Current tool: Eraser");
    });

    connect(copyButton, &QPushButton::clicked, [=]() {
        statusBar()->showMessage("Current tool: Copy");
    });

    connect(cutButton, &QPushButton::clicked, [=]() {
        statusBar()->showMessage("Current tool: Cut");
    });

    connect(pasteButton, &QPushButton::clicked, [=]() {
        statusBar()->showMessage("Current tool: Paste");
    });

    connect(redoButton, &QPushButton::clicked, [=]() {
        statusBar()->showMessage("Current tool: Redo");
    });

    connect(undoButton, &QPushButton::clicked, [=]() {
        statusBar()->showMessage("Current tool: Undo");
    });

    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(penWidthChanged(int)));
    connect(penColorButton, SIGNAL(clicked()), this, SLOT(changePenColor()));
    connect(fillColorButton, SIGNAL(clicked()), this, SLOT(changeFillColor()));
    connect(fillCheckBox, SIGNAL(clicked()), this, SLOT(changeFillProperty()));

    ui->mainToolBar->addWidget(penWidthLabel);
    ui->mainToolBar->addWidget(penWidthSpinBox);
    ui->mainToolBar->addWidget(penColorLabel);
    ui->mainToolBar->addWidget(penColorButton);
    ui->mainToolBar->addWidget(fillColorLabel);
    ui->mainToolBar->addWidget(fillColorButton);
    ui->mainToolBar->addWidget(fillCheckBox);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(penButton);
    ui->mainToolBar->addWidget(rectButton);
    ui->mainToolBar->addWidget(ellipseButton);
    ui->mainToolBar->addWidget(eraserButton);
    ui->mainToolBar->addWidget(starButton);
    ui->mainToolBar->addWidget(copyButton);
    ui->mainToolBar->addWidget(pasteButton);
    ui->mainToolBar->addWidget(cutButton);
    ui->mainToolBar->addWidget(redoButton);
    ui->mainToolBar->addWidget(undoButton);
    ui->mainToolBar->addWidget(textEdit);
    ui->mainToolBar->addWidget(saveButton);
    ui->mainToolBar->addWidget(openButton);
    ui->mainToolBar->addWidget(closeButton);

    QString css = QString("background-color: %1").arg(canvas->getPenColor().name());
    penColorButton->setStyleSheet(css);

    css = QString("background-color: %1").arg(canvas->getFillColor().name());
    fillColorButton->setStyleSheet(css);

    redoUndo = new RedoUndo(this);

    connect(redoButton, &QPushButton::clicked, [=]() {
        if (redoUndo->canRedo()) {
            QImage redoImage = redoUndo->redo();
            canvas->setImage(redoImage);
            statusBar()->showMessage("Redo");
        }
    });

    connect(undoButton, &QPushButton::clicked, [=]() {
        if (redoUndo->canUndo()) {
            QImage undoImage = redoUndo->undo();
            canvas->setImage(undoImage);
            statusBar()->showMessage("Undo");
        }
    });

    connect(canvas, &PaintCanvas::imageChanged, this, &MainWindow::saveState);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeFile);
}

/**
 * @brief Destroys the MainWindow object.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Slot to handle pen width changes.
 * @param width The new pen width.
 */
void MainWindow::penWidthChanged(int width)
{
    canvas->setPenWidth(width);
}

/**
 * @brief Slot to handle pen color changes.
 */
void MainWindow::changePenColor()
{
    QColor color = QColorDialog::getColor(canvas->getPenColor());
    if (color.isValid()) {
        canvas->setPenColor(color);
        QString css = QString("background-color: %1").arg(color.name());
        penColorButton->setStyleSheet(css);
    }
}

/**
 * @brief Slot to handle fill color changes.
 */
void MainWindow::changeFillColor()
{
    QColor color = QColorDialog::getColor(canvas->getPenColor());
    if (color.isValid()) {
        canvas->setFillColor(color);
        QString css = QString("background-color: %1").arg(color.name());
        fillColorButton->setStyleSheet(css);
    }
}

/**
 * @brief Slot to handle fill property changes.
 */
void MainWindow::changeFillProperty()
{
    canvas->setFill(fillCheckBox->isChecked());
}

/**
 * @brief Saves the current state of the canvas.
 */
void MainWindow::saveState()
{
    redoUndo->addState(canvas->getImage());
}

/**
 * @brief Handles drop events.
 * @param event The drop event.
 */
void MainWindow::dropEvent(QDropEvent *event)
{
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    QLabel *star = new QLabel(this);
    star->setPixmap(QPixmap(":/images/star.png"));
    star->show();
    star->setMinimumHeight(70);
    star->move(event->position().toPoint() - offset);

    qDebug() << "ok drop";
}

/**
 * @brief Handles drag enter events.
 * @param event The drag enter event.
 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "ok drag";
    event->accept();
    event->acceptProposedAction();
}

/**
 * @brief Opens a file and loads its content into the canvas.
 */
void MainWindow::openFile()
{
    QString fileName = fileHandler.getOpenFileName(this, tr("Open File"));
    if (!fileName.isEmpty() && fileHandler.openFile(fileName)) {
        QString content = fileHandler.readFile();
        canvas->setImage(QImage(content));
        statusBar()->showMessage("File Opened: " + fileName);
    }
}

/**
 * @brief Saves the current canvas content to a file.
 */
void MainWindow::saveFile()
{
    QString fileName = fileHandler.getSaveFileName(this, tr("Save File"));
    if (!fileName.isEmpty()) {
        QImage image = canvas->getImage();
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG");
        QString content = byteArray.toBase64();

        if (fileHandler.saveFile(fileName, content)) {
            statusBar()->showMessage("File Saved: " + fileName);
        }
    }
}

/**
 * @brief Closes the current file.
 */
void MainWindow::closeFile()
{
    statusBar()->showMessage("File Closed");
}

/**
 * @brief Creates the application menus.
 */
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
}

/**
 * @brief Slot to handle the "Programmeurs" action.
 */
void MainWindow::on_actionProgrammeurs_triggered()
{
    QDialog *diag = new QDialog();
    QLabel *prog = new QLabel();
    prog->setText("Programme de : Soufiani ABOUDOU, Mouhsine CHRINBOU, Djamel AOUAM");
    prog->setParent(diag);
    diag->show();
}
