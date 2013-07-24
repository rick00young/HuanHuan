#ifndef __LinkIcon_H__
#define __LinkIcon_H__

#include "cocos2d.h"

class Beauty : public cocos2d::CCSprite
{
public:
    Beauty(void);
    ~Beauty(void);
    static Beauty* initBeauty(cocos2d::CCSpriteBatchNode *pBatchNodeBeauty, int level);
	bool createBeauty(cocos2d::CCSpriteBatchNode *pBatchNodeBeauty, int level);

    CC_SYNTHESIZE(int, _indexX, indexX);
    CC_SYNTHESIZE(int, _indexY, indexY);
    CC_SYNTHESIZE(cocos2d::CCSprite *, _spriteBeauty, SpriteBeauty);//getter and setter
    void flip();
private:
    int _level;
    void showFace();
    void showBack();
    

};

#endif //

