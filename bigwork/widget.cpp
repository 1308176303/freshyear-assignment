#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QKeyEvent>
#include<QToolButton>
#include"bullet.h"
#include<QRandomGenerator>
#include"gamecontrol.h"

Widget* Widget::widget=nullptr;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(512,768);
    widget=this;



}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
    GameControl::Instance()->mKeyList.append(event->key());
    break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //移除对应按键组合
    if(GameControl::Instance()->mKeyList.contains(event->key()))
    {
        GameControl::Instance()->mKeyList.removeOne(event->key());
    }
}
