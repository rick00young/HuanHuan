#include "GameScene.h"
#include "MenuScene.h"
using namespace cocos2d;

GameScene::GameScene() : firstBeauty(NULL),secondBeauty(NULL), currentBeauty(NULL), okforClip(true)
{

}

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


        CCSize size = CCDirector::sharedDirector()->getWinSize();
        //backgroud
        CCSprite* pSprite = CCSprite::create("bg1.jpg");
        pSprite->setScale(0.4f);
        CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(pSprite, 0);
                
        //this->setTouchEnabled(true);
        this->initBackGround();
        this->intBeauties();

        //locd UI;
        ul = UILayer::create();
        ul->scheduleUpdate();
        this->addChild(ul);

        UIWidget* ui = CCUIHELPER->createWidgetFromJsonFile("gameUI/Export/gameUI_1/gameUI_1.json");
        ui->setWidgetTag(EXAMPLE_PANEL_TAG_ROOT);
        ul->addWidget(ui);

        //CCLog("game_level is %d", GameLevel);
        //scheduleUpdate();
        bindCallbacks();
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
    
    for(int i = 0;i < 4; i++){
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
    
}

void GameScene::setBeautiesPosition(){
    //CCLog("the count is %d", m_pIcons->count());
    
    int index = 0;
    int x = 84;
    int y = 80;
    int j = 0;
    CCMoveTo* moveTo;
    while(index < (int)(m_pBeautiesRoot->count())){
        CardSprite * _Beauty = (CardSprite *)m_pBeautiesRoot->objectAtIndex(index);
        //CCLog("the index is %d", m_pIconsRoot->indexOfObject(_linkIcon));
        if(index % 4 ==0){
            x = 84;
            if( index > 1)
                y = y + 140;
            moveTo = CCMoveTo::create(0.5f, ccp(x,y));
            _Beauty->runAction(moveTo);
            //_Beauty->setPosition(ccp(x,y));
            //_Beauty->openCard();
            reorderChild(_Beauty, index + 1);
            
        }else{
            x = x + 100;
            moveTo = CCMoveTo::create(0.5f, ccp(x,y));
            _Beauty->runAction(moveTo);

            //_Beauty->setPosition(ccp(x,y));
            reorderChild(_Beauty, index + 1);
            //_Beauty->openCard();
        }
        CCLog("the index is %d", index);
        index++;

        
        
    }
    /*
    CCParticleSystem* m_emitter = CCParticleFlower::create();
    m_emitter->retain();
    this->addChild(m_emitter, 10);
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png") ); 
    m_emitter->setPosition(ccp(240, 160));
    */

}


void GameScene::update(float time){

}


bool GameScene::isOkForClip()
{
    
    if((!firstBeauty || !secondBeauty) && okforClip){
        okforClip = false;
        CCLog("okfor clip");
        return true;
    }
    return false;
    
}

void GameScene::gameLogic(CardSprite* card)
{
    //CCLog("qqqqqq   %d qqqqqq", card);
    okforClip = true;

    if(!firstBeauty){
        firstBeauty = card;
        return;
    }

    if(firstBeauty && !secondBeauty){
        secondBeauty = card;
    }

    if(firstBeauty && secondBeauty && !currentBeauty){
        currentBeauty = card;
    }
    
    if(firstBeauty && secondBeauty){
        CCLog("firstBeauty   %d firstBeauty", firstBeauty);
        CCLog("secondBeauty   %d secondBeauty", secondBeauty);
        if((firstBeauty == secondBeauty)){
            firstBeauty->closeCard();
            firstBeauty = NULL;
            secondBeauty = NULL;
            CCLog("======   %d ======", firstBeauty);
            //return;        
        }else{

            if(firstBeauty->getLevel() == secondBeauty->getLevel()){
                firstBeauty->hideCard();
                secondBeauty->hideCard();
                firstBeauty = NULL;
                secondBeauty = NULL;
            }else{
                firstBeauty->closeCard();
                secondBeauty->closeCard();
                currentBeauty->closeCard();
                firstBeauty = secondBeauty;
                secondBeauty = NULL;
                currentBeauty = NULL;
            }        
        }

    }
    okforClip = true;
}


void GameScene::bindCallbacks()
{
    UIWidget* root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
    //back to helloworld
    UIButton* back_btn = dynamic_cast<UIButton*>(root->getChildByName("back")); 
    back_btn->addReleaseEvent(this, coco_releaseselector(GameScene::backToMenu));
}

void GameScene::backToMenu(CCObject* pSender)
{   int i =0;
    int count = (int)(m_pBeautiesRoot->count());
    CCLog("cout is %d", count);
    for(int i = 0; i < count; i++){
    
        CardSprite * _Beauty = (CardSprite *)m_pBeautiesRoot->objectAtIndex(i);
        //_Beauty->touchDelegateRelease();
        
        _Beauty->touchDelegateRelease();
        CCLog("release");
    }
    
    //m_pBeautiesRoot->removeAllObjects();
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    //pDirector->purgeCachedData();
    CCScene *pScene = Menu::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1, pScene));
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

