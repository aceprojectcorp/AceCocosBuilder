//
//  AceExtToggleButton.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#ifndef ScrollViewTest_AceExtToggleButton_h
#define ScrollViewTest_AceExtToggleButton_h

#include "cocos2d.h"
#include "cocos-ext.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;




class AceExtToggleButton
: public cocos2d::CCMenuItem
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceExtToggleButton, create);
    
    
private:
    //NODE_FACTORY_DEC(ExtToggleButton);
    //CHILDREN_HANDLER_DEC(ExtToggleButton);
    
protected:
    CCNode *m_pOffNode;
    CCNode *m_pOnNode;
    
    CC_SYNTHESIZE(std::string, m_clickEffect, ClickEffect);
    
    bool m_bOn;
    
public:
    bool bSelected;
    //CCString* m_cbFunc;
    CC_SYNTHESIZE(std::string, m_cbFunc, CbFunc);
    
public:
    bool init();
    bool init(CCObject *pTarget, SEL_MenuHandler selector);
    static AceExtToggleButton* create(CCObject *pTarget, SEL_MenuHandler selector);
    
    void setOffNode(CCNode *pNode);
    void setOnNode(CCNode *pNode);
    
    void setOn(bool bOn);
    bool isOn();
    
protected:
    void activate();

    
};

NS_CC_EXT_END

#endif
