#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QObject>

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

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    int health;
    int coins;
    bool isJumping;
    bool isCrouching;
    bool isAttacking;
    bool isRight, isLeft;
};

#endif // PLAYER_H

