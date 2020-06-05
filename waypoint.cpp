#include "waypoint.h"

WayPoint::WayPoint(QPoint pos):pos(pos),nextWayPoint(NULL)
{

}

void WayPoint::setNextWayPoint(WayPoint *nextPoint)
{
    nextWayPoint = nextPoint;
}

WayPoint* WayPoint::getNextWayPoint() const
{
    return nextWayPoint;
}

QPoint WayPoint::getPos() const
{
    return pos;
}
