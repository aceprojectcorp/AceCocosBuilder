//
//  AceClippingNode.h
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#ifndef AceStencilNode_h
#define AceStencilNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class AceStencilNode
: public cocos2d::CCClippingNode
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceStencilNode, create);
    
private:
    //NODE_FACTORY_DEC(ClippingNode);
    
protected:

public:
    virtual bool init();
    virtual void onEnter();
    virtual void visit();
    
    static AceStencilNode* node();
    
    void makeStencil();
};

NS_CC_EXT_END

#endif
