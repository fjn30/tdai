//
//  Menu.cpp
//  TowerDefense_new
//


#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void MainMenu::mapTypeMenuBackCallback(cocos2d::Ref* pSender)
{
    this->mapTypeMenu->setVisible(false);
    this->mapTypeMenu_bg->setVisible(false);
    
    if(this->profiles_bg1)
    {
        this->profiles_bg1->setVisible(false);
        this->profilesMenu->setVisible(false);
    }
    
    this->pMenu->setVisible(true);
    this->aiSettings_bg->setVisible(true);
}

void MainMenu::mapTypeMenuInit()
{
    this->aiSettings_bg->setVisible(false);
    this->pMenu->setVisible(false);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->mapTypeMenu_bg = Sprite::create("promptMapType_bg1.png");
    this->mapTypeMenu_bg->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(this->mapTypeMenu_bg);
    
    this->mapTypeMenu = CCMenu::create();
    this->addChild(this->mapTypeMenu);
    
    this->buttonOpenMapType = MenuItemImage::create("mapTypeOpen1.png","mapTypeOpen2.png",CC_CALLBACK_1(MainMenu::openMapTypeCallback, this));
    this->buttonOpenMapType->setPosition(this->mapTypeMenu->getPosition().x / 6 - 200, this->mapTypeMenu->getPosition().y / 6 - 70);
    this->mapTypeMenu->addChild(this->buttonOpenMapType);
    
    this->buttonTradMapType = MenuItemImage::create("mapTypeTrad1.png","mapTypeTrad2.png",CC_CALLBACK_1(MainMenu::tradMapTypeCallback, this));
    this->buttonTradMapType->setPosition(this->mapTypeMenu->getPosition().x / 6 + 30, this->mapTypeMenu->getPosition().y / 6 - 70);
    this->mapTypeMenu->addChild(this->buttonTradMapType);
    
    this->mapTypeMenuBack = MenuItemImage::create("mainMenuBack1.png","mainMenuBack2.png",CC_CALLBACK_1(MainMenu::mapTypeMenuBackCallback, this));
    this->mapTypeMenuBack->setPosition(this->mapTypeMenu->getPosition().x -100, (-1 * this->mapTypeMenu->getPosition().y) + 80 );
    this->mapTypeMenu->addChild(this->mapTypeMenuBack);
}

void MainMenu::openMapTypeCallback(cocos2d::Ref *pSender)
{
    Settings::mapType = MapType::Open;
    profilesMenuInit();
}

void MainMenu::tradMapTypeCallback(cocos2d::Ref *pSender)
{
    Settings::mapType = MapType::TraditionalWithRoads;
    profilesMenuInit();
}

void MainMenu::AITypesMenuInit()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->pMenu = CCMenu::create();
    this->pMenu->setPosition(visibleSize.width/2, 20);
    
    this->aiSettings_bg = Sprite::create("aiSettingsBG1.png");
    this->aiSettings_bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(this->aiSettings_bg);
    
    this->buttonNewGame = MenuItemImage::create("mainMenuAISimple1.png","mainMenuAISimple2.png",CC_CALLBACK_1(MainMenu::newGameCallback, this));
    this->buttonNewGame->setPosition(100, visibleSize.height/2);
    this->pMenu->addChild(this->buttonNewGame);
    
    this->buttonNewGame2 = MenuItemImage::create("mainMenuAIIM1.png","mainMenuAIIM2.png",CC_CALLBACK_1(MainMenu::newGameCallbackIMAI, this));
    this->buttonNewGame2->setPosition(-100, visibleSize.height/2);
    this->pMenu->addChild(this->buttonNewGame2);
    
    this->addChild(this->pMenu,3);
}

void MainMenu::profilesMenuInit()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->profilesMenu = CCMenu::create();
    this->profilesMenu->setPosition(visibleSize.width/2, -10);
    
    this->profiles_bg1 = Sprite::create("menuProfiles_bg1.png");
    this->profiles_bg1->setPosition(visibleSize.width/2, (visibleSize.height/2) - 50);
    this->addChild(this->profiles_bg1);
    
    this->buttonProfile1 = MenuItemImage::create("buttonProfile1_1.png","buttonProfile1_2.png",CC_CALLBACK_1(MainMenu::profile1Callback, this));
    this->buttonProfile1->setPosition(-100, (visibleSize.height/2) );
    this->profilesMenu->addChild(this->buttonProfile1);

    this->buttonProfile2 = MenuItemImage::create("buttonProfile2_1.png","buttonProfile2_2.png",CC_CALLBACK_1(MainMenu::profile2Callback, this));
    this->buttonProfile2->setPosition(100, (visibleSize.height/2) );
    this->profilesMenu->addChild(this->buttonProfile2);
    
    this->buttonProfile3 = MenuItemImage::create("buttonProfile3_1.png","buttonProfile3_2.png",CC_CALLBACK_1(MainMenu::profile3Callback, this));
    this->buttonProfile3->setPosition(-100, (visibleSize.height/2) - 120);
    this->profilesMenu->addChild(this->buttonProfile3);
    
    this->addChild(this->profilesMenu);
}

void MainMenu::profile1Callback(cocos2d::Ref *sender)
{
    ProfileOne* prof1 = new ProfileOne();
    Settings::waveRules = prof1;
    
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,scene));
}

void MainMenu::profile2Callback(cocos2d::Ref *sender)
{
    ProfileTwo* prof2 = new ProfileTwo();
    Settings::waveRules = prof2;
    
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,scene));
}

void MainMenu::profile3Callback(cocos2d::Ref *sender)
{
    GeneticAlgorithmProfile1* prof3 = new GeneticAlgorithmProfile1();
    Settings::waveRules = prof3;
    
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,scene));
}


bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->AITypesMenuInit();
    return true;
}

void MainMenu::newGameCallback(Ref* pSender)
{
    Settings::imEnabled = false;
    this->mapTypeMenuInit();
}

void MainMenu::newGameCallbackIMAI(Ref* pSender)
{
    Settings::imEnabled = true;
    this->mapTypeMenuInit();
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
    #endif
    Director::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    #endif
}

