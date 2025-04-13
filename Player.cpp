#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>

Player::Player() : health(100), coins(0), isJumping(false), isCrouching(false), isAttacking(false), isRight(false), isLeft(false) {
    // Load and scale player images
    QPixmap standingPixmap(":/Character/playerstanding.png");
    QPixmap runningRightPixmap(":/Character/runningright.png");
    QPixmap runningLeftPixmap(":/Character/runningleft.png");
    QPixmap crouchPixmap(":/Character/playercrouch.png");
    QPixmap attackPixmap(":/Character/playersword.png");

    // Scale images to appropriate size (adjust these values as needed)
    int width = 150;
    int height = 200;
    standingPixmap = standingPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation); // maintianing the original ratio and making the image less pixalted
    runningRightPixmap = runningRightPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    runningLeftPixmap = runningLeftPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    crouchPixmap = crouchPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    attackPixmap = attackPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Store scaled pixmaps as member variables for quick access
    standingImage = standingPixmap;
    runningRightImage = runningRightPixmap;
    runningLeftImage = runningLeftPixmap;
    crouchImage = crouchPixmap;
    attackImage = attackPixmap;

    // Set initial pixmap
    setPixmap(standingImage);

    // Set initial position
    setPos(100, 400);
}

Player::~Player() {}

void Player::moveForward() {
    isRight = true;
    setPixmap(runningRightImage);

    if (x() < 600) {
        setPos(x() + 25, y());
    }
}


void Player::moveBackward() {
    isLeft = true;
    setPixmap(runningLeftImage);

    // Only move player until they reach left boundary
    if (x() > 100) {
        setPos(x() - 25, y());
    }

    // Once player reaches left boundary, MainWindow will scroll background instead
}


void Player::jump() {
    if (!isJumping) {
        isJumping = true;

        // Create jump animation using QTimer for smooth movement
        int jumpHeight = 150;
        int jumpDuration = 500; // milliseconds
        int steps = 20;
        int stepDelay = jumpDuration / (steps * 2); // Up and down

        // Jump up
        for (int i = 0; i < steps; i++) {
            QTimer::singleShot(i * stepDelay, this, [this, i, jumpHeight, steps]() {
                setPos(x(), y() - (jumpHeight / steps));
            });
        }

        // Fall down
        for (int i = 0; i < steps; i++) {
            QTimer::singleShot((i + steps) * stepDelay, this, [this, i, jumpHeight, steps]() {
                setPos(x(), y() + (jumpHeight / steps));
            });
        }

        // Reset jumping state
        QTimer::singleShot(jumpDuration, this, [this]() {
            isJumping = false;
        });
    }
}

void Player::crouch() {
    isCrouching = true;
    setPixmap(crouchImage);
}

void Player::attack() {
    isAttacking = true;
    setPixmap(attackImage);
}

void Player::setPosition(int x, int y) {
    setPos(x, y);  // Set player to a specific position
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0)
        health = 0;
}

void Player::heal(int healthPoints) {
    health += healthPoints;
    if (health > 100) health = 100;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int health) {
    this->health = health;
}

void Player::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right) {
        moveForward();
    } else if (event->key() == Qt::Key_Left) {
        moveBackward();
    } else if (event->key() == Qt::Key_Space) {
        jump();
    } else if (event->key() == Qt::Key_Down) {
        crouch();
    } else if (event->key() == Qt::Key_A) {
        attack();
    }
}

void Player::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Down) {
        isCrouching = false;
        setPixmap(standingImage);
    }
    if (event->key() == Qt::Key_A) {
        isAttacking = false;
        setPixmap(standingImage);
    }
    if (event->key() == Qt::Key_Left) {
        isLeft = false;
        setPixmap(standingImage);
    }
    if (event->key() == Qt::Key_Right) {
        isRight = false;
        setPixmap(standingImage);
    }
}
