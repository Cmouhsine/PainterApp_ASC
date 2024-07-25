
// #include "mainwindow.h"
// #include "ui_mainwindow.h"
// #include <QLabel>
// #include <QSpinBox>
// #include <QColorDialog>
// #include <QMouseEvent>
// #include <QDrag>
// #include <QDragEnterEvent>
// #include <QDropEvent>
// #include <QDebug>
// #include <QMessageBox>
// #include <QMimeData>
// #include <QPixmap>
// #include <QHBoxLayout>
// #include <QGridLayout>
// #include <dragbutton.h>
// #include<QMenu>

// MainWindow::MainWindow(QWidget *parent) :
//     QMainWindow(parent),
//     ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);

//     QMenu *mFile =new QMenu();
//     mFile ->setTitle("File");
//     mFile ->setVisible(true);
//     mFile ->show();
//     ui->menuBar->addMenu(mFile);



//     canvas = new PaintCanvas(this);
//     setCentralWidget(canvas);

//     //Pen width
//     QLabel * penWidthLabel = new QLabel("Pen Width",this);
//     QSpinBox * penWidthSpinBox = new QSpinBox(this);
//     penWidthSpinBox->setValue(2);
//     penWidthSpinBox->setRange(1,15);

//     //Pen color
//     QLabel * penColorLabel = new QLabel("Pen Color",this);
//     penColorButton = new QPushButton(this);

//     //Fill Color
//     QLabel * fillColorLabel = new QLabel("Fill Color",this);
//     fillColorButton = new QPushButton(this);

//     //Fill
//     fillCheckBox = new QCheckBox("Fill Shape",this);


//     //Tool Buttons
//     QPushButton * rectButton = new QPushButton(this);
//     rectButton->setIcon(QIcon(":/images/rectangle.png"));

//     QPushButton * penButton = new QPushButton(this);
//     penButton->setIcon(QIcon(":/images/pen.png"));

//     QPushButton * ellipseButton = new QPushButton(this);
//     ellipseButton->setIcon(QIcon(":/images/circle.png"));


//     QPushButton * eraserButton = new QPushButton(this);
//     eraserButton->setIcon(QIcon(":/images/eraser.png"));

//     /*----------------------------------------------------------------------mch--------*/
//     QPushButton * copyButton = new QPushButton(this);
//     copyButton->setIcon(QIcon(":/images/copyIcon.png"));

//     QPushButton * pasteButton = new QPushButton(this);
//     pasteButton->setIcon(QIcon(":/images/pasteIcon.png"));

//     QPushButton * cutButton = new QPushButton(this);
//     cutButton->setIcon(QIcon(":/images/cutIcon.png"));

//     //------------------redo  undo ------------------
//     QPushButton * redoButton = new QPushButton(this);
//     redoButton->setIcon(QIcon(":/images/redoIcon.png"));

//     QPushButton * undoButton = new QPushButton(this);
//     undoButton->setIcon(QIcon(":/images/undoIcon.png"));
//     //------------------save close-----------------------------

//     QPushButton * saveButton= new DragButton(this);
//     saveButton->setIcon(QIcon(":/images/save.png"));

//     QPushButton * closeButton= new DragButton(this);
//     closeButton->setIcon(QIcon(":/images/close.png"));

//     QPushButton * openButton= new DragButton(this);
//     openButton->setIcon(QIcon(":/images/open.png"));
//     //---------------------------------soufiani----

//     DragButton * starButton = new DragButton(this);
//     starButton->setIcon(QIcon(":/images/star.png"));

//     //--------------------------------end soufiani-----------
//     //------------------------------------------------------

//     // Initialize the text editor
//     textEdit = new QTextEdit(this);
//     textEdit->setPlaceholderText("Enter text here...");
//     textEdit->setMaximumSize(100, 30); // Set the minimum size to 200x50 pixels

//     copyPaste = new CopyPaste(textEdit, this);

