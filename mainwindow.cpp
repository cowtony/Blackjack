#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    deck.reset(8);

    player[0].init(0, &deck, ui->groupBox_1, ui->comboBox_1, ui->label_Bet_1, ui->spinBox_1, ui->label_Show_1, ui->pushButton_Double_1, ui->pushButton_Split_1, ui->pushButton_Hit_1, ui->pushButton_Stand_1);
    player[1].init(1, &deck, ui->groupBox_2, ui->comboBox_2, ui->label_Bet_2, ui->spinBox_2, ui->label_Show_2, ui->pushButton_Double_2, ui->pushButton_Split_2, ui->pushButton_Hit_2, ui->pushButton_Stand_2);
    player[2].init(2, &deck, ui->groupBox_3, ui->comboBox_3, ui->label_Bet_3, ui->spinBox_3, ui->label_Show_3, ui->pushButton_Double_3, ui->pushButton_Split_3, ui->pushButton_Hit_3, ui->pushButton_Stand_3);
    player[3].init(3, &deck, ui->groupBox_4, ui->comboBox_4, ui->label_Bet_4, ui->spinBox_4, ui->label_Show_4, ui->pushButton_Double_4, ui->pushButton_Split_4, ui->pushButton_Hit_4, ui->pushButton_Stand_4);
    player[4].init(4, &deck, ui->groupBox_5, ui->comboBox_5, ui->label_Bet_5, ui->spinBox_5, ui->label_Show_5, ui->pushButton_Double_5, ui->pushButton_Split_5, ui->pushButton_Hit_5, ui->pushButton_Stand_5);
    dealer.init(0, &deck, ui->label_Dealer);
    for (int i = 0; i < MAX_PLAYER; i++)
        connect(player + i, SIGNAL(nextPlayerTalk(int)), this, SLOT(talk(int)));

    ui->label_Dealer->setText("");


//    QPixmap pixMap(":/Cards/H1.png");
//    ui->label_Show_1->setPixmap(pixMap);
//    ui->label_Show_1->setScaledContents(true);
//    ui->label_Show_1->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////// Private Slot ///////////////////////
void MainWindow::on_pushButton_Play_clicked()
{
    ui->pushButton_Play->setDisabled(true);
    dealer.startGame();
    for (int i = 0; i < MAX_PLAYER; i++)
        player[i].startGame();

    dealCard(0);
}

void MainWindow::dealCard(int playerID)
{
    for (; playerID < MAX_PLAYER; playerID++)
    {
        if (player[playerID].isOnTable())
        {
            player[playerID].getCard();
            QTimer::singleShot(500, this, [=] () {dealCard(playerID + 1);});
            return;
        }
    }

    if (dealer.getNumberOfCards() < 1)
    {
        dealer.getCard();
        QTimer::singleShot(500, this, [=] () {dealCard(0);});
    }
    else
    {
        talk(0);
    }
}

void MainWindow::talk(int playerID)
{
    for (; playerID < MAX_PLAYER; playerID++)
    {
        if (player[playerID].isOnTable())
        {
            player[playerID].freezeMove(false);
            return;
        }
    }

    for (int i = 0; i < MAX_PLAYER; i++)
        if (player[i].isOnTable() && player[i].getSum() <= 21)
        {
            dealerPlay();
            return;
        }
    settlement();
}

void MainWindow::dealerPlay()
{
    if (dealer.getSum() < 17)
    {
        dealer.getCard();
        QTimer::singleShot(500, this, [=] () {dealerPlay();});
        return;
    }
    else
    {
        settlement();
    }
}
///////////////// Private //////////////////////
void MainWindow::reset()
{
    ui->pushButton_Play->setEnabled(true);
    for (int i = 0; i < MAX_PLAYER; i++)
        player[i].reset();
}

void MainWindow::settlement()
{
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (player[i].isOnTable())
            player[i].getResult(dealer.getSum());
    }
    reset();
}
