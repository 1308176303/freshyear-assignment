#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QKeyEvent>
#include<QToolButton>
#include"bullet.h"
#include<QRandomGenerator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(512,768);

    mGameView.setSceneRect(QRect(0,0,512,800));
    mScene.setSceneRect(QRect(0,0,512,800));//游戏进行场景
    mStartScene.setSceneRect(QRect(0,0,512,760));
    mStartScene.addPixmap(QPixmap(":/img/img/img_bg_logo.jpg"));

    auto startBtn=new QToolButton();
    startBtn->setAutoRaise(true);
    startBtn->resize(171,45);
    startBtn->setIcon(QIcon(":/img/img/startBtn.fw.png"));
    startBtn->setIconSize(QSize(171,45));
    startBtn->move(256-171/2,384);
    //点击开始游戏
    connect(startBtn,&QToolButton::clicked,[this](){
        mGameView.setScene(&mScene);
        mGameView.show();
        //播放音效
        this->mMediaBG=new QMediaPlayer(this);
        this->mMediaBG->setSource(QUrl("qrc:/sound/music/starwars.mp3"));
        this->mMediaBG->play();
    });
    mStartScene.addWidget(startBtn);

    mBackGround1.setPixmap(QPixmap(":/img/img/img_bg_level_2.jpg"));
    mBackGround2.setPixmap(QPixmap(":/img/img/img_bg_level_2.jpg"));
    mPlane.setPixmap(QPixmap(":/img/img/MyPlane1.fw.png"));

    //调整元素位置
    mBackGround2.setPos(0,-mBackGround2.pixmap().height());

    //把图片元素添加到场景
    mScene.addItem(&mBackGround1);
    mScene.addItem(&mBackGround2);
    mScene.addItem(&mPlane);

    //设置视图场景
    mGameView.setScene(&mScene);
    mGameView.setScene(&mStartScene);
    //设置视图的父亲为窗口
    mGameView.setParent(this);
    mGameView.show();


    //开启背景移动定时器
    mBGMoveTimer = new QTimer(this);
    mBGMoveTimer->start(10);
    connect(mBGMoveTimer,&QTimer::timeout,this,&Widget::BGMove);

    //开启飞机移动检测计时器
    mPlaneMoveTimer = new QTimer(this);
    mPlaneMoveTimer->start(10);
    connect(mPlaneMoveTimer,&QTimer::timeout,this,&Widget::PlaneMove);

    //开启飞机发射定时器
    mPlaneShootTimer = new QTimer(this);
    mPlaneShootTimer->start(mPlane.mShootSpeed);
    connect(mPlaneShootTimer,&QTimer::timeout,this,&Widget::PlaneBulletShoot);

    //开启子弹移动定时器
    mBulletMoveTimer = new QTimer(this);
    mBulletMoveTimer->start(10);
    connect(mBulletMoveTimer,&QTimer::timeout,[this](){
        for(auto bullet:mBulletList)
        {
            bullet->BulletMove();
        }

        //碰撞检测
        Collison();
    });

    //开启敌机创建定时器
    mEnemyCreatTimer = new QTimer(this);
    mEnemyCreatTimer->start(3000);
    connect(mEnemyCreatTimer,&QTimer::timeout,this,&Widget::CreatEnemy);

    //开启敌人移动定时器
    mEnemyMoveTimer=new QTimer(this);
    mEnemyMoveTimer->start(10);
    connect(mBGMoveTimer,&QTimer::timeout,[this](){
        for(auto enemy:mEnemylist)
        {
            enemy->EnemyMove();
        }
    });

}

Widget::~Widget()
{
    delete ui;
}
void Widget::BGMove()
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

void Widget::PlaneMove()
{
    for(int keyCode : mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W:mPlane.moveBy(0,-1*mPlane.mMoveSpeed);break;
        case Qt::Key_S:mPlane.moveBy(0,1*mPlane.mMoveSpeed);break;
        case Qt::Key_A:mPlane.moveBy(-1*mPlane.mMoveSpeed,0);break;
        case Qt::Key_D:mPlane.moveBy(1*mPlane.mMoveSpeed,0);break;
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
    if(mPlane.x()>this->width()-mPlane.pixmap().width())
    {
        mPlane.setX(this->width()-mPlane.pixmap().width());
    }
    if(mPlane.y()>this->height()-mPlane.pixmap().height())
    {
        mPlane.setY(this->height()-mPlane.pixmap().height());
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
        mKeyList.append(event->key());
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //移除对应按键组合
    if(mKeyList.contains(event->key()))
    {
        mKeyList.removeOne(event->key());
    }
}

void Widget::PlaneBulletShoot()
{
    //创造子弹
    QPixmap bulletImg(":/img/img/bulletPlane.fw.png");
    QPoint pos(mPlane.x()+mPlane.pixmap().width()/2,mPlane.y());
    Bullet* bullet=new Bullet(pos,bulletImg,Bullet::BT_Player);

    //添加到场景
    mScene.addItem(bullet);

    //添加到子弹管理器
    mBulletList.append(bullet);

}

void Widget::CreatEnemy()
{
    QPixmap pixmap(":/img/img/enemy1.fw.png");
    QRandomGenerator randomGenerator(QRandomGenerator::global()->generate()); // 初始化随机数生成器
    int randX = randomGenerator.bounded(512 - pixmap.width()); //[0, 512 - pixmap.width()]
    Enemy *enemy = new Enemy(QPoint(randX, -200), pixmap);

    //添加到场景
    mScene.addItem(enemy);

    //添加到管理器
    mEnemylist.append(enemy);
}

void Widget::Collison()
{
    //遍历子弹
    for(int i=0;i<mBulletList.size();i++)
    {
        //遍历敌机
        for(int j=0;j<mEnemylist.size();j++)
        {
            if(mBulletList[i]->collidesWithItem(mEnemylist[j]))//碰撞检测
            {
                mScene.removeItem(mBulletList[i]);
                mScene.removeItem(mEnemylist[j]);

                //移除管理器
                mBulletList.removeOne(mBulletList[i]);
                mEnemylist.removeOne(mEnemylist[j]);
            }
        }
    }
}
