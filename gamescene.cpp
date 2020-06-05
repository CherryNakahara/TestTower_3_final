#include "gamescene.h"

GameScene::GameScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1280,800);
    city.setGame(this);
    addGrids();
    addWayPoints();
    //QTimer定时发送信息
    QTimer *timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateMap()));
    //100毫秒一刷
    timer->start(100);
    QTimer::singleShot(300,this,SLOT(gamestart()));
}

void GameScene::paintEvent(QPaintEvent *)
{
    gameEnded=city.getDie();
    if(gameEnded||gameWin)
    {
        if(gameEnded)
        {
            picture=QPixmap(":/image/fail.png");
        }
        else picture=QPixmap(":/image/victory.png");
        QPainter painter(this);
        painter.drawPixmap(0,0,picture);
        return;
    }
    map=QPixmap(":/image/map1.png");
    if(level==2)
    {
        map=QPixmap(":/image/map2.png");
    }
    QPainter map_painter(&map);
    scoreboard.draw(map_painter);
    grid_list[111]->draw(map_painter);
    grid_list[63]->draw(map_painter);
    grid_list[79]->draw(map_painter);
    foreach (Tower *tower, tower_list)
        tower->draw(map_painter);
    foreach (Enemy *enemy, enemy_list)
        enemy->draw(map_painter);
    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&map_painter);
    drawWave(&map_painter);
    QPainter painter(this);
    painter.drawPixmap(0, 0, map);

    city_movement++;
}

void GameScene::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    if (scoreboard.getMoney() >= 200)
    {
        int i = (pressPos.x()/side + pressPos.y()/side*(width)/side);
        if (i==63)
        {
            tower_kind = 1;
        }
        else if (i==79)
        {
            tower_kind = 3;
        }
        else if (i==111)
        {
            tower_kind = 2;
        }
        else if (grid_list[i]->getVacant())
        {
            grid_list[i]->setVacant();
            if (tower_kind==1)
            {
                Tower *tower = new Tower(grid_list[i]->getRect().center(), this);
                tower_list.push_back(tower);
                grid_list[i]->number = tower_list.indexOf(tower);
                scoreboard.setMoney(-100);
            }
            else if (tower_kind==2)
            {
                Icetower *tower = new Icetower(grid_list[i]->getRect().center(), this);
                tower_list.push_back(tower);
                grid_list[i]->number = tower_list.indexOf(tower);
                scoreboard.setMoney(-200);
            }
            else if (tower_kind==3)
            {
                Firetower *tower = new Firetower(grid_list[i]->getRect().center(), this);
                tower_list.push_back(tower);
                grid_list[i]->number = tower_list.indexOf(tower);
                scoreboard.setMoney(-200);
            }
            update();//update()它允许Qt来优化速度并且防止闪烁,几次执行才调用一次paintEvent()。
        }
        else
        {
            tower_list[grid_list[i]->number]->upLevel();
            scoreboard.setMoney(-100);
        }
    }
}

void GameScene::addGrids()
{
    for (int j=0; j<(height/side); j++)
    {
        for (int i=0; i<(width/side); i++)
        {
            Grid *temp_grid = new Grid(i*side, j*side, side);
            grid_list.push_back(temp_grid);
        }
    }
}

