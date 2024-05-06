#include "gameobjectpool.h"

GameObjectPool* GameObjectPool::instance=nullptr;

GameObjectPool::GameObjectPool(QObject *parent)
    : QObject{parent}
{}

void GameObjectPool::Init()
{
    //先创建
    for(int i=0;i<20;i++)
    {
        //bullet
        PlayerBullet* bullet=new PlayerBullet();
        mBulletPool.append(bullet);
        //enemy
        Enemy*enemy=new Enemy();
        mEnemyPool.append(enemy);
    }
}

GameObject *GameObjectPool::GetGameObject(int obtype)
{
    switch(obtype)
    {
        //bullet
    case GameObject::OT_BulletPlayer:
    {
        PlayerBullet* bullet=mBulletPool.first();
        mBulletPool.pop_front();
        return bullet;
    }
        //enemy
    case GameObject::OT_Enemy:
    {
        Enemy* enemy = mEnemyPool.first();
        mEnemyPool.pop_front();
        return enemy;
    }
    }
}

void GameObjectPool::RecoGameObject(GameObject *_object)
{
    switch (_object->GetType())
    {
        //bullet
    case GameObject::OT_BulletPlayer:
    {
        mBulletPool.append((PlayerBullet*)_object);
        break;
    }
        //enemy
    case GameObject::OT_Enemy:
    {
        mEnemyPool.append((Enemy*)_object);
        break;
    }
    }
}

void GameObjectPool::Clear()
{
    // for(auto bulle:mBulletPool)
    // {
    //     delete bulle;
    // }
    for(auto enem:mEnemyPool)
    {
        delete enem;
    }
}

GameObjectPool::~GameObjectPool()
{
    Clear();
}
