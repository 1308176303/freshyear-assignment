#ifndef PLANE_H
#define PLANE_H

#include "gameobjectpool.h"

class Plane : public GameObjectPool
{

public:
    explicit Plane(QObject *parent = nullptr);

    float MoveSpeed()
    {
        return mMoveSpeed;
    }

protected:
    float mMoveSpeed;
    int mShootSpeed;

};

#endif // PLANE_H
