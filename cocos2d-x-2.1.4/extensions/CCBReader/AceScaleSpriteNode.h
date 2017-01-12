//
//  AceScaleSpriteNode.h
//  MLB
//
//  Created by 허정목 on 2014. 7. 30..
//
//

#ifndef MLB_AceScaleSpriteNode_h
#define MLB_AceScaleSpriteNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceScaleSpriteNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceScaleSpriteNode, create);
    
    void resize();
    
};

NS_CC_EXT_END

#endif