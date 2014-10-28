#include "GameScene.h"

#include "MainMenu.h"

//pthread_mutex_t GameScene::mutex = PTHREAD_MUTEX_INITIALIZER;

USING_NS_CC;

void GameScene::InsertTower(Tower* t)
{
    //pthread_mutex_lock(&GameScene::mutex);
    this->towerslist.push_back(t);
    //pthread_mutex_unlock(&GameScene::mutex);
}

void GameScene::DeleteTower(Tower *t)
{
    //pthread_mutex_lock(&GameScene::mutex);
    this->towerslist.remove(t);
    //pthread_mutex_unlock(&GameScene::mutex);
}

void GameScene::InsertCreep(Creep* e)
{
    //pthread_mutex_lock(&GameScene::mutex);
    this->creepslist.push_back(e);
    //pthread_mutex_unlock(&GameScene::mutex);
}

void GameScene::DeleteCreep(Creep *e)
{
    //pthread_mutex_lock(&GameScene::mutex);
    this->creepslist.remove(e);
    //pthread_mutex_unlock(&GameScene::mutex);
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

void GameScene::BackToMainMenu()
{
    //debug print stats
    this->currSessionStats.PrintSession();
    
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,scene));
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    this->gameEnded = false;
    this->browserOpened = false;
    this->gamePaused = false;
    this->simulationMode = false;
    
    this->imEnabled = Settings::imEnabled;
    this->mapType = Settings::mapType;
    this->waveRules = Settings::waveRules;
    
    this->creepDeploymentDelay = 0.7f;
    this->nextWaveStartingDelay = 10.0f;
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //the map layer
    this->_mapLayer = Layer::create();
    this->addChild(_mapLayer);
    
    //the gui initialization and layer
    this->gui = new GUI(*this);
    
    std::string tmxFileName;
    
    if(Settings::mapType == MapType::Open)
    {
        tmxFileName = "map6.tmx";
    }
    else if(Settings::mapType == MapType::TraditionalWithRoads)
    {
        tmxFileName = "map8.tmx";
    }
    
    //the loaded map
    this->_map = TMXTiledMap::create(tmxFileName);
    this->_mapLayer->addChild(_map);
    
    //the loaded map info
    this->_mapInfo = MapInfo::create(tmxFileName); //pMapInfo;
    
    //set the G Cost scale
    if(Settings::mapType == MapType::Open)
    {
        this->_mapInfo->setGScale(this->_mapInfo->GetTilesPerColumn() * this->_mapInfo->GetTilesPerLine() );
    }
    else
    {
        this->_mapInfo->setGScale( 50 );
    }
    
    //initialization of IM
    if(Settings::imEnabled == true)
    {
        _im = new InfluenceMap(_mapInfo, &this->towerslist);
        this->_mapInfo->setInfluenceMap((Ref*)_im);
    }
    
    //the values that an astar ignores
    this->_mapInfo->cantPassOverTypes.push_back(MapInfoType::Tower);
    this->_mapInfo->cantPassOverTypes.push_back(MapInfoType::Block);
    this->_mapInfo->cantPassOverTypes.push_back(MapInfoType::Planes);
    
    //pMapInfo->retain();
    this->_mapInfo->retain();
    
    //the frameCache keeps all the sprites list
    auto *frameCache = SpriteFrameCache::getInstance();
    
    frameCache->addSpriteFramesWithFile("1creep_simpnone1.plist");
    frameCache->addSpriteFramesWithFile("1creep_simpfire1.plist");
    frameCache->addSpriteFramesWithFile("1creep_simpshock1.plist");
    frameCache->addSpriteFramesWithFile("1creep_simpwater1.plist");
    frameCache->addSpriteFramesWithFile("1creep_simpearth1.plist");
    
    frameCache->addSpriteFramesWithFile("1creep_specnone1.plist");
    frameCache->addSpriteFramesWithFile("1creep_specshock1.plist");
    frameCache->addSpriteFramesWithFile("1creep_specfire1.plist");
    frameCache->addSpriteFramesWithFile("1creep_specwater1.plist");
    frameCache->addSpriteFramesWithFile("1creep_specearth1.plist");
    
    frameCache->addSpriteFramesWithFile("1towers1.plist");
    frameCache->addSpriteFramesWithFile("1towers1_fire.plist");
    frameCache->addSpriteFramesWithFile("1towers1_water.plist");
    frameCache->addSpriteFramesWithFile("1towers1_earth.plist");
    frameCache->addSpriteFramesWithFile("1towers1_shock.plist");
    
    //init the players
    this->playerHandler = new Player(*this, "player1", Settings::playerStartingHealthPoints);
    this->playerHandler->AddCoins(Settings::playerStartingCurrency);
    this->aiPlayerHandler = new AICreepsPlayer(*this, Settings::waveRules);
    
    //the game ends after x numbers
    this->gameState.NumberOfCreepsLeft = 0;
    this->gameState.CurrentRound = 0;
    this->gameState.NumberOfRounds = Settings::numberOfRounds;
    
    //session stats
    this->currSessionStats.playerStartingCurrency = Settings::playerStartingCurrency;
    this->currSessionStats.playerHealthPointsTotal = Settings::playerStartingHealthPoints;
    
    this->gui->refreshGameStatusLabel(this->playerHandler->GetLifePoints(), this->gameState.NumberOfCreepsLeft, this->gameState.CurrentRound, this->playerHandler->GetCurrency());
    
    this->currSessionStats.profileId = Settings::waveRules->ProfileId;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //initates the starting message label
    this->announcements = Label::createWithSystemFont("", "Arial", 26);
    this->announcements->setPosition(Point ( visibleSize.width/2, visibleSize.height/2 ) );
    this->announcements->setVisible(false);
    this->addChild(this->announcements);
    
    //schedule the ontick
    this->schedule( schedule_selector(GameScene::update) );
    
    return true;
}

