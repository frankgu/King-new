#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTime>
#include "mapwidget.h"
#include "herowidget.h"
#include "hexwidget.h"
#include "control.h"
#include "dicewidget.h"
#include "selectgoldwidget.h"
#include "thingsdropwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setBackground();
    ~MainWindow();
    int getPlayerTurn() const;
    void setPlayerTurn(int value);
    int getPhaseTurn() const;
    void setPhaseTurn(int value);
    void setThingsRack();
    void initData();
    void initMap();
    void initGlodnTower();
    void startInitMap();
    QRect getMapRect(int index);
    QList<int> getNearHex(int index);
    void initThing();
    void startCollectGold(int count);
    void refreshPlayerGold();    
    void refreshThingWidget();
    void startChooseHero(int count);
    void setHeroWidget();
    void checkOwnHero(int dicevalue);
    void enablePlayerMapClick();
    void Message(QString title, QString body);
    void startRecruitThings(int count);
    void freeRecruitThings();
    void paidRecruitThings();
    int getselectedGold() const;
    void tradeThings();
    void initAllWidget();
    void startMovement(int count);
    void enableNearHexDrag(int hexID);
    void enablePlayerMapDrag();
    void disableMapDrag();
    void resetAllThingMovementCount();
    void deleteAllSeaHex();
public slots:
    void hexHasChangedSlot(HexWidget *tempHexWidget);
    void getRequirePlayerIDnPhaseSlot();
    void changePlayerTurnSlot(QAbstractButton *);
    void changePlayerTurnSlot2(QAbstractButton *);
    void buttonSlot();
    void setBuildingToHexSlot(HexWidget *tempHexWidget);
    void initThingSlot();
    void confirmThingSlot();
    void startDragSlot(QList<mylabel *>);
    void collectGoldSLOT();
    void chooseHeroSLOT();
    void heroConfirmSlot(Hero *tempHero);
    void updateDiceValueSlot(int tempdiceValue);
    void setHeroSlot(HexWidget *tempHexWidget);
    void getSelectedGoldSlot(int gold);
    void dropboxSlot(QList<Thing *> tempThings);
    void tradeboxSlot(QList<Thing *> tempThings);
    void tradeAndDropThingsSlot();
    void confirmPaidRecruitThingsSlot();
    void skipRecruitHeroSlot();
    void getHexForMoveWidgetSlot(HexWidget *tempHex);
    void movePhaseStartDragSlot(QList<mylabel *> tempLabel);
    void sendbackThingToRackSlot(Thing *tempThing);
    void finishedMovementSlot();
    void sendbackThingToHexSlot(const QList<Thing *> tempThing);
    void sendbackOneThingToHexSlot(Thing *tempThing);
    void refreshClickStateSlot(HexWidget *tempwidget);
signals:
    void initThingToRackSignal(QList<Thing*> m_thingData);
    void sendPlayerIDnPhaseSignal(int tempPlayerID, int tempPhase);
    void initHeroToWidget(QList<Hero*> herolist);
    void initThingsToMovementWidget(QList<Thing*>);

private:
    Ui::MainWindow       *ui;
    Control              *GameData;
    Hero                 *temp_hero;
    MapWidget            *Things_rack;
    MapWidget            *MovementWidget;
    QPushButton          *button;
    DiceWidget           *dice;
    SelectGoldWidget     *selectedGold;
    HeroWidget           *Hero_widget;
    QList<HexWidget*>   m_hexWidget;
    HexWidget            *selectedHex;
    ThingsDropWidget     *DropBoxWidget;
    ThingsDropWidget     *TradeBoxWidget;
    int                  temp_selectedGold;
    int                  playerTurn;
    int                  PhaseTurn;
    int getRandomNumber(int range);
    void popMessageBox(int index);
    void disableMapClickandDrag();
};

#endif // MAINWINDOW_H
