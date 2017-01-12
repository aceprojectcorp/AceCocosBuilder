//
//  AceClippingNode.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 25..
//
//

#ifndef ScrollViewTest_AceClippingNode_h
#define ScrollViewTest_AceClippingNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class AceClippingNode
: public cocos2d::CCClippingNode
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceClippingNode, create);
    
private:
    //NODE_FACTORY_DEC(ClippingNode);
    
protected:
    CC_SYNTHESIZE(float, m_widthRatio, WidthRatio);
public:
    virtual bool init();
    virtual void onEnter();
    virtual void setContentSize(const CCSize& contentSize);
    
    static AceClippingNode* node();
    
    void makeStencil();
};

NS_CC_EXT_END

#endif
