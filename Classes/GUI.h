//
//  GUI.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 04/08/2014.
//
//

#ifndef __TowerDefense_new__GUI__
#define __TowerDefense_new__GUI__

#include "GameScene.h"

class GUI : public Ref
{
    
    private:
    cocos2d::Layer* _sc;
    void update(float delta);
    
    public:
    
    GUI(cocos2d::Layer& sc);
    ~GUI();

    void refreshGameStatusLabel(int currentLifePoints, int creepsLeft, int round, int remainingCoins);
    void refreshTowerStatusLabel(int aPower, double aSpeed, ElementalAffinity aff);
    
    //game status labels / status bar
    Label* lbl1;
    Label* lbl2;
    Label* lbl3;
    Label* lbl4;
    Label* lbl5;
    Label* lbl6;
    
    //game message
    Label* lblGameAlert2;
    bool lblGameAlertEnabled;
    void GameAlert2Toggle();
    void SetGameAlert2(std::string str);
    
    Label* lblGameAlert;
    time_t gameAlertPrev;
    void SetGameAlert(std::string str);
    
    //tower stats labels
    Label* lblAP;
    Label* lblAS;
    Label* lblEle;
    
    //status bar
    Sprite* bgStatus;
    Label* lblLifePoints;
    Label* lblCreepsLeft;
    Label* lblRound;
    Label* lblCoins;
    
    Menu* pMenu;
    
    MenuItem *buttonCreateTower;
    MenuItem *buttonSellTower;
    
    MenuItem *buttonBackFromUpgrade;
    
    Sprite * bgTowersUpgrade;
    
    MenuItem *buttonUpgradeAttackSpeedTower;
    MenuItem *buttonUpgradeAttackPowerTower;
    MenuItem *buttonUpgradeToFireTower;
    MenuItem *buttonUpgradeToWaterTower;
    MenuItem *buttonUpgradeToEarthTower;
    MenuItem *buttonUpgradeToShockTower;
    
    void backTowerMenu(Ref* pSender);
    void sellTowerMenu(Ref* pSender);
 
    void upgradeAttackSpeedTowerMenu(Ref* pSender);
    void upgradeAttackPowerTowerMenu(Ref* pSender);
    void upgradeToFireTowerMenu(Ref* pSender);
    void upgradeToWaterTowerMenu(Ref* pSender);
    void upgradeToEarthTowerMenu(Ref* pSender);
    void upgradeToShockTowerMenu(Ref* pSender);
    
    void createTowerInitiation(Ref* pSender);
    void InitTowerManagementGUI(Tower* selectedTower);
    void DestructTowerManagementGUI(bool cleanupElemental);
    void DestructTowerUpgradesGUI(Tower *selectedTower, bool cleanupElemental);
    
    
    //the menu button
    Sprite* bgMenu;
    Menu* escMenu;
    MenuItem* buttonMenuIMStatus;
    MenuItem* buttonMenuMainMenu;
    MenuItem* buttonMenuExit;

    void buttonMenuIMStatusCallback(Ref* sender);
    void buttonMenuMainMenuCallback(Ref* sender);
    void buttonMenuExitCallback(Ref* sender);
    
    Label* lblMenu;
    bool menuOpen;
    void Menu();
    
    
    //Tower GUI vars
    bool towerChosen;
    bool towerUpgradeGUI;
    Tower* towerInUse;
    bool firstTowerUpgrade;
    bool towerDeHighlight;
    bool towerCreationSelected;

    
    Sprite* towerDragSprite;
    
    
};

#endif