//     connect(copyButton, &QPushButton::clicked, copyPaste, &CopyPaste::copy);
//     connect(cutButton, &QPushButton::clicked, copyPaste, &CopyPaste::cut);
//     connect(pasteButton, &QPushButton::clicked, copyPaste, &CopyPaste::paste);


//     /*----------------------------------------------------------------------mch--------*/


//     connect(rectButton,&QPushButton::clicked,[=](){
//         //Set current tool to rect
//         canvas->setTool(PaintCanvas::Rect);
//         statusBar()->showMessage("Current tool : Rect");
//     });

//     connect(penButton,&QPushButton::clicked,[=](){
//         //Set current tool to rect
//         canvas->setTool(PaintCanvas::Pen);
//         statusBar()->showMessage("Current tool : Pen");

//     });


//     connect(ellipseButton,&QPushButton::clicked,[=](){
//         //Set current tool to rect
//         canvas->setTool(PaintCanvas::Ellipse);
//         statusBar()->showMessage("Current tool : Ellipse");

//     });


//     connect(eraserButton,&QPushButton::clicked,[=](){
//         //Set current tool to rect
//         canvas->setTool(PaintCanvas::Eraser);
//         statusBar()->showMessage("Current tool : Eraser");

//     });

//     /*----------------------------------------------------------------------mch--------*/
//     connect(copyButton, &QPushButton::clicked, [=]() {
//         //canvas->setTool(PaintCanvas::Copy);
//         statusBar()->showMessage("Current tool: Copy");
//     });

//     connect(cutButton, &QPushButton::clicked, [=]() {
//         //canvas->setTool(PaintCanvas::Cut);
//         statusBar()->showMessage("Current tool: Cut");
//     });

//     connect(pasteButton, &QPushButton::clicked, [=]() {
//         //canvas->setTool(PaintCanvas::Paste);
//         statusBar()->showMessage("Current tool: Paste");
//     });
//     //----------------------redo undo ----------------------------
//     connect(redoButton, &QPushButton::clicked, [=]() {
//         //canvas->setTool(PaintCanvas::Cut);
//         statusBar()->showMessage("Current tool: redo");
//     });

//     connect(undoButton, &QPushButton::clicked, [=]() {
//         //canvas->setTool(PaintCanvas::Paste);
//         statusBar()->showMessage("Current tool: undo");
//     });


//     /*------------------------------------------------------------------------mch--------*/


//     //Slots connections
//     connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(penWidthChanged(int)));
//     connect(penColorButton, SIGNAL(clicked()), this, SLOT(changePenColor()));
//     connect(fillColorButton, SIGNAL(clicked()), this, SLOT(changeFillColor()));
//     connect(fillCheckBox, SIGNAL(clicked()), this, SLOT(changeFillProperty()));


//     ui->mainToolBar->addWidget(penWidthLabel);
//     ui->mainToolBar->addWidget(penWidthSpinBox);
//     ui->mainToolBar->addWidget(penColorLabel);
//     ui->mainToolBar->addWidget(penColorButton);
//     ui->mainToolBar->addWidget(fillColorLabel);
//     ui->mainToolBar->addWidget(fillColorButton);
//     ui->mainToolBar->addWidget(fillCheckBox);
//     ui->mainToolBar->addSeparator();
//     ui->mainToolBar->addWidget(penButton);
//     ui->mainToolBar->addWidget(rectButton);
//     ui->mainToolBar->addWidget(ellipseButton);
//     ui->mainToolBar->addWidget(eraserButton);
//     /*----------------------------------------------------------------------mch--------*/
//     ui->mainToolBar->addWidget(copyButton);
//     ui->mainToolBar->addWidget(pasteButton);
//     ui->mainToolBar->addWidget(cutButton);
//     ui->mainToolBar->addWidget(redoButton);
//     ui->mainToolBar->addWidget(undoButton);

//     ui->mainToolBar->addWidget(textEdit);  // Add the text editor to the toolbar

//      ui->mainToolBar->addWidget(starButton);






//     /*----------------------------------------------------------------------mch--------*/

