//
//  Tower.cpp
//  Tower Defense
//
//  Created by Georgios Floros on 23/06/2014.
//
//

#include "GameScene.h"


Tower::Tower(cocos2d::Layer &refC, const std::string& fileNameFormat, TowerRules* tr) : Unit(fileNameFormat)
{
    this->mainscene = &refC;
    this->toweRules = tr;
    this->Init();
}

Tower::Tower(cocos2d::Layer &refC, const std::string& fileNameFormat, Rect rect, TowerRules* tr) : Unit(fileNameFormat, rect)
{
    this->mainscene = &refC;
    this->toweRules = tr;
    this->Init();
    //not working properly, missing rect functionality
}

void Tower::Init()
{
    this->SetElement(ElementalAffinity::None);
    this->highlight = NULL;
    this->highlight = CCSprite::create("highlight1.png");
    this->highlight->setPosition(Point(1, 35));
    this->highlight->setVisible(false);
    this->addChild(this->highlight);
    this->attackPoints = 0;
    this->attackRange = 0;
    this->inbetweenAttacksPeriod = 0;
    this->cost = 0;
    this->attackUpgradesDone = 1;
    this->speedUpgradesDone = 1;
    
    this->lblEleStrength = Label::createWithSystemFont("", "Arial", 14);
    this->lblEleStrength->setColor(ccc3(255,192,203));
    this->lblEleStrength->setPosition(0, 90);
    this->addChild(this->lblEleStrength);
    
    this->lblEleStrength->setString(" 1 ");
    
}

Tower::~Tower()
{
    this->highlight->cleanup();
}

void Tower::SetInbetweenAttacksPeriod(double num)
{
    this->inbetweenAttacksPeriod = num;
}

double Tower::GetInbetweenAttacksPeriod()
{
    return this->inbetweenAttacksPeriod;
}

void Tower::IncreaseSpeedUpgradesDone()
{
    this->speedUpgradesDone++;
}

void Tower::IncreaseAttackUpgradesDone()
{
    this->attackUpgradesDone++;
}

int Tower::SpeedsUpgradesDone()
{
    return this->speedUpgradesDone;
}

int Tower::AttackUpgradesDone()
{
    return this->attackUpgradesDone;
}

int Tower::GetSpeedUpgradeCost()
{
    return this->toweRules->GetSpeedUpgradeCost(*this);
}

int Tower::GetAttackUpgradeCost()
{
    return this->toweRules->GetAttackUpgradeCost(*this);
}

int Tower::GetSpeedUpgradesDone()
{
    return this->speedUpgradesDone;
}

int Tower::GetAttackUpgradesDone()
{
    return this->attackUpgradesDone;
}

void Tower::SetElement(ElementalAffinity ele)
{
    this->element = ele;
}

ElementalAffinity Tower::GetElement()
{
    return this->element;
}

std::vector<Point>& Tower::GetHitPosition()
{
    return this->hitPositions;
}

void Tower::AddHitPosition(cocos2d::Point p)
{
    this->hitPositions.push_back(p);
}

int Tower::GetStrength()
{
    return this->toweRules->GetStrength(*this);
}

void Tower::FireProjectile(Point loc)
{
    
    GameScene* sc = (GameScene*)(this->mainscene);

    Layer* _layer = sc->getMapLayer();
        
    Sprite *projectile = Sprite::create("ball1.png", CCRectMake(0, 0, 5, 5));
    projectile->setPosition(this->getPosition());
    
    int realX = loc.x;
    int realY = loc.y;
        
    int offRealX = realX - projectile->getPosition().x;
    int offRealY = realY - projectile->getPosition().y;
    float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
    float velocity = 880/1; // 880pixels/1sec
    float realMoveDuration = length/velocity;

    _layer->addChild(projectile);
        
    FiniteTimeAction* actionMove = MoveTo::create( (float)realMoveDuration, Point(realX, realY));
    FiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(Tower::ProjectileMoveFinished));
    projectile->runAction( Sequence::create(actionMove, actionMoveDone, NULL) );
    
}

void Tower::ToggleHighlight(bool activate)
{
    if(this != nullptr)
    {
        if(this->highlight)
        {
            this->highlight->setVisible(activate);
        }
    }
}

void Tower::ProjectileMoveFinished(Node* sender)
{
    GameScene* sc = (GameScene*)(this->mainscene);
    Sprite *sprite = (Sprite*)sender;
    sc->getMapLayer()->removeChild(sprite, true);
}

void Tower::Attack(Creep* refUnit)
{
    //Affinity related damaging functionality
    double damage = this->attackPoints;
    
    this->FireProjectile(refUnit->getPosition());
    
    if( this->element == ElementalAffinity::Fire )
    {
        refUnit->damageInflict( this->toweRules->GetFireDamage(refUnit->element, damage) );
    }
    else if( this->element == ElementalAffinity::Earth )
    {
        refUnit->damageInflict( this->toweRules->GetEarthDamage(refUnit->element, damage) );
    }
    else if( this->element == ElementalAffinity::Shock )
    {
        refUnit->damageInflict( this->toweRules->GetShockDamage(refUnit->element, damage) );
    }
    else if( this->element == ElementalAffinity::Water )
    {
        refUnit->damageInflict( this->toweRules->GetWaterDamage(refUnit->element, damage) );
    }
    else
    {
        refUnit->damageInflict( damage );
    }
    
    /*
    if(refUnit->GetHealthPoints() >0) {
        this->FireProjectile(refUnit->getPosition());
    }
     */
    
}

