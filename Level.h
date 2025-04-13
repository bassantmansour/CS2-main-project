#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QVector>
#include "Player.h"  // Assuming you have a Player class

class Level {
private:
    QGraphicsScene* scene;       // Scene to hold level objects
    QVector<QGraphicsItem*> obstacles;  // List of obstacles
    QVector<QGraphicsItem*> enemies;    // List of enemies
    Player* p1;              // The player object
    int levelNumber;             // Current level number

public:
    Level(int number, QGraphicsScene* scene, Player* p1);  // Constructor with level number, scene, and player
    void setupLevel();                                          // Setup level objects (obstacles, enemies, etc.)
    void addObstacle(QGraphicsItem* obstacle);                  // Add obstacle to the level
    void addEnemy(QGraphicsItem* enemy);                        // Add enemy to the level
    void resetLevel();                                          // Reset the level (e.g., restart the level)
    void nextLevel();                                           // Move to the next level
    int getLevelNumber() const;                                 // Get the current level number
};

#endif // LEVEL_H


