#include "leftwidget.h"
#include <QGridLayout>
#include <QPalette>
#include <QEvent>
#include <QPainter>
#include <QString>
#include "mainwindow.h"

LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
      pmain=(MainWindow *)parent;
//    xLabel=new QLabel(this);
//    xLabel->setText(tr("x 坐标:"));
//    yLabel=new QLabel(this);
//    yLabel->setText(tr("y 坐标:"));
//    radiusLabel=new QLabel(this);
//    radiusLabel->setText(tr("半径:"));
//    speedLabel=new QLabel(this);
//    speedLabel->setText(tr("速度:"));
//    angleLabel=new QLabel(this);
//    angleLabel->setText(tr("角度:"));
//    colorLabel=new QLabel(this);
//    colorLabel->setText(tr("颜色:"));

//    xEdit=new QLineEdit("100",this);
//    yEdit=new QLineEdit("50",this);
//    radiusEdit=new QLineEdit("10",this);
//    speedEdit=new QLineEdit("5",this);
//    angleEdit=new QLineEdit("40",this);

    reStartButton=new QPushButton(tr("重来(R)"),this);
    stopButton=new QPushButton(tr("暂停(P)"),this);

//    colorPreview=new PaintLabel(this);//自定义类
//    colorPreview->setText(tr("       "));  //初始字符串确定控件大小

    QGridLayout *mainLayout=new QGridLayout(this);
//    mainLayout->addWidget(xLabel,0,0);
//    mainLayout->addWidget(xEdit,0,1);
//    mainLayout->addWidget(yLabel,1,0);
//    mainLayout->addWidget(yEdit,1,1);
//    mainLayout->addWidget(radiusLabel,2,0);
//    mainLayout->addWidget(radiusEdit,2,1);
//    mainLayout->addWidget(speedLabel,3,0);
//    mainLayout->addWidget(speedEdit,3,1);
//    mainLayout->addWidget(angleLabel,4,0);
//    mainLayout->addWidget(angleEdit,4,1);
//    mainLayout->addWidget(colorLabel,5,0);
//    mainLayout->addWidget(colorPreview,5,1);
    mainLayout->addWidget(reStartButton,3,0);
    mainLayout->addWidget(stopButton,6,0);
    setLayout(mainLayout);

    connect(reStartButton,SIGNAL(clicked()),this,SLOT(reStartBall()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopBall()));
//    //实现按钮点击事件的槽方法
}
void LeftWidget::paintEvent(QPaintEvent *){
    QPainter p(this);//需要在不同类之间传参，不能在ball里面定义
    p.drawPixmap(rect(),QPixmap(":/image/background2.jpg"),QRect());
}
void LeftWidget::reStartBall(){
    RightWidget *right=pmain->getRightWidget();
    *right->getBallP1()=Ball(500,250,rect().height()/15,0.5,45,Qt::red,1);
    *right->getBallP2()=Ball(500,250,rect().height()/15,0.5,225,Qt::black,2);
    right->setLabelRight(" ");
}
void LeftWidget::stopBall(){
    if(stopButton->text()==tr("暂停(P)")){
        pmain->StopTimer();
        stopButton->setText(tr("开始(P)"));
    }
    else{
        pmain->resumeTimer();
        stopButton->setText(tr("暂停(P)"));
    }
}//实现按钮点击事件的槽方法
