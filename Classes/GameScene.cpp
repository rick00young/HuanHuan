#include "GameScene.h"
#include "Beauty.h"
using namespace cocos2d;

CCScene* GameScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* pSprite = CCSprite::create("bg1.jpg");
        pSprite->setScale(0.4f);
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

        /*
        CCSprite* icon = CCSprite::create("07.png");
        icon->setPosition(ccp(100, 100));
        icon->setScale(0.4f);
        this->addChild(icon);
        */
        this->initBackGround();
        this->intBeauties();
        bRet = true;
    } while (0);

    return bRet;
}

void GameScene::initBackGround()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("meiren.plist");

    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("meiren.png");
    this->setBatchNode(CCSpriteBatchNode::createWithTexture(texture));
    
    this->addChild(m_pBatchNode);
}

void GameScene::intBeauties(){

     /*
    CCString *originalFrameName = CCString::createWithFormat("%02d.png", 1);
    CCLog("the name is %s", originalFrameName->getCString());
    CCSprite * icon = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());
    icon->setPosition(ccp(100, 100));
    m_pBatchNode->addChild(icon);
    */
    m_pBeauties = new CCArray;
    srand((unsigned)time(NULL));
    //LinkIcon* _linkIcon = LinkIcon::initLinkIcon(m_pBatchNode, 1);
    //m_pBatchNode->addChild(_linkIcon);
    for(int i = 0;i < 6; i++){
        int index = rand() % 6 + 1;
       // CCLog("the index is %d", index);
        Beauty* _Beauty = Beauty::initBeauty(m_pBatchNode, index);
        m_pBeauties->addObject(_Beauty);

        _Beauty = Beauty::initBeauty(m_pBatchNode, index);
        m_pBeauties->addObject(_Beauty);
        
    }
    
    
    this->disPatchBeauties();
    this->setBeautiesPosition();
}

void GameScene::disPatchBeauties()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    m_pBeautiesRoot = new CCArray;

    while(m_pBeauties->count() > 0){
    
        Beauty * _Beauty = (Beauty *)m_pBeauties->randomObject();
        //CCLog("the index is %d", m_pIcons->indexOfObject(_linkIcon));

        m_pBeautiesRoot->addObject(_Beauty);
        
        m_pBeauties->removeObject(_Beauty, false);
    }

    //CCLog("the m_pIcons count is %d", m_pIcons->count());
    //CCLog("the m_pIconsRoot count is %d", m_pIconsRoot->count());
    
}

void GameScene::setBeautiesPosition(){
    //CCLog("the count is %d", m_pIcons->count());
    
    int index = 0;
    int x = 84;
    int y = 80;
    int j = 0;
    while(index < (int)(m_pBeautiesRoot->count())){
        Beauty * _Beauty = (Beauty *)m_pBeautiesRoot->objectAtIndex(index);
        //CCLog("the index is %d", m_pIconsRoot->indexOfObject(_linkIcon));
        if(index % 6 ==0){
            x = 84;
            if( index > 1)
                y = y + 140;
            _Beauty->getSpriteBeauty()->setPosition(ccp(x,y));
            reorderChild(_Beauty->getSpriteBeauty(), index + 1);
            
        }else{
            x = x + 60;
            _Beauty->getSpriteBeauty()->setPosition(ccp(x,y));
            reorderChild(_Beauty->getSpriteBeauty(), index + 1);
        }
        CCLog("the index is %d", index);
        index++;

        
        
    }
    
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

