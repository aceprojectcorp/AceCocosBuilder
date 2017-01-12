//
//  AceSameIntervalNode.h
//  MLB
//
//  Created by 허정목 on 2014. 7. 31..
//
//

#ifndef MLB_AceSameIntervalNode_h
#define MLB_AceSameIntervalNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceSameIntervalNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceSameIntervalNode, create);
    
};

NS_CC_EXT_END

#endif
