//
//  GUI.cpp
//  TowerDefense_new
//
//  Created by Georgios Floros on 04/08/2014.
//
//

#include "GameScene.h"


GUI::GUI(cocos2d::Layer& sc)
{
    this->towerChosen = false;
    this->towerUpgradeGUI = false;
    this->firstTowerUpgrade = false;
    this->towerDeHighlight = false;
    this->towerCreationSelected = false;
    this->menuOpen = false;
    this->lblGameAlertEnabled = false;
    
    this->_sc = &sc;
    GameScene* gs = (GameScene*) _sc;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->pMenu = Menu::create();
    this->pMenu->setPosition(visibleSize.width, 0);
    
    //game message
    this->lblGameAlert = Label::createWithSystemFont("", "Arial", 26);
    this->lblGameAlert->setPosition(visibleSize.width/2, (visibleSize.height/2) - 60);
    this->lblGameAlert->setColor(ccc3(255, 0, 0));
    this->lblGameAlert->setVisible(false);
    gs->addChild(this->lblGameAlert);

    this->lblGameAlert2 = Label::createWithSystemFont("", "Arial", 26);
    this->lblGameAlert2->setPosition(visibleSize.width/2, (visibleSize.height/2) - 90);
    this->lblGameAlert2->setColor(ccc3(255, 0, 0));
    this->lblGameAlert2->setVisible(false);
    gs->addChild(this->lblGameAlert2);
    
    //the menu button
    this->lblMenu = Label::createWithSystemFont("Press ESC for Menu", "Arial", 16);
    this->lblMenu->setPosition(75, visibleSize.height - 22);
    gs->addChild(this->lblMenu);
    
    //the status bar
    this->bgStatus = Sprite::create("statusBG1.png");
    this->bgStatus->setPosition(visibleSize.width - 220, visibleSize.height - 22);
    gs->addChild(this->bgStatus);
    
    this->lblLifePoints = Label::createWithSystemFont("", "Arial", 16);
    this->lblLifePoints->setPosition(visibleSize.width - 360, visibleSize.height - 22);
    this->lblLifePoints->setString("0");
    gs->addChild(this->lblLifePoints);
    
    this->lblCreepsLeft = Label::createWithSystemFont("", "Arial", 16);
    this->lblCreepsLeft->setPosition(visibleSize.width - 255, visibleSize.height - 22);
    this->lblCreepsLeft->setString("0");
    gs->addChild(this->lblCreepsLeft);
    
    this->lblRound = Label::createWithSystemFont("", "Arial", 16);
    this->lblRound->setPosition(visibleSize.width - 160, visibleSize.height - 22);
    this->lblRound->setString("0/0");
    gs->addChild(this->lblRound);
    
    this->lblCoins = Label::createWithSystemFont("", "Arial", 16);
    this->lblCoins->setPosition(visibleSize.width - 70, visibleSize.height - 22);
    this->lblCoins->setString("0");
    gs->addChild(this->lblCoins);
    
    this->buttonCreateTower = MenuItemImage::create("buttonTowerPlace.png","buttonTowerPlace.png",CC_CALLBACK_1(GUI::createTowerInitiation, this));
    this->buttonCreateTower->setPosition(-40, 40);
    this->pMenu->addChild(this->buttonCreateTower);
    gs->addChild(this->pMenu, 3);
    
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector( schedule_selector(GUI::update), this,0.1f,false );
    
}

GUI::~GUI()
{
    GameScene* gs = (GameScene*) _sc;
    
    gs->removeChild(this->pMenu, true);
    gs->removeChild(this->escMenu, true);
    
    gs->removeChild(this->lbl1, true);
    gs->removeChild(this->lbl2, true);
    gs->removeChild(this->lbl3, true);
    gs->removeChild(this->lbl4, true);
    gs->removeChild(this->lbl5, true);
    gs->removeChild(this->lbl6, true);
    gs->removeChild(this->lblAP, true);
    gs->removeChild(this->lblAS, true);
    gs->removeChild(this->lblCoins, true);
    gs->removeChild(this->lblCreepsLeft, true);
    gs->removeChild(this->lblEle, true);
    gs->removeChild(this->lblLifePoints, true);
    gs->removeChild(this->lblMenu, true);
    gs->removeChild(this->lblRound, true);
    
}

