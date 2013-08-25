#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#define EXAMPLE_PANEL_TAG_ROOT 1
#include "cocos-ext.h"
using namespace cocos2d::extension;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void startNewGame(CCObject* pSender);
    void showAbout(CCObject* pSender);
    void closeAbout(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    UILayer* ul;
};

#endif // __HELLOWORLD_SCENE_H__
