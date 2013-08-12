#include "GameScene.h"

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

        

        
        //this->setTouchEnabled(true);
        this->initBackGround();
        this->intBeauties();

        /*
        CCSprite* icon = CCSprite::createWithSpriteFrameName("02.png");
        icon->setPosition(ccp(100, 100));  
        this->addChild(icon);
        CCFlipX3D* flipx = CCFlipX3D::create(1);
        icon->runAction(flipx);
        
        //创建翻牌sprite, 参数：卡片里面的图，卡片的封面，翻牌所花时间
 
        CardSprite* card = CardSprite::create(3);
 
        card->setPosition(ccp(size.width * .5, size.height * .5));
 
        addChild(card);
 
        card->openCard();//开始翻牌</span>*/

        //scheduleUpdate();
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
        int index = rand() % 7;
        CCLog("the index is %d", index);
        CardSprite* _Beauty = CardSprite::create(this, index);
        this->addChild(_Beauty);
        m_pBeauties->addObject(_Beauty);

        _Beauty = CardSprite::create(this, index);
        this->addChild(_Beauty);
        m_pBeauties->addObject(_Beauty);
        
    }
    
    
    this->disPatchBeauties();
    this->setBeautiesPosition();
}

void GameScene::disPatchBeauties()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    m_pBeautiesRoot = new CCArray;
    m_pBeautiesOpen = new CCArray;
    
    while(m_pBeauties->count() > 0){
    
        CardSprite * _Beauty = (CardSprite *)m_pBeauties->randomObject();
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
        CardSprite * _Beauty = (CardSprite *)m_pBeautiesRoot->objectAtIndex(index);
        //CCLog("the index is %d", m_pIconsRoot->indexOfObject(_linkIcon));
        if(index % 6 ==0){
            x = 84;
            if( index > 1)
                y = y + 140;
            _Beauty->setPosition(ccp(x,y));
            //_Beauty->openCard();
            reorderChild(_Beauty, index + 1);
            
        }else{
            x = x + 60;
            _Beauty->setPosition(ccp(x,y));
            reorderChild(_Beauty, index + 1);
            //_Beauty->openCard();
        }
        CCLog("the index is %d", index);
        index++;

        
        
    }
    
    
}

/*
void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    //return true;
}

void GameScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
 	CCSetIterator it = pTouches->begin();
    CCPoint pt;
	for(; it != pTouches->end(); it++)
    {
		CCTouch *pTouch = (CCTouch*)*it;
		pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		//CCLog("pt.x %f ** pt.y %f", pt.x, pt.y);

        //break;
	}
    int index = 0;
    
    for(int j = (int)(m_pBeautiesRoot->count()); j > 0; j--){
        CardSprite * _Beauty = (CardSprite *)m_pBeautiesRoot->objectAtIndex(j - 1);
        if(_Beauty){


            //_Beauty->openCard();
            break;

        }
    }
    
}
*/
void GameScene::update(float time){
    //CCLog("update");
    CCObject *beauty = NULL;
	CCARRAY_FOREACH(m_pBeautiesRoot, beauty){
		
		CardSprite *m_pBeauty = (CardSprite *)beauty;
        if(m_pBeauty->getOpened() && m_pBeauty->isVisible()){
            
            m_pBeautiesOpen->addObject(m_pBeauty);
            if(m_pBeautiesOpen->count() > 3){
                break;
            }

        }
        
	}

    if(m_pBeautiesOpen->count() >= 2){
        currentBeauty = (CardSprite *) m_pBeautiesOpen->objectAtIndex(0);
        firstBeauty = (CardSprite *) m_pBeautiesOpen->objectAtIndex(1);

        CCLog("-----%d-------", currentBeauty->getLevel());
        CCLog("-----%d-------", firstBeauty->getLevel());
        CCLog("-----========================------");
        if(currentBeauty->getLevel() == firstBeauty->getLevel()){
            CCLog("it is the same");
            currentBeauty->hideCard();
            firstBeauty->hideCard();
            
        }else{
            currentBeauty->closeCard();
            firstBeauty->closeCard();  
            if(m_pBeautiesOpen->count()> 2){
                secondBeauty = (CardSprite *) m_pBeautiesOpen->objectAtIndex(2);
                secondBeauty->closeCard();
            }

        }
        
    }
    CCLog("wwwwwwwwwwww %d wwwwww", m_pBeautiesOpen->count());
    m_pBeautiesOpen->removeAllObjects();
   

    
    //CCLog();
}


void GameScene::okForClip()
{
    CCLog("okfor clip");
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

