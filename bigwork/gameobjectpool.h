#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include"gamedefine.h"
#include "widget.h"
#include <QObject>

class GameObjectPool : public QObject
{
    GameObjectPool(QObject *parent = nullptr);
    static GameObjectPool* instance;
public:
    static GameObjectPool* Instance()
    {
        if(instance==nullptr)
        {
            return instance=new GameObjectPool(Widget::widget);
        }
        return instance;
    }

    //初始化
    void Init();

    //获取
    GameObject* GetGameObject(int obtype);

    //xxzxz
    void RecoGameObject(GameObject* _object);
    //清内存
    void Clear();
    ~GameObjectPool();

protected:
    QList<PlayerBullet*> mBulletPool;
    QList<Enemy*> mEnemyPool;

};

#endif // GAMEOBJECTPOOL_H
