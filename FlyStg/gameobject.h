#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QGraphicsPixmapItem>
#include<QDebug>

class GameObject : public QGraphicsPixmapItem
{
public:
    enum ObjectType
    {
        OT_BulletPlayer,
        OT_Enemy,
        OT_Player,
        OT_EnemyBullet
    };
    explicit GameObject(QObject *parent = nullptr);
    int GetType()
    {
        return mObjectType;
    }

    //回收
    void GameObjectDelete(QGraphicsScene* _scene);

    // static int createCount;
    ~GameObject()
    {
        //qDebug() <<"当前释放第"+QString::number(createCount--)+"个对象";

    }

protected:
    int mObjectType;
};

#endif // GAMEOBJECT_H
