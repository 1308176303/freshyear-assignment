#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H
#include<QDebug>
#include <QGraphicsPixmapItem>

class GameObjectPool : public QGraphicsPixmapItem
{
public:
    explicit GameObjectPool(QObject *parent = nullptr);

};

#endif // GAMEOBJECTPOOL_H
