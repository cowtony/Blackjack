#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "decks.h"

#define MAX_PLAYER 5
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_pushButton_Play_clicked();
    void dealCard(int player);
    void talk(int);
    void dealerPlay();

private:
    Ui::MainWindow *ui;

    Player player[MAX_PLAYER];
    Dealer dealer;
    Decks deck;

    void reset();
    void settlement();

};

#endif // MAINWINDOW_H
