//
//  Creep.cpp
//
//  Created by Georgios Floros on 19/06/2014.
//
//

//#include "Creep.h"
#include "GameScene.h"

Creep::Creep(const std::string& fileNameFormat, double _healthPoints, double _movementSpeed) : Unit(fileNameFormat)
{
    
    this->lastSpeedCoefficient = 1.0f;
    this->element = ElementalAffinity::None;
    
    this->fileNameFormat = fileNameFormat;
    this->schedule( schedule_selector(Creep::update) );

    this->startingHP = _healthPoints;
    this->healthPoints = _healthPoints;
    this->movementSpeed = _movementSpeed;
    
    this->healthbar = ProgressTimer::create(CCSprite::create("healthbar1.png"));
    this->healthbar->setType(kCCProgressTimerTypeBar);
    this->healthbar->setMidpoint(ccp(0, 0));
    this->healthbar->setPosition(ccp(0, 60));
    this->healthbar->setBarChangeRate( ccp(1, 0) );
    this->healthbar->setPercentage(100);
    this->addChild(healthbar);
    
    this->lblDamageText = Label::createWithSystemFont("", "Arial", 18);
    this->lblDamageText->setColor(ccc3(255,192,203));
    this->lblDamageText->setPosition(0, 100);
    this->lblDamageText->setVisible(false);
    this->addChild(this->lblDamageText);
    
    this->lblHP = Label::createWithSystemFont("", "Arial", 18);
    this->lblHP->setColor(ccc3(255,192,203));
    this->lblHP->setPosition(0, 80);
    this->lblHP->setVisible(true);
    this->addChild(this->lblHP);
    
    std::stringstream s;
    s << this->healthPoints << "/" << this->startingHP;
    this->lblHP->setString(s.str());
    
    this->prev = time(NULL) * 100;
}

Creep::Creep(const std::string& fileNameFormat, Rect rect, double _healthPoints, double _movementSpeed) : Unit(fileNameFormat, rect)
{
    
    this->lastSpeedCoefficient = 1.0f;
    this->element = ElementalAffinity::None;
    
    this->fileNameFormat = fileNameFormat;
    this->schedule( schedule_selector(Creep::update) );
    
    this->startingHP = _healthPoints;
    this->healthPoints = _healthPoints;
    this->movementSpeed = _movementSpeed;
    
    this->healthbar = ProgressTimer::create(CCSprite::create("healthbar1.png"));
    this->healthbar->setType(kCCProgressTimerTypeBar);
    this->healthbar->setMidpoint(ccp(0, 0));
    this->healthbar->setPosition(ccp(0, 60));
    this->healthbar->setBarChangeRate( ccp(1, 0) );
    this->healthbar->setPercentage(100);
    this->addChild(healthbar);
    
    this->lblDamageText = Label::createWithSystemFont("", "Arial", 18);
    this->lblDamageText->setColor(ccc3(255,192,203));
    this->lblDamageText->setPosition(0, 100);
    this->lblDamageText->setVisible(false);
    this->addChild(this->lblDamageText);
    
    this->lblHP = Label::createWithSystemFont("", "Arial", 18);
    this->lblHP->setColor(ccc3(255,192,203));
    this->lblHP->setPosition(0, 80);
    this->lblHP->setVisible(true);
    this->addChild(this->lblHP);
    
    std::stringstream s;
    s << this->healthPoints << "/" << this->startingHP;
    this->lblHP->setString(s.str());
    
    this->prev = time(NULL) * 100;
}

Creep::~Creep()
{
    this->healthbar->release();
}


double Creep::GetHealthPoints()
{
    return this->healthPoints;
}

double Creep::GetStartingHealthPoints()
{
    return this->startingHP;
}

double Creep::GetMovementSpeed()
{
    return this->movementSpeed;
}

void Creep::update(float delta)
{
    //update healthbar
    double perc =  ( this->healthPoints / this->startingHP ) * 100;
    this->healthbar->setPercentage(perc);
    
    
    //remove damage text if time has past
    time_t cur = time(NULL) * 100;
    double dif = difftime(cur, this->prev);
    if ( dif > 8 )
    {
        this->lblDamageText->setVisible(false);
    }
    
}

void Creep::moveTo(MapPath* path, double speedCoefficient, cocos2d::Layer& sc)
{
    this->_sc = &sc;
    
    if (path != nullptr)
    {
        this->lastStart = path->getStartId();
        this->lastEnd = path->getEndId();
        this->lastSpeedCoefficient = speedCoefficient;
        
        auto *pointArr1 = path->getPointArr();
        auto duration = speedCoefficient * pointArr1->count();
        Movement* walkTo = Movement::create(duration, pointArr1);
        walkTo->setTag((int)PlayerActionType::Invalid);
        this->stopActionByTag(99);
        this->runAction(walkTo);
    }
}

//stops all animations/actions of the creep
//and recalculates the path
void Creep::invalidatePath()
{

    this->stopAllActions();
    
    GameScene* gs = (GameScene*) _sc;
    MapPath * path = gs->getMapInfo()->GetMapPath( gs->getMapInfo()->ConvertPointToId(this->getPosition()) , lastEnd);
    
    auto *pointArr1 = path->getPointArr();
    auto duration = lastSpeedCoefficient * pointArr1->count();
    Movement* walkTo = Movement::create(duration, pointArr1);
    walkTo->setTag((int)PlayerActionType::Invalid);
    this->stopActionByTag(99);
    this->runAction(walkTo);

}

//this method is normally called outside this
//class to inflict damage "ON" this particular entity
void Creep::damageInflict(int dmg)
{
    if(dmg > this->healthPoints)
    {
        this->healthPoints = 0;
    }
    else
    {
        this->healthPoints = this->healthPoints - dmg;
    }
    
    this->lblDamageText->setVisible(true);
    std::stringstream s1;
    s1 << "" << dmg;
    this->lblDamageText->setString(s1.str());
    this->prev = time(NULL) * 100;
     
    
    std::stringstream s2;
    s2 << this->healthPoints << "/" << this->startingHP;
    this->lblHP->setString(s2.str());
    
}

int Creep::getCoins()
{
    return this->coins;
}

void Creep::setCoins(int coins)
{
    this->coins = coins;
}

void Creep::SetHealthPoints(double s)
{
    this->healthPoints = s;
}

void Creep::SetMovementSpeed(double s)
{
    this->movementSpeed = s;
}

void Creep::SetLastSpeedCoefficient(double s)
{
    this->lastSpeedCoefficient = s;
}
