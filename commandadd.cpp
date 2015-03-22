#include "commandadd.h"
#include "boximage.h"
#include "imagebox.h"
#include <iostream>


commandAdd::commandAdd(BoxImage *box_, QList<ImageBox*> *imageList_, int pos_, QUndoCommand *parent) :
    QUndoCommand(parent), box(box_), imageList(imageList_), pos(pos_){
}

commandAdd::~commandAdd()
{
    for(int i=0; i<imageList->size(); i++){
        delete imageList->at(i);
    }
    delete imageList;
}

void commandAdd::redo()
{
    for(int i=0; i<imageList->size(); i++){
        if(!imageList->at(i)->getPixmap().isNull()){
            box->addImageBox(imageList->at(i), pos+i);
        }else{
            if(box->invalidImage(imageList->at(i)->getFilename())){
                imageList->removeAt(i);
                i--;
            }else{
                imageList->erase(imageList->begin()+i, imageList->end());
            }
        }
    }
    QList<ImageBox*> *storeimageList = new QList<ImageBox*>;
    for(int i=0; i<imageList->size(); i++){
        ImageBox *temp = new ImageBox(imageList->at(i)->getFilename(), imageList->at(i)->getPixmap(), imageList->at(i)->getPos(), 0);
        storeimageList->append(temp);
    }
    imageList = storeimageList;
    if(box->imageNum > 0)
        emit box->enableDeleteAll(true);
}

void commandAdd::undo()
{
    QList<ImageBox*> *storeimageList = new QList<ImageBox*>;
    for(int i=0; i<imageList->size(); i++){
        ImageBox *temp = new ImageBox(imageList->at(i)->getFilename(), imageList->at(i)->getPixmap(), imageList->at(i)->getPos(), 0);
        storeimageList->append(temp);
    }
    for(int i=0; i<imageList->size(); i++){
        box->removeImageBox(pos);
    }
    imageList = storeimageList;
    if(box->imageNum == 0){
        emit box->enableDeleteAll(false);
    }
    emit box->enableDeleteOne(false);
    emit box->enableCopy(false);
    emit box->enableCut(false);
}



