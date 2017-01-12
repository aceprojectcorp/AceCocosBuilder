//
//  AceClippingScrollNode.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 2..
//
//

#ifndef ScrollViewTest_AceClippingScrollNode_h
#define ScrollViewTest_AceClippingScrollNode_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AceScrollBar.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
    SCROLL_DIR_UP_DOWN,
    SCROLL_DIR_LEFT_RIGHT,
} _ScrollDir;


struct ItemResource
{
    int  index;
    int  paramA;
};

class AceClippingScrollNode
: public cocos2d::CCLayer
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceClippingScrollNode, create);
    
private:
    //NODE_FACTORY_DEC(ClippingScrollNode);
    //CHILDREN_HANDLER_DEC(ClippingScrollNode);
    
    /** Calibration property. Minimum moving touch length that is enough
     * to cancel menu items and start scrolling a layer.
     */
    CC_SYNTHESIZE(float, m_fMinimumTouchLengthToSlide, MinimumTouchLengthToSlide);
    CC_SYNTHESIZE(float, m_aniTime, AniTime);
    CC_SYNTHESIZE(bool, m_bStealTouches, StealTouches);
    //CC_SYNTHESIZE(int, m_touchPriority, TouchPriority); //jambam 원본
    
    CC_SYNTHESIZE(CCObject*, m_pTarget, Target);
    CC_SYNTHESIZE(SEL_CallFunc, m_pCallback, Callback);
    
    CC_SYNTHESIZE(CCObject*, m_pEndScrollTarget, EndScrollTarget);
    CC_SYNTHESIZE(SEL_CallFunc, m_pEndScrollCallback, EndScrollCallback);
    CC_SYNTHESIZE( bool, _checkScrollLimit, CheckScrollLimit );
    CC_SYNTHESIZE( bool, _resetPositionLock, ResetPositionLock );
public:
    int m_touchPriority; //jambam 추가
    
protected:
	ccVertex2F m_pSquareVertices[4];
	ccColor4B  m_pSquareColors[4];
    bool m_bInitScrollBarVisible;
    bool m_bScrollBarVisible;
    
public:
    AceClippingScrollNode();
    
    bool init();
    static AceClippingScrollNode* node();
    
    void visit(void);
    
    CCNode* getScrollChild();
//    void setScrollChild(CCNode *pNode, bool isScrollable);
    void setScrollChildPos(CCPoint pos);
    void setScrollChildBottom();
    
    void reset();
    void resetScrollBar();
    
    void setInitScrollBarVisible(bool bVisible);
    void setScrollBarVisible(bool bVisible);
    
    void setPriority(int priority);
    void setScrollTouch(CCTouch* pTouch);
    CCTouch* getScrollTouch();
    
protected:
    //    CCPoint m_startSwipePos;
    CCPoint m_touchPoint;
    CCPoint m_scrollDistance;
    CCPoint m_startChildPos;
    CCTouch m_prevTouch;
    
    // Internal state of scrollLayer (scrolling or idle).
    int m_iState;
    bool m_bStealingTouchInProgress;
    // Holds the touch that started the scroll
    CCTouch* m_pScrollTouch;
    

protected:
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    
    void claimTouch(CCTouch* pTouch);
    void cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent);
    
    void onScrollFinished();
    
    void update(float dt);
    
    void deaccelerateScrolling(float dt);
    
    float getResistance(CCNode *pChild);
    
    void createScrollBar(CCNode *pChild);
    
public:
    AceScrollBar *m_pScrollBar;
    
    _ScrollDir scrollDir;
    
    bool bMaxContentSizeW;
    float maxContentSizeW;
    bool bMaxContentSizeH;
    float maxContentSizeH;
    
private:
    bool checkScrollRange(float moveDistanceX);
};

NS_CC_EXT_END

#endif
