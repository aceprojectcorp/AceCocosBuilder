//
//  Ace3DPlayer.h
//  MLB
//
//  Created by 허정목 on 2014. 3. 11..
//
//

#ifndef MLB_Ace3DPlayer_h
#define MLB_Ace3DPlayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Ace3DNode.h"
#include "Ace3DWorld.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class Ace3DPlayer
: public Ace3DNode
{
public:
    virtual bool init();
    virtual void onEnter();
    virtual void visit();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Ace3DPlayer, create);
    
private:
    _Eye mEye;
    _Screen mScreen;
    float fGridDepth;
    
    //_CollisionDBG collision;
    
};

NS_CC_EXT_END

#endif
