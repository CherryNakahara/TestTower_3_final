#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPixmap>
#include <QList>
#include <function.h>
#include "grid.h"
#include <QTimer>
#include "tower.h"
#include "enemy.h"
#include "waypoint.h"
#include "city.h"
#include "scoreboard.h"
#include "bullet.h"

class City;

using namespace std;



class GameScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void addGrids();
    void addWayPoints();
    void mousePressEvent(QMouseEvent *);
    bool loadWave();
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void doGameOver();
    void drawWave(QPainter *painter);
    QList <Enemy*> m_enemylist() const
    {
        return enemy_list;
    }
    QList <Tower*> tower_list;
    City city;
private:
    QList <WayPoint*> waypoint_list_1;
    QList <WayPoint*> waypoint_list_2;
    QList <WayPoint*> waypoint_list_3;
    QList <Enemy*> enemy_list;
    QList <Grid*> grid_list;
    QList <Bullet*> m_bulletList;
    QTimer *timer;
    Scoreboard scoreboard;
    int x_offset,y_offset;
    int tower_kind=1;
    int waves=0;
    int level=1;
    int width=1280;
    int height=800;
    int side=80;
    int city_movement=1;
    bool gameWin=false;
    bool gameEnded=false;
    QPixmap map;
    QPixmap picture;

private slots:
    void updateMap();
    void gamestart()
    {
        loadWave();
    }

};

#endif // GAMESCENE_H
