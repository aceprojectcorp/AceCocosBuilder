//
//  AceExtMenuItem.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#ifndef ScrollViewTest_AceExtMenuItem_h
#define ScrollViewTest_AceExtMenuItem_h

#include "cocos2d.h"
#include "cocos-ext.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;




class AceExtMenuItem
: public cocos2d::CCMenuItem
{
public:
    AceExtMenuItem()
    : m_bMyMode(false)
    , m_pMyModeTarget(NULL)
    , m_pMySelectedFunc(NULL)
    , m_pMyUnSelectedFunc(NULL)
    {
        
    }
    
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceExtMenuItem, create);
    
    
private:
    //NODE_FACTORY_DEC(ExtMenuItem);
    //CHILDREN_HANDLER_DEC(ExtMenuItem);
    
public:
    CCNode *m_pNormalNode;
    CCNode *m_pSelectedNode;
    CCNode* m_pDisableNode;
    
    bool bDisable;
    
    //CC_SYNTHESIZE(std::string, m_selector, m_selector);
    //CCString* m_selector;
    CC_SYNTHESIZE(std::string, m_selector, Selector);
    CC_SYNTHESIZE(std::string, m_btnId, BtnId);
    CC_SYNTHESIZE(std::string, m_clickEffect, ClickEffect);
    
    // 선택되었을때 처리를 내맘대로하고싶을때
    // m_bMyMode 플래그를 켜고
    // 호출될 타겟과, 선택됬을때 호출될 콜백, 풀릴때 호출될 콜백을 등록해주면 된다.
    CC_SYNTHESIZE(bool, m_bMyMode, MyMode);
    CC_SYNTHESIZE(CCObject*, m_pMyModeTarget, MyModeTarget);
    CC_SYNTHESIZE(SEL_CallFuncN, m_pMySelectedFunc, MySelectedFunc);
    CC_SYNTHESIZE(SEL_CallFuncN, m_pMyUnSelectedFunc, MyUnSelectedFunc);
    
public:
    bool init();
    bool init(CCObject* target, SEL_MenuHandler selector);
    static AceExtMenuItem* create(CCObject* target, SEL_MenuHandler selector);
    
    void setNormalNode(CCNode *pNode);
    void setSelectedNode(CCNode *pNode);
    void setDisableNode(CCNode* pNode);
    
    void selected();
    void unselected();
    void disableBtn(bool bRadioBtn = false);
    void ableBtn();
    
    void activate();
    
public:
    CCString* m_normalName;
    CCString* m_selectedName;
    
private:
    CCBAnimationManager* am;
    
public:
    //CCBAnimationManager* getAnimationManager();
    //void setAnimationManager(CCBAnimationManager* am);
    
};

NS_CC_EXT_END


#endif
