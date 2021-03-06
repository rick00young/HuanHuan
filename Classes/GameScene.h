#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#define EXAMPLE_PANEL_TAG_ROOT 1
#include "cocos-ext.h"
using namespace cocos2d::extension;

#define WIDTH 62

#define HEIGHT 62



class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    GameScene();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);
    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBeauties, Beauties);

    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBeautiesRoot, BeautiesRoot);

    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBeautiesOpen, BeautiesOpen);
    //virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    static int GameLevel;
    
    bool isOkForClip();
    void gameLogic(CardSprite* card);
    void bindCallbacks();
    void backToMenu(CCObject* pSender);
    //virtual void onEnter();  

private:
    void initBackGround();
    void intBeauties();
    void setBeautiesPosition();
    void disPatchBeauties();
    bool okforClip;
    CardSprite* currentBeauty;
    CardSprite* firstBeauty;
    CardSprite* secondBeauty;
    UILayer* ul;
    virtual void update(float time);
    //void reorderChild(cocos2d::CCSprite*  child, int zOrder);

};

#endif  // __GAMESCENE_SCENE_H__