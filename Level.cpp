#include "Level.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QTimer>

Level::Level(int number, QGraphicsScene* scene, Player* p1) {
    this->scene = scene;
    this->p1 = p1;
    this->levelNumber = number;
}

void Level::setupLevel() {
    // Clear existing obstacles and enemies in the scene
    for (auto* item : obstacles) {
        scene->removeItem(item);
        delete item;
    }
    for (auto* item : enemies) {
        scene->removeItem(item);
        delete item;
    }

    obstacles.clear();
    enemies.clear();

    const int groundLevel = 450; // Y-position for ground level

    // Set up obstacles, enemies, and the player based on the current level
    if (levelNumber == 1) {
        // LEVEL 1: Desert theme with scaled and properly placed obstacles

        // Add ground platform using brownbricks
        for (int x = 0; x < 800; x += 64) {
            QGraphicsPixmapItem* brick = new QGraphicsPixmapItem(QPixmap(":/backgrounds/brownbricks.png").scaled(64, 64, Qt::KeepAspectRatio));
            brick->setPos(x, groundLevel);
            addObstacle(brick);
        }

        // Add cactus obstacles - scaled appropriately
        QGraphicsPixmapItem* cactus1 = new QGraphicsPixmapItem(QPixmap(":/Obstacles/cactus.png").scaled(50, 100, Qt::KeepAspectRatio));
        cactus1->setPos(200, groundLevel - 100); // Place on top of ground
        addObstacle(cactus1);

        QGraphicsPixmapItem* cactus2 = new QGraphicsPixmapItem(QPixmap(":/Obstacles/cactus.png").scaled(50, 100, Qt::KeepAspectRatio));
        cactus2->setPos(500, groundLevel - 100);
        addObstacle(cactus2);

        // Add a fire pit - scaled appropriately
        QGraphicsPixmapItem* firepit = new QGraphicsPixmapItem(QPixmap(":/Obstacles/firepit.png").scaled(80, 40, Qt::KeepAspectRatio));
        firepit->setPos(350, groundLevel - 40);
        addObstacle(firepit);

        // Add quicksand - scaled appropriately
        QGraphicsPixmapItem* quicksand = new QGraphicsPixmapItem(QPixmap(":/Obstacles/quicksand.png").scaled(100, 30, Qt::KeepAspectRatio));
        quicksand->setPos(600, groundLevel - 15); // Slightly embedded in ground
        addObstacle(quicksand);

        // Add a reward - scaled appropriately
        QGraphicsPixmapItem* water = new QGraphicsPixmapItem(QPixmap(":/Rewards/waterdroplet.tiff").scaled(30, 30, Qt::KeepAspectRatio));
        water->setPos(700, groundLevel - 150); // Positioned higher to make it harder to reach
        addObstacle(water);

    } else if (levelNumber == 2) {
        // LEVEL 2: More complex layout

        // Add ground platforms with gaps
        int platformSegments[] = {0, 150, 250, 400, 500, 650, 750, 800};
        for (int i = 0; i < 7; i++) {
            for (int x = platformSegments[i]; x < platformSegments[i+1]; x += 64) {
                QGraphicsPixmapItem* brick = new QGraphicsPixmapItem(QPixmap(":/backgrounds/brownbricks.png").scaled(64, 64, Qt::KeepAspectRatio));
                brick->setPos(x, groundLevel);
                addObstacle(brick);
            }
        }

        // Add elevated platforms
        for (int x = 200; x < 350; x += 64) {
            QGraphicsPixmapItem* brick = new QGraphicsPixmapItem(QPixmap(":/backgrounds/brownbricks.png").scaled(64, 32, Qt::KeepAspectRatio));
            brick->setPos(x, groundLevel - 150);
            addObstacle(brick);
        }

        for (int x = 500; x < 650; x += 64) {
            QGraphicsPixmapItem* brick = new QGraphicsPixmapItem(QPixmap(":/backgrounds/brownbricks.png").scaled(64, 32, Qt::KeepAspectRatio));
            brick->setPos(x, groundLevel - 200);
            addObstacle(brick);
        }

        // Add cactus - properly scaled
        QGraphicsPixmapItem* cactus = new QGraphicsPixmapItem(QPixmap(":/Obstacles/cactus.png").scaled(50, 100, Qt::KeepAspectRatio));
        cactus->setPos(300, groundLevel - 100);
        addObstacle(cactus);

        // Add fire pits - properly scaled
        QGraphicsPixmapItem* firepit1 = new QGraphicsPixmapItem(QPixmap(":/Obstacles/firepit.png").scaled(80, 40, Qt::KeepAspectRatio));
        firepit1->setPos(425, groundLevel - 40);
        addObstacle(firepit1);

        QGraphicsPixmapItem* firepit2 = new QGraphicsPixmapItem(QPixmap(":/Obstacles/firepit.png").scaled(80, 40, Qt::KeepAspectRatio));
        firepit2->setPos(675, groundLevel - 40);
        addObstacle(firepit2);

        // Add rewards
        QGraphicsPixmapItem* water1 = new QGraphicsPixmapItem(QPixmap(":/Rewards/waterdroplet.tiff").scaled(30, 30, Qt::KeepAspectRatio));
        water1->setPos(275, groundLevel - 200); // Above platform
        addObstacle(water1);

        QGraphicsPixmapItem* water2 = new QGraphicsPixmapItem(QPixmap(":/Rewards/waterdroplet.tiff").scaled(30, 30, Qt::KeepAspectRatio));
        water2->setPos(575, groundLevel - 250); // Above higher platform
        addObstacle(water2);
    }

    // Add the player to the scene at the start of each level
    scene->addItem(p1);
    p1->setPosition(50, groundLevel - 100);  // Starting position just above ground level
}

void Level::addObstacle(QGraphicsItem* obstacle) {
    obstacles.push_back(obstacle);
    scene->addItem(obstacle);
}

void Level::addEnemy(QGraphicsItem* enemy) {
    enemies.push_back(enemy);
    scene->addItem(enemy);
}

void Level::resetLevel() {
    // Reset the player and obstacles for the level
    p1->setPosition(50, 350);  // Reset player to starting position
    p1->setHealth(100);        // Reset player health to full

    // Reload the obstacles and enemies for the current level
    setupLevel();
}

void Level::nextLevel() {
    // Move to the next level by incrementing levelNumber
    levelNumber++;
    setupLevel();
}

int Level::getLevelNumber() const {
    return levelNumber;
}
