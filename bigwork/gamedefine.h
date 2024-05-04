#ifndef GAMEDEFINE_H
#define GAMEDEFINE_H

#include<QDebug>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QTimer>
#include<QList>
#include<QMediaPlayer>
#include<QToolButton>
#include"enemy.h"
#include"bullet.h"
#include"player.h"
#include<QRandomGenerator>

//游戏定义类  定义游戏相关属性
class GameDefine
{
public:
    GameDefine();
    static const int PlaneShootUpdateTime = 600;
    static const int PlayerMoveUpdateTime = 20;
    static const int EnemyMoveUpdateTime = 20;
    static const int BulletMoveUpdateTime = 10;
    static const int BackgroundUpdateTime = 50;
    static const int EnemyCreateTime = 500;

    //屏幕宽高
    static const int ScreenWidth = 512;
    static const int Screen1Height = 768;


};

#endif // GAMEDEFINE_H