#ifndef __CARdSPRITE_H__
#define __CARdSPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene;
class CardSprite : public CCSprite,public CCTargetedTouchDelegate
{
public:
    CardSprite();
    ~CardSprite();
    //virtual void onEnter();
    //virtual void onExit();
    static CardSprite* create(GameScene *gameScene, int level);
    virtual bool init(GameScene *gameScene, int level);

    CC_SYNTHESIZE(GameScene *, m_pgameScene, gameScene);
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
    
    
    void initData(GameScene *gameScene, int level);
    
public:
    void openCard();
    void closeCard();
    void hideCard();
    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
    //virtual void touchDelegateRelease();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //virtual void ccTouchMove(CCTouch* touch, CCEvent* event);
    //virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    void changeStatus();
};
#endif //__CARdSPRITE_H__
