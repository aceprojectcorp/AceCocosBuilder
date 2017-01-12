//
//  Ace3DBall.h
//  MLB
//
//  Created by 허정목 on 2014. 3. 3..
//
//

#ifndef MLB_Ace3DBall_h
#define MLB_Ace3DBall_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Ace3DNode.h"
#include "Ace3DWorld.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


#define MOVEBALL_Z  500

class Ace3DBall
: public Ace3DNode
{
public:
    virtual bool init();
    virtual void onEnter();
    virtual void visit();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Ace3DBall, create);
    
public:
    void createTail();
    void removeTail(cocos2d::CCObject *pSender);
    
private:
    bool bMoveBallDown;
    int moveBallZ;
    
    
public:
    //---loader에서 읽어오는 넘들...(cocosBuilder수정후 삭제될 넘들)
    float tmpPower;
    float tmpAngle;
    float tmpAngleZ;
    float tmpG;
    //---
};

NS_CC_EXT_END

#endif
