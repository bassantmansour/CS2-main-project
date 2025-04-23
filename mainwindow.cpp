#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QtCore/qtimer.h>

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
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    view = new QGraphicsView(scene, this);
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    QPixmap bgPixmap(":/backgrounds/desertbackground.jpg");
    bgPixmap = bgPixmap.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    bg1 = scene->addPixmap(bgPixmap);
    bg2 = scene->addPixmap(bgPixmap);
    bg1->setPos(0, 0);
    bg2->setPos(800, 0);
    bg1->setZValue(-1);
    bg2->setZValue(-1);

    player = new Player();
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPosition(100, 400);

    level = new Level(1, scene, player);
    level->setupLevel();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);

    scene->setSceneRect(0, 0, 800, 600);
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