void GUI::update(float delta)
{
    //remove the game alert text if time has passed
    time_t cur = time(NULL) * 100;
    double dif = difftime(cur, this->gameAlertPrev);
    if ( dif > 180 && this->lblGameAlertEnabled == true )
    {
        if(this->lblGameAlert)
        {
            this->lblGameAlert->setVisible(false);
            this->lblGameAlertEnabled = false;
        }
    }
    
}

void GUI::SetGameAlert(std::string str)
{
    this->lblGameAlert->setString(str);
    this->lblGameAlert->setVisible(true);
    this->gameAlertPrev = time(NULL) * 100;
    this->lblGameAlertEnabled = true;
}

void GUI::SetGameAlert2(std::string str)
{
    this->lblGameAlert2->setString(str);
    this->lblGameAlert2->setVisible(true);
}

void GUI::GameAlert2Toggle()
{
    if(this->lblGameAlert2->isVisible())
    {
        this->lblGameAlert2->setVisible(false);
    }
    else
    {
        this->lblGameAlert2->setVisible(true);
    }
}

void GUI::Menu()
{
    GameScene* gs = (GameScene*) _sc;
    Size visibleSize = Director::getInstance()->getVisibleSize();

    if(this->menuOpen == false)
    {
        this->bgMenu = Sprite::create("menu_bg1.png");
        this->bgMenu->setPosition(visibleSize.width/2, visibleSize.height/2);
        gs->addChild(this->bgMenu);
        
        this->escMenu = Menu::create();
        this->escMenu->setPosition(visibleSize.width/2, visibleSize.height/2);
        
        this->buttonMenuMainMenu = MenuItemImage::create("menuMainMenuButton1.png","menuMainMenuButton2.png",CC_CALLBACK_1(GUI::buttonMenuMainMenuCallback, this));
        this->buttonMenuMainMenu->setPosition(0, 0);
        this->escMenu->addChild(this->buttonMenuMainMenu);
        
        this->buttonMenuExit = MenuItemImage::create("menuButtonExit1.png","menuButtonExit2.png",CC_CALLBACK_1(GUI::buttonMenuExitCallback, this));
        this->buttonMenuExit->setPosition(0, -70);
        this->escMenu->addChild(this->buttonMenuExit);
        
        if(gs->imEnabled == true)
        {
            this->buttonMenuIMStatus = MenuItemImage::create("menuIMStatusButton1.png","menuIMStatusButton2.png",CC_CALLBACK_1(GUI::buttonMenuIMStatusCallback, this));
            this->buttonMenuIMStatus->setPosition(0, 70);
            this->escMenu->addChild(this->buttonMenuIMStatus);
        }
        
        gs->addChild(this->escMenu);
        
        this->menuOpen = true;
        
    }
    else
    {
        gs->removeChild(this->bgMenu, true);
        
        this->escMenu->removeChild(this->buttonMenuMainMenu, true);
        
        this->escMenu->removeChild(this->buttonMenuExit, true);
        
        if(gs->imEnabled == true)
        {
            this->escMenu->removeChild(this->buttonMenuIMStatus, true);
        }
        
        gs->removeChild(this->escMenu, true);
        
        this->menuOpen = false;
    }
    
}

void GUI::buttonMenuMainMenuCallback(Ref* sender)
{
    GameScene* gs = (GameScene*) _sc;
    gs->BackToMainMenu();
}

void GUI::buttonMenuIMStatusCallback(Ref* sender)
{
    GameScene* gs = (GameScene*) _sc;
    
    if(gs->GetAiStatus()->enabled)
    {
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->enabled = false;
    }
    else
    {
        gs->GetAiStatus()->enabled = true;
        gs->GetAiStatus()->IMDraw();
    }
}

void GUI::buttonMenuExitCallback(Ref* sender)
{
    Director::getInstance()->end();
    exit(0);
}


