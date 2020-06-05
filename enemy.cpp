#include "enemy.h"
#include "gamescene.h"

Enemy::Enemy(WayPoint *startWayPoint, GameScene *game, const QPixmap &sprite)
    :QObject(0),
      current_pos(startWayPoint->getPos()), c_sprite(sprite)
{
    destination_waypoint = startWayPoint->getNextWayPoint();
    m_game = game;
    e_fireRateTimer = new QTimer(this);
    connect(e_fireRateTimer, SIGNAL(timeout()), this, SLOT(attackPrincess()));
}

Enemy::~Enemy()
{
    destination_waypoint = NULL;
    m_game = NULL;
}

void Enemy::draw(QPainter &painter)
{
    if (!active)
        return;
    painter.save();
    static const int Health_Bar_Width = 20;
    QPoint healthBarPoint = current_pos + QPoint(-Health_Bar_Width / 2 -10, -60);
    // 绘制血条
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(2 * Health_Bar_Width, 4));
    painter.drawRect(healthBarBackRect);
    painter.setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize(2 * (double)current_hp / max_hp * Health_Bar_Width, 4));
    painter.drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    painter.translate(current_pos);

    // 绘制敌人
    painter.drawPixmap(-50, -50, 120, 100, c_sprite);
    // 保存状态
    painter.restore();
}

void Enemy::move()
{
    if (!active)
        return;
    if (arrive_princess)
        return;
    if (arrive(current_pos, 10, destination_waypoint->getPos(), 10))
    {
        // 敌人抵达了一个航点
        if (destination_waypoint->getNextWayPoint())
        {
            // 还有下一个航点
            destination_waypoint = destination_waypoint->getNextWayPoint();
        }
        else
        {
            e_fireRateTimer->start(attack_speed);
            m_game->city.enemy_list.push_back(this);
            arrive_princess = true;
            // 表示进入基地
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = destination_waypoint->getPos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    double movementSpeed = run_speed;
    QVector2D normalized(targetPoint - current_pos);
    normalized.normalize(); // 向量标准化，让一个向量保持相同的方向，但它的长度为1.0，如果这个向量太小而不能被规范化，一个零向量将会被返回。
    current_pos = current_pos + normalized.toPoint() * movementSpeed; //
    // 确定敌人选择方向
}

void Enemy::setActive()
{
    active = true;
}

void Enemy::getRemoved()
{
    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();	// 通知game,此敌人已经阵亡
    m_game->city.enemy_list.removeOne(this);
    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{
    current_hp -= damage; 	// 阵亡,需要移除
    if (current_hp <= 0)
        getRemoved();
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

void Enemy::attackCity()
{
    m_game->city.getDamage(attack);
}

Enemy2::Enemy2(WayPoint *startWayPoint, GameScene *game, const QPixmap &sprite):
    Enemy(startWayPoint,game,sprite){}

Enemy2::~Enemy2()
{
    destination_waypoint = NULL;
    m_game = NULL;
}

void Enemy2::move()
{
    if (!active)
        return;
    if (arrive(current_pos, 10, destination_waypoint->getPos(), 10))
    {
        // 敌人抵达了一个航点
        if (destination_waypoint->getNextWayPoint())
        {
            // 还有下一个航点
            destination_waypoint = destination_waypoint->getNextWayPoint();
        }
        else
        {
            m_game->city.enemy_list.push_back(this);
            m_game->city.getDamage(current_hp);
            getRemoved();
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = destination_waypoint->getPos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    double movementSpeed = run_speed;
    QVector2D normalized(targetPoint - current_pos);
    normalized.normalize(); // 向量标准化，让一个向量保持相同的方向，但它的长度为1.0，如果这个向量太小而不能被规范化，一个零向量将会被返回。
    current_pos = current_pos + normalized.toPoint() * movementSpeed; //
    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
}

Enemy3::Enemy3(WayPoint *startWayPoint, GameScene *game, const QPixmap &sprite):
    Enemy(startWayPoint,game,sprite){}

Enemy3::~Enemy3()
{
    destination_waypoint = NULL;
    m_game = NULL;
}

void Enemy3::move()
{
    if (!active)
        return;
    if (arrive(current_pos, 10, destination_waypoint->getPos(), 10))
    {
        // 敌人抵达了一个航点
        if (destination_waypoint->getNextWayPoint())
        {
            // 还有下一个航点
            destination_waypoint = destination_waypoint->getNextWayPoint();
        }
        else
        {
            m_game->city.enemy_list.push_back(this);
            m_game->city.getDamage(current_hp);
            getRemoved();
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = destination_waypoint->getPos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    double movementSpeed = run_speed;
    QVector2D normalized(targetPoint - current_pos);
    normalized.normalize(); // 向量标准化，让一个向量保持相同的方向，但它的长度为1.0，如果这个向量太小而不能被规范化，一个零向量将会被返回。
    current_pos = current_pos + normalized.toPoint() * movementSpeed; //
    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
}
