//
//  Player.cpp
//  TowerDefense
//
//  Created by Georgios Floros on 26/06/2014.
//
//


#include "GameScene.h"


Player::~Player()
{
    
}

Player::Player(cocos2d::Layer &refClass, std::string name, int lifePoints)
{
    
    this->lifePoints = 0;
    this->currency = 0;
    
    this->_sc = &refClass;
    GameScene* gs = (GameScene*) _sc;
    
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, gs);
    
    this->playerName = name;
    this->lifePoints = lifePoints;
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    this->tw = new TowerRules();
    //TowerRules * tw = new TowerRules();
    tw->SetAddAttackDamage(30.0f);
    tw->SetSubAttackSpeed(15.5f);

    tw->SetAddFireDamage(30.0f);
    tw->SetAddEarthDamage(30.0f);
    tw->SetAddWaterDamage(30.0f);
    tw->SetAddShockDamage(30.0f);
    
    tw->SetElementsAmplifier(1.1f);
    tw->SetElementWeaknessDamageMultiplier(1.2f);
    
    tw->SetAttackUpgradeCost(50);
    tw->SetSpeedUpgradeCost(50);
    
    tw->SetFireUpgradeCost(500);
    tw->SetEarthUpgradeCost(500);
    tw->SetShockUpgradeCost(500);
    tw->SetWaterUpgradeCost(500);
    
    
    //-----touch began-----
    listener->onTouchBegan = [=] (Touch* touch,Event* event)
    {
        auto touchPoint = gs->getMapLayer()->convertToNodeSpace(touch->getLocation());
        
        if(gs->GetGUI()->towerCreationSelected == true)
        {
            //6 tiles away
            bool inVicinity =  false;
            bool tilesValidRes = false;
            
            if(gs->mapType == MapType::Open)
            {
                inVicinity = gs->getMapInfo()->SurroundingTilesAvailable(touchPoint, 2);
            }
            else
            {
                //**** TODO REFACTOR START ****
                tilesValidRes = gs->getMapInfo()->TilesForTowerValid(touchPoint);
                if( tilesValidRes == true ) //silly, have to refactor
                {
                    inVicinity = false;
                }
                else
                {
                    inVicinity = true;
                }
                //**** TODO REFACTOR END ****
            }
            
            if(!gs->simulationMode)
            {
            
                if(inVicinity == false && gs->playerHandler->GetCurrency() >= 50 ) //the initial tower cost
                {
                    //place the towers
                    Tower *tower = new Tower(*gs, Settings::towerTexture, tw);
                    int index = gs->getMapInfo()->ConvertPointToId(touchPoint);
                    tower->setPosition(gs->getMapInfo()->ConvertIdToPoint(index));
                    //the hitPosition is set always over the touch position in the center of the sprite texture
                    tower->SetHitPositions(gs->getMapInfo());
                    tower->SetStartingStats(Settings::towerAttackRange, Settings::towerAttackPoints, Settings::towerInbetweenAttacksPeriod, Settings::towerCost);
                    gs->getMapLayer()->addChild(tower);
                    gs->InsertTower(tower);
                
                    gs->playerHandler->RemoveCoins(50);
                    gs->GetGUI()->refreshGameStatusLabel(gs->playerHandler->GetLifePoints(), gs->gameState.NumberOfCreepsLeft, gs->gameState.CurrentRound, gs->playerHandler->GetCurrency());
                    //change node type
                    gs->getMapInfo()->ChangeTypeForSurroundingIndexes(MapInfoType::Tower, touchPoint);
                
                    //invalidate Influence Map
                    if(gs->imEnabled == true)
                    {
                        //Invalidates the influence map
                        gs->getInfluenceMap()->Invalidate();
                    
                        gs->GetAiStatus()->ClearIM();
                        gs->GetAiStatus()->IMDraw();
            
                        //debug
                        //sc->getInfluenceMap()->TestPrintAllInfluences();
                    }
                
                    gs->GetAiStatus()->DrawEnvironment();

                    //check if ai has to be invalidated
                    gs->aiPlayerHandler->NotifyAIRecalculate();
             
                    //gs->getRadar()->invalidate();
        
                    gs->currSessionStats.AddTower(gs->gameState.CurrentRound, tower);
                
                    gs->currSessionStats.TowerUpgradesStats(TypeOfActivity::PlaceTower, gs->gameState.CurrentRound);
                    gs->currSessionStats.RemoveCurrency(gs->gameState.CurrentRound, tower->cost);
                
                }
                else
                {
                    gs->GetGUI()->SetGameAlert("Tower couldn't be placed, not enough coins or another tower or road too close.");
                }
            
            }
            else
            {
                gs->GetGUI()->SetGameAlert("Simulation Enabled - can't place towers while simulating, please wait.");
            }
        
            //end spawn tower
            gs->GetGUI()->towerCreationSelected = false;
        }
        else
        {
            //checks for tower touches
            for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
            {
                Tower* t = *tower;
                Point p = t->getPosition();
                p.y = p.y + 30;
                p.getDistance(touchPoint);
                
                if(p.getDistance(touchPoint) < 30)
                {
                    if( gs->GetGUI()->towerChosen == true)
                    {
                        gs->GetGUI()->towerInUse->ToggleHighlight(false);
                        gs->GetGUI()->backTowerMenu(gs->GetGUI()->towerInUse);
                    }
                    else
                    {
                        gs->GetGUI()->towerInUse = t;
                    }
                    
                    gs->GetGUI()->InitTowerManagementGUI(t);
                
                }
            }
            
            this->_bIsMove = false;
        }
        
        return true;
    };
    
    //-----touch moved-----
    listener->onTouchMoved = [=](Touch* touch,Event* event)
    {
        
        if(gs->GetGUI()->towerCreationSelected == true)
        {
            
        }
        else
        {
            
            auto touchPoint = gs->getMapLayer()->convertToNodeSpace(touch->getLocation()); ;
            auto firstTouchPoint = gs->getMapLayer()->convertToNodeSpace(touch->getStartLocation());
            
            if (touchPoint.getDistance(firstTouchPoint) > 5) {
                this->_bIsMove = true;
                
            } else {
                
            }
            
            if (this->_bIsMove) {
                auto preTouchPoint = gs->getMapLayer()->convertToNodeSpace(touch->getPreviousLocation());
                auto position  = gs->getMapLayer()->getPosition();
                gs->getMapLayer()->setPosition(Point(position.x + touchPoint.x - preTouchPoint.x, position.y + touchPoint.y - preTouchPoint.y));
            }
            
        }
    };
    
    //-----touch ended-----
    listener->onTouchEnded = [=](Touch* touch,Event* event)
    {
        if(gs->GetGUI()->towerCreationSelected == true)
        {
            
        }
        else
        {
            
        }
    };
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, gs);
    
    //schedules a schedulable task Player::update
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Player::update),this,0.1f,false);
}

