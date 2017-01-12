//
//  AceMultiNode.h
//  MLB
//
//  Created by 허정목 on 2014. 8. 11..
//
//

#ifndef MLB_AceMultiNode_h
#define MLB_AceMultiNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceMultiNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceMultiNode, create);
    
public:
    bool bMaxContentSizeW;
    float maxContentSizeW;
    bool bMaxContentSizeH;
    float maxContentSizeH;
};

NS_CC_EXT_END

#endif
