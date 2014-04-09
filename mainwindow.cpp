#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
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
    //choose the player amount
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Selection"),
                                                  tr("Yes for 4 Player and No for 3 Player"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes))
    {
        setPlayerNumber(4);
    } else {
        setPlayerNumber(3);
    }
    //start to play
    setPlayerTurn(1);
    setPhaseTurn(0);
    //initial the test data
    //initTestData();
    //minimalFunction();
    //averageFunction();
    //superFunction();
}


MainWindow::~MainWindow()
{
    delete ui;
}
/*********************************************************
 *
 * 2-3 Player
 *
 * *******************************************************/

void MainWindow::setPlayerNumber(int playerNumber)
{
    this->playerNumber = playerNumber;
    if(playerNumber == 4)
    {
        initMap();
    } else {
        initMap();
        initialLessPlayerHex();
        //decrease the player of the game data
        GameData->lessPlayer(playerNumber);
    }
}

void MainWindow::initialLessPlayerHex()
{
    //hidden the other hex
    m_hexWidget.at(0)->hide();
    m_hexWidget.at(1)->hide();
    m_hexWidget.at(4)->hide();
    m_hexWidget.at(9)->hide();
    m_hexWidget.at(16)->hide();
    m_hexWidget.at(23)->hide();
    m_hexWidget.at(30)->hide();
    m_hexWidget.at(31)->hide();
    m_hexWidget.at(32)->hide();
    m_hexWidget.at(33)->hide();
    m_hexWidget.at(34)->hide();
    m_hexWidget.at(35)->hide();
    m_hexWidget.at(36)->hide();
    m_hexWidget.at(29)->hide();
    m_hexWidget.at(22)->hide();
    m_hexWidget.at(15)->hide();
    m_hexWidget.at(8)->hide();
    m_hexWidget.at(3)->hide();
}
/*********************************************************
 *
 * Test data
 *
 * *******************************************************/

void MainWindow::initTestData()
{
    //player 1 data
    Player *one = GameData->getPlayerFromID(1);
    m_hexWidget.at(3)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(8)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(15)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(2)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(7)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(14)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(13)->initialControlMark(one->getControlMark(),1);
    m_hexWidget.at(12)->initialControlMark(one->getControlMark(),1);
    //building
    m_hexWidget.at(7)->initialBuildingLabel(GameData->getBuildingFromID(3));
    m_hexWidget.at(14)->initialBuildingLabel(GameData->getBuildingFromID(1));
    m_hexWidget.at(15)->initialNeutralizedBuilidng(GameData->getBuildingFromID(3));
    m_hexWidget.at(13)->initialNeutralizedBuilidng(GameData->getBuildingFromID(1));
    m_hexWidget.at(12)->initialNeutralizedBuilidng(GameData->getBuildingFromID(2));
    //hex
    one->setPlayerHex(m_hexWidget.at(3));
    one->setPlayerHex(m_hexWidget.at(8));
    one->setPlayerHex(m_hexWidget.at(15));
    one->setPlayerHex(m_hexWidget.at(2));
    one->setPlayerHex(m_hexWidget.at(7));
    one->setPlayerHex(m_hexWidget.at(14));
    one->setPlayerHex(m_hexWidget.at(13));
    one->setPlayerHex(m_hexWidget.at(12));
    //building
    one->setPlayerBuilding(GameData->getBuildingFromID(3));
    one->setPlayerBuilding(GameData->getBuildingFromID(1));
    //village
    one->setPlayerThing(GameData->getThing(173));
    GameData->getThing(173)->setInRack(false);
    GameData->getThing(173)->setUsed(false);
    m_hexWidget.at(3)->setPlayerThing(GameData->getThing(173),1);


    //player 2 data
    Player *two = GameData->getPlayerFromID(2);
    m_hexWidget.at(22)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(29)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(36)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(21)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(28)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(35)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(20)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(27)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(34)->initialControlMark(two->getControlMark(),2);
    m_hexWidget.at(19)->initialControlMark(two->getControlMark(),2);
    //building
    m_hexWidget.at(22)->initialNeutralizedBuilidng(GameData->getBuildingFromID(2));
    m_hexWidget.at(21)->initialNeutralizedBuilidng(GameData->getBuildingFromID(2));
    m_hexWidget.at(28)->initialNeutralizedBuilidng(GameData->getBuildingFromID(2));
    m_hexWidget.at(20)->initialBuildingLabel(GameData->getBuildingFromID(1));
    m_hexWidget.at(27)->initialBuildingLabel(GameData->getBuildingFromID(3));
    //hex
    two->setPlayerHex(m_hexWidget.at(22));
    two->setPlayerHex(m_hexWidget.at(29));
    two->setPlayerHex(m_hexWidget.at(36));
    two->setPlayerHex(m_hexWidget.at(21));
    two->setPlayerHex(m_hexWidget.at(28));
    two->setPlayerHex(m_hexWidget.at(35));
    two->setPlayerHex(m_hexWidget.at(20));
    two->setPlayerHex(m_hexWidget.at(27));
    two->setPlayerHex(m_hexWidget.at(34));
    two->setPlayerHex(m_hexWidget.at(19));
    //building
    two->setPlayerBuilding(GameData->getBuildingFromID(3));
    two->setPlayerBuilding(GameData->getBuildingFromID(1));
    //village
    two->setPlayerThing(GameData->getThing(173));
    m_hexWidget.at(29)->setPlayerThing(GameData->getThing(173),2);

    //Player 3 data
    Player *three = GameData->getPlayerFromID(3);
    m_hexWidget.at(18)->initialControlMark(three->getControlMark(),3);
    m_hexWidget.at(25)->initialControlMark(three->getControlMark(),3);
    m_hexWidget.at(32)->initialControlMark(three->getControlMark(),3);
    m_hexWidget.at(31)->initialControlMark(three->getControlMark(),3);
    m_hexWidget.at(26)->initialControlMark(three->getControlMark(),3);
    m_hexWidget.at(33)->initialControlMark(three->getControlMark(),3);
    //building
    m_hexWidget.at(32)->initialBuildingLabel(GameData->getBuildingFromID(2));
    //hex
    three->setPlayerHex(m_hexWidget.at(18));
    three->setPlayerHex(m_hexWidget.at(25));
    three->setPlayerHex(m_hexWidget.at(32));
    three->setPlayerHex(m_hexWidget.at(31));
    three->setPlayerHex(m_hexWidget.at(26));
    three->setPlayerHex(m_hexWidget.at(33));
    //building
    three->setPlayerBuilding(GameData->getBuildingFromID(2));
    //city
    three->setPlayerThing(GameData->getThing(174));
    m_hexWidget.at(31)->setPlayerThing(GameData->getThing(174),3);

    //player 4 data
    Player *four = GameData->getPlayerFromID(4);
    m_hexWidget.at(1)->initialControlMark(four->getControlMark(),4);
    m_hexWidget.at(5)->initialControlMark(four->getControlMark(),4);
    m_hexWidget.at(4)->initialControlMark(four->getControlMark(),4);
    m_hexWidget.at(10)->initialControlMark(four->getControlMark(),4);
    m_hexWidget.at(9)->initialControlMark(four->getControlMark(),4);
    m_hexWidget.at(16)->initialControlMark(four->getControlMark(),4);
    m_hexWidget.at(23)->initialControlMark(four->getControlMark(),4);
    //building
    m_hexWidget.at(4)->initialNeutralizedBuilidng(GameData->getBuildingFromID(3));
    m_hexWidget.at(10)->initialNeutralizedBuilidng(GameData->getBuildingFromID(1));
    m_hexWidget.at(9)->initialBuildingLabel(GameData->getBuildingFromID(2));
    //hex
    four->setPlayerHex(m_hexWidget.at(1));
    four->setPlayerHex(m_hexWidget.at(5));
    four->setPlayerHex(m_hexWidget.at(4));
    four->setPlayerHex(m_hexWidget.at(10));
    four->setPlayerHex(m_hexWidget.at(9));
    four->setPlayerHex(m_hexWidget.at(16));
    four->setPlayerHex(m_hexWidget.at(23));
    //building
    four->setPlayerBuilding(GameData->getBuildingFromID(2));
    //village
    four->setPlayerThing(GameData->getThing(173));
    m_hexWidget.at(16)->setPlayerThing(GameData->getThing(173),4);

}

