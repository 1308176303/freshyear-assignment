#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

class PlayerBullet : public Bullet
{

public:
    explicit PlayerBullet(QObject *parent = nullptr);
};

#endif // PLAYERBULLET_H
