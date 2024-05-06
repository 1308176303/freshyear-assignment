#include "bullet.h"

Bullet::Bullet(QObject *parent)
{
    mObjectType=GameObject::OT_BulletPlayer;
}
Bullet::Bullet(QPoint _pos, QPixmap _pixmap, int _type)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->mBulletType=_type;
    mSpeed=6;

}

void Bullet::BulletMove(QPoint _dir)
{
    this->moveBy(_dir.x()*mSpeed,_dir.y()*mSpeed);
}

void Bullet::Init(QPoint _pos,QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);

    this->setScale(0.5);//缩放
    this->setX(this->x()-this->scale()*pixmap().width()/2);
}