//     QString css = QString("background-color : %1").arg(canvas->getPenColor().name());
//     penColorButton->setStyleSheet(css);

//     css = QString("background-color : %1").arg(canvas->getFillColor().name());
//     fillColorButton->setStyleSheet(css);

//     //----------------------------------------------------------------------------------------------
//     // In the MainWindow constructor:
//     redoUndo = new RedoUndo(this);

//     connect(redoButton, &QPushButton::clicked, [=]() {
//         if (redoUndo->canRedo()) {
//             QImage redoImage = redoUndo->redo();
//             canvas->setImage(redoImage);  // Assuming setImage updates the canvas with the given image
//             statusBar()->showMessage("Redo");
//         }
//     });

//     connect(undoButton, &QPushButton::clicked, [=]() {
//         if (redoUndo->canUndo()) {
//             QImage undoImage = redoUndo->undo();
//             canvas->setImage(undoImage);  // Assuming setImage updates the canvas with the given image
//             statusBar()->showMessage("Undo");
//         }
//     });

//     connect(canvas, &PaintCanvas::imageChanged, this, &MainWindow::saveState);


// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

// void MainWindow::penWidthChanged(int width)
// {
//     canvas->setPenWidth(width);
// }

// void MainWindow::changePenColor()
// {
//     QColor color = QColorDialog::getColor(canvas->getPenColor());
//     if(color.isValid()){
//         canvas->setPenColor(color);
//         QString css = QString("background-color : %1").arg(color.name());
//         penColorButton->setStyleSheet(css);
//     }

// }

// void MainWindow::changeFillColor()
// {
//     QColor color = QColorDialog::getColor(canvas->getPenColor());
//     if(color.isValid()){
//         canvas->setFillColor(color);
//         QString css = QString("background-color : %1").arg(color.name());
//         fillColorButton->setStyleSheet(css);
//     }

// }

// void MainWindow::changeFillProperty()
// {
//     canvas->setFill(fillCheckBox->isChecked());
// }
// void MainWindow::saveState()
// {
//     redoUndo->addState(canvas->getImage());  // Assuming getImage returns the current image of the canvas
// }


// void MainWindow::dropEvent(QDropEvent *event)
// {
//     // event->accept();
//     // event->acceptProposedAction();

//     //qDebug()<<event->position().toPoint();


//     //qDebug() << event->pos();
//     // qDebug() << event->source();
//     QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
//     QDataStream dataStream(&itemData, QIODevice::ReadOnly);


//     QPixmap pixmap;
//     QPoint offset;
//     dataStream >> pixmap >> offset;




//     qDebug()<< "offset : " << offset;

//     QLabel *star= new QLabel(this);
//     star->setPixmap(QPixmap(":/images/star.png"));

//     star->show();

//     star->setMinimumHeight(70);
//     star->move(event->position().toPoint() - offset);



//     qDebug() << "ok drop";


// }


// void MainWindow::dragEnterEvent(QDragEnterEvent *event)
// {
//     qDebug() << "ok drag";
//     event->accept();
//     event->acceptProposedAction();
//     /* if(canvas->geometry().contains(event->pos()))
//     {
//        // canvas->setText("Dans le drop");
//         ui->dropObjet->setStyleSheet("background-color : black; color : white;");
//         event->acceptProposedAction();
//     }
//     else
//     {
//         ui->dropObjet->setStyleSheet("background-color : blue; color : white;");
//     }
// */

// }

