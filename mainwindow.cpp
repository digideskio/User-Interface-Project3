#include "mainwindow.h"
#include "boximage.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplitter>
#include <QListView>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QShortcut>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
    splitter = new QSplitter();
    box = new BoxImage(splitter);
    Init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::Init()
{
    QMenu *fileMenu;
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction("New", this, SLOT(InvalidItem()), 0);
     fileMenu->addAction("Open", this, SLOT(InvalidItem()), 0);
     fileMenu->addSeparator();
     fileMenu->addAction("Save", this, SLOT(InvalidItem()), 0);
     fileMenu->addAction("Save as", this, SLOT(InvalidItem()), 0);
     fileMenu->addSeparator();
     fileMenu->addAction("Quit", this, SLOT(quit()), 0);

     QMenu *editMenu;
     editMenu = menuBar()->addMenu(tr("&Edit"));

     //Undo & Redo
     QAction *actionUndo = editMenu->addAction("Undo", box, SLOT(slotUndo()), 0);
     QAction *actionRedo = editMenu->addAction("Redo", box, SLOT(slotRedo()), 0);
     actionUndo->setShortcut(QKeySequence::Undo);
     actionRedo->setShortcut(QKeySequence::Redo);
     actionUndo->setEnabled(false);
     actionRedo->setEnabled(false);
     connect(box, SIGNAL(enableUndo(bool)), actionUndo, SLOT(setEnabled(bool)));
     connect(box, SIGNAL(enableRedo(bool)), actionRedo, SLOT(setEnabled(bool)));
     editMenu->addSeparator();

     //Cut & Copy & Paste
     QAction *actionCut = editMenu->addAction("Cut ", box, SLOT(slotCut()), 0);
     QAction *actionCopy = editMenu->addAction("Copy ", box, SLOT(slotCopy()), 0);
     QAction *actionPaste = editMenu->addAction("Paste ", box, SLOT(slotPaste()), 0);
     actionCut->setShortcut(QKeySequence::Cut);
     actionCopy->setShortcut(QKeySequence::Copy);
     actionPaste->setShortcut(QKeySequence::Paste);
     actionCut->setEnabled(false);
     actionCopy->setEnabled(false);
     actionPaste->setEnabled(false);
     connect(box, SIGNAL(enableCut(bool)), actionCut, SLOT(setEnabled(bool)));
     connect(box, SIGNAL(enableCopy(bool)), actionCopy, SLOT(setEnabled(bool)));
     connect(box, SIGNAL(enablePaste(bool)), actionPaste, SLOT(setEnabled(bool)));
     editMenu->addSeparator();

     //Operation Function
     QAction *actionAddCollection = editMenu->addAction("Add Collection", box, SLOT(slotAddCollection()), 0);
     QAction *actionAddImage =  editMenu->addAction("Add Image", box, SLOT(slotAddImage()), 0);
     QAction *actionDeleteImage = editMenu->addAction("Remove Image", box, SLOT(slotDeleteImage()), 0);
     QAction *actionDeleteAllImages = editMenu->addAction("Remove All Images", box, SLOT(slotDeleteAllImages()), 0);
     actionDeleteImage->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_D));
     actionAddCollection->setShortcut(QKeySequence::Open);
     actionAddImage->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_O));
     actionDeleteAllImages->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));
     actionDeleteAllImages->setEnabled(false);
     actionDeleteImage->setEnabled(false);
     connect(box, SIGNAL(enableDeleteOne(bool)), actionDeleteImage, SLOT(setEnabled(bool)));
     connect(box, SIGNAL(enableDeleteAll(bool)), actionDeleteAllImages, SLOT(setEnabled(bool)));

     //Buttons
     QPushButton *AddCollection = new QPushButton("Add Collection", 0);
     QPushButton *AddImage = new QPushButton("Add Image", 0);
     QPushButton *DeleteImage = new QPushButton("Delete Selected Image", 0);
     QPushButton *DeleteAllImages = new QPushButton("Delete All Images", 0);
     connect(AddImage, SIGNAL(clicked()), box, SLOT(slotAddImage()));
     connect(AddCollection, SIGNAL(clicked()), box, SLOT(slotAddCollection()));
     connect(DeleteImage, SIGNAL(clicked()), box, SLOT(slotDeleteImage()));
     connect(DeleteAllImages, SIGNAL(clicked()), box, SLOT(slotDeleteAllImages()));
     connect(box, SIGNAL(enableDeleteOne(bool)), DeleteImage, SLOT(setEnabled(bool)));
     connect(box, SIGNAL(enableDeleteAll(bool)), DeleteAllImages, SLOT(setEnabled(bool)));
     DeleteAllImages->setEnabled(false);
     DeleteImage->setEnabled(false);

     QWidget *leftWidget = new QWidget(0);
     QBoxLayout *leftLayout = new QBoxLayout(QBoxLayout::TopToBottom, 0);
     AddCollection->setMinimumHeight(75);
     AddImage->setMinimumHeight(75);
     DeleteImage->setMinimumHeight(75);
     DeleteAllImages->setMinimumHeight(75);
     leftLayout->addWidget(AddCollection, 1, 0);
     leftLayout->addWidget(AddImage, 1, 0);
     leftLayout->addWidget(DeleteImage,1, 0);
     leftLayout->addWidget(DeleteAllImages, 1, 0);
     leftLayout->addWidget(new QWidget());
     leftLayout->setSpacing(4);
     leftWidget->setLayout(leftLayout);
     leftWidget->resize(150, 500);
     splitter->addWidget(leftWidget);
     QScrollArea *right = new QScrollArea();
     right->setWidget(box);
     right->setWidgetResizable(true);
     right->setMaximumWidth(780);
     right->resize(780, 500);
     splitter->addWidget(right);
     setCentralWidget(splitter);
     this->resize(950, 500);
}


void MainWindow::InvalidItem()
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setText("Not implemented yet");
    msgBox->exec();
}
void MainWindow::quit()
{
    exit(0);
}
