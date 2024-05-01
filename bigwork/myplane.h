#ifndef MYPLANE_H
#define MYPLANE_H

#include <QObject>
#include<QGraphicsPixmapItem>

class MyPlane : public QGraphicsPixmapItem
{

public:
    MyPlane();
    float mMoveSpeed;
    int mShootSpeed;

};

#endif // MYPLANE_H
