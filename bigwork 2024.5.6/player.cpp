#include "player.h"

Player::Player()
{
    this->setPixmap(QPixmap(":/img/img/MyPlane1.fw.png"));
    this->setPos(256,500);

    mMoveSpeed=5;
    mShootSpeed=500;//0.5秒射一个
}
