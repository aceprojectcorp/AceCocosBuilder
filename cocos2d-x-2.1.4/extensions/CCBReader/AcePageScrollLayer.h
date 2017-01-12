//
//  AcePageScrollLayer.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#ifndef ScrollViewTest_AcePageScrollLayer_h
#define ScrollViewTest_AcePageScrollLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class AcePageScrollLayer;

class AceScrollLayerDelegate
{
public:
    /** Called when scroll layer begins scrolling.
     * Usefull to cancel CCTouchDispatcher standardDelegates.
     */
    virtual void scrollLayerScrollingStarted(AcePageScrollLayer* sender) {}
    
    /** Called at the end of moveToPage:
     * Doesn't get called in selectPage:
     */
    virtual void scrollLayerScrolledToPageNumber(AcePageScrollLayer* sender, unsigned int page) {}
};

class AcePageScrollLayer
: public cocos2d::CCLayer
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AcePageScrollLayer, create);
    
private:
    //NODE_FACTORY_DEC(ScrollLayer);
public:
    CC_SYNTHESIZE(AceScrollLayerDelegate*, m_pDelegate, Delegate);
    
    /** Calibration property. Minimum moving touch length that is enough
     * to cancel menu items and start scrolling a layer.
     */
    CC_SYNTHESIZE(float, m_fMinimumTouchLengthToSlide, MinimumTouchLengthToSlide);
    
    /** Calibration property. Minimum moving touch length that is enough to change
     * the page, without snapping back to the previous selected page.
     */
    CC_SYNTHESIZE(float, m_fMinimumTouchLengthToChangePage, MinimumTouchLengthToChangePage);
    
    /** If YES - when starting scrolling CCScrollLayer will claim touches, that are
     * already claimed by others targetedTouchDelegates by calling CCTouchDispatcher#touchesCancelled
     * Usefull to have ability to scroll with touch above menus in pages.
     * If NO - scrolling will start, but no touches will be cancelled.
     * Default is YES.
     */
    CC_SYNTHESIZE(bool, m_bStealTouches, StealTouches);
    
    /** Current page number, that is shown. Belongs to the [0, totalScreen] interval. */
    CC_SYNTHESIZE_READONLY(unsigned int, m_uCurrentScreen, CurrentScreen);
    
    /** Offset that can be used to let user see empty space over first or last page. */
    CC_SYNTHESIZE(float, m_fMarginOffset, MarginOffset);
    
    /** Array of pages CCLayer's  */
    CC_SYNTHESIZE_READONLY(CCArray*, m_pLayers, Pages);
    
    CC_SYNTHESIZE(int, m_touchPriority, TouchPriority);
    CC_SYNTHESIZE(bool, m_checkParent, CheckParent);
    
    CC_SYNTHESIZE(CCSize, m_pageSize, PageSize);
    
    
    
    
    CC_SYNTHESIZE(bool, m_bEdgeMoveStop, EdgeMoveStop);
    
public:
    AcePageScrollLayer();
    virtual ~AcePageScrollLayer();
    
    static AcePageScrollLayer* layer();
    
    bool init();
    
    void updatePages();
    
    void addPage(CCNode *pNode);
    void removeAll();
    
    CCNode* getCurrentChild();
    
    /** Total pages available in scrollLayer. */
    unsigned int getTotalScreens() const;
    
    /* Moves scrollLayer to page with given number & invokes delegate
     * method scrollLayer:scrolledToPageNumber: at the end of CCMoveTo action.
     * Does nothing if number >= totalScreens or < 0.
     */
    void moveToPage(unsigned int pageNumber, int direction = 0);
    
    /* Immedeatly moves scrollLayer to page with given number without running CCMoveTo.
     * Does nothing if number >= totalScreens or < 0.
     */
    void selectPage(unsigned int pageNumber);
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
protected:
    // The x coord of initial point the user starts their swipe.
    float m_fStartSwipe;
    
    // Internal state of scrollLayer (scrolling or idle).
    int m_iState;
    bool m_bStealingTouchInProgress;
    // Holds the touch that started the scroll
    CCTouch* m_pScrollTouch;
    
    void moveToPageEnded();
    unsigned int pageNumberForPosition(const CCPoint& position);
    CCPoint positionForPageWithNumber(unsigned int pageNumber);
    
    void claimTouch(CCTouch* pTouch);
    void cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent);
    
    CCNode* nodeForTouch(CCTouch *touch);

public:
    float startPosX;
    float startPosY;
    
public:
    float m_fPriority;
    
    bool isStateIdle();
    
protected:
    // 페이지 이동시 콜백함수를 연결하여 호출하는 메소드 추가
    SEL_CallFuncO   pCallBackScroll;
    SEL_CallFunc    _pEndCallBack;
    CCObject*       pCallTarget;
    
public:
    void SetFuncAceScroll(CCObject* _pTarget, SEL_CallFuncO _pFunc, SEL_CallFunc _pEndFunc = NULL)
    {
        pCallTarget = _pTarget;
        pCallBackScroll = _pFunc;
        _pEndCallBack = _pEndFunc;
    }
};

NS_CC_EXT_END

#endif