void MainWindow::minimalFunction()
{
    //player one
    Player *one = GameData->getPlayerFromID(1);
    GameData->getThing(123)->setInRack(false);
    GameData->getThing(123)->setUsed(true);
    GameData->getThing(65)->setInRack(false);
    GameData->getThing(65)->setUsed(true);
    GameData->getThing(122)->setInRack(false);
    GameData->getThing(122)->setUsed(true);
    GameData->getThing(131)->setInRack(false);
    GameData->getThing(131)->setUsed(true);
    GameData->getThing(89)->setInRack(false);
    GameData->getThing(89)->setUsed(true);
    GameData->getThing(48)->setInRack(false);
    GameData->getThing(48)->setUsed(true);
    GameData->getThing(96)->setInRack(false);
    GameData->getThing(96)->setUsed(true);
    one->setPlayerThing(GameData->getThing(123));
    one->setPlayerThing(GameData->getThing(65));
    one->setPlayerThing(GameData->getThing(122));
    one->setPlayerThing(GameData->getThing(131));
    one->setPlayerThing(GameData->getThing(89));
    one->setPlayerThing(GameData->getThing(48));
    one->setPlayerThing(GameData->getThing(96));
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(123),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(65),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(122),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(131),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(89),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(48),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(96),1);

    //player two
    Player *two = GameData->getPlayerFromID(2);
    GameData->getThing(142)->setUsed(true);
    GameData->getThing(142)->setInRack(false);
    GameData->getThing(141)->setUsed(true);
    GameData->getThing(141)->setInRack(false);
    GameData->getThing(126)->setUsed(true);
    GameData->getThing(126)->setInRack(false);
    GameData->getThing(94)->setUsed(true);
    GameData->getThing(94)->setInRack(false);
    GameData->getThing(83)->setUsed(true);
    GameData->getThing(83)->setInRack(false);
    GameData->getThing(113)->setUsed(true);
    GameData->getThing(113)->setInRack(false);
    GameData->getThing(110)->setUsed(true);
    GameData->getThing(110)->setInRack(false);
    two->setPlayerThing(GameData->getThing(142));
    two->setPlayerThing(GameData->getThing(141));
    two->setPlayerThing(GameData->getThing(126));
    two->setPlayerThing(GameData->getThing(94));
    two->setPlayerThing(GameData->getThing(83));
    two->setPlayerThing(GameData->getThing(113));
    two->setPlayerThing(GameData->getThing(110));
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(142),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(141),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(126),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(94),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(83),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(113),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(110),2);
}

void MainWindow::averageFunction()
{
    //player one
    Player *one = GameData->getPlayerFromID(1);
    GameData->getThing(123)->setInRack(false);
    GameData->getThing(123)->setUsed(true);
    GameData->getThing(65)->setInRack(false);
    GameData->getThing(65)->setUsed(true);
    GameData->getThing(114)->setInRack(false);
    GameData->getThing(114)->setUsed(true);
    GameData->getThing(113)->setInRack(false);
    GameData->getThing(113)->setUsed(true);
    GameData->getThing(89)->setInRack(false);
    GameData->getThing(89)->setUsed(true);
    GameData->getThing(48)->setInRack(false);
    GameData->getThing(48)->setUsed(true);
    GameData->getThing(10)->setInRack(false);
    GameData->getThing(10)->setUsed(true);
    GameData->getThing(3)->setInRack(false);
    GameData->getThing(3)->setUsed(true);
    GameData->getThing(26)->setInRack(false);
    GameData->getThing(26)->setUsed(true);
    one->setPlayerThing(GameData->getThing(123));
    one->setPlayerThing(GameData->getThing(65));
    one->setPlayerThing(GameData->getThing(114));
    one->setPlayerThing(GameData->getThing(113));
    one->setPlayerThing(GameData->getThing(89));
    one->setPlayerThing(GameData->getThing(48));
    one->setPlayerThing(GameData->getThing(10));
    one->setPlayerThing(GameData->getThing(3));
    one->setPlayerThing(GameData->getThing(26));
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(123),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(65),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(114),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(113),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(89),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(48),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(10),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(3),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(26),1);
    //Things in rack
    GameData->getThing(153)->setUsed(true);
    one->setPlayerThing(GameData->getThing(153));
    GameData->getThing(152)->setUsed(true);
    one->setPlayerThing(GameData->getThing(152));
    //player two
    Player *two = GameData->getPlayerFromID(2);
    GameData->getThing(142)->setUsed(true);
    GameData->getThing(142)->setInRack(false);
    GameData->getThing(141)->setUsed(true);
    GameData->getThing(141)->setInRack(false);
    GameData->getThing(126)->setUsed(true);
    GameData->getThing(126)->setInRack(false);
    GameData->getThing(94)->setUsed(true);
    GameData->getThing(94)->setInRack(false);
    GameData->getThing(83)->setUsed(true);
    GameData->getThing(83)->setInRack(false);
    GameData->getThing(101)->setUsed(true);
    GameData->getThing(101)->setInRack(false);
    GameData->getThing(110)->setUsed(true);
    GameData->getThing(110)->setInRack(false);
    GameData->getThing(143)->setUsed(true);
    GameData->getThing(143)->setInRack(false);
    GameData->getThing(103)->setUsed(true);
    GameData->getThing(103)->setInRack(false);
    GameData->getThing(95)->setUsed(true);
    GameData->getThing(95)->setInRack(false);
    two->setPlayerThing(GameData->getThing(142));
    two->setPlayerThing(GameData->getThing(141));
    two->setPlayerThing(GameData->getThing(126));
    two->setPlayerThing(GameData->getThing(94));
    two->setPlayerThing(GameData->getThing(83));
    two->setPlayerThing(GameData->getThing(101));
    two->setPlayerThing(GameData->getThing(110));
    two->setPlayerThing(GameData->getThing(143));
    two->setPlayerThing(GameData->getThing(103));
    two->setPlayerThing(GameData->getThing(95));
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(142),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(141),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(126),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(94),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(83),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(101),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(110),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(143),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(103),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(95),2);
    //Things in rack
    GameData->getThing(146)->setUsed(true);
    GameData->getThing(148)->setUsed(true);
    GameData->getThing(157)->setUsed(true);
    two->setPlayerThing(GameData->getThing(146));
    two->setPlayerThing(GameData->getThing(148));
    two->setPlayerThing(GameData->getThing(157));
}

