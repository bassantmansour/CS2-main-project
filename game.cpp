#include "Player.h"
#include "game.h"
#include <QTimer>

Game::Game(QWidget* parent)
    : QGraphicsView(parent), levelIndex(1) {

    // Set up the scene and view
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);

    // Initialize player
    p1 = new Player();
    p1->setFlag(QGraphicsItem::ItemIsFocusable);
    p1->setFocus(); // Ensure the player receives key events

    // Set up first level
    currentLevel = new Level(levelIndex, scene, p1);
    currentLevel->setupLevel();
}

Game::~Game() {
    delete currentLevel;
    delete p1;
    delete scene;
}

void Game::startGame() {
    currentLevel->setupLevel();
}
