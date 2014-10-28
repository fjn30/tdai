//
//  Menu.h
//  TowerDefense_new
//

/**
 *  @Author Georgios Floros
 *
 *  @brief  The MainMenu, extends Scene
 */

#ifndef __TowerDefense_new__MainMenu__
#define __TowerDefense_new__MainMenu__

#include "GameScene.h"

USING_NS_CC;
class MainMenu : public cocos2d::Layer
{
    public:

    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainMenu);
    
    virtual bool init();
    
    cocos2d::MenuItem* buttonNewGame;
    cocos2d::MenuItem* buttonNewGame2;
    Menu* pMenu;
    Sprite* aiSettings_bg;
    
    Sprite* mapTypeMenu_bg;
    void mapTypeMenuInit();
    Menu* mapTypeMenu;
    MenuItem* buttonOpenMapType;
    MenuItem* buttonTradMapType;
    void openMapTypeCallback(cocos2d::Ref* pSender);
    void tradMapTypeCallback(cocos2d::Ref* pSender);
    MenuItem* mapTypeMenuBack;
    void mapTypeMenuBackCallback(cocos2d::Ref* pSender);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void statsCallback(cocos2d::Ref* pSender);
    
    void profilesMenuInit();
    Sprite* profiles_bg1;
    Menu* profilesMenu;
    MenuItem* buttonProfile1;
    MenuItem* buttonProfile2;
    MenuItem* buttonProfile3;
    void profile1Callback(Ref* sender);
    void profile2Callback(Ref* sender);
    void profile3Callback(Ref* sender);

    void AITypesMenuInit();

    void newGameCallback(cocos2d::Ref* pSender);
    void newGameCallbackIMAI(Ref* pSender);
    
    void continueCallback(cocos2d::Ref* pSender);
    
    private:    
    
    
};

#endif 
