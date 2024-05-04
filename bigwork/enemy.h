#ifndef ENEMY_H
#define ENEMY_H

#include "plane.h"

class Enemy : public Plane
{

public:
    Enemy(QPoint _pos,QPixmap _pixmap);

    void EnemyMove(QPoint _dir = QPoint(0,1));
};

#endif // ENEMY_H
