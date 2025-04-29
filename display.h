#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsItem>
#include <QFont>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

            class Display : public QGraphicsItem
{
public:
    Display(int initialHealth, int level, QGraphicsScene* scene);
    void updateHealth(int newHealth);
    void updateLevel(int newLevel);
    void updateDisplay();

    // Override boundingRect and paint for custom rendering
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int health;  // The player's current health
    int level;   // The current level number
    QGraphicsTextItem* healthText;
    QGraphicsTextItem* levelText;
    QGraphicsRectItem* healthBar; // To show health as a bar
    QGraphicsScene* scene;
};

#endif // DISPLAY_H
