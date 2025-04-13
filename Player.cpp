#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>

Player::Player() : health(100), coins(0), isJumping(false), isCrouching(false), isAttacking(false), isRight (false), isLeft (false) {
    setPixmap(QPixmap(":/images/playerstanding.png"));
    setPos(100, 100);
}

Player::~Player() {}

void Player::moveForward() {
    isRight = true;
    setPixmap(QPixmap(":/images/runningright.png"));
    setPos(x() + 5, y());

}

void Player::moveBackward() {
    isLeft = true;
    setPixmap(QPixmap(":/images/runningleft.png"));
    setPos(x() - 5, y());
}

void Player::jump() {
    if (!isJumping) {
        isJumping = true;
        setPos(x(), y() - 50);
        QTimer::singleShot(500, this, [this]() { isJumping = false; setPos(x(), y() + 50); });
    }
}

void Player::crouch() {
    isCrouching = true;
    setPixmap(QPixmap(":/images/playercrouch.png"));
}


void Player::attack() {
    isAttacking = true;
    setPixmap(QPixmap(":/images/playersword.png"));
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
        setPixmap(QPixmap(":/images/playerstanding.png"));
    }
    if (event->key() == Qt::Key_A) {
        isAttacking = false;
        setPixmap(QPixmap(":/images/playerstanding.png"));
    }
    if (event->key() == Qt::Key_Left) {
        isLeft = false;
        setPixmap(QPixmap(":/images/playerstanding.png"));
    }
    if (event->key() == Qt::Key_Right) {
        isRight = false;
        setPixmap(QPixmap(":/images/playerstanding.png"));
    }

}