void Tower::NotifyCreepInRange(Creep* unit)
{
    /*
    if(this->firstAttack == false)
    {
        this->Attack(unit);
        this->prev = time(NULL) * 100;
        this->firstAttack = true;
    }
    else
    {
        time_t cur = time(NULL);
        double dif = difftime(cur, this->prev);
        std::cout << "\n prev : " << this->prev << " cur : " << cur << " inbetween : " << this->inbetweenAttacksPeriod << " dif : " << dif << "\n";
        if( dif > this->inbetweenAttacksPeriod )
        {
            this->Attack(unit);
            this->prev = time(NULL);
        }
    }
     */
    
    if(this->firstAttack == false)
    {
        this->Attack(unit);
        this->prevAttack = std::chrono::system_clock::now();
        this->firstAttack = true;
    }
    else
    {
        std::chrono::system_clock::time_point cur = std::chrono::system_clock::now();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(cur - this->prevAttack);        
        if( ms.count() > this->inbetweenAttacksPeriod )
        {
            this->Attack(unit);
            this->prevAttack = std::chrono::system_clock::now();
        }
    }
    
}

bool Tower::UpgradeAttackPower(Ref* p)
{
    bool success = this->toweRules->UpgradeAttackPower(p, *this);
    std::stringstream ss;
    if(this->element == ElementalAffinity::Fire)
    {
        ss << "Fire - " << this->toweRules->GetStrength(*this);
    }
    else if(this->element == ElementalAffinity::Water)
    {
        ss << "Water - " << this->toweRules->GetStrength(*this);
    }
    else if(this->element == ElementalAffinity::Earth)
    {
        ss << "Earth - " << this->toweRules->GetStrength(*this);
    }
    else if(this->element == ElementalAffinity::Shock)
    {
        ss << "Shock - " << this->toweRules->GetStrength(*this);
    }
    else
    {
        ss << "" << this->toweRules->GetStrength(*this);
    }
    
    if(success == true)
    {
        this->lblEleStrength->setString(ss.str());
    }
    
    return success;
}

bool Tower::UpgradeAttackSpeed(Ref* p)
{
    bool success = this->toweRules->UpgradeAttackSpeed(p, *this);
    std::stringstream ss;
    if(this->element == ElementalAffinity::Fire)
    {
        ss << "Fire - " << this->toweRules->GetStrength(*this);
    }
    else if(this->element == ElementalAffinity::Water)
    {
        ss << "Water - " << this->toweRules->GetStrength(*this);
    }
    else if(this->element == ElementalAffinity::Earth)
    {
        ss << "Earth - " << this->toweRules->GetStrength(*this);
    }
    else if(this->element == ElementalAffinity::Shock)
    {
        ss << "Shock - " << this->toweRules->GetStrength(*this);
    }
    else
    {
        ss << "" << this->toweRules->GetStrength(*this);
    }
    
    if(success == true)
    {
        this->lblEleStrength->setString(ss.str());
    }
    
    return success;
}

bool Tower::UpgradeToFire(Ref* p)
{
    bool success = this->toweRules->UpgradeToFire(p,*this);
    if(success == true)
    {
        std::stringstream ss;
        ss << "Fire - " << this->toweRules->GetStrength(*this);
        this->lblEleStrength->setString(ss.str());
    }
    return success;
}

bool Tower::UpgradeToWater(Ref* p)
{
    bool success = this->toweRules->UpgradeToWater(p,*this);
    if(success == true)
    {
        std::stringstream ss;
        ss << "Water - " << this->toweRules->GetStrength(*this);
        this->lblEleStrength->setString(ss.str());
    }
    return success;
}

bool Tower::UpgradeToShock(Ref* p)
{
    bool success = this->toweRules->UpgradeToShock(p,*this);
    if(success == true)
    {
        std::stringstream ss;
        ss << "Shock - " << this->toweRules->GetStrength(*this);
        this->lblEleStrength->setString(ss.str());
    }
    return success;
}

bool Tower::UpgradeToEarth(Ref* p)
{
    bool success = this->toweRules->UpgradeToEarth(p, *this);
    if(success == true)
    {
        std::stringstream ss;
        ss << "Earth - " << this->toweRules->GetStrength(*this);
        this->lblEleStrength->setString(ss.str());
    }
    return success;
}

void Tower::SetHitPositions(MapInfo* mi)
{
    int index = mi->ConvertPointToId(this->getPosition());
    this->AddHitPosition(mi->ConvertIdToPoint( (index + (mi->GetTilesPerLine() * 2) + 1 ) ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index + (mi->GetTilesPerLine() * 2) ) ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index + (mi->GetTilesPerLine() * 2) - 1 ) ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index + (mi->GetTilesPerLine())) + 1 ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index + (mi->GetTilesPerLine())) ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index + (mi->GetTilesPerLine())) - 1 ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index + 1 ) ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index ) ));
    this->AddHitPosition(mi->ConvertIdToPoint( (index - 1 ) ));
}

void Tower::SetStartingStats(double attackRange, int attackPoints, double inbetweenAttacksPeriod, int cost)
{
    this->attackRange = attackRange;
    this->attackPoints = attackPoints;
    this->inbetweenAttacksPeriod = inbetweenAttacksPeriod;
    this->cost = cost;
}

