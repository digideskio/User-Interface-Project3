#ifndef COMMANDDELETE_H
#define COMMANDDELETE_H

#include <QUndoCommand>
#include <QList>
#include <QString>

#include "boximage.h"

class commandDelete : public QUndoCommand
{
public:
    commandDelete(BoxImage *box_, QList<ImageBox*> *imageList_, int pos_, QUndoCommand *parent = 0);
    void undo();
    void redo();
private:
    BoxImage *box;
    QList<ImageBox*> *imageList;
    int pos;
};

#endif // COMMANDDELETE_H

