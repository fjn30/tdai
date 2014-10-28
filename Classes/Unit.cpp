//
//  Unit.cpp
//  Tower Defense
//
//  Created by Georgios Floros on 16/06/2014.
//
//

#include "GameScene.h"

Unit::Unit()
{
    
}

Unit::Unit(const std::string& fileNameFormat)
{
    this->init(fileNameFormat);
    //this->autorelease();
}

Unit::Unit(const std::string& fileNameFormat, Rect rect)
{
    this->initWithRect(fileNameFormat, rect);
    //this->autorelease();
}

Unit::~Unit()
{
    this->release();
}

bool Unit::initWithRect(const std::string & fileNameFormat, Rect r) {
    if (Sprite::init())
    {
        cocos2d::SpriteFrameCache *frameCache = cocos2d::SpriteFrameCache::getInstance();
        for (int j = 0; j < 4; j++) {
            cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
            for(int i = 0; i < 4; i++)
            {
                cocos2d::__String * str = cocos2d::__String::createWithFormat(fileNameFormat.c_str(), j, i);
                cocos2d::SpriteFrame *frame = frameCache->getSpriteFrameByName(str->getCString());
                frame->setRect(r);
                animFrames.pushBack(frame);
            }
            cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);
            int actionTag = j + 1;
            _playerAnimMap.insert(actionTag, animation);
        }
        cocos2d::__String * fileStr = cocos2d::__String::createWithFormat(fileNameFormat.c_str(), 0, 0);
        Sprite *animSprite = Sprite::createWithSpriteFrameName(fileStr->getCString());
        animSprite->setAnchorPoint(Point(0.5, 0));
        this->addChild(animSprite);
        _animationSprite = animSprite;
        return true;
    }
    else
    {
        return false;
    }
}

bool Unit::init(const std::string & fileNameFormat) {
    if (Sprite::init())
    {
        cocos2d::SpriteFrameCache *frameCache = cocos2d::SpriteFrameCache::getInstance();
        for (int j = 0; j < 4; j++) {
            cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
            for(int i = 0; i < 4; i++)
            {
                cocos2d::__String * str = cocos2d::__String::createWithFormat(fileNameFormat.c_str(), j, i);
                cocos2d::SpriteFrame *frame = frameCache->getSpriteFrameByName(str->getCString());
                animFrames.pushBack(frame);
            }
            cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);
            int actionTag = j + 1;
            _playerAnimMap.insert(actionTag, animation);
        }
        cocos2d::__String * fileStr = cocos2d::__String::createWithFormat(fileNameFormat.c_str(), 0, 0);
        Sprite *animSprite = Sprite::createWithSpriteFrameName(fileStr->getCString());
        animSprite->setAnchorPoint(Point(0.5, 0));
        this->addChild(animSprite);
        _animationSprite = animSprite;
        return true;
    }
    else
    {
        return false;
    }
}

void Unit::playAction(PlayerActionType actionType) {
    if (actionType == _lastActionType) {
        return;
    }
    
    if (_lastActionType != PlayerActionType::Invalid) {
        _animationSprite->stopActionByTag((int)_lastActionType);
    }
    
    _lastActionType = actionType;
    cocos2d::Animation *animation = (cocos2d::Animation*)_playerAnimMap.at((int)actionType);
    
    if (animation != nullptr) {
        cocos2d::Animate *anim = cocos2d::Animate::create(animation);
        cocos2d::RepeatForever *repeat = cocos2d::RepeatForever::create(anim);
        
        repeat->setTag((int)actionType);
        _animationSprite->runAction(repeat);
    }
    
}




