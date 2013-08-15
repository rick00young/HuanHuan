#include "HelloWorldScene.h"
#include "TT.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


    UILayer* ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    UIButton* exit = UIButton::create();
    exit->setTextures("CloseNormal.png", "CloseSelected.png", "");
    exit->setPosition(ccp(430, 60));
    exit->setTouchEnable(true);
    //exit->addReleaseEvent(this, coco_releaseselector(HelloWorld::toCocosGUITestScene));

    ul->addWidget(exit);

    UIWidget* ui = CCUIHELPER->createWidgetFromJsonFile("start/Export/start_1/start_1.json");
    ui->setWidgetTag(EXAMPLE_PANEL_TAG_ROOT);
    ul->addWidget(ui);

    //bind event
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    UIButton* button_new_game = dynamic_cast<UIButton*>(example_root->getChildByName("newgame")); 
    CCLog("button_pannel is %d", button_new_game);
    button_new_game->addReleaseEvent(this, coco_releaseselector(HelloWorld::StartNewGame));
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::StartNewGame(CCObject *pSender)
{
    CCLog("newGame ");
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameScene::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, pScene));
}