void GUI::InitTowerManagementGUI(Tower* selectedTower)
{
    GameScene* gs = (GameScene*) _sc;
    
    if(this->towerChosen == false)
    {
        this->towerInUse = selectedTower;
        
        if(!this->buttonCreateTower)
        {
            this->pMenu->removeChild(this->buttonCreateTower, true);
        }
        
    
        this->buttonSellTower = MenuItemImage::create("buttonTowerSell.png","buttonTowerSell.png", CC_CALLBACK_0(GUI::sellTowerMenu, this, (Ref*)selectedTower));
        this->buttonSellTower->setPosition(-700, 40);
        this->pMenu->addChild(this->buttonSellTower);
        
        
        //tower bg
        if(selectedTower->GetElement() == ElementalAffinity::None)
        {
            this->bgTowersUpgrade = Sprite::create("towerUpgradesBG1.png");
            this->bgTowersUpgrade->setPosition(Director::getInstance()->getVisibleSize().width - 270, 40);
            gs->addChild(this->bgTowersUpgrade);
            
            //the stats
            this->lblAP = Label::createWithSystemFont("", "Arial", 12);
            this->lblAP->setPosition(Director::getInstance()->getVisibleSize().width - 490, 60);
            this->lblAP->setString("Atk: 0");
            gs->addChild(this->lblAP);
            
            this->lblAS = Label::createWithSystemFont("", "Arial", 12);
            this->lblAS->setPosition(Director::getInstance()->getVisibleSize().width - 490, 45);
            this->lblAS->setString("Spd: 0");
            gs->addChild(this->lblAS);
            
            this->lblEle = Label::createWithSystemFont("", "Arial", 12);
            this->lblEle->setPosition(Director::getInstance()->getVisibleSize().width - 490, 30);
            this->lblEle->setString("Ele: 0");
            gs->addChild(this->lblEle);
            
            
        }
        else
        {
            this->bgTowersUpgrade = Sprite::create("towerUpgradesBG2.png");
            this->bgTowersUpgrade->setPosition(Director::getInstance()->getVisibleSize().width - 155 , 40);
            gs->addChild(this->bgTowersUpgrade);
            
            
            //the stats
            this->lblAP = Label::createWithSystemFont("", "Arial", 12);
            this->lblAP->setPosition(Director::getInstance()->getVisibleSize().width - 260, 60);
            this->lblAP->setString("Atk: 0");
            gs->addChild(this->lblAP);
            
            this->lblAS = Label::createWithSystemFont("", "Arial", 12);
            this->lblAS->setPosition(Director::getInstance()->getVisibleSize().width - 260, 45);
            this->lblAS->setString("Spd: 0");
            gs->addChild(this->lblAS);
            
            this->lblEle = Label::createWithSystemFont("", "Arial", 12);
            this->lblEle->setPosition(Director::getInstance()->getVisibleSize().width - 260, 30);
            this->lblEle->setString("Ele: none");
            gs->addChild(this->lblEle);
            
        }
        
        this->refreshTowerStatusLabel(((Tower*)selectedTower)->attackPoints, ((Tower*)selectedTower)->inbetweenAttacksPeriod, ((Tower*)selectedTower)->GetElement());
        
        std::stringstream ss1;
        ss1 << selectedTower->GetAttackUpgradeCost();
        std::stringstream ss2;
        ss2 << selectedTower->GetSpeedUpgradeCost();
        
        this->lbl1 = Label::create(ss1.str(), "Arial", 16, CCSizeMake(60, 32), kCCTextAlignmentRight);
        this->lbl1->setColor(Color3B::WHITE);
        this->lbl1->setPosition(Director::getInstance()->getVisibleSize().width - 110, 10);
        gs->addChild(this->lbl1);
        
        this->lbl2 = Label::create(ss2.str(), "Arial", 16, CCSizeMake(60, 32), kCCTextAlignmentRight);
        this->lbl2->setColor(Color3B::WHITE);
        this->lbl2->setPosition(Director::getInstance()->getVisibleSize().width - 170, 10);
        gs->addChild(this->lbl2);
        
        if(selectedTower->GetElement() == ElementalAffinity::None)
        {
            std::stringstream ss3;
            ss3 << selectedTower->toweRules->GetWaterUpgradeCost();
            this->lbl3 = Label::create(ss3.str(), "Arial", 16, CCSizeMake(60, 32), kCCTextAlignmentRight);
            this->lbl3->setColor(Color3B::WHITE);
            this->lbl3->setPosition(Director::getInstance()->getVisibleSize().width - 230, 10);
            gs->addChild(this->lbl3);
            
            std::stringstream ss4;
            ss4 << selectedTower->toweRules->GetEarthUpgradeCost();
            this->lbl4 = Label::create(ss4.str(), "Arial", 16, CCSizeMake(60, 32), kCCTextAlignmentRight);
            this->lbl4->setColor(Color3B::WHITE);
            this->lbl4->setPosition(Director::getInstance()->getVisibleSize().width - 290, 10);
            gs->addChild(this->lbl4);
            
            std::stringstream ss5;
            ss5 << selectedTower->toweRules->GetFireUpgradeCost();
            this->lbl5 = Label::create(ss5.str(), "Arial", 16, CCSizeMake(60, 32), kCCTextAlignmentRight);
            this->lbl5->setColor(Color3B::WHITE);
            this->lbl5->setPosition(Director::getInstance()->getVisibleSize().width - 350, 10);
            gs->addChild(this->lbl5);
            
            std::stringstream ss6;
            ss6 << selectedTower->toweRules->GetShockUpgradeCost();
            this->lbl6 = Label::create(ss6.str(), "Arial", 16, CCSizeMake(60, 32), kCCTextAlignmentRight);
            this->lbl6->setColor(Color3B::WHITE);
            this->lbl6->setPosition(Director::getInstance()->getVisibleSize().width - 410, 10);
            gs->addChild(this->lbl6);
        }
        
        //sets up the upgrades menu
        this->towerUpgradeGUI = true;
        
        //the back button
        this->buttonBackFromUpgrade = MenuItemImage::create("buttonTowerBack.png","buttonTowerBack.png",CC_CALLBACK_0(GUI::backTowerMenu, this, (Ref*)selectedTower));
        this->buttonBackFromUpgrade->setPosition(-40, 40);
        this->pMenu->addChild(this->buttonBackFromUpgrade);
        
        this->buttonUpgradeAttackPowerTower = MenuItemImage::create("buttonTowerUpgradeAttackPower.png","buttonTowerUpgradeAttackPower.png", CC_CALLBACK_0(GUI::upgradeAttackPowerTowerMenu, this, (Ref*)selectedTower));
        this->buttonUpgradeAttackPowerTower->setPosition(-100, 50);
        this->pMenu->addChild(this->buttonUpgradeAttackPowerTower);
        
        this->buttonUpgradeAttackSpeedTower = MenuItemImage::create("buttonTowerUpgradeAttackSpeed.png","buttonTowerUpgradeAttackSpeed.png",CC_CALLBACK_0(GUI::upgradeAttackSpeedTowerMenu, this, (Ref*)selectedTower));
        this->buttonUpgradeAttackSpeedTower->setPosition(-160, 50);
        this->pMenu->addChild(this->buttonUpgradeAttackSpeedTower);
        
        //affinity can only be once selected
        if(selectedTower->GetElement() == ElementalAffinity::None)
        {
            this->buttonUpgradeToFireTower = MenuItemImage::create("buttonTowerUpgradeFire.png","buttonTowerUpgradeFire.png",CC_CALLBACK_0(GUI::upgradeToFireTowerMenu, this, (Ref*)selectedTower));
            this->buttonUpgradeToFireTower->setPosition(-220, 50);
            this->pMenu->addChild(this->buttonUpgradeToFireTower);
            
            this->buttonUpgradeToWaterTower = MenuItemImage::create("buttonTowerUpgradeWater.png","buttonTowerUpgradeWater.png",CC_CALLBACK_0(GUI::upgradeToWaterTowerMenu, this, (Ref*)selectedTower));
            this->buttonUpgradeToWaterTower->setPosition(-280, 50);
            this->pMenu->addChild(this->buttonUpgradeToWaterTower);
            
            this->buttonUpgradeToEarthTower = MenuItemImage::create("buttonTowerUpgradeEarth.png","buttonTowerUpgradeEarth.png",CC_CALLBACK_0(GUI::upgradeToEarthTowerMenu, this, (Ref*)selectedTower));
            this->buttonUpgradeToEarthTower->setPosition(-340, 50);
            this->pMenu->addChild(this->buttonUpgradeToEarthTower);
            
            this->buttonUpgradeToShockTower = MenuItemImage::create("buttonTowerUpgradeShock.png","buttonTowerUpgradeShock.png",CC_CALLBACK_0(GUI::upgradeToShockTowerMenu, this, (Ref*)selectedTower));
            this->buttonUpgradeToShockTower->setPosition(-400, 50);
            this->pMenu->addChild(this->buttonUpgradeToShockTower);
        }
        
        ////////////////////////////////////
        //Hightlight toggle
        selectedTower->ToggleHighlight(true);
        ////////////////////////////////////
        
        this->towerChosen = true;
    }
}