void MainWindow::superFunction()
{
    //player one
    Player *one = GameData->getPlayerFromID(1);
    GameData->getThing(97)->setInRack(false);
    GameData->getThing(97)->setUsed(true);
    GameData->getThing(98)->setInRack(false);
    GameData->getThing(98)->setUsed(true);
    GameData->getThing(113)->setInRack(false);
    GameData->getThing(113)->setUsed(true);
    GameData->getThing(48)->setInRack(false);
    GameData->getThing(48)->setUsed(true);
    GameData->getThing(89)->setInRack(false);
    GameData->getThing(89)->setUsed(true);
    GameData->getThing(10)->setInRack(false);
    GameData->getThing(10)->setUsed(true);
    GameData->getThing(26)->setInRack(false);
    GameData->getThing(26)->setUsed(true);
    GameData->getThing(124)->setInRack(false);
    GameData->getThing(124)->setUsed(true);
    GameData->getThing(134)->setInRack(false);
    GameData->getThing(134)->setUsed(true);
    one->setPlayerThing(GameData->getThing(97));
    one->setPlayerThing(GameData->getThing(98));
    one->setPlayerThing(GameData->getThing(113));
    one->setPlayerThing(GameData->getThing(10));
    one->setPlayerThing(GameData->getThing(89));
    one->setPlayerThing(GameData->getThing(48));
    one->setPlayerThing(GameData->getThing(26));
    one->setPlayerThing(GameData->getThing(124));
    one->setPlayerThing(GameData->getThing(134));
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(97),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(98),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(113),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(10),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(89),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(48),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(26),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(124),1);
    m_hexWidget.at(13)->setPlayerThing(GameData->getThing(134),1);

    //player two
    Player *two = GameData->getPlayerFromID(2);
    GameData->getThing(142)->setUsed(true);
    GameData->getThing(142)->setInRack(false);
    GameData->getThing(94)->setUsed(true);
    GameData->getThing(94)->setInRack(false);
    GameData->getThing(83)->setUsed(true);
    GameData->getThing(83)->setInRack(false);
    GameData->getThing(110)->setUsed(true);
    GameData->getThing(110)->setInRack(false);
    GameData->getThing(101)->setUsed(true);
    GameData->getThing(101)->setInRack(false);
    GameData->getThing(143)->setUsed(true);
    GameData->getThing(143)->setInRack(false);
    GameData->getThing(103)->setUsed(true);
    GameData->getThing(103)->setInRack(false);
    GameData->getThing(95)->setUsed(true);
    GameData->getThing(95)->setInRack(false);
    GameData->getThing(38)->setUsed(true);
    GameData->getThing(38)->setInRack(false);
    GameData->getThing(30)->setUsed(true);
    GameData->getThing(30)->setInRack(false);


    GameData->getThing(114)->setUsed(true);
    GameData->getThing(114)->setInRack(false);
    GameData->getThing(103)->setUsed(true);
    GameData->getThing(103)->setInRack(false);
    two->setPlayerThing(GameData->getThing(142));
    two->setPlayerThing(GameData->getThing(94));
    two->setPlayerThing(GameData->getThing(83));
    two->setPlayerThing(GameData->getThing(110));
    two->setPlayerThing(GameData->getThing(101));
    two->setPlayerThing(GameData->getThing(143));
    two->setPlayerThing(GameData->getThing(103));
    two->setPlayerThing(GameData->getThing(95));
    two->setPlayerThing(GameData->getThing(30));
    two->setPlayerThing(GameData->getThing(38));

    two->setPlayerThing(GameData->getThing(114));
    two->setPlayerThing(GameData->getThing(103));

    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(142),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(94),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(83),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(110),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(101),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(143),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(103),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(95),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(30),2);
    m_hexWidget.at(20)->setPlayerThing(GameData->getThing(38),2);

    m_hexWidget.at(21)->setPlayerThing(GameData->getThing(114),2);
    m_hexWidget.at(21)->setPlayerThing(GameData->getThing(103),2);

    //Player three
    Player *three = GameData->getPlayerFromID(3);
    GameData->getThing(100)->setUsed(true);
    GameData->getThing(100)->setInRack(false);
    GameData->getThing(96)->setUsed(true);
    GameData->getThing(96)->setInRack(false);
    GameData->getThing(92)->setUsed(true);
    GameData->getThing(92)->setInRack(false);
    GameData->getThing(93)->setUsed(true);
    GameData->getThing(93)->setInRack(false);

    three->setPlayerThing(GameData->getThing(100));
    three->setPlayerThing(GameData->getThing(96));
    three->setPlayerThing(GameData->getThing(92));
    three->setPlayerThing(GameData->getThing(93));

    m_hexWidget.at(18)->setPlayerThing(GameData->getThing(100),3);
    m_hexWidget.at(18)->setPlayerThing(GameData->getThing(96),3);
    m_hexWidget.at(18)->setPlayerThing(GameData->getThing(92),3);
    m_hexWidget.at(18)->setPlayerThing(GameData->getThing(93),3);

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
    if(playerNumber == 4)
    {
        if(GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs().size() == 0)
        {
            if(m_hexWidget[4]->objectName() == "0")
            {
                m_hexWidget[4]->setIsEnabledClick(true);
                m_hexWidget[4]->setSelectState(4);
            }
            if(m_hexWidget[8]->objectName() == "0")
            {
                m_hexWidget[8]->setIsEnabledClick(true);
                m_hexWidget[8]->setSelectState(4);
            }
            if(m_hexWidget[31]->objectName() == "0")
            {
                m_hexWidget[31]->setIsEnabledClick(true);
                m_hexWidget[31]->setSelectState(4);
            }
            if(m_hexWidget[35]->objectName() == "0")
            {
                m_hexWidget[35]->setIsEnabledClick(true);
                m_hexWidget[35]->setSelectState(4);
            }
        } else {
            QList<HexWidget *> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
            for(int i = 0; i < temp.size(); i++)
            {
                QList<int> temp2 = getNearHex(temp.at(i)->getID());
                for(int j = 0; j < temp2.size(); j++)
                {
                    if((m_hexWidget.at(temp2.at(j))->hexData()->getTypeID() == 1) ||
                            (m_hexWidget.at(temp2.at(j))->childAt(57,50))) {
                        m_hexWidget.at(temp2.at(j))->setIsEnabledClick(false);
                        m_hexWidget.at(temp2.at(j))->setIsEnableDrag(false);
                        m_hexWidget.at(temp2.at(j))->setSelectState(3);
                    } else {
                        m_hexWidget.at(temp2.at(j))->setIsEnabledClick(true);
                        m_hexWidget.at(temp2.at(j))->setIsEnableDrag(true);
                        m_hexWidget.at(temp2.at(j))->setSelectState(4);
                    }
                }
            }
            for(int i = 0; i < temp.size(); i++)
            {
                temp.at(i)->setIsEnabledClick(false);
                temp.at(i)->setIsEnableDrag(false);
            }
        }
    } else {
        if(m_hexWidget[2]->objectName() == "0")
        {
            m_hexWidget[2]->setIsEnabledClick(true);
            m_hexWidget[2]->setSelectState(4);
        }
        if(m_hexWidget[14]->objectName() == "0")
        {
            m_hexWidget[14]->setIsEnabledClick(true);
            m_hexWidget[14]->setSelectState(4);
        }
        if(m_hexWidget[28]->objectName() == "0")
        {
            m_hexWidget[28]->setIsEnabledClick(true);
            m_hexWidget[28]->setSelectState(4);
        }
        if(m_hexWidget[26]->objectName() == "0")
        {
            m_hexWidget[26]->setIsEnabledClick(true);
            m_hexWidget[26]->setSelectState(4);
        }
        if(m_hexWidget[24]->objectName() == "0")
        {
            m_hexWidget[24]->setIsEnabledClick(true);
            m_hexWidget[24]->setSelectState(4);
        }
        if(m_hexWidget[10]->objectName() == "0")
        {
            m_hexWidget[10]->setIsEnabledClick(true);
            m_hexWidget[10]->setSelectState(4);
        }
    }
}

void MainWindow::hexHasChangedSlot(HexWidget *tempHexWidget)
{
    int playerID = getPlayerTurn();
    GameData->addHexWidget(tempHexWidget, playerID);
    //set the control mark on this Hex
    tempHexWidget->initialControlMark(GameData->getPlayerFromID(getPlayerTurn())->getControlMark(), getPlayerTurn());
    //check for next step
    int count = 0;
    if(playerNumber == 4 || playerNumber == 2)
    {
        for(int i = 1; i <= playerNumber; i++)
        {
            if(GameData->getPlayerFromID(i)->getPlayerHexs().size() == 3)
            {
                count++;
            }
        }
    } else {
        for(int i = 1; i <= playerNumber; i++)
        {
            if(GameData->getPlayerFromID(i)->getPlayerHexs().size() == 2)
            {
                count++;
            }
        }
    }
    //if all the player set up their three hex
    //set up the gold and one tower
    if(count == playerNumber)
    {
        //show up all the other hex
        for(int i = 0; i < m_hexWidget.size(); i++)
        {
            if(m_hexWidget.at(i)->objectName() == "0")
            {
                m_hexWidget.at(i)->setObjectName("1");
                m_hexWidget.at(i)->setSelectState(0);
            }
        }
        //show the warning message
        //and call the next player
        popMessageBox(1);
        //init the gold and tower        
        initGlodnTower();
    } else {
        //show the warning message
        //and call the next player
        popMessageBox(1);
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
    QList<Thing *> temp;
    //just for the test
    if(getPlayerTurn() == 2)
    {
        temp = GameData->getRandomThingFromNum(9);
        GameData->getThing(175)->setUsed(true);
        temp.push_back(GameData->getThing(175));
    } else {
        temp = GameData->getRandomThingFromNum(10);
    }
    //show the trade
    TradeBoxWidget->show();
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
    TradeBoxWidget->hide();
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(confirmThingSlot()));
    //change next player
    popMessageBox(1);

    int count = 0;
    for(int i = 0; i < playerNumber; i++)
    {
        if(GameData->getPlayerFromID(i+1)->getPlayerThings().size() != 0)
        {
            count++;
        }
    }
    if(count == playerNumber)
    {
        //go to another phase
        setPhaseTurn(1);
    } else {
        initThing();
    }
}

