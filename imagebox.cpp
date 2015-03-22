#include "imagebox.h"
#include <QFrame>
#include <QPalette>

ImageBox::ImageBox(QWidget *parent) :
    QLabel(parent)
{
}

ImageBox::ImageBox(QString filename_, QPixmap pixmap_, int pos_, QWidget *parent) :
    QLabel(parent), filename(filename_), pixmap(pixmap_), pos(pos_)
{
    if(pixmap_.isNull())
        return;
    this->setPixmap(pixmap_.scaled(150,150,Qt::KeepAspectRatio));
    this->setMaximumHeight(150);
    this->setMaximumWidth(150);
    this->setMinimumHeight(150);
    this->setMinimumWidth(150);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("background-color: grey; border: 1px solid black ;");
}

void ImageBox::mousePressEvent(QMouseEvent *)
{
    emit selected(pos/5, pos%5);
}

QString ImageBox::getFilename()
{
    return filename;
}

QPixmap ImageBox::getPixmap()
{
    return pixmap;
}

int ImageBox::getPos()
{
    return pos;
}

void ImageBox::movebackward()
{
    pos--;
}

void ImageBox::moveforward()
{
    pos++;
}

void ImageBox::setPos(int pos_)
{
    pos = pos_;
}