GUI* GameScene::GetGUI()
{
    return this->gui;
}

InfluenceMap* GameScene::getInfluenceMap()
{
    return this->_im;
}

void GameScene::update(float delta)
{
    if(this->firstRun == false)
    {
        //initiate the first wave
        this->gameState.NumberOfCreepsLeft = 1;
        this->aiPlayerHandler->ReadyForNextWave();
        this->firstRun = true;
        Settings::fullyInitialized = true;
    }

    if(this->gameEnded == true)
    {
        //game over message
        if(this->playerHandler->GetLifePoints() <= 0) {
            this->announcements->setString("The game has ended, you lost.");
            this->announcements->setVisible(true);
        }
        else if( this->playerHandler->GetLifePoints() > 0 && this->gameState.CurrentRound == this->gameState.NumberOfRounds ) {
            this->announcements->setString("The game has ended, you won!");
            this->announcements->setVisible(true);
        }
        else {
            this->announcements->setString("The game has ended");
            this->announcements->setVisible(true);
        }
        
        //opens the browser for the survey
        if(this->browserOpened == false)
        {
            this->currSessionStats.OpenBrowser();
            this->browserOpened = true;
        }
    }
    else
    {
        for ( std::list<Creep*>::iterator creep = creepslist.begin(); creep != creepslist.end(); ++creep )
        {
            Creep *cP = *creep;
            double maxhp = cP->GetStartingHealthPoints();
            double hpleft = cP->GetHealthPoints();
            
            /* DEATH */
            if(cP->GetHealthPoints() <=0)
            {
                //coins per kill
                this->playerHandler->AddCoins(cP->getCoins());

                if(!this->simulationMode)
                {
                    //sessionStats update
                    this->currSessionStats.AddCurrency(this->gameState.CurrentRound, cP->getCoins());
                }
                
                this->_mapLayer->removeChild(cP);
                this->DeleteCreep(cP);
            
                this->gameState.NumberOfCreepsLeft--;
                
                if(this->simulationMode) {
                }
                
                if(this->gameState.CurrentRound == this->gameState.NumberOfRounds && this->gameState.NumberOfCreepsLeft == 0)
                {
                    //gameover max round reached
                    this->gameEnded = true;
                }
                else if(this->gameState.NumberOfCreepsLeft <= 0)
                {
                    if(this->simulationMode)
                    {
                        this->aiPlayerHandler->BeforeNextWave(&this->gaScores);
                    }
                    else
                    {
                        this->aiPlayerHandler->BeforeNextWave(nullptr);
                    }
                    
                    //finish wave, start new, unless gameover
                    this->aiPlayerHandler->ReadyForNextWave();
                }
            
                this->gui->refreshGameStatusLabel(this->playerHandler->GetLifePoints(), this->gameState.NumberOfCreepsLeft, this->gameState.CurrentRound, this->playerHandler->GetCurrency());
            
                //to revalidate the iterator
                break;
            }
            /* CREEP REACHED END POINT */
            else if(cP->getPosition().getDistance(_mapInfo->GetRandomPointByType(MapInfoType::End)) < 22.8)
            {
                //remove life points from player
                this->playerHandler->RemoveLifePoints(1);
                
                //session stats, an add past through
                if(!this->simulationMode)
                {
                    RoundStats& p = this->currSessionStats.sessionStats.at(this->gameState.CurrentRound - 1);
                    p.successfulAttackers = p.successfulAttackers + 1;
                }
                
                if(this->playerHandler->GetLifePoints() <= 0)
                {
                    if(this->simulationMode)
                    {
                        this->aiPlayerHandler->BeforeNextWave(&this->gaScores);
                    }
                    else
                    {
                        //end game GAMEOVER!
                        this->gameEnded = true;
                    }
                }
                else if(this->gameState.CurrentRound == this->gameState.NumberOfRounds)
                {
                    //gameover max round reached
                    if(this->simulationMode)
                    {
                        //this->aiPlayerHandler->BeforeNextWave(&this->gaScores);
                    }
                    else
                    {
                        //end game GAMEOVER!
                        this->gameEnded = true;
                    }
                }
                else
                {
                    //decrement wave number
                    this->gameState.NumberOfCreepsLeft--;
                    
                    if(this->simulationMode) {
                        this->gaScores.creepsLeftFitness++;
                        this->gaScores.creepsLeftPercFitness = (hpleft / maxhp) * 100;
                        //this->gaScores.creepsLeftHP.push_back(hpleft);
                        //this->gaScores.creepsLeftHPMax.push_back(maxhp);
                    }
                    
                    //remove unit from map
                    _mapLayer->removeChild(cP);
                    this->DeleteCreep(cP);
                
                    if(this->gameState.NumberOfCreepsLeft <= 0)
                    {
                        if(this->simulationMode)
                        {
                            this->aiPlayerHandler->BeforeNextWave(&this->gaScores);
                        }
                        else
                        {
                            this->aiPlayerHandler->BeforeNextWave(nullptr);
                        }
                        //finish wave, start new, unless gameover
                        this->aiPlayerHandler->ReadyForNextWave();
                    }
                }
            
                this->gui->refreshGameStatusLabel(this->playerHandler->GetLifePoints(), this->gameState.NumberOfCreepsLeft, this->gameState.CurrentRound, this->playerHandler->GetCurrency());
            
                //to revalidate the iterator
                break;
        }
        else
        {
            //check for enemies in range of towers
            for ( std::list<Tower*>::iterator tower = towerslist.begin(); tower != towerslist.end(); ++tower )
            {
                Tower *refT = *tower;
                float range = refT->attackRange;
            
                //check if testsprite in range
                if(cP->GetHealthPoints() >= 0)
                {
                    
                    for( std::vector<Point>::iterator point = refT->GetHitPosition().begin(); point != refT->GetHitPosition().end(); ++point )
                    {
                        if(this->_mapInfo->GetDistanceInTiles(*point, cP->getPosition()) < range )
                        {
                            refT->NotifyCreepInRange(cP);
                            break;
                        }
                    }
                    
                }
            }
        
        }
        
      }
    }
    
}