void GUI::DestructTowerManagementGUI(bool cleanupElemental)
{
    GameScene* gs = (GameScene*) _sc;
    
    //re add main place button
    this->buttonCreateTower = MenuItemImage::create("buttonTowerPlace.png","buttonTowerPlace.png",CC_CALLBACK_1(GUI::createTowerInitiation, this));
    this->buttonCreateTower->setPosition(-40, 40);
    this->pMenu->addChild(this->buttonCreateTower);
        
    this->towerChosen = false;
    
    //BG TOWERS UI
    gs->removeChild(this->bgTowersUpgrade, true);
    gs->removeChild(this->lblAP, true);
    gs->removeChild(this->lblAS, true);
    gs->removeChild(this->lblEle, true);
        
    this->pMenu->removeChild(this->buttonUpgradeAttackPowerTower, true);
    this->pMenu->removeChild(this->buttonUpgradeAttackSpeedTower, true);
    
    this->pMenu->removeChild(this->buttonSellTower, true);
    
    gs->removeChild(lbl1, true);
    gs->removeChild(lbl2, true);
        
    if(cleanupElemental == true)
    {
        gs->removeChild(this->lbl3, true);
        gs->removeChild(this->lbl4, true);
        gs->removeChild(this->lbl5, true);
        gs->removeChild(this->lbl6, true);
            
        gs->removeChild(this->lblAP, true);
        gs->removeChild(this->lblAS, true);
        gs->removeChild(this->lblEle, true);
            
        this->buttonUpgradeToFireTower->setVisible(false);
        this->buttonUpgradeToWaterTower->setVisible(false);
        this->buttonUpgradeToEarthTower->setVisible(false);
        this->buttonUpgradeToShockTower->setVisible(false);
            
    }
    
}

