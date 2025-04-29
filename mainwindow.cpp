#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QFont>
#include <QPixmap>
#include "obstacle.h"
#include "waterdroplet.h"
#include <QGraphicsRectItem>
#include <QPen>


                 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGame();

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
    bgPixmap = bgPixmap.scaled(800, 600);
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

    // Health bar outline
    healthOutline = new QGraphicsRectItem(0, 0, 200, 20); // Fixed size
    healthOutline->setPen(QPen(Qt::black));              // Black border
    healthOutline->setBrush(Qt::NoBrush);                // Transparent inside
    scene->addItem(healthOutline);

    // Health bar fill (green inside)
    healthBar = new QGraphicsRectItem(0, 0, 200, 20);     // Same size initially
    healthBar->setBrush(Qt::green);                      // Green fill
    healthBar->setPen(Qt::NoPen);                        // No border
    scene->addItem(healthBar);



    // Level Text
    levelText = new QLabel("Level: 1", this);
    levelText->setStyleSheet("color: black; font-weight: bold;");
    levelText->move(600, 10);
    levelText->resize(150, 30);

    // Water Icon
    waterIcon = new QLabel(this);
    waterIcon->setPixmap(QPixmap(":/Obstacles/waterdroplet.tiff").scaled(30, 30));
    waterIcon->move(600, 50);
    waterIcon->resize(30, 30);

    // Score Text
    scoreText = new QLabel("0/20", this);
    scoreText->setStyleSheet("color: black; font-weight: bold;");
    scoreText->move(635, 50);
    scoreText->resize(100, 30);

    // Update timer
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);
}

void MainWindow::updateHealthBar()
{
    int hp = player->getHealth();
    healthBar->setRect(0, 0, 2 * hp, 20);  // Shrink width based on health
}

void MainWindow::updateScore()
{
    int collected = player->getCollectedDroplets();
    scoreText->setText(QString::number(collected) + "/20");
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

        // Move other items (e.g., bricks, enemies, etc.) based on scroll
        for (QGraphicsItem* item : scene->items()) {
            if (item == player || item == bg1 || item == bg2) continue;

            // Check if item is off the screen to the left, and reposition it
            if (item->x() + item->boundingRect().width() < 0) {
                item->setX(scene->sceneRect().width());
            }

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

        // Move other items (e.g., bricks, enemies, etc.) based on scroll
        for (QGraphicsItem* item : scene->items()) {
            if (item == player || item == bg1 || item == bg2) continue;

            // Check if item is off the screen to the right, and reposition it
            if (item->x() > scene->sceneRect().width()) {
                item->setX(0 - item->boundingRect().width());
            }

            item->moveBy(scrollSpeed, 0);
        }
    }
    int margin = 10;
    int viewRight = this->width();
    healthOutline->setPos(viewRight - 230, margin + 30);
    healthBar->setPos(viewRight - 230, margin + 30);


    updateHealthBar();
    updateScore();

}




void MainWindow::keyPressEvent(QKeyEvent *event)
{
    player->keyPressEvent(event);
    if (event->key() == Qt::Key_R) {
        level->resetLevel();
    } else if (event->key() == Qt::Key_N) {
        level->nextLevel();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
    QMainWindow::keyReleaseEvent(event);
}
