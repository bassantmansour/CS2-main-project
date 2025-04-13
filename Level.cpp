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
    // for (auto* item : obstacles) {
    //     scene->removeItem(item);
    // }
    // for (auto* item : enemies) {
    //     scene->removeItem(item);
    // }

    // obstacles.clear();
    // enemies.clear();

    // Set up obstacles, enemies, and the p1 based on the current level
    if (levelNumber == 1) {
        // Level 1 setup: Add some basic obstacles and enemies
        addObstacle(new QGraphicsRectItem(100, 200, 50, 50));  // Example obstacle
        addEnemy(new QGraphicsRectItem(300, 200, 50, 50));      // Example enemy
    } else if (levelNumber == 2) {
        // Level 2 setup: Add more complex obstacles and enemies
        addObstacle(new QGraphicsRectItem(200, 150, 50, 50));  // Example obstacle
        addEnemy(new QGraphicsRectItem(400, 150, 50, 50));     // Example enemy
    }
    // Add the player to the scene at the start of each level
    p1->setPosition(50, 50);  // Starting position of the player
    scene->addItem(p1);
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
    // Reset the player and obstacles for the level (e.g., player position and health)
    p1->setPosition(50, 50);  // Reset player to starting position
    p1->setHealth(0);   // Assuming Player class has a resetHealth() method

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


