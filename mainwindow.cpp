#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), temp_selectedGold(0),
    ui(new Ui::MainWindow)
{
    //initial the all the widget and background
    ui->setupUi(this);
    setBackground();
    this->setWindowTitle("King and Thing");
    setThingsRack();
    setHeroWidget();
    initAllWidget();

    //game start, set player turn and initial the board
    initData();
    initMap();
    //start to play
    setPlayerTurn(1);
    setPhaseTurn(0);
}


MainWindow::~MainWindow()
{
    delete ui;
}

/*********************************************************
 *
 * function for the phase 0
 *
 * *******************************************************/
//Each player set up the board in phase 0
//there are four hex that the first player can choose
void MainWindow::startInitMap()
{
    if(GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs().size() == 0)
    {
        if(m_hexWidget[4]->objectName() == "0")
        {
            m_hexWidget[4]->setIsEnabledClick(true);
        }
        if(m_hexWidget[8]->objectName() == "0")
        {
            m_hexWidget[8]->setIsEnabledClick(true);
        }
        if(m_hexWidget[31]->objectName() == "0")
        {
            m_hexWidget[31]->setIsEnabledClick(true);
        }
        if(m_hexWidget[35]->objectName() == "0")
        {
            m_hexWidget[35]->setIsEnabledClick(true);
        }
    } else {
        vector<HexWidget *> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
        for(size_t i = 0; i < temp.size(); i++)
        {
            QList<int> temp2 = getNearHex(temp.at(i)->getID());
            for(int j = 0; j < temp2.size(); j++)
            {
                m_hexWidget.at(temp2.at(j))->setIsEnabledClick(true);
                m_hexWidget.at(temp2.at(j))->setIsEnableDrag(true);
            }
        }
        for(size_t i = 0; i < temp.size(); i++)
        {
            temp.at(i)->setIsEnabledClick(false);
            temp.at(i)->setIsEnableDrag(false);
        }
    }
}

void MainWindow::hexHasChangedSlot(HexWidget *tempHexWidget)
{
    int playerID = getPlayerTurn();
    GameData->addHexWidget(tempHexWidget, playerID);
    //set the control mark on this Hex
    QImage tempImage = QImage(GameData->getPlayerFromID(playerID)->getControlMark());
    QPixmap pixmap = QPixmap::fromImage(tempImage.scaled(QSize(30,30), Qt::IgnoreAspectRatio));
    QLabel *controlMark = new QLabel(tempHexWidget);
    controlMark->setFixedSize(30,30);
    controlMark->setGeometry(42,35,30,30);
    controlMark->setPixmap(pixmap);
    controlMark->show();
    //show the warning message
    //and call the next player
    popMessageBox(1);
    //check for next step
    int count = 0;
    for(int i = 1; i < 5; i++)
    {
        if(GameData->getPlayerFromID(i)->getPlayerHexs().size() == 3)
        {
            count++;
        }
    }
    //if all the player set up their three hex
    //set up the gold and one tower
    if(count == 4)
    {
        //init the gold and tower
        this->initGlodnTower();
    } else {
        startInitMap();
    }
}

void MainWindow::initGlodnTower()
{
    int playerID = getPlayerTurn();
    //set up the gold
    GameData->getPlayerFromID(playerID)->setGold(10);
    refreshPlayerGold();
    //set up the building to the player
    GameData->getPlayerFromID(playerID)->setPlayerBuilding(GameData->getBuildingFromID(1));
    //set the tower
    connect(button,SIGNAL(clicked()),this,SLOT(buttonSlot()));
    QString tempBuidlingUrl = GameData->getPlayerFromID(playerID)->getPlayerBuildings().at(0)->getUrl();
    QString temp = "border-image: url(" +  tempBuidlingUrl + ");";
    button->setStyleSheet(temp);
    button->show();
}

void MainWindow::initThing()
{
    //collect things
    button->setText("Collect");
    connect(button,SIGNAL(clicked()),this,SLOT(initThingSlot()));
    button->show();
}

void MainWindow::initThingSlot()
{
    vector<Thing *> temp = GameData->getRandomThingFromNum(10);
    //set the thing to the player
    GameData->getPlayerFromID(getPlayerTurn())->setPlayerThings(temp);
    //refresh the thingWidget
    refreshThingWidget();
    disconnect(button,SIGNAL(clicked()),this,SLOT(initThingSlot()));
    button->setText("Next");
    connect(button,SIGNAL(clicked()),this,SLOT(confirmThingSlot()));
}