void MainWindow::startDragSlot(QList<mylabel*>)
{
    QList<HexWidget *> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(int i = 0; i < temp.size(); i++)
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
    tempHexWidget->initialBuildingLabel(GameData->getPlayerFromID(getPlayerTurn())->getPlayerBuildings().at(0));
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
    if(count == playerNumber)
    {
        //start next phase
        setPhaseTurn(2);
    } else {
        //hide the things rack
        Things_rack->hide();
        //set up the button
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
    QList<HexWidget *> tempHex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(int i = 0; i < tempHex.size(); i++)
    {
        if(tempHex.at(i)->hexData()->getTypeName() != "")
        {
            amount++;
        }
    }
    //combat value of forks
    QList<Building*> tempBuilding = GameData->getPlayerFromID(getPlayerTurn())->getPlayerBuildings();
    for(int i = 0; i < tempBuilding.size(); i++)
    {
        amount += tempBuilding.at(i)->getIncome();
    }
    //special income and hero and city and village
    for(int i = 0; i < tempHex.size(); i++)
    {
        QList<mylabel *> tempLabel = tempHex.at(i)->thingsLabel();
        for(int j = 0; j < tempLabel.size(); j++)
        {
            //Things is special income and map the terrain
            if(tempLabel.at(j)->getData()->getType() == 7 &&
                    (tempLabel.at(j)->getData()->getTerrainType() == tempHex.at(i)->hexData()->getTypeID() ||
                    tempLabel.at(j)->getData()->getTerrainType() == 0))
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
    if(count == playerNumber)
    {
        //start next phase
        setPhaseTurn(4);
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
    //set up the choosen of the hero
    temp_hero = tempHero;
    if(getPhaseTurn() == 2)
    {
        disconnect(button, SIGNAL(clicked()), this, SLOT(skipRecruitHeroSlot()));
    }
    button->hide();
    button->setText("Confirm");
    connect(button, SIGNAL(clicked()), this, SLOT(chooseHeroSLOT()));
    button->show();    
    selectedGold->refreshGoldValue(GameData->getPlayerFromID(getPlayerTurn())->getGold());
    selectedGold->show();
    button->show();
}

void MainWindow::chooseHeroSLOT()
{    
    Hero_widget->hide();
    selectedGold->hide();
    disconnect(button, SIGNAL(clicked()), this, SLOT(chooseHeroSLOT()));
    button->hide();
    //decrease the player gold;
    GameData->getPlayerFromID(getPlayerTurn())->setGold(
                GameData->getPlayerFromID(getPlayerTurn())->getGold() - getselectedGold());    
    refreshPlayerGold();
    dice->refreshLabel();
    dice->show();
    if(getPhaseTurn() == 4)
    {
        //defection event
        disableMapClickandDrag();
    }
}

void MainWindow::checkOwnHero(int dicevalue)
{
    int additionDice = getselectedGold()/5;
    temp_selectedGold = 0;
    if(dicevalue + additionDice >= temp_hero->getAttackValue())
    {
        Message("Message", "Win a Hero");
        //reduce from the controller
        GameData->removeHeroFromID(temp_hero->getID());
        enablePlayerMapClick();
    } else {
        Message("Message", "Lose");
        if(getPhaseTurn() == 2)
        {
            popMessageBox(1);
            startChooseHero(button->objectName().toInt() + 1);
        } else if(getPhaseTurn() == 4) {
            //lose to choose the hero
            button->setText("Skip");
            connect(button,SIGNAL(clicked()),this,SLOT(skipRandomEvent()));
            button->show();
        }

    }
    dice->hide();
}

void MainWindow::setHeroSlot(HexWidget* tempHexWidget)
{
    if(tempHexWidget->heroLabel())
    {
        //the hex already have hero
        Message("Warning", "Already have hero in this hex");
    } else {
        //add hero to the player
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerHero(temp_hero);
        //show the hero on the hex
        temp_hero->setMode(SmallIcon_Mode);
        HeroLabel *tempHero = new HeroLabel(temp_hero, tempHexWidget);
        tempHero->setGeometry(12,35,30,30);
        tempHero->show();
        //set up the hero on the hex
        tempHexWidget->setHeroLabel(tempHero);
        //check the terrain loard and update the hex information of the player
        checkTerrainLord();
        //change next player
        disableMapClickandDrag();
        Hero_widget->hide();
        popMessageBox(1);
        startChooseHero(button->objectName().toInt() + 1);
    }
}

/*********************************************************
 *
 * phase 3 function : recruit things
 *
 * *******************************************************/

void MainWindow::startRecruitThings(int count)
{
    if(count == playerNumber)
    {
        //start next phase
        setPhaseTurn(4);
    } else {
        button->setObjectName(QString::number(count));
        freeRecruitThings();
    }
}

//free recruits
void MainWindow::freeRecruitThings()
{
    QList<HexWidget*> temphex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    int count = 0;
    for(int i = 0; i < temphex.size(); i++)
    {
        if(temphex.at(i)->hexData()->getTypeName() != "")
        {
            count++;
        }
    }
    if(count % 2 == 0)
    {
        count = count/2;
    } else {
        count = (count+1)/2;
    }
    QList<Thing *> temp = GameData->getRandomThingFromNum(count);
    for(int i = 0; i < temp.size(); i++)
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
        QList<Thing *> temp = GameData->getRandomThingFromNum(count);
        for(int i = 0; i < temp.size(); i++)
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
    int count;
    if(getPhaseTurn() == 0)
    {
        count = tempThings.size();
    } else {
        count = tempThings.size()/2;
    }
    QList<Thing *> tempThing = GameData->getRandomThingFromNum(count);
    for(int i = 0; i < count; i++)
    {
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerThing(tempThing.at(i));
    }
    refreshThingWidget();
    TradeBoxWidget->hide();
}

//confirm use treasure slot
void MainWindow::confirmUseTreasure(mylabel* tempLabel)
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Warning"),
                                                  tr("Use the treasure?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
        //add the money to the player
        int temp = GameData->getPlayerFromID(getPlayerTurn())->getGold();
        GameData->getPlayerFromID(getPlayerTurn())->setGold(temp + tempLabel->getData()->getAttackValue());
        refreshPlayerGold();
        //return the thing to the system
        tempLabel->getData()->setUsed(false);
        //delete the thing in the player
        GameData->getPlayerFromID(getPlayerTurn())->deletePlayerThing(tempLabel->getData());
        //refresh the thing widget
        refreshThingWidget();
    } else {
        //do nothing
    }

}

/*********************************************************
 *
 * phase 4 function : Random Event phases
 *
 * *******************************************************/

void MainWindow::startRandomEvent(int count)
{
    if(count == playerNumber)
    {
        //change to next phase
        setPhaseTurn(5);
    } else {
        //skip the random event
        button->setText("Skip");
        button->setObjectName(QString::number(count));
        connect(button,SIGNAL(clicked()),this,SLOT(skipRandomEvent()));
        button->show();
        //start to use the random event
    }
}

void MainWindow::skipRandomEvent()
{
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(skipRandomEvent()));
    //change to next player
    popMessageBox(1);
    startRandomEvent(button->objectName().toInt() + 1);
}

void MainWindow::confirmUseRandomEventSlot(mylabel *tempLabel)
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Warning"),
                                                  tr("Use this event?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes))
    {
        disconnect(button,SIGNAL(clicked()),this,SLOT(skipRandomEvent()));
        int eventID = tempLabel->getData()->getID();
        switch (eventID) {
        case 175:
            defectionEvent();
            break;
        default:
            Message("Warning", "No function for this event now!");
            break;
        }
    } else {
        //do nothing
    }
}

//defection event
void MainWindow::defectionEvent()
{
    //return this event to the system
    GameData->getPlayerFromID(getPlayerTurn())->deletePlayerThing(GameData->getThing(175));
    refreshThingWidget();
    Things_rack->hide();
    Hero_widget->show();
    //enable other player hexclick
    for(int i = 1; i <= playerNumber; i++)
    {
        if(i != getPlayerTurn())
        {
            QList<HexWidget*> tempHex = GameData->getPlayerFromID(i)->getPlayerHexs();
            for(int j = 0; j < tempHex.size(); j++)
            {
                if(tempHex.at(j)->heroLabel())
                {
                    tempHex.at(j)->setIsEnabledClick(true);
                }
            }
        }
    }
}

void MainWindow::defectionCheckHero(HexWidget *temphex)
{
    //hide the hero_widget
    Hero_widget->hide();
    disableMapClickandDrag();

    if(temphex->childAt(50,57)->objectName().toInt() == getPlayerTurn())
    {
        //set up the hero to the player
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerHero(temp_hero);
        //set up the hero label to hex
        temp_hero->setMode(SmallIcon_Mode);
        HeroLabel *tempHero = new HeroLabel(temp_hero, temphex);
        tempHero->setGeometry(12,35,30,30);
        tempHero->show();
        //set up the hero on the hex
        temphex->setHeroLabel(tempHero);
        //set up the skip button
        button->setText("Skip");
        connect(button,SIGNAL(clicked()),this,SLOT(skipRandomEvent()));
        button->show();
    } else {
        //choose the other player hex
        int currentPlayer = getPlayerTurn();
        int selectPlayer = temphex->childAt(50,57)->objectName().toInt();
        int dice1 = qrand()%6 + 1;
        int dice2 = qrand()%6 + 1;
        if(dice1 > dice2)
        {
            //set the select hero
            temp_hero = temphex->heroLabel()->getData();
            //delete the hero belong to the player
            GameData->getPlayerFromID(selectPlayer)->deleteHero(temphex->heroLabel()->getData());
            //delete the hero in the previous hex
            temphex->deleteHeroLabel();
            //enable hex click for the player
            enablePlayerMapClick();
            //apply the defection effect
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ". "
                    + "Steal the hero successfully.";
            Message("Result",temp);
        } else {
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + "."
                    + "Fail for defection.";
            Message("Result",temp);
            button->setText("Skip");
            connect(button,SIGNAL(clicked()),this,SLOT(skipRandomEvent()));
            button->show();
        }
    }

}

/*********************************************************
 *
 * phase 5 function : movement phases
 *
 * *******************************************************/

void MainWindow::startMovement(int count)
{
    if(count == playerNumber)
    {
        //next phase
        setPhaseTurn(6);
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
    //conquer enemy hex
    //return all the things in the sea
    deleteAllSeaHex();
    //disable all the hex click and drag
    disableMapClickandDrag();
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(finishedMovementSlot()));
    //reset all the things movment count
    resetAllThingMovementCount();
    popMessageBox(1);
    startMovement(button->objectName().toInt()+1);
}

void MainWindow::deleteAllSeaHex()
{
    for(int i = 0; i < m_hexWidget.size(); i++)
    {
        //if the hex is sea , delete all the things
        if(m_hexWidget.at(i)->hexData()->getTypeID() == 1)
        {
            m_hexWidget.at(i)->returnAllThings();
        }
    }
}

void MainWindow::getHexForMoveWidgetSlot(HexWidget *tempHex)
{
    //show the move widget
    QRect temp = getMapRect(tempHex->getID());
    MovementWidget->move(temp.x()+114,temp.y());
    MovementWidget->hide();
    //get the things that belong to this player
    int ownPlayer;
    QList<Thing*> tempThings;
    if(tempHex->hexData()->getTypeID() != 1){
        QWidget *controlMark = tempHex->childAt(57,50);
        ownPlayer = controlMark->objectName().toInt();
    }
    if(tempHex->hexData()->getTypeID() == 1) {
        QList<mylabel*> tempThingsLabel = tempHex->getPlayerThingsLabel(getPlayerTurn());
        for(int i = 0; i < tempThingsLabel.size(); i++)
        {
            //special income can't move
            if(tempThingsLabel.at(i)->getData()->getType() != 7)
            {
                tempThings.push_back(tempThingsLabel.at(i)->getData());
            }
        }
    } else if(ownPlayer == getPlayerTurn()){
        QList<mylabel*> tempThingsLabel = tempHex->getPlayerThingsLabel(getPlayerTurn());
        if(tempThingsLabel.size() < tempHex->thingsLabel().size())
        {
            int count = 0;
            //calculate the all flying feature
            for(int i = 0; i < tempHex->thingsLabel().size(); i++)
            {
                if(tempHex->thingsLabel().at(i)->getData()->getType() == 2 ||
                        tempHex->thingsLabel().at(i)->getData()->getType() == 8)
                {
                    count++;
                }
            }
            //calculate the player flying feature
            for(int i = 0; i < tempThingsLabel.size(); i++)
            {
                if(tempThingsLabel.at(i)->getData()->getType() == 2 ||
                        tempThingsLabel.at(i)->getData()->getType() == 8)
                {
                    count--;
                }
            }
            for(int i = 0; i < tempThingsLabel.size(); i++)
            {
                if(count <= 0)
                {
                    break;
                }
                if(tempThingsLabel.at(i)->getData()->getType() == 2 ||
                        tempThingsLabel.at(i)->getData()->getType() == 8)
                {
                    tempThings.push_back(tempThingsLabel.at(i)->getData());
                    count--;
                }
            }
        } else {
            for(int i = 0; i < tempThingsLabel.size(); i++)
            {
                //special income can't move
                if(tempThingsLabel.at(i)->getData()->getType() != 7)
                {
                    tempThings.push_back(tempThingsLabel.at(i)->getData());
                }
            }
        }
    } else {
        if(tempHex->getPlayerThingsLabel(ownPlayer).size() != 0)
        {
            QList<mylabel*> turnPlayerLabel = tempHex->getPlayerThingsLabel(getPlayerTurn());
            QList<mylabel*> ownPlayerLabel = tempHex->getPlayerThingsLabel(ownPlayer);
            //calculate the flying creature that the ownPlayer has
            int ownFlyCreatureCount = 0;
            for(int i = 0; i < ownPlayerLabel.size(); i++)
            {
                if(ownPlayerLabel.at(i)->getData()->getType() == 2 ||
                        ownPlayerLabel.at(i)->getData()->getType() == 8)
                {
                    ownFlyCreatureCount++;
                }
            }
            //decrease the flying creature in the turnplayer
            int turnFlyCreatureCount = 0;
            for(int i = 0; i < turnPlayerLabel.size(); i++)
            {
                if(turnPlayerLabel.at(i)->getData()->getType() == 2 ||
                        turnPlayerLabel.at(i)->getData()->getType() == 8)
                {
                    turnFlyCreatureCount++;
                }
            }
            int count = turnFlyCreatureCount-ownFlyCreatureCount;
            for(int i = 0; i < turnPlayerLabel.size(); i++)
            {
                if(count <= 0)
                {
                    break;
                }
                if(turnPlayerLabel.at(i)->getData()->getType() == 2 ||

                        turnPlayerLabel.at(i)->getData()->getType() == 8)
                {
                    tempThings.push_back(turnPlayerLabel.at(i)->getData());
                    count--;
                }
            }
        } else {
            QList<mylabel*> tempThingsLabel = tempHex->getPlayerThingsLabel(getPlayerTurn());
            for(int i = 0; i < tempThingsLabel.size(); i++)
            {
                //special income can't move
                if(tempThingsLabel.at(i)->getData()->getType() != 7)
                {
                    tempThings.push_back(tempThingsLabel.at(i)->getData());
                }
            }
        }
    }
    if(tempThings.size() != 0)
    {
        emit(initThingsToMovementWidget(tempThings));
        MovementWidget->show();
    }
    //disable all the hex drag
    disableMapDrag();
    //set the selected hex
    selectedHex = tempHex;
}

void MainWindow::movePhaseStartDragSlot(QList<mylabel*> tempLabel)
{
    //enable the nearby hex drag
    enableNearHexDrag(selectedHex->getID());
    //hidden the widget
    MovementWidget->hide();
    //delete the ThingsLabel data in the previous Hex
    selectedHex->deleteThingsLabel(tempLabel);
    if(selectedHex->thingsLabel().size() == 0)
    {
        //delete the battle icon
        if(selectedHex->childAt(57,80))
        {
            delete selectedHex->childAt(57,80);
        }
    }
}

//finish the drag behaviour
void MainWindow::refreshClickStateSlot(HexWidget *tempwidget)
{
    //check if we should put battle mark on the hex
    if(tempwidget->childAt(57,50))
    {
        //the control mark is not belongs to the player
        QWidget *controlmark = tempwidget->childAt(57,50);
        int ownPlayer = controlmark->objectName().toInt();
        if(ownPlayer != getPlayerTurn())
        {
            //the hex contain other player things
            if(tempwidget->getPlayerThingsLabel(getPlayerTurn()).size() != tempwidget->thingsLabel().size())
            {
                //set the battle mark on the hex, this hex is uncontrolled
                QImage tempImage = QImage(":/palyer/image/things/player_battle_building/Thing26.jpg");
                QPixmap pixmap = QPixmap::fromImage(tempImage.scaled(QSize(30,30), Qt::IgnoreAspectRatio));
                QLabel *battle = new QLabel(tempwidget);
                battle->setPixmap(pixmap);
                battle->setGeometry(42,65,30,30);
                battle->show();
            }
            //enable the click of this hex
            tempwidget->setIsEnabledClick(true);
        }
    } else {
        //set the battle mark on the hex, this hex is uncontrolled
        if(!tempwidget->childAt(57,80)&&tempwidget->hexData()->getTypeID() != 1)
        {
            QImage tempImage = QImage(":/palyer/image/things/player_battle_building/Thing26.jpg");
            QPixmap pixmap = QPixmap::fromImage(tempImage.scaled(QSize(30,30), Qt::IgnoreAspectRatio));
            QLabel *battle = new QLabel(tempwidget);
            battle->setPixmap(pixmap);
            battle->setGeometry(42,65,30,30);
            battle->show();
        }
    }
    //disable all the hex drag
    disableMapDrag();
    //enable hex owned click
    enablePlayerMapClick();
    //enable the near sea click
    QList<HexWidget*> tempHex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(int i = 0; i < tempHex.size(); i++)
    {
        if(tempHex.at(i)->hexData()->getTypeName() != "")
        {
            QList<int> temp = getNearHex(tempHex.at(i)->getID());
            for(int j = 0; j < temp.size(); j++)
            {
                if(m_hexWidget.at(temp.at(j))->hexData()->getTypeID() == 1)
                {
                    m_hexWidget.at(temp.at(j))->setIsEnabledClick(true);
                }
            }
        }
    }
}

void MainWindow::sendbackThingToHexSlot(const QList<Thing *> tempThing)
{
    //set the things back to the hex because there are too many things in
    //the hex
    if(tempThing.size() != 0)
    {
        for(int i = 0; i < tempThing.size(); i++)
        {
            tempThing.at(i)->setMode(SmallIcon_Mode);
            mylabel *tempLabel = new mylabel(tempThing.at(i), selectedHex);
            selectedHex->setThingsLabel(tempLabel);
        }
    }
}

void MainWindow::sendbackOneThingToHexSlot(Thing* tempThing)
{
    tempThing->setMode(SmallIcon_Mode);
    mylabel *tempLabel = new mylabel(tempThing, selectedHex);
    selectedHex->setThingsLabel(tempLabel);
}

void MainWindow::resetAllThingMovementCount()
{
    GameData->getPlayerFromID(getPlayerTurn())->setAllThingsMovementCount(4);
}

/*********************************************************
 *
 * phase 6 function : Combat phases
 *
 * *******************************************************/

void MainWindow::startCombat(int count)
{
    if(count == playerNumber)
    {
        //start nex phase
        setPhaseTurn(7);
    } else {
        button->setObjectName(QString::number(count));
        Things_rack->hide();
        enableCombatHexClick();
    }
}

void MainWindow::enableCombatHexClick()
{
    int count = 0;
    for(int i = 0; i < m_hexWidget.size(); i++)
    {
        //hex has this player things and has battle mark
        if(m_hexWidget.at(i)->childAt(57,80)&&
                (m_hexWidget.at(i)->getPlayerThingsLabel(getPlayerTurn()).size() != 0))
        {
            m_hexWidget.at(i)->setIsEnabledClick(true);
            count++;
        }
    }
    if(count == 0)
    {
        //change to next player
        popMessageBox(1);
        startCombat(button->objectName().toInt()+1);
    }
}

void MainWindow::checkExploration(int diceValue)
{
    dice->hide();
    selectedHex->setIsEnabledClick(false);
    if(diceValue == 1 || diceValue == 6)
    {
        //own the hex directly
        //set the control mark on this Hex
        selectedHex->initialControlMark(GameData->getPlayerFromID(getPlayerTurn())->getControlMark(),getPlayerTurn());
        //send the hex to the player
        GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(selectedHex);
        //delete the battle mark
        delete selectedHex->childAt(57,80);
        //show the message
        Message("Congratulation", "You win the hex");
        //change to next player
        popMessageBox(1);
        startCombat(button->objectName().toInt()+1);
    } else {
        //exploration
        //get random things from the bag as the defence
        QList<Thing*> tempCreatures = GameData->getRandomCreatureFromNum(diceValue);
        for(int i = 0; i < tempCreatures.size(); i++)
        {
            tempCreatures.at(i)->setUsed(false);
        }
        emit(sendThingToCombatSignal(tempCreatures,(getPlayerTurn()+1)%4));
        //get the player things from the hex and delete things in this player
        QList<mylabel*> tempMyLabel = selectedHex->getPlayerThingsLabel(getPlayerTurn());
        QList<Thing*> tempThings;
        for(int i = 0; i < tempMyLabel.size(); i++)
        {
            tempThings.push_back(tempMyLabel.at(i)->getData());
            GameData->getPlayerFromID(getPlayerTurn())->deletePlayerThing(tempThings.at(i));
        }
        //check bluff feature
        QList<HexWidget*> PlayerHex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
        QList<int> HexType;
        for(int i = 0; i < PlayerHex.size(); i++)
        {
            HexType.push_back(PlayerHex.at(i)->hexData()->getTypeID());
        }
        for(int i = 0; i < tempThings.size();)
        {
            if(!HexType.contains(tempThings.at(i)->getTerrainType()))
            {
                if(tempThings.at(i)->getType() != 7)
                {
                    //return the things to the rack
                    tempThings.at(i)->setUsed(false);
                    tempThings.at(i)->setInRack(true);
                    //delete the thing in this player
                    tempThings.removeAt(i);
                } else {
                    ++i;
                }
            } else {
                ++i;
            }
        }
        //delete the battle mark
        delete selectedHex->childAt(57,80);
        //initial the combat data
        emit(sendThingToCombatSignal(tempThings,getPlayerTurn()));
        //delete all the things in the hex
        selectedHex->deleteAllThingsLabel();
        //start exploration
        if(tempThings.size() == 0)
        {
            Message("Warning", "All the things are bluff");
            //change to next player
            popMessageBox(1);
            startCombat(button->objectName().toInt()+1);
        } else {
            emit(sendOwnerToCombatSignal(getPlayerTurn()));
            emit(startCombatSignal(false));
        }
    }
}

void MainWindow::changeNextPlayerSlot()
{
    popMessageBox(1);
    startCombat(button->objectName().toInt()+1);
}

void MainWindow::startCombatSlot(HexWidget *tempHex)
{
    selectedHex = tempHex;
    int hexOwner = 0;
    if(tempHex->childAt(57,50))
    {
        hexOwner = tempHex->childAt(57,50)->objectName().toInt();
    }
    if(hexOwner == 0 &&
            tempHex->thingsLabel().size() == tempHex->getPlayerThingsLabel(getPlayerTurn()).size())
    {
        //row the dice
        dice->show();
    } else {
        if(tempHex->thingsLabel().size() == tempHex->getPlayerThingsLabel(getPlayerTurn()).size()
                && tempHex->building() == NULL)
        {
            //change the owner of this hex
            //delete the owner of the previous player
            int hexOwner = tempHex->childAt(57,50)->objectName().toInt();
            GameData->getPlayerFromID(hexOwner)->deleteHexWidget(tempHex);
            delete tempHex->childAt(57,50);
            //set the control mark on this Hex
            tempHex->initialControlMark(GameData->getPlayerFromID(getPlayerTurn())->getControlMark(),getPlayerTurn());
            //send the hex to the player
            GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(tempHex);
            //delete the battle mark
            delete tempHex->childAt(57,80);
            //disable the click for the hex
            tempHex->setIsEnabledClick(false);
        } else {
            GameData->getPlayerFromID(hexOwner)->deleteHexWidget(tempHex);
            //delete the owner of the hex
            //Combat or fighting over explorations
            //send all the creature to the combat widget including special income item
            //and delete all the thing of the player
            for(int j = 1; j <= playerNumber; j++)
            {
                QList<mylabel*> tempMyLabel = tempHex->getPlayerThingsLabel(j);
                if(tempMyLabel.size() != 0)
                {
                    QList<Thing*> tempThings;
                    for(int i = 0; i < tempMyLabel.size(); i++)
                    {
                        tempThings.push_back(tempMyLabel.at(i)->getData());
                        GameData->getPlayerFromID(j)->deletePlayerThing(tempThings.at(i));
                    }
                    //check bluff feature
                    QList<HexWidget*> PlayerHex = GameData->getPlayerFromID(j)->getPlayerHexs();
                    QList<int> HexType;
                    for(int i = 0; i < PlayerHex.size(); i++)
                    {
                        HexType.push_back(PlayerHex.at(i)->hexData()->getTypeID());
                    }
                    for(int i = 0; i < tempThings.size();)
                    {
                        if(tempThings.at(i)->getType() != 7)
                        {
                            if(!HexType.contains(tempThings.at(i)->getTerrainType()))
                            {
                                //delete the thing in this player
                                tempThings.removeAt(i);
                            } else {
                                ++i;
                            }

                        } else {
                            ++i;
                        }
                    }
                    emit(sendThingToCombatSignal(tempThings,j));
                }
            }
            //remove all the things in the hex
            tempHex->deleteAllThingsLabel();
            //send the building to the combat
            if(tempHex->building())
            {
                emit(sendBuildingToCombatSignal(tempHex->building()));
                //delete the building in this player
                GameData->getPlayerFromID(hexOwner)->deleteBuilding(tempHex->building());
                //delete the building in the hex
                tempHex->deleteBuilding();
                delete tempHex->childAt(87,50);               
            }
            //send the owner of the hex to the combats
            emit(sendOwnerToCombatSignal(hexOwner));
            //set up the hex player
            hexOwnPlayer = hexOwner;
            //disable the click for the hex
            tempHex->setIsEnabledClick(false);
            //delete the controal mark
            delete tempHex->childAt(57,50);
            //delete the battle mark
            delete tempHex->childAt(57,80);
            emit(startCombatSignal(true));
        }
    }
}

void MainWindow::getThingsFromRetreatSlot(QList<Thing*> tempThings, int playerID)
{
    QList<int> tempHexs = getNearHex(selectedHex->getID());
       for(int j = 0; j < tempThings.size(); j++)
       {
           for(int i = 0; i < tempHexs.size(); i++)
           {
               if(m_hexWidget.at(tempHexs.at(i))->childAt(57,50) &&
                       m_hexWidget.at(tempHexs.at(i))->childAt(57,50)->objectName().toInt() == playerID &&
                       m_hexWidget.at(tempHexs.at(i))->getPlayerThingsLabel(playerID).size() < 10)
               {
                           tempThings.at(j)->setUsed(true);
                           tempThings.at(j)->setInRack(false);
                           //set the thing on the hex
                           m_hexWidget.at(tempHexs.at(j))->setPlayerThing(tempThings.at(j),playerID);
                           //set the thing to the player
                           GameData->getPlayerFromID(playerID)->setPlayerThing(tempThings.at(j));
                           break;
               } else {
                   break;
               }
           }
       }
}

void MainWindow::getThingsFromCombatWinnerSlot(QList<Thing*> tempThings, int playerID)
{
    //set the controlmark
    selectedHex->initialControlMark(GameData->getPlayerFromID(playerID)->getControlMark(),playerID);
    //set the things to the player
    for(int i = 0; i < tempThings.size(); i++)
    {
        tempThings.at(i)->setUsed(true);
        tempThings.at(i)->setInRack(false);
        GameData->getPlayerFromID(playerID)->setPlayerThing(tempThings.at(i));
    }
    //set the things on the hex
    selectedHex->setPlayerThing(tempThings,playerID);
    //set the hexwidget to the player
    GameData->getPlayerFromID(playerID)->setPlayerHex(selectedHex);
    //change to next player
    popMessageBox(1);
    startCombat(button->objectName().toInt()+1);
}

void MainWindow::getBuildingFromCombatSlot(Building* tempBuilding, int playerID)
{
    //set building to the hex
    selectedHex->setBuilding(tempBuilding);
    //set the label on the hex
    selectedHex->initialBuildingLabel(tempBuilding);
    //set building to the player
    GameData->getPlayerFromID(playerID)->setPlayerBuilding(tempBuilding);
    //check the winning of this player
    if(checkPlayerCitadel(playerID) == 2)
    {
        QString temp = "Player " + QString::number(playerID) + " Win the Game";
        Message("Congratulation", temp);
        this->close();
    }
    //refresh the keep one turn
    if((tempBuilding->getID() == 4) && (hexOwnPlayer == playerID))
    {
        KeepOneTurn = false;
    }
}

/*********************************************************
 *
 * phase 7 function : Construction phases
 *
 * *******************************************************/

void MainWindow::startConstruction(int count)
{
    if(count == playerNumber)
    {
        //change to next phase
        //check the winnning of the game
        if((checkTotalCitadelNumber() == 1) && KeepOneTurn)
        {
            int playerID = 0;
            for(int i = 1; i <= playerNumber; i++)
            {
                if(checkPlayerCitadel(i) == 1)
                {
                    playerID = i;
                }
            }
            QString temp = "Player " + QString::number(playerID) + " Win the Game";
            Message("Congratulation", temp);
            this->close();
        } else {
            setPhaseTurn(8);
        }
    } else {
        //disable all the hex click first
        disableMapClickandDrag();
        button->setObjectName(QString::number(count));
        //set skip button
        button->setText("Skip");
        connect(button,SIGNAL(clicked()),this,SLOT(constrcutionSkipSlot()));
        button->show();
        //enable the hex click for updating the tower
        enablePlayerMapClick();
    }

}

void MainWindow::constrcutionSkipSlot()
{
    //hide the button
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(constrcutionSkipSlot()));
    //skip this phase,change to nex player
    popMessageBox(1);
    startConstruction(button->objectName().toInt()+1);
}

void MainWindow::startConstructionSlot(HexWidget *tempHex)
{
    //disable the click for the hex
    tempHex->setIsEnabledClick(false);
    //check the player have enough money or not
    if(GameData->getPlayerFromID(getPlayerTurn())->getGold() < 5)
    {
        Message("Warning", "Don't have enough money!");
        //hide the button
        button->hide();
        disconnect(button,SIGNAL(clicked()),this,SLOT(constrcutionSkipSlot()));
        popMessageBox(1);
        startConstruction(button->objectName().toInt()+1);
    } else {
        /*
         * check the hex has buidling or not, if it has builidng then update the building
         * if not, then put a tower on the building
         * */
        if(tempHex->building())
        {
            if(tempHex->building()->getID() == 3)
            {
                if(checkTotalCitadelNumber() < 2 && checkPlayerCitadel(getPlayerTurn()) == 0)
                {
                    if(GameData->getPlayerFromID(getPlayerTurn())->getGold() < 20)
                    {
                        Message("Warning", "Don't have enough money to build a citadel!");
                    } else {
                        //build a citadel
                        //delete the building in the player
                        GameData->getPlayerFromID(getPlayerTurn())->deleteBuilding(tempHex->building());
                        //delete the building in the hex
                        tempHex->deleteBuilding();
                        //delete the building label in the hex
                        delete tempHex->childAt(87,50);
                        //add citadel to the player
                        Building* citadel = GameData->getBuildingFromID(4);
                        GameData->getPlayerFromID(getPlayerTurn())->setPlayerBuilding(citadel);
                        //add the citadel to the hex
                        tempHex->setBuilding(citadel);
                        //set the citadel label to the hex
                        tempHex->initialBuildingLabel(citadel);
                        KeepOneTurn = false;
                    }
                } else {
                    Message("Warning", "Too many Citadel!");
                }
            } else if(tempHex->building()->getID() == 4) {
                Message("Warning", "Can't upgrade the citadel!");
            } else {
                //upgrade the building in the hex
                Building* building = NULL;
                switch (tempHex->building()->getID()) {
                case 1:
                    building = GameData->getBuildingFromID(2);
                    break;
                case 2:
                    building = GameData->getBuildingFromID(3);
                    break;
                default:
                    break;
                }
                //delete the building in the player
                GameData->getPlayerFromID(getPlayerTurn())->deleteBuilding(tempHex->building());
                //delete the building in the hex
                tempHex->deleteBuilding();
                //delete the building label in the hex
                delete tempHex->childAt(87,50);
                //add the building to the player
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerBuilding(building);
                //add the building to the hex
                tempHex->setBuilding(building);
                //set the building label on the hex
                tempHex->initialBuildingLabel(building);
                //decrease the money of the player
                int money = GameData->getPlayerFromID(getPlayerTurn())->getGold();
                GameData->getPlayerFromID(getPlayerTurn())->setGold(money-5);
                refreshPlayerGold();
            }
        } else {
            //add tower to the player
            Building* tower = GameData->getBuildingFromID(1);
            GameData->getPlayerFromID(getPlayerTurn())->setPlayerBuilding(tower);
            //add the citadel to the hex
            tempHex->setBuilding(tower);
            //set the tower label to the hex
            tempHex->initialBuildingLabel(tower);
            //decrease the money of the player
            int money = GameData->getPlayerFromID(getPlayerTurn())->getGold();
            GameData->getPlayerFromID(getPlayerTurn())->setGold(money-5);
            refreshPlayerGold();
        }
    }

}

int MainWindow::checkTotalCitadelNumber()
{
    int count = 0;
    for(int i = 1; i <= playerNumber; i++)
    {
        QList<Building*> tempBuildings = GameData->getPlayerFromID(i)->getPlayerBuildings();
        for(int j = 0; j < tempBuildings.size(); j++)
        {
            if(tempBuildings.at(j)->getID() == 4)
            {
                count++;
            }
        }
    }
    return count;
}

int MainWindow::checkPlayerCitadel(int playerID)
{
    int count = 0;
    QList<Building*> tempBuildings = GameData->getPlayerFromID(playerID)->getPlayerBuildings();
    for(int i = 0; i < tempBuildings.size(); i++)
    {
        if(tempBuildings.at(i)->getID() == 4)
        {
            count++;
        }
    }
    return count;
}

/*********************************************************
 *
 * phase 8 function : Special power phases
 *
 * *******************************************************/
void MainWindow::startSpecialPower(int count)
{
    if(count == playerNumber)
    {
        //change to next phase
        changePlayerOrder();
    } else {
        //hid the things rack
        Things_rack->hide();
        //show the skip button
        button->setObjectName(QString::number(count));
        button->setText("skip");
        connect(button,SIGNAL(clicked()),this,SLOT(specialPowerSkipSlot()));
        button->show();
        //check all the hero ability power
        Things_rack->hide();
        enableHeroHexClick();
    }
}

void MainWindow::specialPowerSkipSlot()
{
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(specialPowerSkipSlot()));
    //change to next player
    popMessageBox(1);
    startSpecialPower(button->objectName().toInt()+1);
}

