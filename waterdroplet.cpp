#include "waterdroplet.h"
#include <QGraphicsScene>

                   WaterDroplet::WaterDroplet(int x, int y)
{
    QPixmap dropletPixmap(":/waterdroplet.tiff");
    setPixmap(dropletPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setPos(x, y);
    setData(0, "droplet");
}

void WaterDroplet::checkCollision(Player* player)
{
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (item == player) {
            scene()->removeItem(this);
            this->deleteLater();
            player->incrementDroplets();
        }
    }
}
