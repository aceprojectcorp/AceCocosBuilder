//
//  AceCompositeLabel.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#ifndef ScrollViewTest_AceCompositeLabel_h
#define ScrollViewTest_AceCompositeLabel_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

#define COMPOSITE_LABEL_ALIGN_LEFT      0
#define COMPOSITE_LABEL_ALIGN_CENTER    1
#define COMPOSITE_LABEL_ALIGN_RIGHT     2

class AceCompositeLabel
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceCompositeLabel, create);

private:
    //NODE_FACTORY_DEC(CompositeLabel);
    
public:
    int m_align;
    
    float m_gapX;
    
public:
    bool init();
    bool init(int align);
    static AceCompositeLabel* node(int align = COMPOSITE_LABEL_ALIGN_CENTER);
    
    void addChild(CCNode * child);
    
    
public:
    void repaint();

    
};

NS_CC_EXT_END

#endif
