#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Level.h"
#include "Player.h"

class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game(QWidget* parent = nullptr);
    ~Game();

    void startGame();

private:
    QGraphicsScene* scene;
    Player* p1;
    Level* currentLevel;
    int levelIndex;
};

#endif // GAME_H
