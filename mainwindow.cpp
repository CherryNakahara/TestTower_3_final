#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mybutton.h"
#include "introduction.h"
#include <QTimer>
#include "gamescene.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1019,616);
    //设置开始游戏按钮
    MyButton *bts=new MyButton(":/image/start.png");
    bts->setParent(this);
    bts->move(470,450);
    //设置游戏简介按钮
    MyButton *btj=new MyButton(":/image/jianjie.png");
    btj->setParent(this);
    btj->move(470,510);
    //链接主界面和游戏简介界面
    introduction *intr=new introduction;
    connect(btj,&QPushButton::clicked,this,[=]()
    {
        btj->zoomdown();
        btj->zoomup();
        QTimer::singleShot(500,this,[=]()
        {
            this->hide();
            intr->show();
        });
    });
    connect(intr,&introduction::chooseBack,this,[=]()
    {

        intr->hide();
        this->show();
    });
    //链接主界面和游戏界面
    GameScene *gs=new GameScene;
    connect(bts,&QPushButton::clicked,this,[=]()
    {
        bts->zoomdown();
        bts->zoomup();
        QTimer::singleShot(500,this,[=]()
        {
            this->hide();
            gs->show();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