// void MainWindow::createMenus()
// {
//     fileMenu = menuBar()->addMenu(tr("&File"));
// }


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
#include<QBuffer>
#include <QDialog>

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

    /*----------------------------------------------------------------------mch--------*/
    QPushButton *copyButton = new QPushButton(this);
    copyButton->setIcon(QIcon(":/images/copyIcon.png"));

    QPushButton *pasteButton = new QPushButton(this);
    pasteButton->setIcon(QIcon(":/images/pasteIcon.png"));

    QPushButton *cutButton = new QPushButton(this);
    cutButton->setIcon(QIcon(":/images/cutIcon.png"));

    //------------------redo undo------------------
    QPushButton *redoButton = new QPushButton(this);
    redoButton->setIcon(QIcon(":/images/redoIcon.png"));

    QPushButton *undoButton = new QPushButton(this);
    undoButton->setIcon(QIcon(":/images/undoIcon.png"));

    //------------------save close-----------------------------

    QPushButton *saveButton = new QPushButton(this);
    saveButton->setIcon(QIcon(":/images/save.png"));

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(QIcon(":/images/close.png"));

    QPushButton *openButton = new QPushButton(this);
    openButton->setIcon(QIcon(":/images/open.png"));

    //-----------------------------------------------------------------------------------------------------sf----

    DragButton *starButton = new DragButton(this);

    starButton->setIcon(QIcon(":/images/star.png"));
    starButton->setStyleSheet("background-color:red;padding:6px");

    //---------------------------------------------------------------------------------------------------sf----
    //------------------------------------------------------

    // Initialize the text editor
    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("Enter text here...");
    textEdit->setMaximumSize(100, 30); // Set the minimum size to 200x50 pixels

    copyPaste = new CopyPaste(textEdit, this);

    connect(copyButton, &QPushButton::clicked, copyPaste, &CopyPaste::copy);
    connect(cutButton, &QPushButton::clicked, copyPaste, &CopyPaste::cut);
    connect(pasteButton, &QPushButton::clicked, copyPaste, &CopyPaste::paste);

    /*----------------------------------------------------------------------mch--------*/

    connect(rectButton, &QPushButton::clicked, [=]() {
        // Set current tool to rect
        canvas->setTool(PaintCanvas::Rect);
        statusBar()->showMessage("Current tool: Rect");
    });

    connect(penButton, &QPushButton::clicked, [=]() {
        // Set current tool to pen
        canvas->setTool(PaintCanvas::Pen);
        statusBar()->showMessage("Current tool: Pen");
    });

    connect(ellipseButton, &QPushButton::clicked, [=]() {
        // Set current tool to ellipse
        canvas->setTool(PaintCanvas::Ellipse);
        statusBar()->showMessage("Current tool: Ellipse");
    });

    connect(eraserButton, &QPushButton::clicked, [=]() {
        // Set current tool to eraser
        canvas->setTool(PaintCanvas::Eraser);
        statusBar()->showMessage("Current tool: Eraser");
    });

    /*----------------------------------------------------------------------mch--------*/
    connect(copyButton, &QPushButton::clicked, [=]() {
        // canvas->setTool(PaintCanvas::Copy);
        statusBar()->showMessage("Current tool: Copy");
    });

    connect(cutButton, &QPushButton::clicked, [=]() {
        // canvas->setTool(PaintCanvas::Cut);
        statusBar()->showMessage("Current tool: Cut");
    });

    connect(pasteButton, &QPushButton::clicked, [=]() {
        // canvas->setTool(PaintCanvas::Paste);
        statusBar()->showMessage("Current tool: Paste");
    });

    //----------------------redo undo----------------------------
    connect(redoButton, &QPushButton::clicked, [=]() {
        // canvas->setTool(PaintCanvas::Cut);
        statusBar()->showMessage("Current tool: Redo");
    });

    connect(undoButton, &QPushButton::clicked, [=]() {
        // canvas->setTool(PaintCanvas::Paste);
        statusBar()->showMessage("Current tool: Undo");
    });

    /*------------------------------------------------------------------------mch--------*/

    // Slots connections
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


    //---------------------------------------------------------------------- sf-----------------------------

     ui->mainToolBar->addWidget(starButton);

    //--------------------------------------------------------------------- sf -----------------------------






    /*----------------------------------------------------------------------mch--------*/
    ui->mainToolBar->addWidget(copyButton);
    ui->mainToolBar->addWidget(pasteButton);
    ui->mainToolBar->addWidget(cutButton);
    ui->mainToolBar->addWidget(redoButton);
    ui->mainToolBar->addWidget(undoButton);

    ui->mainToolBar->addWidget(textEdit);  // Add the text editor to the toolbar


    ui->mainToolBar->addWidget(saveButton);
    ui->mainToolBar->addWidget(openButton);
    ui->mainToolBar->addWidget(closeButton);

    /*----------------------------------------------------------------------mch--------*/

    QString css = QString("background-color: %1").arg(canvas->getPenColor().name());
    penColorButton->setStyleSheet(css);

    css = QString("background-color: %1").arg(canvas->getFillColor().name());
    fillColorButton->setStyleSheet(css);

    // ----------------------------------------------------------------------------------------------
    // In the MainWindow constructor:
    redoUndo = new RedoUndo(this);

    connect(redoButton, &QPushButton::clicked, [=]() {
        if (redoUndo->canRedo()) {
            QImage redoImage = redoUndo->redo();
            canvas->setImage(redoImage);  // Assuming setImage updates the canvas with the given image
            statusBar()->showMessage("Redo");
        }
    });

    connect(undoButton, &QPushButton::clicked, [=]() {
        if (redoUndo->canUndo()) {
            QImage undoImage = redoUndo->undo();
            canvas->setImage(undoImage);  // Assuming setImage updates the canvas with the given image
            statusBar()->showMessage("Undo");
        }
    });

    connect(canvas, &PaintCanvas::imageChanged, this, &MainWindow::saveState);

    // Connect file buttons to their respective slots
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::penWidthChanged(int width)
{
    canvas->setPenWidth(width);
}

