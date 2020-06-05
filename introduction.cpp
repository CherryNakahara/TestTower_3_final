#include "introduction.h"
#include "mybutton.h"

introduction::introduction(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1240,874);
    MyButton *btf=new MyButton(":/image/fanhui.png");
    btf->setParent(this);
    btf->move(1000,500);
    connect(btf,&MyButton::clicked,this,[=]()
    {
        emit chooseBack();
    });
}

void introduction::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/image/introduction.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