void GameScene::addWayPoints()
{
    WayPoint *wayPoint11 = new WayPoint(QPoint(860, 420));
    waypoint_list_1.push_back(wayPoint11);

    WayPoint *wayPoint12 = new WayPoint(QPoint(0, 420));
    waypoint_list_1.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);



    WayPoint *wayPoint21 = new WayPoint(QPoint(1240, 440));
    waypoint_list_2.push_back(wayPoint21);

    WayPoint *wayPoint22 = new WayPoint(QPoint(1180, 440));
    waypoint_list_2.push_back(wayPoint22);
    wayPoint22->setNextWayPoint(wayPoint21);

    WayPoint *wayPoint23 = new WayPoint(QPoint(1180, 760));
    waypoint_list_2.push_back(wayPoint23);
    wayPoint23->setNextWayPoint(wayPoint22);

    WayPoint *wayPoint24 = new WayPoint(QPoint(0, 760));
    waypoint_list_2.push_back(wayPoint24);
    wayPoint24->setNextWayPoint(wayPoint23);

    WayPoint *wayPoint31 = new WayPoint(QPoint(1240, 110));
    waypoint_list_3.push_back(wayPoint31);

    WayPoint *wayPoint32 = new WayPoint(QPoint(130, 110));
    waypoint_list_3.push_back(wayPoint32);
    wayPoint32->setNextWayPoint(wayPoint31);

    WayPoint *wayPoint33 = new WayPoint(QPoint(130, 420));
    waypoint_list_3.push_back(wayPoint33);
    wayPoint33->setNextWayPoint(wayPoint32);

    WayPoint *wayPoint34 = new WayPoint(QPoint(0, 420));
    waypoint_list_3.push_back(wayPoint34);
    wayPoint34->setNextWayPoint(wayPoint33);
}

bool GameScene::loadWave()
{
    if (waves>=8)
        return false;
    else if (waves>=0)
    {
        if (waves==3)
        {
            level = 2;
            city.current_hp += 500;
        }
        WayPoint *startWayPoint1 = waypoint_list_1.back(); // 这里是个逆序的，尾部才是其实节点
        if (level==1)
        {
            int enemyStartInterval1[] = { 500, 1000, 2000, 3000, 6000, 7000, 13000};
            for (int i = 0; i < 6; ++i)
            {
                Enemy *enemy = new Enemy(startWayPoint1, this);
                enemy_list.push_back(enemy);
                QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(setActive()));
            }
            return true;
        }
        else if (level==2)
        {
            int enemyStartInterval2[] = { 500, 1000, 2000, 3000, 6000, 10000, 20000};
            WayPoint *startWayPoint2 = waypoint_list_2.back(); // 这里是个逆序的，尾部才是其实节点
            WayPoint *startWayPoint3 = waypoint_list_3.back(); // 这里是个逆序的，尾部才是其实节点
            for (int i=0; i<4; ++i)
            {
                Enemy *enemy1 = new Enemy(startWayPoint1, this);
                enemy_list.push_back(enemy1);
                QTimer::singleShot(enemyStartInterval2[i], enemy1, SLOT(setActive()));
                Enemy2 *enemy2 = new Enemy2(startWayPoint2, this);
                enemy_list.push_back(enemy2);
                QTimer::singleShot(enemyStartInterval2[i], enemy2, SLOT(setActive()));
            }
            for (int i=4; i<6; ++i)
            {
                Enemy2 *enemy2 = new Enemy2(startWayPoint2, this);
                enemy_list.push_back(enemy2);
                QTimer::singleShot(enemyStartInterval2[i], enemy2, SLOT(setActive()));
                Enemy3 *enemy3 = new Enemy3(startWayPoint3, this);
                enemy_list.push_back(enemy3);
                QTimer::singleShot(enemyStartInterval2[i], enemy3, SLOT(setActive()));
            }
            return true;
        }
    }
}

void GameScene::updateMap() //槽函数(接收对象在接收到信号之后所需要调用的函数)
{
    foreach (Enemy *enemy, enemy_list)
        enemy->move();
    foreach (Tower *tower, tower_list)
        tower->checkEnemyInRange();
    update();
}

void GameScene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    enemy_list.removeOne(enemy); //删去第一个
    delete enemy;
    scoreboard.setMoney(100);
    if (enemy_list.empty())
    {
        ++waves; // 当前波数加1
        // 继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
            gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void GameScene::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void GameScene::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void GameScene::doGameOver()
{
    if (!gameEnded)
    {
        gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void GameScene::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::black));
    QFont font("宋体", 30, QFont::Black, true);
    painter->setFont(font);
    painter->drawText(QRect(1000,100,200,130), QString("Wave:%1").arg(waves+1));
}
