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
    QPixmap background(":/backgrounds/desertbackground.jpg");
    background = background.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(background);

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
    // Add game update logic here
    // This will be called approximately 60 times per second

    // Check if player is out of bounds
    if (player->y() > 600) {
        // Player fell off the screen - reset level
        level->resetLevel();
    }

    // Make sure player has focus
    if (!player->hasFocus()) {
        player->setFocus();
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
