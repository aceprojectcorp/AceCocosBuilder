//
//  AceExtRadioButton.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#ifndef ScrollViewTest_AceExtRadioButton_h
#define ScrollViewTest_AceExtRadioButton_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AceExtMenuItem.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;




class AceExtRadioButton
: public AceExtMenuItem
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceExtRadioButton, create);
    
    
private:
    //NODE_FACTORY_DEC(ExtRadioButton);
    //CHILDREN_HANDLER_DEC(ExtRadioButton);
    
public:
    bool bSelected;
    bool bRevitalize;
    
    void setRevitalize(bool isRevitalize) {bRevitalize = isRevitalize;}
    bool getRevitalize() {return bRevitalize;}
    
    //CCString* m_cbFunc;
    CC_SYNTHESIZE(std::string, m_cbFunc, CbFunc);
    
public:
    static AceExtRadioButton* create(CCObject *pTarget, SEL_MenuHandler selector);
    
    
    void setSelected(bool isSelected);
    void activate(bool isEffect = true);
    //---test
    void clkicked(CCObject* pSender);
    //---
    
public:
    AceExtRadioButton();
    ~AceExtRadioButton();
};

NS_CC_EXT_END

#endif
