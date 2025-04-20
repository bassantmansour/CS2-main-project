#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGame();

    // Set window title and size
    setWindowTitle("Desert Adventure Game");
    setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete view;
    delete player;
    delete level;
}

void MainWindow::setupGame()
{
    // Create the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    // Create the view and set it as the central widget
    view = new QGraphicsView(scene, this);
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing); // Smoother graphics
    setCentralWidget(view);

    // Set background - desert scene scaled to fit
    QPixmap bgPixmap(":/backgrounds/desertbackground.jpg");
    bgPixmap = bgPixmap.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Add two background images side by side
    bg1 = scene->addPixmap(bgPixmap);
    bg2 = scene->addPixmap(bgPixmap);

    // Set their positions and z-order
    bg1->setPos(0, 0);
    bg2->setPos(800, 0);
    bg1->setZValue(-1);
    bg2->setZValue(-1);


    // Create player
    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    // Create level
    level = new Level(1, scene, player);
    level->setupLevel();

    // Create a game loop timer for updating animations and game state
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16); // Approximately 60 FPS

    // Give focus to the player so it can receive key events
    player->setFocus();
}

void MainWindow::updateGame()
{
    if (player->y() > 600) {
        level->resetLevel();
        return;
    }

    if (!player->hasFocus()) {
        player->setFocus();
    }

    const int scrollSpeed = 5;

    // Scroll left if player is at right boundary and moving right
    if (player->x() >= 600 && player->isMovingRight()) {
        bg1->moveBy(-scrollSpeed, 0);
        bg2->moveBy(-scrollSpeed, 0);

        if (bg1->x() + 800 <= 0) {
            bg1->setX(bg2->x() + 800);
        }
        if (bg2->x() + 800 <= 0) {
            bg2->setX(bg1->x() + 800);
        }

        for (QGraphicsItem* item : scene->items()) {
            if (item == player || item == bg1 || item == bg2) continue;
            item->moveBy(-scrollSpeed, 0);
        }
    }

    // Scroll right if player is at left boundary and moving left
    if (player->x() <= 100 && player->isMovingLeft()) {
        bg1->moveBy(scrollSpeed, 0);
        bg2->moveBy(scrollSpeed, 0);

        if (bg1->x() >= 800) {
            bg1->setX(bg2->x() - 800);
        }
        if (bg2->x() >= 800) {
            bg2->setX(bg1->x() - 800);
        }

        for (QGraphicsItem* item : scene->items()) {
            if (item == player || item == bg1 || item == bg2) continue;
            item->moveBy(scrollSpeed, 0);
        }
    }

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Forward key events to the player
    player->keyPressEvent(event);

    // Additional game controls
    if (event->key() == Qt::Key_R) {
        // Reset level on 'R' key
        level->resetLevel();
    } else if (event->key() == Qt::Key_N) {
        // Next level on 'N' key
        level->nextLevel();
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // Forward key events to the player
    player->keyReleaseEvent(event);
    QMainWindow::keyReleaseEvent(event);
}
