#include "boximage.h"
#include "commandadd.h"
#include "commanddelete.h"
#include "imagebox.h"
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QLayoutItem>
#include <QApplication>
#include <iostream>

using namespace std;

BoxImage::BoxImage(QWidget* parent) : QWidget(parent)
{
    BoxImage::layout = new QGridLayout();
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    BoxImage::imageNum = 0;
    this->setLayout(layout);
    undoStack = new QUndoStack();
    BoxImage::totalImageBox = new QList<ImageBox*>;
    clipBoard = QApplication::clipboard();
    emit enableDeleteAll(false);
}

BoxImage::~BoxImage()
{}

QGridLayout* BoxImage::getLayout()
{
    return layout;
}

void BoxImage::addImageBox(ImageBox *label, int pos)
{
    if(label->getPixmap().isNull())
        return;
    label->setPos(pos);
    connect(label, SIGNAL(selected(int ,int)), this, SLOT(selectImageInfo(int,int)));
    for(int i=pos; i<imageNum; i++){
            QLayoutItem *current = layout->itemAtPosition(i/5, i%5);
            QLayoutItem *temp = layout->itemAtPosition(i/5, i%5);
            ImageBox *tempImage = static_cast<ImageBox*>(temp->widget());
            //currentImage->moveforward();
            //QLayoutItem *next = layout->itemAtPosition((i+1)/5, (i+1)%5);
            //ImageBox *nextImage = static_cast<ImageBox*>(next->widget());
            tempImage->moveforward();
            //layout->addWidget(currentImage, (i+1)/5, (i+1)%5);
            layout->addWidget(tempImage, (i+1)/5, (i+1)%5);
            layout->removeItem(current);
    }
    BoxImage::layout->addWidget(label, pos/5, pos%5);
    totalImageBox->insert(pos, label);
    BoxImage::imageNum++;
}

void BoxImage::removeImageBox(int pos)
{
        QLayoutItem *item = layout->itemAtPosition(pos/5, pos%5);
        layout->removeItem(item);
        totalImageBox->removeAt(pos);
        delete static_cast<ImageBox*>(item->widget());
        imageNum--;
        for(int i=pos; i<imageNum; i++){
            QLayoutItem *temp = layout->itemAtPosition((i+1)/5, (i+1)%5);
            ImageBox *tempImage = static_cast<ImageBox*>(temp->widget());
            tempImage->movebackward();
            layout->removeItem(temp);
            layout->addWidget(tempImage, (i)/5, (i)%5);
        }
}

bool BoxImage::invalidImage(QString filename)
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setText("Image "+filename+" cannot be read. Continue or exit the application?");
    msgBox->addButton(tr("Continue"), QMessageBox::AcceptRole);
    msgBox->addButton(tr("Exit"), QMessageBox::RejectRole);
    int reply;
    reply = msgBox->exec();
    if(reply == QMessageBox::AcceptRole){
        return true;
    }else
        return false;
}

void BoxImage::slotAddImage()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg *.gif *jpeg)"));
    if(filename.isEmpty())
        return;
    QList<ImageBox *> *imageList = new QList<ImageBox*>;
    QPixmap image(filename, 0, Qt::AutoColor);
    ImageBox *imageBox = new ImageBox(filename, image, -1, 0);
    imageList->append(imageBox);
    commandAdd *command = new commandAdd(this, imageList, imageNum, 0);
    undoStack->push(command);
    emit enableUndo(true);
}