void MainWindow::confirmThingSlot()
{
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(confirmThingSlot()));
    //change next player
    popMessageBox(1);

    int count = 0;
    for(size_t i = 0; i < 4; i++)
    {
        if(GameData->getPlayerFromID(i+1)->getPlayerThings().size() != 0)
        {
            count++;
        }
    }
    if(count == 4)
    {
        //go to another phase
        setPhaseTurn(1);
    } else {
        initThing();
    }
}

void MainWindow::startDragSlot(QList<mylabel*> tempLabel)
{
    vector<HexWidget *> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(size_t i = 0; i < temp.size(); i++)
    {
        temp.at(i)->setIsEnableDrag(true);
    }
}

void MainWindow::buttonSlot()
{
    enablePlayerMapClick();
}

void MainWindow::setBuildingToHexSlot(HexWidget *tempHexWidget)
{
    //draw the buildings on the Hex
    QString tempBuidlingUrl = GameData->getPlayerFromID(getPlayerTurn())->getPlayerBuildings().at(0)->getUrl();
    QImage tempImage = QImage(tempBuidlingUrl);
    QPixmap pixmap = QPixmap::fromImage(tempImage.scaled(QSize(30,30), Qt::IgnoreAspectRatio));
    QLabel *building = new QLabel(tempHexWidget);
    building->setFixedSize(30,30);
    building->setGeometry(72,35,30,30);
    building->setPixmap(pixmap);
    building->show();
    //pass the building to the hex
    tempHexWidget->setBuilding(GameData->getPlayerFromID(getPlayerTurn())->getPlayerBuildings().at(0));
    //delete the button of the mainwindow
    disconnect(button,SIGNAL(clicked()),this,SLOT(buttonSlot()));
    button->setStyleSheet("");
    button->hide();
    //change next player
    popMessageBox(2);
}

/*********************************************************
 *
 * phase 1 function : collect gold
 *
 * *******************************************************/

void MainWindow::startCollectGold(int count)
{
    if(count == 4)
    {
        //start next phase
        setPhaseTurn(2);
    } else {
        button->setText("Collect");
        button->setObjectName(QString::number(count));
        connect(button, SIGNAL(clicked()), this, SLOT(collectGoldSLOT()));
        button->show();
    }
}

void MainWindow::collectGoldSLOT()
{
    button->hide();
    disconnect(button, SIGNAL(clicked()), this, SLOT(collectGoldSLOT()));
    int amount = GameData->getPlayerFromID(getPlayerTurn())->getGold();
    //hex you control
    vector<HexWidget *> tempHex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    amount += tempHex.size();
    //combat value of forks
    for(size_t i = 0; i < tempHex.size(); i++)
    {
        Building *tempBuilding = tempHex.at(i)->building();
        if(tempBuilding != NULL)
        {
            amount += tempBuilding->getIncome();
        }
    }
    //special income and hero
    for(size_t i = 0; i < tempHex.size(); i++)
    {
        vector<mylabel *> tempLabel = tempHex.at(i)->thingsLabel();
        for(size_t j = 0; j < tempLabel.size(); j++)
        {
            //Things is special income and map the terrain
            if(tempLabel.at(j)->getData()->getType() == 7 &&
                    tempLabel.at(j)->getData()->getTerrainType() == tempHex.at(i)->hexData()->getTypeID())
            {
                amount += tempLabel[j]->getData()->getAttackValue();
            }
        }
        //hero
        HeroLabel *tempHero = tempHex.at(i)->heroLabel();
        if(tempHero != NULL)
        {
            amount += 1;
        }
    }
    tempHex.clear();
    //set the new gold
    GameData->getPlayerFromID(getPlayerTurn())->setGold(amount);
    refreshPlayerGold();
    //change next player
    popMessageBox(1);
    startCollectGold(button->objectName().toInt() + 1);
}


/*********************************************************
 *
 * phase 2 function : choose hero
 *
 * *******************************************************/
void MainWindow::startChooseHero(int count)
{
    if(count == 4)
    {
        //start next phase
        setPhaseTurn(3);
    } else {
        emit(initHeroToWidget(GameData->get10heroData()));
        Hero_widget->show();
        Things_rack->hide();
        //skip the recuit if player don't want to recruit hero
        connect(button, SIGNAL(clicked()), this, SLOT(skipRecruitHeroSlot()));
        button->setText("skip");
        button->setObjectName(QString::number(count));
        button->show();
    }
}

