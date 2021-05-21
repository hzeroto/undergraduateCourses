#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H
#include "ball.h"
#include <QWidget>
#include <QList>
#include <QMouseEvent>
#include <QLabel>
#include <QTime>

class MainWindow;
class RightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RightWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);//重载虚函数
    void updateBalls();  //定义移动小球的接口
    void addBalltoP1(const Ball& b);  //添加小球的接口
    void addBalltoP2(const Ball& b);
    void setBallPlace(double x,double y,double angle);
    void setTimeInterval(int type){timeInterval=type;}
    void setLabelRight(QString s){resultLabel->setText(s);}
    Ball* getBallP1(){return &ballPlayer1;}
    Ball* getBallP2(){return &ballPlayer2;}
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private:
    int width;
    int height;
    bool timeInterval;
    bool flagP1[4];//记录键值情况
    bool flagP2[4];
    MainWindow *pmain;
    Ball ballPlayer1;
    void stopBall();
    void reStartBall();
    Ball ballPlayer2;
    //Ball ball;//定义小球,单个小球
    QList<Ball> ballsofP1;//多个小球
    QList<Ball> ballsofP2;//多个小球
    QLabel *resultLabel;
    QPoint p1,p2;
signals:

public slots:
};

#endif // RIGHTWIDGET_H
