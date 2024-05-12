#include "gamecontrol.h"
#include "gamedefine.h"
#include "gameobjectpool.h"
#include<QLabel>

GameControl* GameControl::instance =nullptr;
GameControl::GameControl(QWidget*parent):QObject(parent) {
}

int bebulletcount=0;

void GameControl::BGMove()
{
    mBackGround1.moveBy(0,2);
    mBackGround2.moveBy(0,2);

    if(mBackGround1.y()>=mBackGround1.pixmap().height())
    {
        mBackGround1.setY(-mBackGround1.pixmap().height());
    }
    else if(mBackGround2.y()>=mBackGround2.pixmap().height())
    {
        mBackGround2.setY(-mBackGround2.pixmap().height());
    }
}
void GameControl::GameInit()
{

    //初始化pool
    GameObjectPool::Instance()->Init();
    //设置视图的父亲为窗口
    mGameView.setParent(Widget::widget);

    LoadStartScene();//开始场景初始化


    //定时器初始化
    mPlaneShootTimer =  new QTimer(this);
    mPlaneMoveTimer = new QTimer(this);
    mEnemyMoveTimer = new QTimer(this);
    mBulletMoveTimer = new QTimer(this);
    mBGMoveTimer = new QTimer(this);
    mEnemyCreatTimer = new QTimer(this);
    mEnemyShootTimer = new QTimer(this);

    //绑定定时器处理函数
    connect(mBGMoveTimer,&QTimer::timeout,this,&GameControl::BGMove);
    connect(mPlaneMoveTimer,&QTimer::timeout,this,&GameControl::PlaneMove);
    connect(mPlaneShootTimer,&QTimer::timeout,this,&GameControl::PlaneBulletShoot);
    connect(mEnemyShootTimer,&QTimer::timeout,this,&GameControl::EnemyBulletShoot);
    connect(mEnemyCreatTimer,&QTimer::timeout,this,&GameControl::CreatEnemy);
    connect(mBulletMoveTimer,&QTimer::timeout,[this](){
        for(auto bullet:mBulletList)
        {
            int y = bullet->y();
            bullet->BulletMove();
            //越界
            y = bullet->y();
            if(bullet->y()<-100)
            {
                bullet->GameObjectDelete(&mGameScene);
                mBulletList.removeOne(bullet);
            }
        }

        for(auto bullet:mEnemyBulletList)
        {

            bullet->BulletMove(QPoint(0,1));
            //越界
            if(bullet->y()>GameDefine::Screen1Height)
            {
                bullet->GameObjectDelete(&mGameScene);
                mEnemyBulletList.removeOne(bullet);
            }
        }

        //碰撞检测
        Collison();
    });
    connect(mBGMoveTimer,&QTimer::timeout,[this](){
        for(auto enemy:mEnemylist)
        {
            enemy->EnemyMove();

            if(enemy->y()>GameDefine::Screen1Height+enemy->pixmap().height())
            {
                enemy->GameObjectDelete(&mGameScene);
                mEnemylist.removeOne(enemy);            }
        }
    });
}

void GameControl::LoadStartScene()
{
    mGameView.setSceneRect(QRect(0,0,514,770));
    mStartScene.setSceneRect(QRect(0,0,512,768));//游戏开始场景大小
    //开始场景初始化
    mStartScene.addPixmap(QPixmap(":/img/img/gamestart.jpg"));

    auto startBtn=new QToolButton();
    startBtn->setAutoRaise(true);
    startBtn->setIcon(QIcon(":/img/img/startBtn.fw.png"));
    startBtn->setIconSize(QSize(171,45));
    startBtn->move(256-171/2,384);
    //点击开始游戏
    connect(startBtn,&QToolButton::clicked,[this](){

        //加载游戏场景
        this->LoadGameScene();
        //开始游戏
        this->GameStart();

    });
    mStartScene.addWidget(startBtn);

    //设置当前场景为开始场景
    mGameView.setScene(&mStartScene);
    mGameView.show();

}

void GameControl::LoadGameScene()
{
    mGameScene.setSceneRect(QRect(0,0,512,768));//游戏进行场景大小
    mBackGround1.setPixmap(QPixmap(":/img/img/background.jpg"));
    mBackGround2.setPixmap(QPixmap(":/img/img/background.jpg"));
    mPlane.setPixmap(QPixmap(":/img/img/MyPlane1.fw.png"));

    //调整元素位置
    mBackGround2.setPos(0,-mBackGround2.pixmap().height());

    //把图片元素添加到场景
    mGameScene.addItem(&mBackGround1);
    mGameScene.addItem(&mBackGround2);
    mGameScene.addItem(&mPlane);



    //设置当前场景为游戏场景
    mGameView.setScene(&mGameScene);
    mGameView.show();


}

