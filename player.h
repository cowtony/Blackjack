#ifndef PLAYER_H
#define PLAYER_H
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include "dealer.h"
#include "decks.h"

class Player : public QObject, public Dealer
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void init(int, Decks*, QGroupBox*, QComboBox*, QLabel*, QSpinBox*, QLabel*, QPushButton*, QPushButton*, QPushButton*, QPushButton*);

    void reset();
    void startGame();
    void freezeMove(const bool& freeze);
    void getResult(const int& number);
    bool isOnTable() const;

signals:
    void nextPlayerTalk(int playerID);

public slots:
    void getCard();

private slots:
    void on_playerType_Changed(int index);
    void on_bet_Changed(int value);
    void on_Double();
    void finishPlay();

private:
    QGroupBox*   groupBox;
    QComboBox*   playerType;
    QLabel*      labelBet;
    QSpinBox*    bet;
    QPushButton* buttonDouble;
    QPushButton* buttonSplit;
    QPushButton* buttonHit;
    QPushButton* buttonStand;

    void win();
    void lose();
    void draw();
};

#endif // PLAYER_H
