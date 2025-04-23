#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QPixmap>
#include <QTimer>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Player();
    ~Player();

    void moveForward();
    void moveBackward();
    void jump();
    void crouch();
    void attack();

    void setPosition(int x, int y);
    void takeDamage(int damage);
    void heal(int healthPoints);

    int getHealth() const;
    void setHealth(int health);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    bool isMovingRight() const { return isRight; }
    bool isMovingLeft() const { return isLeft; }

private:
    int health;
    int coins;
    bool isJumping;
    bool isCrouching;
    bool isAttacking;
    bool isRight, isLeft;
    float totalDistanceMoved = 0.0f;
    QTimer* jumpTimer;
    int velocityY;
    int groundY;

    QPixmap standingImage;
    QPixmap runningRightImage;
    QPixmap runningLeftImage;
    QPixmap crouchImage;
    QPixmap attackImage;
};

#endif 


#endif // PLAYER_H
