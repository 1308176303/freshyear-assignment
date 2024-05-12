#include "gameobject.h"
#include<QGraphicsScene>
#include"gameobjectpool.h"
#include<QDebug>

//int GameObject ::createCount=0;
GameObject::GameObject(QObject *parent)

{

}

void GameObject::GameObjectDelete(QGraphicsScene* _scene)
{
    _scene->removeItem(this);
    GameObjectPool::Instance()->RecoGameObject(this);
}
