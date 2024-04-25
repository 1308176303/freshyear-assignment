#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>

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

    //背景移动函数
    void BGMove();

private:
    Ui::Widget *ui;
    QGraphicsView mGameView;//游戏视图
    QGraphicsScene mScene;//场景

    QGraphicsPixmapItem mPlane;//飞机
    QGraphicsPixmapItem mBackGround1;
    QGraphicsPixmapItem mBackGround2;

    //背景移动定时器
    QTimer* mBGMoveTimer;

};
#endif // WIDGET_H