void MainWindow::skipRecruitHeroSlot()
{
    button->hide();
    disconnect(button, SIGNAL(clicked()), this, SLOT(skipRecruitHeroSlot()));
    Hero_widget->hide();
    popMessageBox(1);
    startChooseHero(button->objectName().toInt() + 1);
}

void MainWindow::heroConfirmSlot(Hero *tempHero)
{
    disconnect(button, SIGNAL(clicked()), this, SLOT(skipRecruitHeroSlot()));
    button->hide();
    button->setText("Confirm");
    connect(button, SIGNAL(clicked()), this, SLOT(chooseHeroSLOT()));
    button->show();
    temp_hero = tempHero;
    selectedGold->refreshGoldValue(GameData->getPlayerFromID(getPlayerTurn())->getGold());
    selectedGold->show();
    button->show();
}

void MainWindow::chooseHeroSLOT()
{
    selectedGold->hide();
    disconnect(button, SIGNAL(clicked()), this, SLOT(chooseHeroSLOT()));
    button->hide();
    //decrease the player gold;
    GameData->getPlayerFromID(getPlayerTurn())->setGold(
                GameData->getPlayerFromID(getPlayerTurn())->getGold() - getselectedGold());
    refreshPlayerGold();
    dice->refreshLabel();
    dice->show();
}

void MainWindow::checkOwnHero(int dicevalue)
{
    int additionDice = getselectedGold()/5;
    if(dicevalue + additionDice >= temp_hero->getAttackValue())
    {
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerHero(temp_hero);
        //reduce from the controller
        GameData->removeHeroFromID(temp_hero->getID());
        Message("Message", "Win a Hero");
        enablePlayerMapClick();        
        Hero_widget->hide();
    } else {
        Message("Message", "Lose");
        popMessageBox(1);
        Hero_widget->hide();
        startChooseHero(button->objectName().toInt() + 1);
    }
    dice->hide();
}

void MainWindow::setHeroSlot(HexWidget* tempHexWidget)
{
    //show the hero on the hex
    temp_hero->setMode(SmallIcon_Mode);
    HeroLabel *tempHero = new HeroLabel(temp_hero, tempHexWidget);
    tempHero->setGeometry(12,35,30,30);
    tempHero->show();
    //set up the hero on the hex
    tempHexWidget->setHeroLabel(tempHero);
    tempHero->clear();
    //change next player
    disableMapClickandDrag();
    Hero_widget->hide();
    popMessageBox(1);
    startChooseHero(button->objectName().toInt() + 1);
}

/*********************************************************
 *
 * phase 3 function : recruit things
 *
 * *******************************************************/

void MainWindow::startRecruitThings(int count)
{
    if(count == 4)
    {
        //start next phase
        setPhaseTurn(5);
    } else {
        button->setObjectName(QString::number(count));
        freeRecruitThings();
    }
}

//free recruits
void MainWindow::freeRecruitThings()
{
    int count = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs().size()/2 + 1;
    vector<Thing *> temp = GameData->getRandomThingFromNum(count);
    for(size_t i = 0; i < temp.size(); i++)
    {
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerThing(temp.at(i));
    }
    refreshThingWidget();
    paidRecruitThings();
    temp.clear();
}

//paid recruits
void MainWindow::paidRecruitThings()
{
    //get the selected gold
    selectedGold->refreshGoldValue(GameData->getPlayerFromID(getPlayerTurn())->getGold());
    selectedGold->show();
    //comfirm button
    button->setText("Confirm");
    connect(button, SIGNAL(clicked()), this, SLOT(confirmPaidRecruitThingsSlot()));
    button->show();
}

void MainWindow::confirmPaidRecruitThingsSlot()
{
    button->hide();
    selectedGold->hide();
    disconnect(button, SIGNAL(clicked()), this, SLOT(confirmPaidRecruitThingsSlot()));
    //up to five paid recruits
    int count = getselectedGold()/5;
    if(count > 5)
    {
        Message("Warning","Up to 25 gold");
        paidRecruitThings();
    } else {
        vector<Thing *> temp = GameData->getRandomThingFromNum(count);
        for(size_t i = 0; i < temp.size(); i++)
        {
            GameData->getPlayerFromID(getPlayerTurn())->setPlayerThing(temp.at(i));
        }
        refreshThingWidget();
        //decrease the player gold
        int preGold = GameData->getPlayerFromID(getPlayerTurn())->getGold();
        GameData->getPlayerFromID(getPlayerTurn())->setGold(preGold - getselectedGold());
        refreshPlayerGold();
        //treade things
        tradeThings();
    }
}

