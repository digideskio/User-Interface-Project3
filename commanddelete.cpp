#include "commanddelete.h"
#include "boximage.h"
#include "imagebox.h"
#include <iostream>
commandDelete::commandDelete(BoxImage *box_, QList<ImageBox*> *imageList_, int pos_, QUndoCommand *parent) :
    QUndoCommand(parent), box(box_), imageList(imageList_), pos(pos_)
{
}

void commandDelete::undo(){
    QList<ImageBox*> *storeimageList = new QList<ImageBox*>;
    for(int i=0; i<imageList->size(); i++){
        ImageBox *temp = new ImageBox(imageList->at(i)->getFilename(), imageList->at(i)->getPixmap(), imageList->at(i)->getPos(), 0);
        storeimageList->append(temp);
    }
    for(int i=0; i<imageList->size(); i++){
        box->addImageBox(imageList->at(i), pos+i);
    }
    imageList = storeimageList;
    if(box->imageNum > 0)
        emit box->enableDeleteAll(true);
}

void commandDelete::redo(){
    QList<ImageBox*> *storeimageList = new QList<ImageBox*>;
    for(int i=0; i<imageList->size(); i++){
        ImageBox *temp = new ImageBox(imageList->at(i)->getFilename(), imageList->at(i)->getPixmap(), imageList->at(i)->getPos(), 0);
        storeimageList->append(temp);
    }
    for(int i=0; i<imageList->size(); i++){
        box->removeImageBox(pos);
    }
    imageList = storeimageList;
    emit box->enableDeleteOne(false);
    emit box->enableCopy(false);
    emit box->enableCut(false);
    if(box->imageNum == 0){
        emit box->enableDeleteAll(false);
    }
}

