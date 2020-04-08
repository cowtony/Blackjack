#ifndef DEALER_H
#define DEALER_H
#include <QList>
#include <QLabel>
#include "decks.h"

class Dealer
{
public:
    Dealer();

    void init(int, Decks*, QLabel*);

    int getNumberOfCards() const;
    int getSum() const;

    void startGame();
    void getCard();

protected:
    int playerID;
    int money;
    int sum;
    QList<int> cards;
    Decks* decks;

    QLabel* labelShow;

    void display();
};

#endif // DEALER_H
