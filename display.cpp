#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QFont>
#include "Display.h"

Display::Display(int initialHealth, int level, QGraphicsScene* scene)
    : health(initialHealth), level(level), scene(scene)
{
    // Create the health text item
    healthText = new QGraphicsTextItem("Health: " + QString::number(health) + "%");
    healthText->setDefaultTextColor(Qt::red);
    healthText->setPos(10, 10);
    scene->addItem(healthText);

    // Create the level text item
    levelText = new QGraphicsTextItem("Level: " + QString::number(level));
    levelText->setDefaultTextColor(Qt::white);
    levelText->setPos(10, 30);
    scene->addItem(levelText);

    // Create the health bar
    healthBar = new QGraphicsRectItem(10, 50, 200, 20);
    healthBar->setBrush(Qt::green);
    scene->addItem(healthBar);
}

void Display::updateHealth(int newHealth)
{
    health = newHealth;
    updateDisplay();
}

void Display::updateLevel(int newLevel)
{
    level = newLevel;
    updateDisplay();
}

void Display::updateDisplay()
{
    // Update the health text
    healthText->setPlainText("Health: " + QString::number(health) + "%");

    // Update the health bar (width will depend on health percentage)
    healthBar->setRect(10, 50, (health * 2), 20); // Health bar width based on percentage (200px = 100%)

    // Update the level text
    levelText->setPlainText("Level: " + QString::number(level));
}

QRectF Display::boundingRect() const
{
    return QRectF(0, 0, 220, 80);  // Area covered by the display
}

void Display::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Custom rendering of the display
}