void GUI::refreshGameStatusLabel(int currentLifePoints, int creepsLeft, int round, int remainingCoins)
{
    GameScene* gs = (GameScene*) _sc;
    
    std::stringstream ss1;
    ss1 << currentLifePoints;
    this->lblLifePoints->setString(ss1.str());
    
    std::stringstream ss2;
    ss2 << creepsLeft;
    this->lblCreepsLeft->setString(ss2.str());
    
    std::stringstream ss3;
    ss3 << round << "/" << gs->gameState.NumberOfRounds;
    this->lblRound->setString(ss3.str() );
    
    std::stringstream ss4;
    ss4 << remainingCoins;
    this->lblCoins->setString(ss4.str());
}

void GUI::refreshTowerStatusLabel(int aPower, double aSpeed, ElementalAffinity aff)
{
    std::stringstream ss1;
    ss1 << "Atk: " << aPower;
    this->lblAP->setString(ss1.str());
    
    std::stringstream ss2;
    ss2 << "Spd: " <<  aSpeed;
    this->lblAS->setString(ss2.str());
    
    std::stringstream ss3;
    
    if(aff==ElementalAffinity::None)
    {
        ss3 << "Ele: none";
    }
    else if(aff==ElementalAffinity::Earth)
    {
        ss3 << "Ele: Earth";
    }
    else if(aff==ElementalAffinity::Fire)
    {
        ss3 << "Ele: Fire";

    }
    else if(aff==ElementalAffinity::Water)
    {
        ss3 << "Ele: Water";

    }
    else if(aff==ElementalAffinity::Shock)
    {
        ss3 << "Ele: Shock";
    }
    
    this->lblEle->setString(ss3.str() );
    
}

