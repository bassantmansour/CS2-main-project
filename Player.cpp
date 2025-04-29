#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QDebug>

Player::Player() : health(100), coins(0), isJumping(false), isCrouching(false), isAttacking(false), isRight(false), isLeft(false) {
    QPixmap standingPixmap(":/Character/playerstanding.png");
    QPixmap runningRightPixmap(":/Character/runningright.png");
    QPixmap runningLeftPixmap(":/Character/runningleft.png");
    QPixmap crouchPixmap(":/Character/playercrouch.png");
    QPixmap attackPixmap(":/Character/playersword.png");

    int width = 150;
    int height = 200;
    standingImage = standingPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    runningRightImage = runningRightPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    runningLeftImage = runningLeftPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    crouchImage = crouchPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    attackImage = attackPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(standingImage);
    setPos(100, 400);

    velocityY = 0;
    jumpTimer = new QTimer(this);

    groundY = y();

    connect(jumpTimer, &QTimer::timeout, this, [this]() {
        setPos(x(), y() - velocityY);
        velocityY -= 1;

        qDebug() << "Player Y:" << y() << " velocityY:" << velocityY;

        QList<QGraphicsItem*> colliding = collidingItems();
        for (QGraphicsItem* item : colliding) {
            if (item == this) continue;

            if (item->data(0) == "platform" &&
                velocityY < 0 &&
                y() + boundingRect().height() >= item->y()) {

                setY(item->y() - boundingRect().height());
                isJumping = false;
                velocityY = 0;
                jumpTimer->stop();
                setPixmap(standingImage);
                qDebug() << "LANDED ON PLATFORM";
                return;
            }
        }

        if (velocityY < 0 && y() >= groundY) {
            setY(groundY);
            isJumping = false;
            velocityY = 0;
            jumpTimer->stop();
            setPixmap(standingImage);
            qDebug() << "LANDED ON GROUND";
        }

        if (y() > 1000) {
            setY(groundY);
            isJumping = false;
            velocityY = 0;
            jumpTimer->stop();
            setPixmap(standingImage);
            qDebug() << "FELL AND RESET TO GROUND";
        }
    });
}

Player::~Player() {}

void Player::moveForward() {
    isRight = true;
    setPixmap(runningRightImage);
    if (x() < 600) setPos(x() + 25, y());
}

void Player::moveBackward() {
    isLeft = true;
    setPixmap(runningLeftImage);
    if (x() > 100) setPos(x() - 25, y());
}

void Player::jump() {
    if (!isJumping) {
        isJumping = true;
        velocityY = 15;
        jumpTimer->start(20);
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
    setPos(x, y);
    groundY = y;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Player::heal(int healthPoints) {
    health += healthPoints;
    if (health > 100) health = 100;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int h) {
    health = h;
}

void Player::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right) moveForward();
    else if (event->key() == Qt::Key_Left) moveBackward();
    else if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Up) jump();
    else if (event->key() == Qt::Key_Down) crouch();
    else if (event->key() == Qt::Key_A) attack();
}

void Player::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Down || event->key() == Qt::Key_A ||
        event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        isCrouching = false;
        isAttacking = false;
        isRight = false;
        isLeft = false;
        setPixmap(standingImage);
    }
}
<<<<<<< HEAD


=======
>>>>>>> ff98e12 (29 april)
