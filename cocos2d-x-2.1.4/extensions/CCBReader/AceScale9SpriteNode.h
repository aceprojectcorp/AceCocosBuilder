//
//  AceScale9SpriteNode.h
//  MLB
//
//  Created by 허정목 on 2014. 5. 23..
//
//

#ifndef MLB_AceScale9SpriteNode_h
#define MLB_AceScale9SpriteNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceScale9SpriteNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceScale9SpriteNode, create);
    
};

NS_CC_EXT_END

#endif
