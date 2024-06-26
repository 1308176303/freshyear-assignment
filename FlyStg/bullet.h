﻿#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

class Bullet : public GameObject
{
public:
    //子弹类型
    enum BulletType
    {
        BT_Player,//我方
        TT_Enemy//敌方
    };
    explicit Bullet(QObject *parent = nullptr);
    Bullet(QPoint _pos,QPixmap _pixmap,int _type);

    //移动
    virtual void BulletMove(QPoint _dir=QPoint(0,-1));

    void Init(QPoint _pos,QPixmap _pixmap);

    ~Bullet()
    {
        qDebug() <<"子弹被释放";
    }
protected:
    int mBulletType;
    int mSpeed;

};

#endif // BULLET_H