void BoxImage::slotAddCollection()
{
    QString dirname = QFileDialog::getExistingDirectory(this, tr("Add Images from Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    if(dirname.isEmpty())
        return;
    QDir directory(dirname);
    QList<ImageBox *> *imageList = new QList<ImageBox*>;
    foreach (QString filename, directory.entryList(QDir::Files))
    {
        filename = dirname + "/" + filename;
        QPixmap image(filename, 0, Qt::AutoColor);
        ImageBox *imageBox = new ImageBox(filename, image, -1, 0);
        imageList->append(imageBox);
    }
    commandAdd *command = new commandAdd(this, imageList, imageNum, 0);
    undoStack->push(command);
    emit enableUndo(true);
}

void BoxImage::slotDeleteAllImages()
{
    validSelect = false;
    QList<ImageBox*> *imageList = new QList<ImageBox*>;
    imageList->append(*totalImageBox);
    commandDelete *command = new commandDelete(this, imageList, 0, 0);
    undoStack->push(command);
    emit enableUndo(true);
}

void BoxImage::slotDeleteImage()
{
    validSelect = false;
    emit enableDeleteOne(false);
    emit enableCopy(false);
    QList<ImageBox*> *imageList = new QList<ImageBox*>;
    QLayoutItem *temp = layout->itemAtPosition(selectRow, selectCol);
    ImageBox *imageBox = static_cast<ImageBox*>(temp->widget());
    imageList->append(imageBox);
    commandDelete *command = new commandDelete(this, imageList, selectRow*5+selectCol, 0);
    undoStack->push(command);
    emit enableUndo(true);
}

void BoxImage::selectImageInfo(int row, int col)
{
    if(validSelect){
        QLayoutItem *temp = layout->itemAtPosition(selectRow, selectCol);
        temp->widget()->setStyleSheet("background-color: grey; border: 1px solid black ;");
    }
    validSelect = true;
    selectRow = row;
    selectCol = col;
    QLayoutItem *temp = layout->itemAtPosition(selectRow, selectCol);
    temp->widget()->setStyleSheet("background-color: grey; border: 1px solid red ;");
    emit enableDeleteOne(true);
    emit enableCopy(true);
    emit enableCut(true);
}

void BoxImage::slotCopy()
{
    if(validSelect){
        QLayoutItem *temp = layout->itemAtPosition(selectRow, selectCol);
        ImageBox *imageBox = static_cast<ImageBox*>(temp->widget());
        clipBoard->clear();
        BoxImage::clipBoard->setPixmap(imageBox->getPixmap());
        emit enablePaste(true);
        emit enableUndo(true);
    }
}

void BoxImage::slotCut()
{
    if(validSelect){
        validSelect = false;
        QLayoutItem *temp = layout->itemAtPosition(selectRow, selectCol);
        ImageBox *imageBox = static_cast<ImageBox*>(temp->widget());
        clipBoard->clear();
        BoxImage::clipBoard->setPixmap(imageBox->getPixmap());
        QList<ImageBox*> *imageList = new QList<ImageBox*>;
        imageList->append(imageBox);
        commandDelete *command = new commandDelete(this, imageList, selectRow*5+selectCol, 0);
        undoStack->push(command);
        emit enablePaste(true);
        emit enableUndo(true);
        emit enableDeleteOne(false);
        emit enableCopy(false);
        emit enableCut(false);
    }
}

void BoxImage::slotPaste()
{
    if(!validSelect){
        QMessageBox *msgBox = new QMessageBox;
        msgBox->setText("Please select a proper place to paste the image");
        msgBox->exec();
    }else{
        QPixmap content=clipBoard->pixmap();
        ImageBox *imageBox = new ImageBox("", content, -1, 0);
        QList<ImageBox*> *imageList = new QList<ImageBox*>;
        imageList->append(imageBox);
        commandAdd *command = new commandAdd(this, imageList, selectRow*5+selectCol+1, 0);
        undoStack->push(command);
        emit enableUndo(true);
    }
}

void BoxImage::slotUndo()
{
    if(BoxImage::undoStack->canUndo()){
        undoStack->undo();
        if(!undoStack->canUndo())
            emit enableUndo(false);
        emit enableRedo(true);
    }
}

void BoxImage::slotRedo()
{
    if(BoxImage::undoStack->canRedo()){
        undoStack->redo();
        if(!undoStack->canRedo())
            emit enableRedo(false);
        emit enableUndo(true);
    }
}

QUndoStack* BoxImage::getUndoStack()
{
    return undoStack;
}