//trade and drop Things
void MainWindow::tradeThings()
{    
    DropBoxWidget->show();
    TradeBoxWidget->show();

    //set up the confirm button
    button->setText("Finished");
    connect(button, SIGNAL(clicked()), this, SLOT(tradeAndDropThingsSlot()));
    button->show();
}

void MainWindow::tradeAndDropThingsSlot()
{
    //check the player rack is within 10 things
    if(GameData->getPlayerFromID(getPlayerTurn())->getInRackThings().size() > 10){
        Message("Warning", "Rack over 10 Things");
    } else {
        DropBoxWidget->hide();
        TradeBoxWidget->hide();
        button->hide();
        disconnect(button, SIGNAL(clicked()), this, SLOT(tradeAndDropThingsSlot()));
        popMessageBox(1);
        startRecruitThings(button->objectName().toInt() + 1);
    }
}

//dropbox slot
void MainWindow::dropboxSlot(QList<Thing *> tempThings)
{
    //delete the things in the player
    GameData->getPlayerFromID(getPlayerTurn())->deletePlayerThings(tempThings);
}

void MainWindow::tradeboxSlot(QList<Thing *> tempThings)
{
    //delete the things in the player
    GameData->getPlayerFromID(getPlayerTurn())->deletePlayerThings(tempThings);
    //send player new things
    int count = tempThings.size()/2;
    vector<Thing *> tempThing = GameData->getRandomThingFromNum(count);
    for(size_t i = 0; i < tempThing.size(); i++)
    {
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerThing(tempThing.at(i));
    }
    refreshThingWidget();
}

/*********************************************************
 *
 * phase 5 function : movement phases
 *
 * *******************************************************/
void MainWindow::startMovement(int count)
{
    if(count == 4)
    {
        //next phase
    } else {
        button->setObjectName(QString::number(count));
        button->setText("Finished");
        connect(button,SIGNAL(clicked()),this,SLOT(finishedMovementSlot()));
        button->show();
        //hide the movement widget
        MovementWidget->hide();
        //disable the click of the things rack
        Things_rack->hide();
        //enable the hex click for this player
        enablePlayerMapClick();
    }
}

void MainWindow::finishedMovementSlot()
{
    //diable all the hex click and drag
    disableMapClickandDrag();
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(finishedMovementSlot()));
    popMessageBox(1);
    startMovement(button->objectName().toInt());
}

void MainWindow::getHexForMoveWidgetSlot(HexWidget *tempHex)
{
    //show the move widget
    QRect temp = getMapRect(tempHex->getID());
    MovementWidget->move(temp.x()+114,temp.y());
    vector<mylabel*> tempThingsLabel = tempHex->thingsLabel();
    vector<Thing*> tempThings;
    for(size_t i = 0; i < tempThingsLabel.size(); i++)
    {
        tempThings.push_back(tempThingsLabel.at(i)->getData());
    }
    emit(initThingsToMovementWidget(tempThings));
    MovementWidget->show();
    //disable all the hex drag
    disableMapDrag();
    //enable the nearby hex drag
    enableNearHexDrag(tempHex->getID());
    //set the selected hex
    selectedHex = tempHex;
}

void MainWindow::movePhaseStartDragSlot(QList<mylabel*> tempLabel)
{
    //hidden the widget
    MovementWidget->hide();
    //delete the ThingsLabel data in the previous Hex
    selectedHex->deleteThingsLabel(tempLabel);
}

void MainWindow::sendbackThingToHexSlot(const QList<Thing *> *tempThing)
{
    //set the things back to the hex because there are too many things in
    //the hex
    if(tempThing)
    {
        for(int i = 0; i < tempThing->size(); i++)
        {
            tempThing->at(i)->setMode(SmallIcon_Mode);
            mylabel *tempLabel = new mylabel(tempThing->at(i), selectedHex);
            selectedHex->setThingsLabel(tempLabel);
        }
    }
}
/*********************************************************
 *
 * general function
 *
 * *******************************************************/

