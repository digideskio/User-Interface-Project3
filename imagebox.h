#ifndef IMAGEBOX_H
#define IMAGEBOX_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QPalette>


class ImageBox : public QLabel
{
    Q_OBJECT
public:
    ImageBox(QWidget* parent = 0);
    ImageBox(QString filename_, QPixmap pixmap_, int pos_, QWidget* parent);
    QString getFilename();
    void moveforward();
    void movebackward();
    QPixmap getPixmap();
    int getPos();
    void setPos(int pos_);

private:
    QString filename;
    QPixmap pixmap;
    int pos;

signals:
    void selected(int row, int column);

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // IMAGEBOX_H