void Player::SetCurrency(int coins)
{
    this->currency = coins;
}

void Player::SetLifePoints(int lp)
{
    this->lifePoints = lp;
}

void Player::SetPlayerName(std::string name)
{
    this->playerName = name;
}

std::string& Player::GetPlayerName()
{
    return this->playerName;
}

void Player::update(float delta)
{
    GameScene* gs = (GameScene*) _sc;
    
    //camera movement
    if( this->_ForwardMove == true && Settings::fullyInitialized == true)
    {
        auto position  = gs->getMapLayer()->getPosition();
        gs->getMapLayer()->setPosition(Point(position.x, position.y - 50));
    }
    else if( this->_BackMove == true && Settings::fullyInitialized == true)
    {
        auto position  = gs->getMapLayer()->getPosition();
        gs->getMapLayer()->setPosition(Point(position.x, position.y + 50));
    }
    else if( this->_LeftMove == true && Settings::fullyInitialized == true)
    {
        auto position  = gs->getMapLayer()->getPosition();
        gs->getMapLayer()->setPosition(Point(position.x + 50, position.y));
    }
    else if( this->_RightMove == true && Settings::fullyInitialized == true)
    {
        auto position  = gs->getMapLayer()->getPosition();
        gs->getMapLayer()->setPosition(Point(position.x - 50, position.y));
    }
    
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    GameScene* gs = (GameScene*) _sc;
    
    if (keyCode == EventKeyboard::KeyCode::KEY_W && Settings::fullyInitialized == true)
    {
        //camera forward
        this->_ForwardMove = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S && Settings::fullyInitialized == true)
    {
        //camera back
        this->_BackMove = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A && Settings::fullyInitialized == true)
    {
        //camera left
        this->_LeftMove = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D && Settings::fullyInitialized == true)
    {
        //camera right
        this->_RightMove = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && Settings::fullyInitialized == true)
    {
        gs->GetGUI()->Menu();
    }
    
}

void Player::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W && Settings::fullyInitialized == true)
    {
        //camera forward
        this->_ForwardMove = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S && Settings::fullyInitialized == true)
    {
        //camera back
        this->_BackMove = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A && Settings::fullyInitialized == true)
    {
        //camera left
        this->_LeftMove = false;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D && Settings::fullyInitialized == true)
    {
        //camera right
        this->_RightMove = false;
    }

}

int Player::GetLifePoints()
{
    return this->lifePoints;
}

void Player::RemoveLifePoints(int i)
{
    this->lifePoints = this->lifePoints-i;
}

int Player::GetCurrency()
{
    return this->currency;
}

void Player::AddCoins(int coins)
{
    this->currency = this->currency + coins;
}

void Player::RemoveCoins(int coins)
{
    this->currency = this->currency - coins;
}

