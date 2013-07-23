#include "Beauty.h"
using namespace cocos2d;

Beauty::Beauty(void) : _indexX(0), _indexY(0)
{

}


Beauty::~Beauty(void)
{
    CCLog("Beauty is deleted!");
}

Beauty* Beauty::initBeauty(cocos2d::CCSpriteBatchNode *pBatchNodeBeauty, int level)
{
    Beauty* _spriteBeauty = new Beauty();
    if(_spriteBeauty && _spriteBeauty->createBeauty(pBatchNodeBeauty, level)){
        return _spriteBeauty;
    }else{
        CC_SAFE_DELETE(_spriteBeauty);
        return NULL;
    }
}

bool Beauty::createBeauty(cocos2d::CCSpriteBatchNode *pBatchNodeBeauty, int level){
    
    _level = level;
    //CCString* originalFrameName = CCString::createWithFormat("%02d.png", level);

	//CCLog("fish name is %s", originalFrameName->getCString());
	//_spriteFish = CCSprite::createWithSpriteFrameName("fish01_01.png");
    //this->createWithSpriteFrameName(originalFrameName->getCString());//´´½¨Óã¾«Áé

    this->setSpriteBeauty(CCSprite::createWithSpriteFrameName("back.png"));
    pBatchNodeBeauty->addChild(_spriteBeauty);
    //s_spriteBeauty->setScale(0.7f);
    //_spriteBeauty->setPosition(ccp(100, 100)); 
    
    return true;
   
}

void Beauty::showFace(){
   
    CCString* frameName = CCString::createWithFormat("%02d.png", _level);

    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString()); 
    if(frame){
        _spriteBeauty->setDisplayFrame(frame); 
    }
}

void Beauty::showBack(){
   
    //CCString* frameName = CCString::createWithFormat("%02d.png", _level);

    CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("back.png"); 
    if(frame){
        _spriteBeauty->setDisplayFrame(frame); 
    }
}
