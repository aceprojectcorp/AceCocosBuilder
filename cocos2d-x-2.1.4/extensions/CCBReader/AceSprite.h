//
//  AceSprite.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#ifndef ScrollViewTest_AceSprite_h
#define ScrollViewTest_AceSprite_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
    BLEND_TYPE_NORMAL,
    BLEND_TYPE_LINEAR_DODGE,
    BLEND_TYPE_SCREEN,
    BLEND_TYPE_MULTIPLY,
} _BlendType;

class AceSprite
: public CCSprite
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceSprite, create);
    
public:
    _BlendType blendType;
    
public:
    void setBlendType(int type);
    
};

NS_CC_EXT_END

#endif