void GUI::sellTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;
    
    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        gs->playerHandler->AddCoins(t->cost);
        gs->getMapLayer()->removeChild(t);
        //make the occupied tiles available again
    
        //change that based on map
        if(Settings::mapType == MapType::Open)
        {
            gs->getMapInfo()->ChangeTypeForSurroundingIndexes(MapInfoType::RoadAllowedTower, t->getPosition());
        }
        else
        {
            gs->getMapInfo()->ChangeTypeForSurroundingIndexes(MapInfoType::Planes, t->getPosition());
        }
    
        this->backTowerMenu(t);
        
        std::cout << "test "; 
        
        gs->DeleteTower(t);
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        gs->aiPlayerHandler->NotifyAIRecalculate();
    
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::SellTower, gs->gameState.CurrentRound);
        gs->currSessionStats.AddCurrency(gs->gameState.CurrentRound, t->cost);
    
        //DEBUGGING HELPERS
        gs->GetAiStatus()->ClearEnvironment();
        gs->GetAiStatus()->DrawEnvironment();
    
        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
            gs->GetAiStatus()->ClearIM();
            gs->GetAiStatus()->IMDraw();
        }
        
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't sell while simulating, please wait.");
    }
    
}


void GUI::backTowerMenu(Ref* pSender)
{
    Tower* t = (Tower*)pSender;
    this->towerInUse = t;
    this->towerInUse->ToggleHighlight(false);
    
    if( this->firstTowerUpgrade == true )
    {
        this->DestructTowerManagementGUI(true);
        this->firstTowerUpgrade = false;
    }
    else
    {
        if( ((Tower*)pSender)->GetElement() == ElementalAffinity::None )
        {
            this->DestructTowerManagementGUI(true);
        }
        else
        {
            this->DestructTowerManagementGUI(false);
        }
    }

}


void GUI::DestructTowerUpgradesGUI(Tower *selectedTower, bool cleanupElemental)
{
    GameScene* gs = (GameScene*) _sc;
    
    //BG TOWERS UI
    gs->removeChild(this->bgTowersUpgrade, true);
    gs->removeChild(this->lblAP, true);
    gs->removeChild(this->lblAS, true);
    gs->removeChild(this->lblEle, true);
        
    this->pMenu->removeChild(this->buttonUpgradeAttackPowerTower, true);
    this->pMenu->removeChild(this->buttonUpgradeAttackSpeedTower, true);
        
    gs->removeChild(lbl1, true);
    gs->removeChild(lbl2, true);
        
    if(cleanupElemental == true)
    {
        gs->removeChild(this->lbl3, true);
        gs->removeChild(this->lbl4, true);
        gs->removeChild(this->lbl5, true);
        gs->removeChild(this->lbl6, true);
            
        gs->removeChild(this->lblAP, true);
        gs->removeChild(this->lblAS, true);
        gs->removeChild(this->lblEle, true);
          
        this->buttonUpgradeToFireTower->setVisible(false);
        this->buttonUpgradeToWaterTower->setVisible(false);
        this->buttonUpgradeToEarthTower->setVisible(false);
        this->buttonUpgradeToShockTower->setVisible(false);
            
    }
    
}


void GUI::upgradeAttackPowerTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;
    
    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        this->towerInUse = t;
    
        bool success = t->UpgradeAttackPower(gs->playerHandler);
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        if(success==false)
        {
            std::stringstream ss;
            ss << "Not enough coins to upgrade (";
            ss << t->toweRules->GetAttackUpgradeCost(*t) << " needed).";
            this->SetGameAlert(ss.str());
        }
    
        this->backTowerMenu((Ref*)t);
        this->InitTowerManagementGUI(t);
        
        this->refreshTowerStatusLabel(t->attackPoints, t->inbetweenAttacksPeriod, t->GetElement());
    
        //sessionStats update
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::UpgradeTowerAttack, gs->gameState.CurrentRound);
        gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, t->toweRules->GetAttackUpgradeCost(*t));

        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
        }
        
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->IMDraw();
        
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't upgrade attack speed while simulating, please wait.");
    }
     
}


void GUI::upgradeAttackSpeedTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;

    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        this->towerInUse = t;
    
        bool success = t->UpgradeAttackSpeed(gs->playerHandler);
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        if(success==false)
        {
            std::stringstream ss;
            ss << "Not enough coins to upgrade (";
            ss << t->toweRules->GetSpeedUpgradeCost(*t) << " needed).";
            this->SetGameAlert(ss.str());
        }
    
        this->backTowerMenu((Ref*)t);
        this->InitTowerManagementGUI(t);

        this->refreshTowerStatusLabel(t->attackPoints, t->inbetweenAttacksPeriod, t->GetElement());
    
        //sessionStats update
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::UpgradeTowerSpeed, gs->gameState.CurrentRound);
        gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, t->toweRules->GetSpeedUpgradeCost(*t));

        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
        }
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->IMDraw();
        
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't upgrade attack points while simulating, please wait.");
    }
}

