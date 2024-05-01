#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QList>
#include"enemy.h"
#include"bullet.h"
#include<QMediaPlayer>//媒体播放器播放

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //背景的移动
    void BGMove();

    //飞机的移动
    void PlaneMove();

    //按键事件
    void keyPressEvent(QKeyEvent* event);//按下
    void keyReleaseEvent(QKeyEvent* event);//释放按键

    //我的子弹生成函数
    void PlaneBulletShoot();

    //敌机生成函数
    void CreatEnemy();
    //碰撞检测
    void Collison();

private:
    Ui::Widget *ui;
    QGraphicsView mGameView;//游戏视图
    QGraphicsScene mScene;//游戏中场景
    QGraphicsScene mStartScene;//开始游戏的场景

    QGraphicsPixmapItem mBackGround1;
    QGraphicsPixmapItem mBackGround2;

    MyPlane mPlane;

    //定时器
    QTimer* mBGMoveTimer;//背景的
    QTimer* mPlaneMoveTimer;//飞机的
    QTimer* mPlaneShootTimer;//飞机发射定时器
    QTimer* mBulletMoveTimer;//子弹移动定时器
    QTimer* mEnemyCreatTimer; //敌机创建定时器
    QTimer* mEnemyMoveTimer;//敌机移动定时器

    //容器
    QList<int> mKeyList;//按键的组合
    QList<Bullet*> mBulletList;//子弹容器
    QList<Enemy*> mEnemylist;//敌人的容器

    //背景音乐
    QMediaPlayer* mMediaBG= new QMediaPlayer;

};
#endif // WIDGET_H
