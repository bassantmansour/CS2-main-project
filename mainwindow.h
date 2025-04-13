#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "Player.h"
#include "Level.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;  // The main scene where the game happens
    QGraphicsView *view;    // View to show the scene
    Player *player;         // The player object
    Level *level;           // The current level
    void setupGame();       // Function to set up the game environment
    void updateGame();      // Update the game each frame
    // protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    QGraphicsPixmapItem* bg1;
    QGraphicsPixmapItem* bg2;

};

#endif // MAINWINDOW_H