Layer* GameScene::getMapLayer()
{
    return GameScene::_mapLayer;
}

MapInfo* GameScene::getMapInfo()
{
    return GameScene::_mapInfo;
}

TMXTiledMap* GameScene::getTiledMap()
{
    return GameScene::_map;
}

void GameScene::InitiateWave(WaveRulesInterface* wv)
{
    this->announcements->setString("Next Wave is starting soon...");
    this->announcements->setVisible(true);

    auto cb = CallFunc::create( std::bind( &GameScene::nextWave, this, wv));
    DelayTime* delayAction = DelayTime::create(this->nextWaveStartingDelay);
    this->runAction(CCSequence::create(delayAction, cb, NULL));
}

void GameScene::nextWave(Ref* ref)
{
    this->announcements->setVisible(false);
    
    WaveRules * wv = (WaveRules*)ref;
    std::list<Creep*> list = wv->GetWaveCreeps();
    
    this->gameState.CurrentRound++; //increase the current round
    
    //updates the sessionstats
    if(!this->simulationMode)
    {
        this->currSessionStats.WaveStats(this->gameState.CurrentRound, list.front(), list.back(), list.size(), this->playerHandler->GetLifePoints(), this->playerHandler->GetCurrency());
        this->currSessionStats.AddAllTowers(this->gameState.CurrentRound, this->towerslist);
    }
    else
    {
        //this->gaScores.NumberOfCreepsLeft = 0;
        this->gaScores.creepsLeftFitness = 0;
        this->gaScores.creepsLeftPercFitness = 0;
    }
        
    //reset wave number
    this->gameState.NumberOfCreepsLeft = list.size();
    
    int i = 0;
    for ( std::list<Creep*>::iterator creep = list.begin(); creep != list.end(); ++creep )
    {
        i++;
        Creep *cP = *creep;
        auto cb = CallFunc::create( std::bind( &GameScene::SpawnCreep, this, cP));
        DelayTime* delayAction = DelayTime::create(i * this->creepDeploymentDelay); //spawn delay
        this->runAction(CCSequence::create(delayAction, cb, NULL));
    }
    
    this->gui->refreshGameStatusLabel(this->playerHandler->GetLifePoints(), this->gameState.NumberOfCreepsLeft, this->gameState.CurrentRound, this->playerHandler->GetCurrency());
    
    //after deployment
    this->aiPlayerHandler->AfterDeployment();
    
}


void GameScene::SpawnCreep(Ref *pSender)
{
    if(this->gameEnded != true)
    {
        Creep* creep = (Creep*)pSender;
        auto p = _mapInfo->GetRandomMapIdByType(MapInfoType::Start);
    
        creep->setPosition(_mapInfo->ConvertIdToPoint(p));
        auto originId = _mapInfo->ConvertPointToId(creep->getPosition());
        auto endId = _mapInfo->GetRandomMapIdByType(MapInfoType::End);
        auto* pMapPath = _mapInfo->GetMapPath(originId, endId);
        creep->moveTo(pMapPath, creep->GetMovementSpeed(), *this);
    
        _mapLayer->addChild(creep);
        this->InsertCreep(creep);
    }
}


AIStatus* GameScene::GetAiStatus()
{
    if(this->_aiStatus == nullptr)
    {
        this->_aiStatus = new AIStatus(*this);
    }
    return this->_aiStatus;
}

