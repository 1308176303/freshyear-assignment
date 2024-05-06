#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include"gamedefine.h"
#include"widget.h"

class GameControl:public QObject
{
    //单例
    GameControl(QWidget*parent = nullptr);
    static GameControl* instance;
public:
    //获取单例
    static GameControl* Instance()
    {
        if(instance==nullptr)
        {
            return instance =new GameControl(Widget::widget);
        }
        return instance;
    }
    ~GameControl()
    {
        qDebug()<<"游戏控制释放";
    }
    //游戏初始化
    void GameInit();
    void LoadStartScene();//加载开始场景
    void LoadGameScene();//游戏场景加载

    //游戏逻辑定时器开启(游戏开始）
    void GameStart();
    //游戏逻辑定时器关闭（游戏结束)
    void GameOver();

    //背景移动
    void BGMove();


    //飞机的移动
    void PlaneMove();



    //我的子弹生成函数
    void PlaneBulletShoot();

    //敌机生成函数
    void CreatEnemy();
    //碰撞检测
    void Collison();
    QList<int> mKeyList;//按键的组合

protected:
    QGraphicsView mGameView;//游戏视图
    QGraphicsScene mGameScene;//游戏中场景
    QGraphicsScene mStartScene;//开始游戏的场景

    QGraphicsPixmapItem mBackGround1;
    QGraphicsPixmapItem mBackGround2;

    Player mPlane;

    //定时器
    QTimer* mBGMoveTimer;//背景的
    QTimer* mPlaneMoveTimer;//飞机的
    QTimer* mPlaneShootTimer;//飞机发射定时器
    QTimer* mBulletMoveTimer;//子弹移动定时器
    QTimer* mEnemyCreatTimer; //敌机创建定时器
    QTimer* mEnemyMoveTimer;//敌机移动定时器

    //容器

    QList<Bullet*> mBulletList;//子弹容器
    QList<Enemy*> mEnemylist;//敌人的容器
};

#endif // GAMECONTROL_H
