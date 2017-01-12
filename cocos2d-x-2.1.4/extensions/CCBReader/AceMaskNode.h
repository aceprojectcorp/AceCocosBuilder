//
//  AceMaskNode.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#ifndef ScrollViewTest_AceMaskNode_h
#define ScrollViewTest_AceMaskNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceMaskNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceMaskNode, create);
    
    
    void run(float dt);
    
    void maskedSpriteWithSprite(CCSprite* pTextureSprite, CCSprite* pMaskSprite);

    CCSprite* m_pMaskSprite;
    CCSprite* m_pTextureSprite;
    CCRenderTexture* m_rt;

    
    CCSprite* newSprite;
};

NS_CC_EXT_END

#endif
