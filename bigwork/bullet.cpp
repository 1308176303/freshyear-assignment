#include "bullet.h"

Bullet::Bullet(QPoint _pos, QPixmap _pixmap, int _type)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->mBulletType=_type;
    mSpeed=6;

    this->setScale(0.25);//缩放
    this->setX(this->x()-this->scale()*pixmap().width()/2);
}

void Bullet::BulletMove(QPoint _dir)
{
    this->moveBy(_dir.x()*mSpeed,_dir.y()*mSpeed);
}
