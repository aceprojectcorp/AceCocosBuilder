//
//  AceFlowLayer.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#ifndef ScrollViewTest_AceFlowLayer_h
#define ScrollViewTest_AceFlowLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

#define COMPOSITE_LABEL_ALIGN_LEFT      0
#define COMPOSITE_LABEL_ALIGN_CENTER    1
#define COMPOSITE_LABEL_ALIGN_RIGHT     2



class AceFlowLayer
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceFlowLayer, create);
    
    
private:
    //NODE_FACTORY_DEC(FlowLayer);
    //CHILDREN_HANDLER_DEC(AceFlowLayer);
    
public:
    CCPoint m_padding;
    float m_gap;
    int m_align;
    
public:
    bool init();
    bool init(CCPoint padding, float gap);
    static AceFlowLayer* create(CCPoint padding, float gap);
    
    void addNodes(CCArray *pArray);
    
    void refresh();
    
protected:
    CCSize calculateSize(CCArray *pArray);
};

NS_CC_EXT_END

#endif