void GUI::upgradeToShockTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;
    
    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        this->towerInUse = t;
    
        bool success = t->UpgradeToShock(gs->playerHandler);
    
        if(success==false)
        {
            this->SetGameAlert("Not enough coins to upgrade (500 needed).");
        }
    
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        this->firstTowerUpgrade = true;
        
        this->backTowerMenu((Ref*)t);
        this->InitTowerManagementGUI(t);
    
        this->refreshTowerStatusLabel(t->attackPoints, t->inbetweenAttacksPeriod, t->GetElement());
    
        //sessionStats update
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::UpgradeTowerElement, gs->gameState.CurrentRound);
        gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, t->toweRules->GetShockUpgradeCost());
    
        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
        }
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->IMDraw();
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't upgrade to shock while simulating, please wait.");
    }
}

void GUI::upgradeToEarthTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;

    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        this->towerInUse = t;
    
        bool success = t->UpgradeToEarth(gs->playerHandler);
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        if(success==false)
        {
            this->SetGameAlert("Not enough coins to upgrade (500 needed).");
        }
    
        this->firstTowerUpgrade = true;
        
        this->backTowerMenu((Ref*)t);
        this->InitTowerManagementGUI(t);
    
        this->refreshTowerStatusLabel(t->attackPoints, t->inbetweenAttacksPeriod, t->GetElement());
    
        //sessionStats update
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::UpgradeTowerElement, gs->gameState.CurrentRound);
        gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, t->toweRules->GetEarthUpgradeCost());
    
        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
        }
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->IMDraw();
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't upgrade to earth while simulating, please wait.");
    }
}

void GUI::upgradeToWaterTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;

    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        this->towerInUse = t;
    
        bool success = t->UpgradeToWater(gs->playerHandler);
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        if(success==false)
        {
            this->SetGameAlert("Not enough coins to upgrade (500 needed).");
        }
    
        this->firstTowerUpgrade = true;
        
        this->backTowerMenu((Ref*)t);
        this->InitTowerManagementGUI(t);
    
        this->refreshTowerStatusLabel(t->attackPoints, t->inbetweenAttacksPeriod, t->GetElement());
    
        //sessionStats update
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::UpgradeTowerElement, gs->gameState.CurrentRound);
        gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, t->toweRules->GetWaterUpgradeCost());
    
        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
        }
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->IMDraw();
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't upgrade to water while simulating, please wait.");
    }
}

void GUI::upgradeToFireTowerMenu(Ref* pSender)
{
    GameScene* gs = (GameScene*) _sc;

    if(!gs->simulationMode)
    {
        Tower* t = (Tower*)pSender;
        this->towerInUse = t;
    
        bool success = t->UpgradeToFire(gs->playerHandler);
        this->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
    
        if(success==false)
        {
            this->SetGameAlert("Not enough coins to upgrade (500 needed).");
        }
    
        this->firstTowerUpgrade = true;
        
        this->backTowerMenu((Ref*)t);
        this->InitTowerManagementGUI(t);
    
        this->refreshTowerStatusLabel(t->attackPoints, t->inbetweenAttacksPeriod, t->GetElement());
    
        //sessionStats update
        gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::UpgradeTowerElement, gs->gameState.CurrentRound);
        gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, t->toweRules->GetFireUpgradeCost());
    
        if(gs->imEnabled)
        {
            gs->getInfluenceMap()->Invalidate();
        }
        gs->GetAiStatus()->ClearIM();
        gs->GetAiStatus()->IMDraw();
    }
    else
    {
        this->SetGameAlert("Simulation Enabled - can't upgrade to fire while simulating, please wait.");
    }
}

void GUI::createTowerInitiation(Ref* pSender)
{
    if(this->towerCreationSelected == true)
    {
        this->towerCreationSelected = false;
    }
    else
    {
        this->towerCreationSelected = true;
    }
}

