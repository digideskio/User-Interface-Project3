#ifndef COMMANDADD_H
#define COMMANDADD_H

#include <QUndoCommand>
#include <QList>
#include <QString>

#include "boximage.h"

class commandAdd : public QUndoCommand
{
public:
    //explicit commandAdd(QUndoCommand *parent = 0);
    commandAdd(BoxImage *box_, QList<ImageBox*> *imageList_, int pos_, QUndoCommand *parent = 0);
    void undo();
    void redo();
    ~commandAdd();
private:
    BoxImage *box;
    QList<ImageBox*> *imageList;
    int pos;
};


#endif // COMMANDADD_H

