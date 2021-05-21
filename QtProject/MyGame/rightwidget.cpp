#include "rightwidget.h"
#include "mainwindow.h"
#include <algorithm>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <cmath>
#include <QPainter>
#include <QTime>
#include <QGridLayout>
#include <QPalette>
using namespace std;
void RightWidget::keyPressEvent(QKeyEvent *e){
    int keyHere=e->key();
    double x,y,s,angle,r;
    QColor color;
    switch(keyHere){
    case Qt::Key_R://R
        reStartBall();
        break;
    case Qt::Key_P://P
        stopBall();
        break;
    case Qt::Key_B:
        if(ballPlayer1.getSpeed()<10)
            ballPlayer1.resetSpeed(ballPlayer1.getSpeed()+2);
        break;
    case Qt::Key_N:
        if(ballPlayer1.getSpeed()>4)
            ballPlayer1.resetSpeed(
                        ballPlayer1.getSpeed()-4);
        else
            ballPlayer1.resetSpeed(1);
        break;
    case Qt::Key_BracketLeft:
        if(ballPlayer2.getSpeed()<10)
            ballPlayer2.resetSpeed(ballPlayer2.getSpeed()+2);
        break;
    case Qt::Key_BracketRight:
        if(ballPlayer2.getSpeed()>4)
            ballPlayer2.resetSpeed(ballPlayer2.getSpeed()-4);
        else
            ballPlayer2.resetSpeed(1);
        break;
    case Qt::Key_Space:
        if(abs(QTime::currentTime().secsTo(ballPlayer1.getLastTime()))<1&&timeInterval){
            break;
        }
        ballPlayer1.resetLastTime(QTime::currentTime());
        x=ballPlayer1.getX();
        y=ballPlayer1.getY();
        r=ballPlayer1.getRadius();
        s=ballPlayer1.getSpeed();
        angle=ballPlayer1.getAngle();
        color=ballPlayer1.getColor();
        addBalltoP1(Ball(x,y,ballPlayer1.getRadius()/3,max(rect().height()/70,(int)(4*ballPlayer1.getSpeed())),angle,color,ballPlayer1.getImageType()));
        break;
    case Qt::Key_Slash:
        if(abs(QTime::currentTime().secsTo(ballPlayer2.getLastTime()))<1&&timeInterval){
            break;
        }
        ballPlayer2.resetLastTime(QTime::currentTime());
        x=ballPlayer2.getX();
        y=ballPlayer2.getY();
        r=ballPlayer2.getRadius();
        s=ballPlayer2.getSpeed();
        angle=ballPlayer2.getAngle();
        color=ballPlayer2.getColor();
        addBalltoP2(Ball(x,y,ballPlayer2.getRadius()/3,max(rect().height()/70,(int)(4*ballPlayer2.getSpeed())),angle,color,ballPlayer2.getImageType()));
        break;
    case Qt::Key_W:
        flagP1[0]=1;
        if(flagP1[3]==1){
            ballPlayer1.resetAngle(145);
        }
        else if(flagP1[2]==1){
            ballPlayer1.resetAngle(225);
        }
        else ballPlayer1.resetAngle(180);
        break;
    case Qt::Key_S:
        flagP1[1]=1;
        if(flagP1[3]==1){
            ballPlayer1.resetAngle(45);
        }
        else if(flagP1[2]==1){
            ballPlayer1.resetAngle(315);
        }
        else ballPlayer1.resetAngle(0);
        break;
    case Qt::Key_A:
        flagP1[2]=1;
        if(flagP1[0]==1){
            ballPlayer1.resetAngle(225);
        }
        else if(flagP1[1]==1){
            ballPlayer1.resetAngle(315);
        }
        else ballPlayer1.resetAngle(270);
        break;
    case Qt::Key_D:
        flagP1[3]=1;
        if(flagP1[0]==1){
            ballPlayer1.resetAngle(145);
        }
        else if(flagP1[1]==1){
            ballPlayer1.resetAngle(45);
        }
        else ballPlayer1.resetAngle(90);
        break;
    case Qt::Key_Up:
        flagP2[0]=1;
        if(flagP2[3]==1){
            ballPlayer2.resetAngle(145);
        }
        else if(flagP2[2]==1){
            ballPlayer2.resetAngle(225);
        }
        else ballPlayer2.resetAngle(180);
        break;
    case Qt::Key_Down:
        flagP2[1]=1;
        if(flagP2[3]==1){
            ballPlayer2.resetAngle(45);
        }
        else if(flagP2[2]==1){
            ballPlayer2.resetAngle(315);
        }
        else ballPlayer2.resetAngle(0);
        break;
    case Qt::Key_Left:
        flagP2[2]=1;
        if(flagP2[0]==1){
            ballPlayer2.resetAngle(225);
        }
        else if(flagP2[1]==1){
            ballPlayer2.resetAngle(315);
        }
        else ballPlayer2.resetAngle(270);
        break;
    case Qt::Key_Right:
        flagP2[3]=1;
        if(flagP2[0]==1){
            ballPlayer2.resetAngle(145);
        }
        else if(flagP2[1]==1){
            ballPlayer2.resetAngle(45);
        }
        else ballPlayer2.resetAngle(90);
        break;
    }

}
void RightWidget::keyReleaseEvent(QKeyEvent *e){
    int keyHere=e->key();
    switch(keyHere){
    case Qt::Key_W:
        flagP1[0]=0;
        break;
    case Qt::Key_S:
        flagP1[1]=0;
        break;
    case Qt::Key_A:
        flagP1[2]=0;
        break;
    case Qt::Key_D:
        flagP1[3]=0;
        break;
    case Qt::Key_Up:
        flagP2[0]=0;
        break;
    case Qt::Key_Down:
        flagP2[1]=0;
        break;
    case Qt::Key_Left:
        flagP2[2]=0;
        break;
    case Qt::Key_Right:
        flagP2[3]=0;
        break;
    }
}

