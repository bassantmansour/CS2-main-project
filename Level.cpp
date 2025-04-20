#include "Level.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

Level::Level(int number, QGraphicsScene* scene, Player* p1)
    : scene(scene), p1(p1), levelNumber(number)
{
}

void Level::setupLevel()
{
    // Clear existing obstacles
    for (auto* item : obstacles) {
        scene->removeItem(item);
        delete item;
    }
    obstacles.clear();

    const int groundY = 550;



    // Add thick, wide platforms stacked upward
    const int platformWidth = 200;
    const int platformHeight = 100;
    const int platformSpacingY = 80;

    QVector<QPoint> platformPositions = {
        {100, groundY - platformSpacingY},
        {300, groundY - 2 * platformSpacingY}, // Row 2
        {500, groundY - 3 * platformSpacingY}, // Row 3
        {200, groundY - 4 * platformSpacingY}, // Row 4
        {400, groundY - 5 * platformSpacingY}, // Row 5
        {600, groundY - 6 * platformSpacingY}, // Row 6
        {100, groundY - 7 * platformSpacingY}, // Row 7
    };

    for (const QPoint& pos : platformPositions) {
        QGraphicsPixmapItem* platform = new QGraphicsPixmapItem(QPixmap(":/backgrounds/brownbricks.png").scaled(platformWidth, platformHeight));
        platform->setPos(pos);
        platform->setData(0, "platform");  // Mark as platform for collision detection
        addObstacle(platform);
    }

    // Add player
    scene->addItem(p1);
    p1->setPosition(50, groundY - 100); // Start just above the ground
}



void Level::addObstacle(QGraphicsItem* obstacle)
{
    obstacles.push_back(obstacle);
    scene->addItem(obstacle);
}

void Level::resetLevel()
{
    p1->setPosition(50, 350);
    p1->setHealth(100);
    setupLevel();
}

void Level::nextLevel()
{
    levelNumber++;
    setupLevel();
}

int Level::getLevelNumber() const
{
    return levelNumber;
}
