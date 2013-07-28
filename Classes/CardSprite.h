//  CardSprite.h
//  Cocos2dev.com
//
//  Created by LiuYanghui on 13-6-17.
//
//

#ifndef __Test__CardSprite__
#define __Test__CardSprite__

#include "cocos2d.h"
USING_NS_CC;

class CardSprite : public CCSprite,public CCTargetedTouchDelegate
{
public:
    CardSprite();
    ~CardSprite();
    //virtual void onEnter();
    //virtual void onExit();
    static CardSprite* create(int level);
    virtual bool init(int level);
    int getLevel();
    bool getOpened();
    void setDone();
    bool getDone();
    
private:
    bool m_isOpened;
    bool _isDone;
    bool isReady;
    int _level;
    CCActionInterval* m_openAnimIn;
    CCActionInterval* m_openAnimOut;
    
    
    void initData(int level);
    
public:
    void openCard();
    void closeCard();
    virtual void touchDelegateRetain();
    //virtual void touchDelegateRelease();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //virtual void ccTouchMove(CCTouch* touch, CCEvent* event);
    //virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    void changeStatus();
};

#endif /* defined(__Test__CardSprite__) */
