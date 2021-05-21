#include "ball.h"
#include <cmath>
Ball::Ball():Ball(40,100,10,10,45,Qt::red,1)
{   //通过委托构造实现缺省构造函数
}
Ball::Ball(double xpos,double ypos,double r,double s,double a,QColor c,int type)
    :x(xpos),y(ypos),radius(r),speed(s),angle(a),color(c)
{
    boundary=0;
    imageType=type;
    lasttime=QTime::currentTime();
}
void Ball::draw(QPainter *p)
{
    QPen pen(color,1,Qt::SolidLine);
    QBrush brush(color);
    p->setPen(pen);
    p->setBrush(brush);
    QRect r(x-radius,y-radius,radius*2,radius*2);//定义坐标,左上角坐标+矩形长宽
    QRect source(0.0,0.0,160,160);
    QImage image;
    switch(imageType){
    case 1:
        image.load(":/image/huaji.png");
        break;
    case 2:
        image.load(":/image/huaji2 .png");
        break;
    case 3:
        image.load(":/image/huaji3.png");
        break;
    case 4:
        image.load(":/image/huaji4.png");
        break;
    }
   // p->drawEllipse(r);
    p->drawImage(r,image,source);
}

void Ball::move(){
    double dx,dy;
    const double PI=3.14159;
    dx=speed*std::sin(angle*PI/180);
    dy=speed*std::cos(angle*PI/180);
    x+=dx;
    y+=dy;
    checkBoundary();
}
Ball Ball::fakemoveofSon(){
    Ball fakeball=*this;
    double dx,dy;
    const double PI=3.14159;
    dx=speed*std::sin(angle*PI/180);
    dy=speed*std::cos(angle*PI/180);
    fakeball.x+=dx;
    fakeball.y+=dy;
    return fakeball;
}
void Ball::checkBoundary(){ //左上角（0,0）向右下递增。
    if(y+radius>rect.height()||y-radius<0||x+radius>rect.width()||x-radius<0){
        y=rect.height()+3*radius;
        x=rect.width()+3*radius;
        speed=0;
        boundary=1;
    }
}

bool get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y,
    double p2_x, double p2_y, double p3_x, double p3_y)
{
    double s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
    s10_x = p1_x - p0_x;
    s10_y = p1_y - p0_y;
    s32_x = p3_x - p2_x;
    s32_y = p3_y - p2_y;

    denom = s10_x * s32_y - s32_x * s10_y;
    if (fabs(denom-0)<0.0001)//平行或共线
        return 0; // Collinear
    bool denomPositive = denom > 0;

    s02_x = p0_x - p2_x;
    s02_y = p0_y - p2_y;
    s_numer = s10_x * s02_y - s10_y * s02_x;
    if ((s_numer < 0) == denomPositive)//参数是大于等于0且小于等于1的，分子分母必须同号且分子小于等于分母
        return 0; // No collision

    t_numer = s32_x * s02_y - s32_y * s02_x;
    if ((t_numer < 0) == denomPositive)
        return 0; // No collision

    if (fabs(s_numer) > fabs(denom) || fabs(t_numer) > fabs(denom))
        return 0; // No collision
    // Collision detected
    t = t_numer / denom;

    return 1;
}
bool Ball::checkCollision(Ball &b){
    Ball fakethis=this->fakemoveofSon();
    Ball fakeb=b.fakemoveofSon();//预防掉帧 预测行为
    double dx,dy;
    dx=x-b.x;
    dy=y-b.y;
    double dis=std::sqrt(dx*dx+dy*dy);
    double x1=x,y1=y,x2=fakethis.getX(),y2=fakethis.getY(),x3=b.x,y3=b.y,x4=fakeb.getX(),y4=fakeb.getY();
    bool res=get_line_intersection(x1, y1, x2, y2,
                                   x3, y3, x4, y4);
    if(dis<=radius+b.radius||res){ //碰撞后只是交换速度和角度

        //进行优化 动量守恒 2D 质量与半径平方正相关(伪)
        double temp;
        temp=speed;
        speed=(b.speed+speed)/2;//*b.getRadius()*b.getRadius()/(this->getRadius()*this->getRadius());
        b.speed=(temp+b.speed)/2;//*this->getRadius()*this->getRadius()/(b.getRadius()*b.getRadius());
        temp=angle;
        angle=b.angle;
        b.angle=temp;
        return 1;
    }
    return 0;
}
