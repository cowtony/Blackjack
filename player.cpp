#include "player.h"
#include <QDebug>

Player::Player(QObject *parent) : QObject(parent)
{

}

void Player::init(int id, Decks* deck, QGroupBox* group, QComboBox* player, QLabel* labelB, QSpinBox* spinBox, QLabel* labelS, QPushButton* doubl, QPushButton* split, QPushButton* hit, QPushButton* stand)
{
    Dealer::init(id, deck, labelS);

    groupBox     = group;
    playerType   = player;
    labelBet     = labelB;
    bet          = spinBox;
    buttonDouble = doubl;
    buttonSplit  = split;
    buttonHit    = hit;
    buttonStand  = stand;

    groupBox->setTitle("Player " + QString::number(playerID) + ": $" + QString::number(money));

    bet->setMinimum(1);
    bet->setMaximum(999999);
    bet->setValue(1);
    connect(bet, SIGNAL(valueChanged(int)), this, SLOT(on_bet_Changed(int)));

    playerType->addItems(QStringList() << "Not Seated" << "Player" << "Computer");
    connect(playerType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_playerType_Changed(int)));
    playerType->setCurrentIndex(1);
    playerType->setCurrentIndex(0);
    connect(buttonDouble, SIGNAL(clicked()), this, SLOT(on_Double()));
    connect(buttonHit,    SIGNAL(clicked()), this, SLOT(getCard()));
    connect(buttonStand,  SIGNAL(clicked()), this, SLOT(finishPlay()));

    reset();
}

void Player::reset()
{
    playerType->setEnabled(true);
    on_playerType_Changed(playerType->currentIndex());
    bet         ->setDisabled(false);
    buttonDouble->setDisabled(true);
    buttonSplit ->setDisabled(true);
    buttonHit   ->setDisabled(true);
    buttonStand ->setDisabled(true);
}

bool Player::isOnTable() const
{
    return playerType->currentIndex() != 0;
}

void Player::startGame()
{
    Dealer::startGame();

    playerType->setDisabled(true);
    groupBox->setDisabled(true);
    bet->setDisabled(true);
}

void Player::getCard()
{
    Dealer::getCard();

    if (cards.size() == 2 && cards[0] == cards[1])
        buttonSplit->setEnabled(true);

    if (cards.size() == 2 && money >= 2 * bet->value())
        buttonDouble->setEnabled(true);
    else
        buttonDouble->setEnabled(false);

    if (cards.size() == 2)
    {
        buttonHit->setEnabled(true);
        buttonStand->setEnabled(true);
    }

    if (sum > 21)
        finishPlay();
}

void Player::freezeMove(const bool& freeze)
{
    groupBox->setDisabled(freeze);
}

void Player::getResult(const int& number)
{
    if (!isOnTable())
        return;
    if (sum > 21)
        lose();
    else if (number > 21)
        win();
    else if (sum > number)
        win();
    else if (sum < number)
        lose();
    else
        draw();
}
////////// Private Slots ////////////
void Player::on_playerType_Changed(int index)
{
    switch (index)
    {
    case 0:
        freezeMove(true);
        break;
    case 1:
        freezeMove(false);
        break;
    case 2:
        freezeMove(true);
        break;
    default:
        break;
    }
}

void Player::on_bet_Changed(int value)
{
    if (value > money)
        bet->setValue(money);
}

void Player::on_Double()
{
    buttonDouble->setDisabled(true);
    buttonHit->setDisabled(true);
    bet->setValue(bet->value() * 2);
    getCard();
//    finishPlay();
}

void Player::finishPlay()
{
    freezeMove(true);
    emit nextPlayerTalk(playerID + 1);
}

//////////// Private //////////////
void Player::win()
{
    if (sum == 21 && cards.size() == 2)    // Blackjack
        money += bet->value() * 1.5;
    else
        money += bet->value();

    groupBox->setTitle("Player " + QString::number(playerID) + ": $" + QString::number(money));
    labelShow->setText(labelShow->text() + " Win!");
}
void Player::lose()
{
    money -= bet->value();
    groupBox->setTitle("Player " + QString::number(playerID) + ": $" + QString::number(money));
    labelShow->setText(labelShow->text() + " Lose!");
}
void Player::draw()
{
    labelShow->setText(labelShow->text() + " Push!");
}