//index should between 0-36
QList<int> MainWindow::getNearHex(int index)
{
    QList<int> temp;
    switch (index) {
    case 0:
        temp << 1 << 2 << 3;
        break;
    case 1:
        temp << 0 << 2 << 4 << 5;
        break;
    case 2:
        temp << 0 << 1 << 5 << 6 << 7 << 3;
        break;
    case 3:
        temp << 0 << 2 << 7 << 8;
        break;
    case 4:
        temp << 9 << 10 << 5 << 1;
        break;
    case 5:
        temp << 1 << 4 << 10 << 11 << 6 << 2;
        break;
    case 6:
        temp << 2 << 5 << 11 << 12 << 13 << 7;
        break;
    case 7:
        temp << 3 << 2 << 6 << 13 << 14 << 8;
        break;
    case 8:
        temp << 3 << 7 << 14 << 15;
        break;
    case 9:
        temp << 16 << 10 << 4;
        break;
    case 10:
        temp << 4 << 9 << 16 << 17 << 11 << 5;
        break;
    case 11:
        temp << 5 << 10 << 17 << 18 << 12 << 6;
        break;
    case 12:
        temp << 6 << 11 << 18 << 19 << 20 << 13;
        break;
    case 13:
        temp << 7 << 6 << 12 << 20 << 21 << 14;
        break;
    case 14:
        temp << 8 << 7 << 13 << 21 << 22 << 15;
        break;
    case 15:
        temp << 8 << 14 << 22;
        break;
    case 16:
        temp << 9 << 10 << 17 << 23;
        break;
    case 17:
        temp << 10 << 16 << 23 << 24 << 18 << 11;
        break;
    case 18:
        temp << 11 << 17 << 24 << 25 << 19 << 12;
        break;
    case 19:
        temp << 12 << 18 << 25 << 26 << 27 << 20;
        break;
    case 20:
        temp << 13 << 12 << 19 << 27 << 28 << 21;
        break;
    case 21:
        temp << 14 << 13 << 20 << 28 << 29 << 22;
        break;
    case 22:
        temp << 15 << 14 << 21 << 29;
        break;
    case 23:
        temp << 16 << 17 << 24 << 30;
        break;
    case 24:
        temp << 17 << 23 << 30 << 31 << 25 << 18;
        break;
    case 25:
        temp << 18 << 24 << 31 << 32 << 26 << 19;
        break;
    case 26:
        temp << 19 << 25 << 32 << 33 << 34 << 27;
        break;
    case 27:
        temp << 20 << 19 << 26 << 34 << 35 << 28;
        break;
    case 28:
        temp << 21 << 20 << 27 << 35 << 36 << 29;
        break;
    case 29:
        temp << 22 << 21 << 28 << 36;
        break;
    case 30:
        temp << 23 << 24 << 31;
        break;
    case 31:
        temp << 30 << 24 << 25 << 32;
        break;
    case 32:
        temp << 31 << 25 << 26 << 33;
        break;
    case 33:
        temp << 32 << 26 << 34;
        break;
    case 34:
        temp << 33 << 26 << 27 << 35;
        break;
    case 35:
        temp << 34 << 27 << 28 << 36;
        break;
    case 36:
        temp << 35 << 28 << 29;
        break;
    default:
        break;
    }
    return temp;
}

int MainWindow::getPlayerTurn() const
{
    return playerTurn;
}

void MainWindow::enableNearHexDrag(int hexID)
{
    QList<int> temp2 = getNearHex(hexID);
    for(int j = 0; j < temp2.size(); j++)
    {
        m_hexWidget.at(temp2.at(j))->setIsEnableDrag(true);
    }
}

void MainWindow::setPlayerTurn(int value)
{
    playerTurn = value;
    QString temp = "Player : " + QString::number(value) + " turn.";
    ui->label->setText(temp);
    ui->label->setStyleSheet("background-color: white;");
    refreshThingWidget();
}

int MainWindow::getPhaseTurn() const
{
    return PhaseTurn;
}

void MainWindow::setPhaseTurn(int value)
{
    PhaseTurn = value;
    QString temp = "Phase : " + QString::number(value) + ".";
    ui->label_2->setText(temp);
    ui->label_2->setStyleSheet("background-color: white;");
    switch (value) {
    case 0:
        startInitMap();
        break;
    case 1:
        startCollectGold(0);
        break;
    case 2:
        startChooseHero(0);
        break;
    case 3:
        startRecruitThings(0);
        break;
    case 5:
        startMovement(0);
        break;
    default:
        break;
    }
}

