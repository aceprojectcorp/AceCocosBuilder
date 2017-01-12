//
//  CCBGridLayer.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 18..
//
//

#ifndef ScrollViewTest_CCBGridLayer_h
#define ScrollViewTest_CCBGridLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class CCGridLayer
: public cocos2d::CCNode

{
public:
    CCGridLayer();
    ~CCGridLayer();
    virtual bool init();
    virtual void onEnter();
    virtual void draw();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCGridLayer, create);
    
public:
    float m_fRow;
    float m_fCol;
    float m_fPadingLeft;
    float m_fPadingTop;
    float m_fCellWidth;
    float m_fCellHight;
    float m_fGapX;
    float m_fGapY;
    
public:
    void run(cocos2d::CCTime dt);
};

NS_CC_EXT_END

#endif