void GameControl::GameStart()
{
    //开启定时器
    mBGMoveTimer->start(GameDefine::BackgroundUpdateTime);
    mPlaneMoveTimer->start(GameDefine::PlayerMoveUpdateTime);
    mPlaneShootTimer->start(GameDefine::PlaneShootUpdateTime);
    mBulletMoveTimer->start(GameDefine::BulletMoveUpdateTime);
    mEnemyCreatTimer->start(GameDefine::EnemyCreateTime);
    mEnemyMoveTimer->start(GameDefine::EnemyMoveUpdateTime);
    mEnemyShootTimer->start(GameDefine::EnemyShootUpdateTime);
}

void GameControl::GameOver()
{
    bebulletcount++;
    if(bebulletcount==3)
    {
        LoadOverScene();
    }
    // 结束逻辑
}


void GameControl::PlaneMove()
{
    for(int keyCode : mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W:mPlane.moveBy(0,-1*mPlane.MoveSpeed());break;
        case Qt::Key_S:mPlane.moveBy(0,1*mPlane.MoveSpeed());break;
        case Qt::Key_A:mPlane.moveBy(-1*mPlane.MoveSpeed(),0);break;
        case Qt::Key_D:mPlane.moveBy(1*mPlane.MoveSpeed(),0);break;
        }
    }

    //边界的判断！！！
    if(mPlane.x()<0)
    {
        mPlane.setX(0);
    }
    if(mPlane.y()<0)
    {
        mPlane.setY(0);
    }
    if(mPlane.x()>GameDefine::ScreenWidth-mPlane.pixmap().width())
    {
        mPlane.setX(GameDefine::ScreenWidth-mPlane.pixmap().width());
    }
    if(mPlane.y()>GameDefine::Screen1Height-mPlane.pixmap().height())
    {
        mPlane.setY(GameDefine::Screen1Height-mPlane.pixmap().height());
    }
}



//我的子弹生成函数
void GameControl::PlaneBulletShoot()
{
    QPixmap bulletImg(":/img/img/bulletPlane.fw.png");
    QPoint pos(mPlane.x()+mPlane.pixmap().width()/2,mPlane.y());

    GameObject* obj=GameObjectPool::Instance()->GetGameObject(GameObject::OT_BulletPlayer);

    PlayerBullet* bullet=(PlayerBullet*)obj;
    bullet->Init(pos,bulletImg);

    //添加到场景
    mGameScene.addItem(bullet);

    //添加到子弹管理器
    mBulletList.append(bullet);

}
//敌方子弹生成函数
void GameControl::EnemyBulletShoot()
{
    //pool构建bullet
    for(auto & enemy: mEnemylist)
    {
    QPixmap bulletImg(":/img/img/bulletEnemy1.fw.png");
        QPoint pos(enemy->x()+enemy->pixmap().width()/2,enemy->y());

    GameObject* obj=GameObjectPool::Instance()->GetGameObject(GameObject::OT_EnemyBullet);

    EnemyBullet* bullet=(EnemyBullet*)obj;
    bullet->Init(pos,bulletImg);

    //添加到场景
    mGameScene.addItem(bullet);

    //添加到子弹管理器
    mEnemyBulletList.append(bullet);
    }
}

void GameControl::CreatEnemy()
{
    QPixmap pixmap(":/img/img/enemy1.fw.png");
    QRandomGenerator randomGenerator(QRandomGenerator::global()->generate()); // 初始化随机数生成器
    int randX = randomGenerator.bounded(512 - pixmap.width()); //[0, 512 - pixmap.width()]
    GameObject*obj=GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy);

#if 1
    if(obj == 0) return ;
#endif

    Enemy* enemy=(Enemy*)obj;
    enemy->Init(QPoint(randX,-200),pixmap);

    //添加到场景
    mGameScene.addItem(enemy);

    //添加到管理器
    mEnemylist.append(enemy);
}

void GameControl::Collison()
{
    //遍历子弹
    for(int i=0;i<mBulletList.size();i++)
    {
        //遍历敌机
        for(int j=0;j<mEnemylist.size();j++)
        {
            if(mBulletList[i]->collidesWithItem(mEnemylist[j]))//碰撞检测
            {
                //移除场景回收对象
                //mBulletList[i]->GameObjectDelete(&mGameScene);
                mEnemylist[j]->GameObjectDelete(&mGameScene);

                //移除管理器
                //mBulletList.removeOne(mBulletList[i]);
                mEnemylist.removeOne(mEnemylist[j]);
            }
        }
    }

    for(int i=0;i<mEnemyBulletList.size();i++)
    {
        if(mEnemyBulletList[i]->collidesWithItem(&mPlane))
        {
            mEnemyBulletList[i]->GameObjectDelete(&mGameScene);
            mEnemyBulletList.removeOne(mEnemyBulletList[i]);
            GameOver();
        }
    }
}

void GameControl::LoadOverScene()
{
    mOverScene.setSceneRect(QRect(0,0,512,768));//游戏进行场景大小
    mBackGround3.setPixmap(QPixmap(":/img/img/gameover1.jpg"));

    mOverScene.addItem(&mBackGround3);
    mGameView.setScene(&mOverScene);
    mGameView.show();

}

