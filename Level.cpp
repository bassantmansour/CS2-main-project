#include "Level.h"
#include "obstacle.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include "waterdroplet.h"


            Level::Level(int number, QGraphicsScene* scene, Player* p1)
    : scene(scene), p1(p1), levelNumber(number)
{
}

void Level::setupLevel()
{
    // Clear previous obstacles
    for (auto* item : obstacles) {
        scene->removeItem(item);
        delete item;
    }
    obstacles.clear();

    for (int i = 0; i < 20; ++i) {
        int x = 150 + i * 100;
        int y = 100 + (i % 3) * 80;
        WaterDroplet* droplet = new WaterDroplet(x, y);
        scene->addItem(droplet);
    }


    const int groundY = 550;
    const int platformWidth = 250;
    const int platformHeight = 100;
    const int platformSpacingY = 80;

    if (levelNumber == 1) {
        QVector<QPoint> platformPositions = {
                                             {100, groundY - platformSpacingY},
                                             {300, groundY - 2 * platformSpacingY},
                                             {500, groundY - 3 * platformSpacingY},
                                             {200, groundY - 4 * platformSpacingY},
                                             {400, groundY - 5 * platformSpacingY},
                                             {600, groundY - 6 * platformSpacingY},
                                             };

        QRandomGenerator *randomGen = QRandomGenerator::global();

        // Add platforms to the scene
        for (const QPoint& pos : platformPositions) {
            QGraphicsPixmapItem* platform = new QGraphicsPixmapItem(QPixmap(":/backgrounds/brownbricks.png").scaled(platformWidth, platformHeight));
            platform->setPos(pos);
            platform->setData(0, "platform");
            scene->addItem(platform);  // Add the platform to the scene
            obstacles.append(platform); // Track platform in the obstacles list
        }

        // Add random obstacles
        for (const QPoint& pos : platformPositions) {
            // Randomly pick one of the three obstacles
            int randObstacle = randomGen->bounded(3); // Random number between 0 and 2

            // Place fire obstacle
            if (randObstacle == 0) {
                Fire* fire = new Fire(pos.x() + 80, pos.y() - platformHeight / 2);  // Adjust Y position to place on top of the platform
                addObstacle(fire);
            }
            // Place cactus obstacle
            else if (randObstacle == 1) {
                Cactus* cactus = new Cactus(pos.x() + 100, pos.y() - platformHeight / 2);  // Slight X offset
                addObstacle(cactus);
            }
            // Place quicksand obstacle
            else if (randObstacle == 2) {
                Quicksand* quicksand = new Quicksand(pos.x() - 50, pos.y() + 50);  // Below the platform
                quicksand->setLevel(this);
                addObstacle(quicksand);
            }
        }
    }

    // Add player
    scene->addItem(p1);
    p1->setPosition(50, groundY - 100); // Start just above the ground
}




void Level::addObstacle(QGraphicsItem* obstacle) {
    obstacles.push_back(obstacle);
    scene->addItem(obstacle);
}

void Level::addFireObstacles() {
    const int groundY = 550;
    const int platformSpacingY = 80;

    // Fire obstacles will be placed directly on the platforms.
    QVector<QPoint> firePositions = {
        {100, groundY - platformSpacingY - 50},  // On first platform
        {300, groundY - 2 * platformSpacingY - 50},  // On second platform
        {500, groundY - 3 * platformSpacingY - 50}   // On third platform
    };

    for (const QPoint& pos : firePositions) {
        Fire* fire = new Fire(pos.x(), pos.y());
        addObstacle(fire);
    }
}

void Level::addCactusObstacles() {
    const int groundY = 550;
    const int platformSpacingY = 80;

    // Cactus obstacles will be placed directly on the platforms.
    QVector<QPoint> cactusPositions = {
        {300, groundY - 2 * platformSpacingY - 30},  // On second platform
        {500, groundY - 3 * platformSpacingY - 30}   // On third platform
    };

    for (const QPoint& pos : cactusPositions) {
        Cactus* cactus = new Cactus(pos.x(), pos.y());
        addObstacle(cactus);
    }
}

void Level::addQuicksandObstacles() {
    const int groundY = 550;
    const int platformSpacingY = 80;

    // Quicksand obstacles will be placed directly on the platforms.
    QVector<QPoint> quicksandPositions = {
        {100, groundY - platformSpacingY - 50},  // On first platform
        {300, groundY - 2 * platformSpacingY - 50},  // On second platform
        {500, groundY - 3 * platformSpacingY - 50}   // On third platform
    };

    for (const QPoint& pos : quicksandPositions) {
        Quicksand* quicksand = new Quicksand(pos.x(), pos.y());
        quicksand->setLevel(this);
        addObstacle(quicksand);
    }
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