void MainWindow::enableHeroHexClick()
{
    QList<HexWidget*> tempHex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(int i = 0; i < tempHex.size(); i++)
    {
        if(tempHex.at(i)->heroLabel())
        {
            tempHex.at(i)->setIsEnabledClick(true);
        }
    }
}

void MainWindow::heroHexClickSlot(HexWidget* tempHex)
{
    selectedHex = tempHex;
    switch (tempHex->heroLabel()->getData()->getID()) {
    case 4:
        heroMasterThief(0);
        break;
    default:
        Message("Warning", "Don't have this kind of hero!");
        break;
    }
    tempHex->setIsEnabledClick(false);
}

void MainWindow::heroMasterThief(int count)
{
    if(count == 2)
    {
        Message("Warning", "You loss the Master Thief");
        //delete the master thief of the player
        GameData->getPlayerFromID(getPlayerTurn())->deleteHeroFromID(4);
        //add the master to the board
        GameData->addHeroTo10HeroData(GameData->heroData().at(4));
        //delete the master thief of the hex
        selectedHex->deleteHeroLabel();
    } else {
        dice->setObjectName(QString::number(count));
        //this is the operation of the hero master thief
        selectPlayerWidget = new QComboBox(this);
        selectPlayerWidget->move(800,300);
        //set up the three label
        for(int i = 1; i <= playerNumber; i++)
        {
            if(i != getPlayerTurn())
            {
                selectPlayerWidget->addItem(QString::number(i));
            }
        }
        connect(selectPlayerWidget, SIGNAL(activated(QString)), this, SLOT(heroMasterThiefButtonClicked(QString)));
        selectPlayerWidget->show();
    }
}

