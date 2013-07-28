//
//  CardSprite.cpp
//  Cocos2dev.com
//
//  Created by LiuYanghui on 13-6-17.
//
//

#include "CardSprite.h"

#define kInAngleZ        270 //���濨�Ƶ���ʼZ��Ƕ�
#define kInDeltaZ        90  //���濨����ת��Z��ǶȲ�

#define kOutAngleZ       0   //���濨�Ƶ���ʼZ��Ƕ�
#define kOutDeltaZ       90  //���濨����ת��Z��ǶȲ�

enum {
    tag_inCard = 1,
    tag_outCard
};

CardSprite::CardSprite()
{
    
}

CardSprite::~CardSprite()
{
    m_openAnimIn->release();
    m_openAnimOut->release();
}

CardSprite* CardSprite::create(int level)
{
    CardSprite *pSprite = new CardSprite();
    if (pSprite && pSprite->init(level))
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool CardSprite::init(int level)
{
    if (!CCSprite::init())
    {
        return false;
    }
    initData(level);
    return true;
}
/*
void CardSprite::onEnter(){
    CCLog("on enter");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
*/
void CardSprite::initData(int level)
{
    //CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, kCCMenuHandlerPriority);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);

    m_isOpened = false;
    isReady = true;
    _level = level;
    _isDone = false;
    CCString* frameName = CCString::createWithFormat("%02d.png", _level);
    
    CCSprite* inCard = CCSprite::createWithSpriteFrameName(frameName->getCString());
    inCard->setPosition(CCPointZero);
    inCard->setVisible(false);
    inCard->setTag(tag_inCard);
    addChild(inCard);
    
    CCSprite* outCard = CCSprite::createWithSpriteFrameName("back.png");
    outCard->setPosition(CCPointZero);
    outCard->setTag(tag_outCard);
    addChild(outCard);
    
    CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(CardSprite::changeStatus));

    m_openAnimIn = (CCActionInterval*)CCSequence::create(CCDelayTime::create(0.5f),
                                                         //CCDelayTime::create(0.3f),
                                                         CCShow::create(),
                                                         CCOrbitCamera::create(0.5f, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                         NULL);
    m_openAnimIn->retain();
    
    m_openAnimOut = (CCActionInterval *)CCSequence::create(CCOrbitCamera::create(0.5f, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
                                                           CCHide::create(),
                                                           CCDelayTime::create(0.5f),
                                                           //CCDelayTime::create(2.5f),
                                                           releaseFunc,
                                                           NULL);
    m_openAnimOut->retain();
}


void CardSprite::openCard()
{
    isReady = false;
    CCSprite* inCard = (CCSprite*)getChildByTag(tag_inCard);
    CCSprite* outCard = (CCSprite*)getChildByTag(tag_outCard);
    inCard->runAction(m_openAnimIn);
    outCard->runAction(m_openAnimOut);
    //CCLog("open card");
}

void CardSprite::closeCard()
{
    
    if(isReady){
        CCSprite* inCard = (CCSprite*)getChildByTag(tag_inCard);
        CCSprite* outCard = (CCSprite*)getChildByTag(tag_outCard);
        inCard->runAction(m_openAnimOut);
        outCard->runAction(m_openAnimIn);

        isReady = false;
        m_isOpened = false;
    }

    
}


void CardSprite::touchDelegateRetain()
{
    this->retain();
}

bool CardSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

    CCSprite* inCard = (CCSprite*)getChildByTag(tag_inCard);
    CCSprite* outCard = (CCSprite*)getChildByTag(tag_outCard);

    CCPoint touchPoint = pTouch->getLocationInView();
    CCPoint pt = CCDirector::sharedDirector()->convertToGL(touchPoint);



    CCPoint pos = this->getPosition();
    float w = inCard->boundingBox().size.width;
    float h = inCard->boundingBox().size.height;
    CCRect rect = CCRectMake(pos.x - w/2, pos.y - h/2 , w, h);

    //CCLog("this box is %f---%f", rect.size.width, rect.size.height);
    if(rect.containsPoint(pt)){
        if(isReady){
            m_isOpened = true;
            CCLog("containsPoint");
            this->openCard();
        }
        return true;
    }else{
        //return true;
    }

    return false;
    
}

int CardSprite::getLevel()
{
    return _level;
}

bool CardSprite::getOpened()
{
    return m_isOpened;
}

bool CardSprite::getDone()
{
    return _isDone;
}

void CardSprite::setDone(){
    this->setVisible(false);
    _isDone = true;
}

void CardSprite::changeStatus()
{
    CCLog("change status");
    //return;
    /*
    if(m_isOpened){
        m_isOpened = false;
    }else{
        m_isOpened = true;
    }
    */
    isReady = true;
}