#include "widget.h"
#include "ui_widget.h"
#include<QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(512,768);

    mGameView.setSceneRect(QRect(0,0,512,768));
    mScene.setSceneRect(QRect(0,0,512,768));

    mBackGround1.setPixmap(QPixmap(":/img/img/img_bg_level_2.jpg"));
    mBackGround2.setPixmap(QPixmap(":/img/img/img_bg_level_2.jpg"));
    mPlane.setPixmap(QPixmap(":/img/img/MyPlane1.fw.png"));

    //调整元素位置
    mBackGround2.setPos(0,-mBackGround2.pixmap().height());
    mPlane.setPos(100,100);


    //把图片元素添加到场景
    mScene.addItem(&mBackGround1);
    mScene.addItem(&mBackGround2);
    mScene.addItem(&mPlane);
    //设置视图场景
    mGameView.setScene(&mScene);
    //设置视图的父亲为窗口
    mGameView.setParent(this);
    mGameView.show();


    //开启背景移动定时器
    mBGMoveTimer = new QTimer(this);
    mBGMoveTimer->start(10);
    connect(mBGMoveTimer,&QTimer::timeout,this,&Widget::BGMove);
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
