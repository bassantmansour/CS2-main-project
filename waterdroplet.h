#ifndef WATERDROPLET_H
#define WATERDROPLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "Player.h"

                                          class WaterDroplet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    WaterDroplet(int x, int y);
    void checkCollision(Player* player);
};

#endif // WATERDROPLET_H
