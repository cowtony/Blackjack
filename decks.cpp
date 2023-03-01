#include "decks.h"

#include <QDebug>

Decks::Decks()
{
    random.seed(1);
}

void Decks::reset(int decks)
{
    numberOfDecks = decks;

    for (int i = 0; i < 9; i++)
        remainingCards[i] = decks * 4;
    remainingCards[9] = decks * 16;

    numberOfRemainingCards = decks * 52;
}

int Decks::drawACard()
{
    int draw = random.bounded(1, numberOfRemainingCards);

    for (int i = 0; i < 10; i++)
    {
        if (draw <= remainingCards[i])
        {
            numberOfRemainingCards--;
            remainingCards[i]--;

            return i + 1;
        }
        else
        {
            draw -= remainingCards[i];
        }
    }

}
