#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>


class WayPoint
{
public:
    WayPoint(QPoint pos);
    void setNextWayPoint(WayPoint *nextPoint);
    WayPoint* getNextWayPoint() const;
    QPoint getPos() const;

private:
    QPoint pos;
    WayPoint * nextWayPoint;
};

#endif // WAYPOINT_H