void MainWindow::enablePlayerMapClick()
{
    vector<HexWidget*> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(size_t i = 0; i < temp.size(); i++)
    {
        temp[i]->setIsEnabledClick(true);
    }
}

void MainWindow::enablePlayerMapDrag()
{
    vector<HexWidget*> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(size_t i = 0; i < temp.size(); i++)
    {
        temp[i]->setIsEnableDrag(true);
    }
}

void MainWindow::disableMapClickandDrag()
{
    for(size_t i = 0; i < m_hexWidget.size(); i++)
    {
        m_hexWidget[i]->setIsEnabledClick(false);
        m_hexWidget[i]->setIsEnableDrag(false);
    }
}

void MainWindow::disableMapDrag()
{
    for(size_t i = 0; i < m_hexWidget.size(); i++)
    {
        m_hexWidget[i]->setIsEnableDrag(false);
    }
}

void MainWindow::getRequirePlayerIDnPhaseSlot()
{
    emit(sendPlayerIDnPhaseSignal(getPlayerTurn(), getPhaseTurn()));
}

//get the random number from 1 to range
int MainWindow::getRandomNumber(int range)
{
    int x = qrand() % range + 1;
    return x;
}
void MainWindow::refreshThingWidget()
{
    emit(initThingToRackSignal(GameData->getPlayerFromID(getPlayerTurn())->getInRackThings()));
    Things_rack->show();
}

void MainWindow::refreshPlayerGold()
{
    int player1 = GameData->getPlayerFromID(1)->getGold();
    int player2 = GameData->getPlayerFromID(2)->getGold();
    int player3 = GameData->getPlayerFromID(3)->getGold();
    int player4 = GameData->getPlayerFromID(4)->getGold();
    ui->Player1_Gold->setText(QString::number(player1));
    ui->Player2_Gold->setText(QString::number(player2));
    ui->Player3_Gold->setText(QString::number(player3));
    ui->Player4_Gold->setText(QString::number(player4));
}

void MainWindow::getSelectedGoldSlot(int gold)
{
    temp_selectedGold = gold;
}

int MainWindow::getselectedGold() const
{
    return temp_selectedGold;
}

void MainWindow::updateDiceValueSlot(int tempdiceValue)
{
    if(getPhaseTurn() == 2)
    {
        checkOwnHero(tempdiceValue);
    }
}

void MainWindow::sendbackThingToRackSlot(const QList<Thing*> *pList)
{
    for(int i = 0; i < pList->size(); i++)
    {
        pList->at(i)->setInRack(true);
    }
    refreshThingWidget();
}

void MainWindow::Message(QString title, QString body)
{
    QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, title, body);
    message->setIconPixmap(QPixmap(":/palyer/image/things/player_battle_building/Thing26.jpg"));
    message->exec();
    delete message;
}

//popup message box change next player
void MainWindow::popMessageBox(int index)
{
    disableMapClickandDrag();
    Things_rack->hide();
    QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, "Next Player", "Next player Turn");
    message->setIconPixmap(QPixmap(":/palyer/image/things/player_battle_building/Thing26.jpg"));
    switch (index) {
    case 1:
        connect(message, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(changePlayerTurnSlot(QAbstractButton*)));
        break;
    case 2:
        connect(message, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(changePlayerTurnSlot2(QAbstractButton*)));
        break;
    default:
        break;
    }
    message->exec();
    delete message;
}

void MainWindow::changePlayerTurnSlot(QAbstractButton*)
{
    setPlayerTurn(getPlayerTurn()%4 + 1);
    refreshThingWidget();
    refreshPlayerGold();
}

void MainWindow::changePlayerTurnSlot2(QAbstractButton *)
{
    setPlayerTurn(getPlayerTurn()%4 + 1);
    //if every one set the tower then system divide things
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        if(GameData->getPlayerFromID(i+1)->getPlayerBuildings().size() == 1)
        {
            count++;
        }
    }
    if(count == 4)
    {
        //go to the next step
        initThing();
    } else {
        this->initGlodnTower();
    }
}

/*********************************************************
 *
 * initial function
 *
 * *******************************************************/
