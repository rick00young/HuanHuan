#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#define WIDTH 62

#define HEIGHT 62


class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);
    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBeauties, Beauties);

    CC_SYNTHESIZE(cocos2d::CCArray *, m_pBeautiesRoot, BeautiesRoot);

private:
    void initBackGround();
    void intBeauties();
    void setBeautiesPosition();
    void disPatchBeauties();
    //void reorderChild(cocos2d::CCSprite*  child, int zOrder);

};

#endif  // __HELLOWORLD_SCENE_H__