void MainWindow::changePenColor()
{
    QColor color = QColorDialog::getColor(canvas->getPenColor());
    if (color.isValid()) {
        canvas->setPenColor(color);
        QString css = QString("background-color: %1").arg(color.name());
        penColorButton->setStyleSheet(css);
    }
}

void MainWindow::changeFillColor()
{
    QColor color = QColorDialog::getColor(canvas->getPenColor());
    if (color.isValid()) {
        canvas->setFillColor(color);
        QString css = QString("background-color: %1").arg(color.name());
        fillColorButton->setStyleSheet(css);
    }
}

void MainWindow::changeFillProperty()
{
    canvas->setFill(fillCheckBox->isChecked());
}

void MainWindow::saveState()
{
    redoUndo->addState(canvas->getImage());  // Assuming getImage returns the current image of the canvas
}

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



//------------------------------------------------------------------------------------------------------sf----

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "ok drag";
    event->accept();
    event->acceptProposedAction();
}



//-----------------------------------------------------------------------------------sf----


void MainWindow::openFile()
{
    QString fileName = fileHandler.getOpenFileName(this, tr("Open File"));
    if (!fileName.isEmpty() && fileHandler.openFile(fileName)) {
        QString content = fileHandler.readFile();
        canvas->setImage(QImage(content)); // Assuming setImage updates the canvas with the given image content
        statusBar()->showMessage("File Opened: " + fileName);
    }
}

void MainWindow::saveFile()
{
    QString fileName = fileHandler.getSaveFileName(this, tr("Save File"));
    if (!fileName.isEmpty()) {
        QImage image = canvas->getImage(); // Assuming getImage returns the current image of the canvas
        // Convert QImage to QString
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG"); // Save the image as a PNG in a byte array
        QString content = byteArray.toBase64();

        if (fileHandler.saveFile(fileName, content)) {
            statusBar()->showMessage("File Saved: " + fileName);
        }
    }
}

void MainWindow::closeFile()
{
    //canvas->clear(); // Assuming clear method clears the canvas
    statusBar()->showMessage("File Closed");
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
}





//------------------------------------------------------------------------------------------------sf ------------------------------------------

void MainWindow::on_actionProgrammeurs_triggered()
{
    QDialog *diag = new QDialog();
    QLabel *prog = new QLabel();

    prog->setText(("Programme de : Soufiani ABOUDOU , Mouhsine CHRINBOU, Djamel AOUAM"));

    prog->setParent(diag);

    diag->show();
}


//------------------------------------------------------------------------------------------------sf ------------------------------------------
