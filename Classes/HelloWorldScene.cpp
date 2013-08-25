#include "HelloWorldScene.h"
#include "MenuScene.h"
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
    this->setTouchEnabled(true);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    /*
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
    //this->addChild(pMenu, 1);
    */

    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);

    UIWidget* ui = CCUIHELPER->createWidgetFromJsonFile("startUI/Export/startUI_1/startUI_1.json");
    ui->setWidgetTag(EXAMPLE_PANEL_TAG_ROOT);
    ul->addWidget(ui);

    //bind event
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    UIPanel* buttons = dynamic_cast<UIPanel*>(ul->getWidgetByTag(5));

    //new game
    UIButton* button_new_game = dynamic_cast<UIButton*>(buttons->getChildByName("button_1")); 
    //CCLog("button_pannel is %d", button_new_game);
    button_new_game->addReleaseEvent(this, coco_releaseselector(HelloWorld::startNewGame));

    //setting
    UIButton* button_setting = dynamic_cast<UIButton*>(buttons->getChildByName("button_2")); 

    //about
    UIButton* button_about = dynamic_cast<UIButton*>(buttons->getChildByName("button_3")); 
    button_about->addReleaseEvent(this, coco_releaseselector(HelloWorld::showAbout));

    UIImageView* about_bg = dynamic_cast<UIImageView*>(ul->getWidgetByName("about_bg"));
    //about_bg->setAnchorPoint(ccp(0.5f, 0.0f));
    UIButton* close_about = dynamic_cast<UIButton*>(about_bg->getChildByName("close_about"));
    close_about->addReleaseEvent(this, coco_releaseselector(HelloWorld::closeAbout));
    //exit
    UIButton* button_exit = dynamic_cast<UIButton*>(buttons->getChildByName("button_4")); 
    button_exit->addReleaseEvent(this, coco_releaseselector(HelloWorld::menuCloseCallback));
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::startNewGame(CCObject *pSender)
{
    CCLog("newGame ");
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = Menu::scene();
    //pDirector->purgeCachedData();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(1, pScene));
}

void HelloWorld::showAbout(CCObject *pSender)
{
    CCLog("showAbout ");
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    UIPanel* about_panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("About"));
    UIImageView* about_bg = dynamic_cast<UIImageView*>(ul->getWidgetByName("about_bg"));
    UIButton* close_about = dynamic_cast<UIButton*>(about_bg->getChildByName("close_about"));

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    about_panel->setVisible(true);
    about_bg->setPosition(ccp(size.width/2, size.height*2));
    about_bg->setVisible(true);
    CCMoveTo* moveTo = CCMoveTo::create(1.0f, ccp(size.width/2, size.height/1.5));
    about_bg->runAction(CCEaseBounceOut::create(moveTo));
}

void HelloWorld::closeAbout(CCObject *pSender)
{
    CCLog("closeAbout ");
    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    UIPanel* about_panel = dynamic_cast<UIPanel*>(ul->getWidgetByName("About"));
    about_panel->setVisible(false);
    UIImageView* about_bg = dynamic_cast<UIImageView*>(ul->getWidgetByName("about_bg"));

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    about_bg->setPosition(ccp(size.width/2, size.height));
    CCMoveTo* moveTo = CCMoveTo::create(0.5f, ccp(size.width/2, size.height*2));
    about_bg->runAction(CCActionEase::create(moveTo));
    
}