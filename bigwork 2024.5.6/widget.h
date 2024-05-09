#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QList>
#include"enemy.h"
#include"player.h"
#include<QMediaPlayer>//媒体播放器播放
#include<bullet.h>

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

    static Widget* widget;
    //按键事件
    void keyPressEvent(QKeyEvent* event);//按下
    void keyReleaseEvent(QKeyEvent* event);//释放按键

private:
    Ui::Widget *ui;


};
#endif // WIDGET_H
