#ifndef BOXIMAGE
#define BOXIMAGE

#include <QGridLayout>
#include <QScrollArea>
#include <QClipboard>
#include <QList>
#include "mainwindow.h"
#include "imagebox.h"
#include <QUndoStack>

using namespace std;

class BoxImage : public QWidget
{
    Q_OBJECT
public:
    BoxImage(QWidget* parent = 0);
    ~BoxImage();
    QGridLayout* getLayout();
    int imageNum;
    int selectRow;
    int selectCol;
    bool openImage(QString filename, int pos);
    void removeImageBox(int pos);
    bool invalidImage(QString filename);
    void addImageBox(ImageBox *label, int pos);
    QUndoStack* getUndoStack();

signals:
    void enableCut(bool);
    void enableCopy(bool);
    void enablePaste(bool);
    void enableDeleteOne(bool);
    void enableDeleteAll(bool);
    void enableUndo(bool);
    void enableRedo(bool);

private slots:
    void slotAddCollection();
    void slotAddImage();
    void slotDeleteAllImages();
    void slotDeleteImage();
    void slotCopy();
    void slotPaste();
    void slotCut();
    void slotUndo();
    void slotRedo();
    void selectImageInfo(int row, int col);

private:
    QGridLayout* layout;
    pair<int, int> selectedImage;
    QUndoStack *undoStack;
    QList<QString> *totalImage;
    QList<ImageBox*> *totalImageBox;
    bool validSelect;
    QClipboard *clipBoard;
};
#endif // BOXIMAGE

