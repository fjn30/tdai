//
//  Movement.cpp
//  
//
// created by chenquanjun on 14-3-14 (testAStar).
//
//

#include "GameScene.h"


Movement::Movement() : _pointArr(nullptr), _nIndex(0)
{
    
}

Movement::~Movement()
{
    CC_SAFE_RELEASE(_pointArr);
}

Movement* Movement::create(float duration, PointArray* pointArr)
{
    Movement *goTo = new Movement();
    goTo->initWithDuration(duration, pointArr);
    goTo->autorelease();
    return goTo;
}

bool Movement::initWithDuration(float duration, PointArray* pointArr)
{
    if (ActionInterval::initWithDuration(duration))
    {
        CCASSERT(pointArr != nullptr, "should not be null");
        setPointArr(pointArr);
        return true;
    }
    
    return false;
}

Movement* Movement::clone() const
{
	// no copy constructor
	auto a = new Movement();
	a->initWithDuration(_duration, _pointArr->clone());
	a->autorelease();
	return a;
}

Movement* Movement::reverse() const
{
    auto a = new Movement();
	a->initWithDuration(_duration, _pointArr->reverse());
	a->autorelease();
	return nullptr;
}

void Movement::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    if (_target)
    {
        if (_pointArr->count() > 0) {
            Point point = _pointArr->getControlPointAtIndex(0);
            _target->setPosition(point);
        }
        
    }
    
}

void Movement::update(float time)
{
    if (_target)
    {
        int count = _pointArr->count();
        float fIndex = count * time;
        int index = (int)fIndex;

        if (index < count) {
            Point pointBegin = _pointArr->getControlPointAtIndex(index);
            Point pointEnd = _pointArr->getControlPointAtIndex(index + 1);
            float offset = fIndex - index;

            float x = pointBegin.x + (pointEnd.x - pointBegin.x) * offset;
            float y = pointBegin.y + (pointEnd.y - pointBegin.y) * offset;
            _target->setPosition(Point(x, y));
            _nIndex = index;
            
            this->playActionByPos(pointBegin, pointEnd, _target);
        } else {
            Point point = _pointArr->getControlPointAtIndex(index - 1);
            _target->setPosition(point);

            Unit *isTestSprite = dynamic_cast<Unit*>(_target);
            
            if (isTestSprite != nullptr) {
                isTestSprite->playAction(PlayerActionType::Invalid);
            }
        }
    }    
}

void Movement::playActionByPos(Point start, Point end, Node *target){
    float offsetX = end.x - start.x;
    float offsetY = end.y - start.y;
    PlayerActionType actionType = PlayerActionType::Invalid;
    
    bool isAction = true;
    
    if (offsetY > 5) {
        actionType = PlayerActionType::Up;
    }else if (offsetY < -5){
        actionType = PlayerActionType::Down;
    }else if (offsetX > 5){
        actionType = PlayerActionType::Right;
    }else if (offsetX < -5){
        actionType = PlayerActionType::Left;
    }else{
        actionType = PlayerActionType::Invalid;
        isAction =false;
    }
    
    Unit *isTestSprite = dynamic_cast<Unit*>(_target);
    
    if (isTestSprite != nullptr) {
        isTestSprite->playAction(actionType);
    }

}