//set the background of the main window
void MainWindow::setBackground()
{
    ui->centralWidget->setObjectName("mypage");
    ui->centralWidget->setStyleSheet("QWidget#mypage{border-image: url(:/background/image/background/background.jpg)}");
}
//initial all the Data
void MainWindow::initData()
{
    GameData = new Control(this);
    GameData->initThings();
    GameData->initPlayers();
    GameData->initHex();
    GameData->init37hex();
    GameData->initBuilding();
    GameData->initHero();
    GameData->chooseTenRandomHeros();

    refreshPlayerGold();
}
//initial all the Hex in the map
void MainWindow::initMap()
{
    for(size_t i = 0; i < 37; i++)
    {
        HexWidget *tempHexWidget = new HexWidget(this->centralWidget(),
                                                 GameData->get37hex().at(i));
        connect(tempHexWidget, SIGNAL(hexHasChangedSignal(HexWidget*)),
                this, SLOT(hexHasChangedSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(requirePlayerIDnPhaseSignal()),
                this, SLOT(getRequirePlayerIDnPhaseSlot()));
        connect(this, SIGNAL(sendPlayerIDnPhaseSignal(int, int)),
                tempHexWidget, SLOT(setPlayerIDnPhaseSlot(int, int)));
        connect(tempHexWidget, SIGNAL(setBulidngSingal(HexWidget*)),
                this, SLOT(setBuildingToHexSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(setHeroSignal(HexWidget*)),
                this, SLOT(setHeroSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(setThingsToMoveWidgetSignal(HexWidget*)),
                this, SLOT(getHexForMoveWidgetSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(sendbackThingSignal(const QList<Thing*>*)),
                this, SLOT(sendbackThingToRackSlot(const QList<Thing*>*)));
        connect(tempHexWidget, SIGNAL(sendThingsBackToHex(const QList<Thing*>*)),
                this, SLOT(sendbackThingToHexSlot(const QList<Thing*>*)));
        //show that this widget is unowned
        tempHexWidget->setObjectName("0");
        tempHexWidget->setID(i);
        tempHexWidget->setGeometry(getMapRect(i));
        m_hexWidget.push_back(tempHexWidget);
    }
}
QRect MainWindow::getMapRect(int index)
{
    int HexWidth = 114;
    int HexHeight = 100;
    switch (index) {
    case 0:
        return QRect(290,30,HexWidth,HexHeight);
        break;
    case 1:
        return QRect(200,80,HexWidth,HexHeight);
        break;
    case 2:
        return QRect(290,130,HexWidth,HexHeight);
        break;
    case 3:
        return QRect(380,80,HexWidth,HexHeight);
        break;
    case 4:
        return QRect(110,130,HexWidth,HexHeight);
        break;
    case 5:
        return QRect(200,180,HexWidth,HexHeight);
        break;
    case 6:
        return QRect(290,230,HexWidth,HexHeight);
        break;
    case 7:
        return QRect(380,180,HexWidth,HexHeight);
        break;
    case 8:
        return QRect(470,130,HexWidth,HexHeight);
        break;
    case 9:
        return QRect(20,180,HexWidth,HexHeight);
        break;
    case 10:
        return QRect(110,230,HexWidth,HexHeight);
        break;
    case 11:
        return QRect(200,280,HexWidth,HexHeight);
        break;
    case 12:
        return QRect(290,330,HexWidth,HexHeight);
        break;
    case 13:
        return QRect(380,280,HexWidth,HexHeight);
        break;
    case 14:
        return QRect(470,230,HexWidth,HexHeight);
        break;
    case 15:
        return QRect(560,180,HexWidth,HexHeight);
        break;
    case 16:
        return QRect(20,280,HexWidth,HexHeight);
        break;
    case 17:
        return QRect(110,330,HexWidth,HexHeight);
        break;
    case 18:
        return QRect(200,380,HexWidth,HexHeight);
        break;
    case 19:
        return QRect(290,430,HexWidth,HexHeight);
        break;
    case 20:
        return QRect(380,380,HexWidth,HexHeight);
        break;
    case 21:
        return QRect(470,330,HexWidth,HexHeight);
        break;
    case 22:
        return QRect(560,280,HexWidth,HexHeight);
        break;
    case 23:
        return QRect(20,380,HexWidth,HexHeight);
        break;
    case 24:
        return QRect(110,430,HexWidth,HexHeight);
        break;
    case 25:
        return QRect(200,480,HexWidth,HexHeight);
        break;
    case 26:
        return QRect(290,530,HexWidth,HexHeight);
        break;
    case 27:
        return QRect(380,480,HexWidth,HexHeight);
        break;
    case 28:
        return QRect(470,430,HexWidth,HexHeight);
        break;
    case 29:
        return QRect(560,380,HexWidth,HexHeight);
        break;
    case 30:
        return QRect(20,480,HexWidth,HexHeight);
        break;
    case 31:
        return QRect(110,530,HexWidth,HexHeight);
        break;
    case 32:
        return QRect(200,580,HexWidth,HexHeight);
        break;
    case 33:
        return QRect(290,630,HexWidth,HexHeight);
        break;
    case 34:
        return QRect(380,580,HexWidth,HexHeight);
        break;
    case 35:
        return QRect(470,530,HexWidth,HexHeight);
        break;
    case 36:
        return QRect(560,480,HexWidth,HexHeight);
        break;
    default:
        return QRect();
        break;
    }

}
//set up the Things Rack Widget
void MainWindow::setThingsRack()
{
    Things_rack = new MapWidget(this);
    //height = 240
    Things_rack->setFixedWidth(500);
    Things_rack->move(700, 440);
    Things_rack->hide();
    //send data to the player's rack
    connect(this, SIGNAL(initThingToRackSignal(vector<Thing*>)),
            Things_rack, SLOT(initThingToRackSlot(vector<Thing*>)));
    connect(Things_rack, SIGNAL(startDragSignal(QList<mylabel*>)),
            this, SLOT(startDragSlot(QList<mylabel*>)));
}
//set up the special character widget
void MainWindow::setHeroWidget()
{
    Hero_widget = new HeroWidget(this);
    Hero_widget->setFixedSize(500,240);
    Hero_widget->move(700, 440);
    Hero_widget->hide();
    //send data to the hero widget
    connect(this, SIGNAL(initHeroToWidget(QList<Hero*>)),
            Hero_widget, SLOT(initHeroToWidgetSlot(QList<Hero*>)));
    connect(Hero_widget, SIGNAL(heroConfirmSignal(Hero*)),
            this, SLOT(heroConfirmSlot(Hero*)));
}

void MainWindow::initAllWidget()
{
    //set up the function button
    button = new QPushButton(this);
    button->setGeometry(900,150,80,80);
    button->hide();
    //set up the dice
    dice = new DiceWidget(this);
    dice->setGeometry(900,140,100,100);
    dice->hide();
    connect(dice, SIGNAL(updateDiceValueSignal(int)), this, SLOT(updateDiceValueSlot(int)));
    //set up the selected gold widget
    selectedGold = new SelectGoldWidget(this);
    connect(selectedGold, SIGNAL(selectedGoldSignal(int)), this, SLOT(getSelectedGoldSlot(int)));
    selectedGold->move(800,140);
    selectedGold->hide();
    //set up the dropbox
    DropBoxWidget = new ThingsDropWidget(this);
    DropBoxWidget->setGeometry(800,300,100,100);
    DropBoxWidget->setDropBox();
    connect(DropBoxWidget, SIGNAL(tradeThingsSignal(QList<Thing*>)),
            this, SLOT(dropboxSlot(QList<Thing*>)));
    DropBoxWidget->hide();
    //set up the tradebox
    TradeBoxWidget = new ThingsDropWidget(this);
    TradeBoxWidget->setGeometry(950,300,100,100);
    TradeBoxWidget->setTradeBox();
    connect(TradeBoxWidget, SIGNAL(tradeThingsSignal(QList<Thing*>)),
            this, SLOT(tradeboxSlot(QList<Thing*>)));
    TradeBoxWidget->hide();
    //set up the movement widget
    MovementWidget = new MapWidget(this);
    MovementWidget->setFixedSize(500,240);
    MovementWidget->hide();
    MovementWidget->setStyleSheet("background-color:white");
    connect(this,SIGNAL(initThingsToMovementWidget(vector<Thing*>)),
            MovementWidget, SLOT(initThingToRackSlot(vector<Thing*>)));
    connect(MovementWidget,SIGNAL(startDragSignal(QList<mylabel*>)),
            this,SLOT(movePhaseStartDragSlot(QList<mylabel*>)));
}
