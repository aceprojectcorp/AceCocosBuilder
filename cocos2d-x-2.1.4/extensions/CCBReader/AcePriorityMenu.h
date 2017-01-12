//
//  AcePriorityMenu.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#ifndef ScrollViewTest_AcePriorityMenu_h
#define ScrollViewTest_AcePriorityMenu_h

#include "cocos2d.h"
#include "cocos-ext.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

#define SOUND_PLAYER_UTILS_EFFECT_DISABLED      "effectDisabled"


class AcePriorityMenu
: public cocos2d::CCMenu
{
public:
    AcePriorityMenu()
    : m_bRadioTouchMovedLive(false)
    , m_bTouchMovedLive(false)
    , m_bRadioNotDoubleTouch(true)
    , m_pOriginItem(NULL)
    {
    }
    
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AcePriorityMenu, create);
    
    
private:
    //NODE_FACTORY_DEC(PriorityMenu);
    CCMenuItem* m_pOriginItem;
    
    bool m_bRadioTouchMovedLive;
    
public:
    int m_priority;
    bool m_swallowTouches;
    
    CC_SYNTHESIZE(bool, m_checkParent, CheckParent);
    CC_SYNTHESIZE(bool, m_bRadioNotDoubleTouch, RadioNotDoubleTouch);
    
    CC_SYNTHESIZE(bool, m_bTouchMovedLive, TouchMovedLive);
public:
    bool init();
    bool init(int priority, bool swallowTouches);
    static AcePriorityMenu* create(int priority, bool swallowTouches = true);
    
//protected:
public:
    void registerWithTouchDispatcher();
    
    bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    void ccTouchEnded(CCTouch* touch, CCEvent* event);
    void ccTouchCancelled(CCTouch *touch, CCEvent* event);
    void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    void setPriority(int mPriority);

    void setOriginItem(CCMenuItem* pMenu) { m_pOriginItem = pMenu; }
    
    const CCMenuItem* getSelectedItem() {return m_pSelectedItem;}
    
    CCMenuItem* getRadioChildItem();
    
    
    // ccTouchBegan상태에서 setTouchEnabled(false)를 하면
    // m_eState가 kCCMenuStateTrackingTouch로 남아있어 다시 터치할수없어서 reset()함수를 만듬
    // 나중에 setTouchEnabled에서 m_eState가 kCCMenuStateTrackingTouch일때 m_bTouchEnabled를 false로 바꾸려고하면,
    // reset()함수를 호출하도록 수정해야함
    void reset();
    
    
public:
    // 창현 - 다중터치를 막기위해 생성
    static bool isTouch;
};

NS_CC_EXT_END

#endif
