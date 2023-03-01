#ifndef DECKS_H
#define DECKS_H
#include <QRandomGenerator>

class Decks
{
public:
    Decks();
    void reset(int decks);
    int drawACard();

private:
    int numberOfDecks;
    int remainingCards[10];
    int numberOfRemainingCards;
    QRandomGenerator random;
};

#endif // DECKS_H
