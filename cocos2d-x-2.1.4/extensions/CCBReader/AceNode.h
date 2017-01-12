//
//  AceNode.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 19..
//
//

#ifndef ScrollViewTest_AceNode_h
#define ScrollViewTest_AceNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceNode, create);
    
};

NS_CC_EXT_END

#endif
