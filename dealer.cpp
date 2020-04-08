#include "dealer.h"

Dealer::Dealer()
{
    money = 100;
}

void Dealer::init(int id, Decks* deck, QLabel* label)
{
    playerID  = id;
    decks     = deck;
    labelShow = label;
}

int Dealer::getSum() const
{
    return sum;
}

int Dealer::getNumberOfCards() const
{
    return cards.size();
}

void Dealer::startGame()
{
    labelShow->setText("");
    sum = 0;
    cards.clear();
}

void Dealer::getCard()
{
    int number = decks->drawACard();

    cards.append(number);

    display();
}

void Dealer::display()
{
    sum = 0;
    QString s = "";
    for (int i: cards)
    {
        if (i == 1)
            s += " A";
        else
            s += QString::number(i) + " ";
        sum += i;
    }

    if (cards.contains(1) && sum <= 11)
    {
        s += "(" + QString::number(sum) + "/" + QString::number(sum + 10) + ")";
        sum += 10;
    }
    else
        s += "(" + QString::number(sum) + ")";

    if (sum > 21)
        s += " BUST!";

    labelShow->setText(s);
}