RightWidget::RightWidget(QWidget *parent) : QWidget(parent)
{
//    QPalette pal =this->palette();
//    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/background.jpg")));
//    this->setPalette(pal);
    pmain=(MainWindow *)parent;
    timeInterval=1;
    resultLabel=new QLabel(this);
    QFont ft;
    ft.setPointSize(30);
    resultLabel->setFont(ft);
    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->addWidget(resultLabel,rect().height()/2,rect().width()/2);
    for(int i=0;i<4;++i){
        flagP1[i]=flagP2[i]=0;
    }
    setMinimumSize(1000,500);
    width=500;
    height=1000;
    ballsofP1.clear();
    ballsofP2.clear();
    ballPlayer1=Ball(rect().width()/2,rect().height()/2,rect().height()/15,0.5,45,Qt::red,1);
    ballPlayer2=Ball(rect().width()/2,rect().height()/2,rect().height()/15,0.5,225,Qt::black,2);
    grabKeyboard();

}
void RightWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);//需要在不同类之间传参，不能在ball里面定义
    p.drawPixmap(rect(),QPixmap(":/image/background.jpg"),QRect());
    // ball.draw(&p);//传p给draw，小球在draw中完成自我绘制
    if(rect().width()!=width&&rect().height()!=height){
        ballPlayer1.resetRadius(rect().height()/15);
        ballPlayer1.resetX(rect().width()/2);
        ballPlayer1.resetY(rect().height()/2);
        ballPlayer2.resetRadius(rect().height()/15);
        ballPlayer2.resetX(rect().width()/2);
        ballPlayer2.resetY(rect().height()/2);
        width=rect().width();
        height=rect().height();
    }
    ballPlayer1.draw(&p);
    ballPlayer2.draw(&p);
    for(auto& b:ballsofP1)
            b.draw(&p);//C++11特性，循环，对容器中对每个元素进行快速遍历.
    for(auto& b:ballsofP2)
            b.draw(&p);
}
void RightWidget::updateBalls()  //封装的控制小球移动的接口
{
   // ball.setRectangle(this->geometry());
   // ball.move();//自己移动一次.
    ballPlayer1.setRectangle(this->geometry());
    ballPlayer1.move();
    if(ballPlayer1.getBoundary()&&!ballPlayer2.getBoundary()){
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::black);
        resultLabel->setPalette(pa);
        ballPlayer1.resetSpeed(0);
        resultLabel->setText(tr("\t玩家二胜利！"));
    }
    ballPlayer2.setRectangle(this->geometry());
    ballPlayer2.move();
    if(ballPlayer2.getBoundary()&&!ballPlayer1.getBoundary()){
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);
        resultLabel->setPalette(pa);
        ballPlayer2.resetSpeed(0);
        resultLabel->setText(tr("\t玩家一胜利！"));
    }
    auto it=ballsofP1.begin();
    for(;it!=ballsofP1.end();++it){
        auto temp=it;
        it->setRectangle(this->geometry());
        it->move();
        if(it->getBoundary()){
            ballsofP1.erase(temp);
        }
    }//先移动小球，处理与边框的碰撞，再处理小球间碰撞
    auto it2=ballsofP2.begin();
    for(;it2!=ballsofP2.end();++it2){
        auto temp=it2;
        it2->setRectangle(this->geometry());
        it2->move();
        if(it2->getBoundary()){
            ballsofP2.erase(temp);
        }
    }
    //C++11特性，循环，对容器中对每个元素进行快速遍历.
    it=ballsofP2.begin();
    for(;it!=ballsofP2.end();++it){
        auto temp=it;
        if(ballPlayer1.checkCollision(*it)){
            ballsofP2.erase(temp);
            ballPlayer1.resetImageType(3);
            break;
        }
    }
    it2=ballsofP1.begin();
    for(;it2!=ballsofP1.end();++it2){
        auto temp=it2;
        if(ballPlayer2.checkCollision(*it2)){
            ballsofP1.erase(temp);
            ballPlayer2.resetImageType(4);
            break;
        }
    }
    update();    //更新窗口显示，重绘小球
}
void RightWidget::addBalltoP1(const Ball &b){
    ballsofP1.append(b);
}//预留给别的接口
void RightWidget::addBalltoP2(const Ball &b){
    ballsofP2.append(b);
}
void RightWidget::stopBall(){
    LeftWidget* left=pmain->getLeftWidget();
    if(left->getStop()->text()==tr("暂停(P)")){
        pmain->StopTimer();
        left->getStop()->setText(tr("开始(P)"));
    }
    else{
        pmain->resumeTimer();
        left->getStop()->setText(tr("暂停(P)"));
    }
}//实现按钮点击事件的槽方法
void RightWidget::reStartBall(){
    RightWidget *right=pmain->getRightWidget();
    *right->getBallP1()=Ball(rect().width()/2,rect().height()/2,rect().height()/15,0.5,45,Qt::red,1);
    *right->getBallP2()=Ball(rect().width()/2,rect().height()/2,rect().height()/15,0.5,225,Qt::black,2);
    right->setLabelRight(" ");
}