void MainWindow::heroMasterThiefButtonClicked(QString tempPlayer)
{
    selectPlayerWidget->hide();
    selectPlayerWidget->clear();

    int currentPlayer = getPlayerTurn();
    int selectPlayer = tempPlayer.toInt();
    int dice1 = qrand() % 6 + 1;
    int dice2 = qrand() % 6 + 1;
    if(dice1 > dice2)
    {
        //the first roll player win
        if(dice->objectName().toInt() == 0)
        {
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ". "
                    + "Player " + QString::number(currentPlayer) + " Win, Apply Master thief";
            Message("Result",temp);
            //change all the gold from player 2 to player 1
            int currentPlayerGold = GameData->getPlayerFromID(getPlayerTurn())->getGold();
            int selectedPlayerGold = GameData->getPlayerFromID(selectPlayer)->getGold();
            GameData->getPlayerFromID(getPlayerTurn())->setGold(currentPlayerGold + selectedPlayerGold);
            GameData->getPlayerFromID(selectPlayer)->setGold(0);
            refreshPlayerGold();
        } else {
            //the second roll player win, there is no effect
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ".";
            Message("Result",temp);
            Message("Warning", "No effect!");
        }
    } else if (dice1 == dice2){
        if(dice->objectName().toInt() == 0)
        {
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ".";
            Message("Result",temp);
            heroMasterThief(dice->objectName().toInt() + 1);
        } else {
            //the second roll player equal, there is no effect
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ".";
            Message("Result",temp);
            Message("Warning", "No effect!");
        }
    } else {
        if(dice->objectName().toInt() == 0)
        {
            //the first roll player lose, there is no effect
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ".";
            Message("Result",temp);
            Message("Warning", "No effect!");
        } else {
            //the second roll player lose, player lose the master thief
            QString temp =  "Player " + QString::number(currentPlayer) + " dice value : " + QString::number(dice1)
                    + ". Player " + QString::number(selectPlayer) + " dice value : " + QString::number(dice2) + ".";
            Message("Result",temp);
            heroMasterThief(dice->objectName().toInt() + 1);
        }
    }
}

//check therain loard and add the hex to the player
void MainWindow::checkTerrainLord()
{
    //get all the hex of this player
    QList<HexWidget*> tempHex = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    //get the hex type
    QList<int> hexType;
    for(int i = 0; i < tempHex.size(); i++)
    {
        hexType.push_back(tempHex.at(i)->hexData()->getTypeID());
    }
    //check if there has hero, heroID
    QList<int> tempID;
    for(int i = 0; i < tempHex.size(); i++)
    {
        if(tempHex.at(i)->heroLabel())
        {
            //they are all terrain lords
            if(tempHex.at(i)->heroLabel()->getData()->getID() == 0 ||
                    tempHex.at(i)->heroLabel()->getData()->getID() == 2 ||
                    tempHex.at(i)->heroLabel()->getData()->getID() == 19 ||
                    tempHex.at(i)->heroLabel()->getData()->getID() == 17||
                    tempHex.at(i)->heroLabel()->getData()->getID() == 9 ||
                    tempHex.at(i)->heroLabel()->getData()->getID() == 21 ||
                    tempHex.at(i)->heroLabel()->getData()->getID() == 12
                    )
            {
                tempID.push_back(tempHex.at(i)->heroLabel()->getData()->getID());
            }
        }
    }
    //set the new type of hex into the player
    for(int i = 0; i < tempID.size(); i++)
    {

        switch (tempID.at(i)) {
        case 0:
            //desert master
            if(!hexType.contains(2))
            {
                Hex *hextype = new Hex(2,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        case 2:
            //forest king
            if(!hexType.contains(3))
            {
                Hex *hextype = new Hex(3,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        case 19:
            //ice lord
            if(!hexType.contains(4))
            {
                Hex *hextype = new Hex(4,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        case 17:
            //jungle king
            if(!hexType.contains(5))
            {
                Hex *hextype = new Hex(5,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        case 9:
            //mountain king
            if(!hexType.contains(6))
            {
                Hex *hextype = new Hex(6,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        case 21:
            //plains king
            if(!hexType.contains(7))
            {
                Hex *hextype = new Hex(7,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        case 12:
            //swamp king
            if(!hexType.contains(8))
            {
                Hex *hextype = new Hex(8,"","","","");
                HexWidget *temphexwidget = new HexWidget(this,hextype);
                GameData->getPlayerFromID(getPlayerTurn())->setPlayerHex(temphexwidget);
            }
            break;
        default:
            break;
        }
    }
}

/*********************************************************
 *
 * phase 9 function : change player order
 *
 * *******************************************************/

void MainWindow::changePlayerOrder()
{
    Message("Warning", "Start next game turn");
    //finish one turn
    if(checkTotalCitadelNumber() == 1)
    {
        KeepOneTurn = true;
    }
    //change the player turn
    setPlayerTurn((getPlayerTurn()+1)%4);
    //start the gold collection phase
    setPhaseTurn(1);
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
    case 4:
        startRandomEvent(0);
        break;
    case 5:
        startMovement(0);
        break;
    case 6:
        startCombat(0);
        break;
    case 7:
        startConstruction(0);
        break;
    case 8:
        startSpecialPower(0);
        break;
    default:
        break;
    }
}

void MainWindow::enablePlayerMapClick()
{
    QList<HexWidget*> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(int i = 0; i < temp.size(); i++)
    {
        temp[i]->setIsEnabledClick(true);
    }
}

void MainWindow::enablePlayerMapDrag()
{
    QList<HexWidget*> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(int i = 0; i < temp.size(); i++)
    {
        temp[i]->setIsEnableDrag(true);
    }
}

void MainWindow::disableMapClickandDrag()
{
    for(int i = 0; i < m_hexWidget.size(); i++)
    {
        m_hexWidget[i]->setIsEnabledClick(false);
        m_hexWidget[i]->setIsEnableDrag(false);
    }
}

void MainWindow::disableMapDrag()
{
    for(int i = 0; i < m_hexWidget.size(); i++)
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
    if(playerNumber == 4)
    {
        int player1 = GameData->getPlayerFromID(1)->getGold();
        int player2 = GameData->getPlayerFromID(2)->getGold();
        int player3 = GameData->getPlayerFromID(3)->getGold();
        int player4 = GameData->getPlayerFromID(4)->getGold();
        ui->Player1_Gold->setText(QString::number(player1));
        ui->Player2_Gold->setText(QString::number(player2));
        ui->Player3_Gold->setText(QString::number(player3));
        ui->Player4_Gold->setText(QString::number(player4));
    } else if(playerNumber == 3) {
        int player1 = GameData->getPlayerFromID(1)->getGold();
        int player2 = GameData->getPlayerFromID(2)->getGold();
        int player3 = GameData->getPlayerFromID(3)->getGold();
        ui->Player1_Gold->setText(QString::number(player1));
        ui->Player2_Gold->setText(QString::number(player2));
        ui->Player3_Gold->setText(QString::number(player3));
    } else if(playerNumber == 2) {
        int player1 = GameData->getPlayerFromID(1)->getGold();
        int player2 = GameData->getPlayerFromID(2)->getGold();
        ui->Player1_Gold->setText(QString::number(player1));
        ui->Player2_Gold->setText(QString::number(player2));
    }

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
    if(getPhaseTurn() == 2 ||
            getPhaseTurn() == 4)
    {
        checkOwnHero(tempdiceValue);
    } else if(getPhaseTurn() == 6){
        checkExploration(tempdiceValue);
    }
}

void MainWindow::sendbackThingToRackSlot(Thing *tempThing)
{
    tempThing->setInRack(true);
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
    if(PhaseTurn == 0)
    {
        for(int i = 0; i < m_hexWidget.size(); i++)
        {
            if(m_hexWidget.at(i)->objectName() == "0")
            {
                m_hexWidget.at(i)->setSelectState(3);
            }
        }
    }
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
    setPlayerTurn(getPlayerTurn()%playerNumber + 1);
    refreshThingWidget();
    refreshPlayerGold();
}

void MainWindow::changePlayerTurnSlot2(QAbstractButton *)
{
    setPlayerTurn(getPlayerTurn()%playerNumber + 1);
    //if every one set the tower then system divide things
    int count = 0;
    for(int i = 0; i < playerNumber; i++)
    {
        if(GameData->getPlayerFromID(i+1)->getPlayerBuildings().size() == 1)
        {
            count++;
        }
    }
    if(count == playerNumber)
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
    KeepOneTurn = false;
    temp_selectedGold = 0;
}

//initial all the Hex in the map
void MainWindow::initMap()
{
    for(int i = 0; i < 37; i++)
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
        connect(tempHexWidget, SIGNAL(sendbackThingSignal(Thing*)),
                this, SLOT(sendbackThingToRackSlot(Thing*)));
        connect(tempHexWidget, SIGNAL(sendThingsBackToHex(const QList<Thing*>)),
                this, SLOT(sendbackThingToHexSlot(const QList<Thing*>)));
        connect(tempHexWidget, SIGNAL(sendbackOneThingSignal(Thing*)),
                this, SLOT(sendbackOneThingToHexSlot(Thing*)));
        connect(tempHexWidget, SIGNAL(refreshMapClickState(HexWidget*)),
                this, SLOT(refreshClickStateSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(startCombatSignal(HexWidget*)),
                this, SLOT(startCombatSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(refrshThingRack()),
                this, SLOT(refreshThingWidget()));
        connect(tempHexWidget, SIGNAL(startConstrction(HexWidget*)),
                this, SLOT(startConstructionSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(startSpecialPowerSingal(HexWidget*)),
                this, SLOT(heroHexClickSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(checkHeroOwner(HexWidget*)),
                this, SLOT(defectionCheckHero(HexWidget*)));
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
    connect(this, SIGNAL(initThingToRackSignal(QList<Thing*>)),
            Things_rack, SLOT(initThingToRackSlot(QList<Thing*>)));
    connect(Things_rack, SIGNAL(startDragSignal(QList<mylabel*>)),
            this, SLOT(startDragSlot(QList<mylabel*>)));
    connect(Things_rack, SIGNAL(confirmUseTreasure(mylabel*)),
            this, SLOT(confirmUseTreasure(mylabel*)));
    connect(Things_rack, SIGNAL(confirmUseRandomEvent(mylabel*)),
            this, SLOT(confirmUseRandomEventSlot(mylabel*)));
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
    button->setGeometry(1000,150,80,80);
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
    connect(this,SIGNAL(initThingsToMovementWidget(QList<Thing*>)),
            MovementWidget, SLOT(initThingToRackSlot(QList<Thing*>)));
    connect(MovementWidget,SIGNAL(startDragSignal(QList<mylabel*>)),
            this,SLOT(movePhaseStartDragSlot(QList<mylabel*>)));
}
