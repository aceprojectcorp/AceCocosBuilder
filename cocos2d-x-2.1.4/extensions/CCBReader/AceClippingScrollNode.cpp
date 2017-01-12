//
//  AceClippingScrollNode.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 2..
//
//

#include "AceClippingScrollNode.h"

USING_NS_CC_EXT;

enum {
    kClippingScrollNodeStateIdle = 10,
    kClippingScrollNodeStateSliding
};

#define CLIPPING_SCROLL_NODE_DEACCEL_RATE   0.95f
#define CLIPPING_SCROLL_NODE_DEACCEL_DIST   1.0f
#define CLIPPING_SCROLL_NODE_RESISTANCE     1.8
#define CLIPPING_SCROLL_NODE_CONTENT_TAG       1

void AceClippingScrollNode::onEnter()
{
    CCLayer::onEnter();
    
    setTouchPriority(this->getTouchPriority());
    
    
    if(this->bMaxContentSizeW)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.width > maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
            
            this->setContentSize(mySize);
        }
    }
    
    if(this->bMaxContentSizeH)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.height > maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
            
            this->setContentSize(mySize);
        }
    }
    
    
    m_bIgnoreAnchorPointForPosition = false;
    
    reset();
}

AceClippingScrollNode::AceClippingScrollNode()
: m_pScrollTouch(NULL)
, m_pScrollBar(NULL)
, m_pTarget(NULL)
, m_pCallback(NULL)

, m_pEndScrollTarget(NULL)
, m_pEndScrollCallback(NULL)

, _checkScrollLimit( false )
, _resetPositionLock(false)
{}


bool AceClippingScrollNode::init()
{
    if(!CCLayer::init()) return false;
    
    this->setAnchorPoint(CCPointZero);
    
    // Set default minimum touch length to scroll.
    //m_fMinimumTouchLengthToSlide = 10.0f * AppContext::sharedContext()->getUIScale();
    m_fMinimumTouchLengthToSlide = 10.0f;
    m_aniTime = 0.3;
    m_bInitScrollBarVisible = true;
    m_bScrollBarVisible = true;
    
    bMaxContentSizeW = false;
    bMaxContentSizeH = false;
    
    m_touchPriority = kCCMenuHandlerPriority - 1;
    
    setTouchEnabled(true);
    
    m_bStealTouches = true;
    
    this->scheduleUpdate();
    
    return true;
}

AceClippingScrollNode* AceClippingScrollNode::node()
{
    AceClippingScrollNode *pNode = new AceClippingScrollNode();
    if(pNode && pNode->init()) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}


void AceClippingScrollNode::visit()
{
    // glScissor는 월드 좌표계로 설정해야하기 때문에 현재 노드의 위치 및 크기를 변환함
    CCPoint pos = this->convertToWorldSpace(CCPointZero);
    CCSize size = getContentSize();
    
    glEnable(GL_SCISSOR_TEST);
    
    // 직접 glScissor를 사용하면 android의 auto scale 모드 때문에 안됨
    CCEGLView::sharedOpenGLView()->setScissorInPoints(pos.x, pos.y, size.width, size.height);
    
    CCNode::visit();
    
    glDisable(GL_SCISSOR_TEST);
}

void AceClippingScrollNode::registerWithTouchDispatcher()
{
    // ccmenu 보다 먼저 터치 이벤트를 받음
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, false);
}

void AceClippingScrollNode::claimTouch(CCTouch* pTouch)
{
    CCTargetedTouchHandler *handler = (CCTargetedTouchHandler*)CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this);
    if(handler) {
        CCSet *claimedTouches = handler->getClaimedTouches();
        if(!claimedTouches->containsObject(pTouch)) {
            claimedTouches->addObject(pTouch);
        } else {
            CCLOGERROR("ScrollLayer::claimTouch is already claimed!");
        }
    }
}

void AceClippingScrollNode::cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent)
{
    // Throw Cancel message for everybody in TouchDispatcher.
    CCSet* touchSet = new CCSet();
    touchSet->addObject(pTouch);
    touchSet->autorelease();
    
    m_bStealingTouchInProgress = true;
    CCDirector::sharedDirector()->getTouchDispatcher()->touchesCancelled(touchSet, pEvent);
    m_bStealingTouchInProgress = false;
    
    //< after doing this touch is already removed from all targeted handlers
    
    // Squirrel away the touch
    claimTouch(pTouch);
    
}


bool AceClippingScrollNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(!isVisible()) return false;
    
    CCNode *pParent = NULL;
    for (pParent = this->m_pParent; pParent != NULL; pParent = pParent->getParent())
    {
        if(pParent->isVisible() == false)
            return false;
    }
    
    CCNode *pChild = getScrollChild();
    
    // 자식 노드가 없거나 스크롤바가 없으면 스크롤 불가
    if(!pChild || !m_pScrollBar) return false;
    
    
    
    // 터치 영역 확인
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    
    CCSize size = this->getContentSize();
    
    CCRect r = CCRectMake(0, 0, size.width, size.height);
    if(!r.containsPoint(touchPoint)) return false;
    
    if (!m_pScrollTouch)
        m_pScrollTouch = pTouch;
    else
        return false;
    
    
    m_touchPoint = touchPoint;
    
    m_iState = kClippingScrollNodeStateIdle;
    
    // 자식 노드의 포지션 저장
    pChild->stopAllActions();
    m_startChildPos = pChild->getPosition();
    
    
    return true;
}

void AceClippingScrollNode::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pScrollTouch != pTouch)
        return;
    
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    
    // If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
    // Of course only if we not already in sliding mode
    
    float fValue = 0;
    if(scrollDir == SCROLL_DIR_UP_DOWN)
    {
        fValue = touchPoint.y - m_touchPoint.y;
    }
    else
    {
        fValue = touchPoint.x - m_touchPoint.x;
    }
    
    //if ((m_iState != kClippingScrollNodeStateSliding) && (fabsf(touchPoint.y - m_touchPoint.y) >= m_fMinimumTouchLengthToSlide))
    
    
//    CCLog("m_iState = %d", m_iState);
//    CCLog("fValue = %f", fValue);
//    CCLog("fabsf(fValue) = %f", fabsf(fValue));
//    CCLog("m_fMinimumTouchLengthToSlide = %f", m_fMinimumTouchLengthToSlide);
    
    if ((m_iState != kClippingScrollNodeStateSliding) && (fabsf(fValue) >= m_fMinimumTouchLengthToSlide))
    {
        m_iState = kClippingScrollNodeStateSliding;
        
        // Avoid jerk after state change.
        m_touchPoint = touchPoint;
        
        // 자식 노드의 포지션 저장
        m_startChildPos = getScrollChild()->getPosition();
        
        // scrollbar
        
        if(m_pScrollBar && m_bScrollBarVisible/* && scrollDir == SCROLL_DIR_UP_DOWN*/)
            m_pScrollBar->show();
        
        
        if (m_bStealTouches)
            cancelAndStoleTouch(pTouch, pEvent);
        
    }
    
    if (m_iState == kClippingScrollNodeStateSliding)
    {
        CCNode *pChild = getScrollChild();
        
        CCPoint moveDistance = ccpSub(touchPoint, m_touchPoint);
        m_touchPoint = touchPoint;
        
        //moveDistance.x = 0;
        if( getCheckScrollLimit() && !checkScrollRange( moveDistance.x ) ) return;
        
        float resistance = getResistance(pChild);
        
//        CCLog("resistance = %f", resistance);
//        CCLog("[0] moveDistance.x = %f", moveDistance.x);
//        CCLog("[0] moveDistance.y = %f", moveDistance.y);
        moveDistance = ccpMult(moveDistance, resistance);
        
        if(scrollDir == SCROLL_DIR_UP_DOWN)
        {
            moveDistance.x = 0;
        }
        else
        {
            moveDistance.y = 0;
        }
        
//        CCLog("[1] moveDistance.x = %f", moveDistance.x);
//        CCLog("[1] moveDistance.y = %f", moveDistance.y);
        
        m_scrollDistance = moveDistance;
        
        pChild->setPosition(ccpAdd(pChild->getPosition(), moveDistance));
        //CCLog("ChildPositionX = %f, Y = %f", pChild->getPositionX(), pChild->getPositionY());
    }
    
    if (m_pTarget && m_pCallback) {
        (m_pTarget->*(m_pCallback))();
    }
}

void AceClippingScrollNode::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
    if(m_pScrollTouch != pTouch)
        return;
    
    m_pScrollTouch = NULL;
    
    if(m_iState == kClippingScrollNodeStateSliding) {
        this->schedule(schedule_selector(AceClippingScrollNode::deaccelerateScrolling));
        
    } else {
        onScrollFinished();
    }
}

void AceClippingScrollNode::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
    // Do not cancel touch, if this method is called from cancelAndStoleTouch:
    if (m_bStealingTouchInProgress)
        return;
    
    
    if (m_pScrollTouch == pTouch)
    {
        // 2013.08.16 by horset
        // m_pScrollTouch가 null이 아니면 다음번 스크롤이 작동을 안함
        // 정상적인 상황에서는 ccTouchCancelled가 호출이 안되나 가끔 스크롤이 멈추는 경우가 있어서 NULL값 세팅이 누락된것이 의심스러워 일단 추가함
        m_pScrollTouch = NULL;
        
        onScrollFinished();
    }
}

CCNode* AceClippingScrollNode::getScrollChild()
{
    CCNode* scrollChildNode = NULL;
    int childrenCnt = this->getChildrenCount();
    if(childrenCnt > 0)
    {
        scrollChildNode = (CCNode*)this->getChildren()->objectAtIndex(0);
    }
    return scrollChildNode;
    
    /*
    AceClippingScrollNode* scrollChildNode = NULL;
    CCObject* scrollObejct = NULL;
    CCARRAY_FOREACH(this->getChildren(), scrollObejct) {
        scrollChildNode = (AceClippingScrollNode*)scrollObejct;
        break;
    }
    return scrollChildNode;
     */
//    return getChildByTag(CLIPPING_SCROLL_NODE_CONTENT_TAG);
}

void AceClippingScrollNode::createScrollBar(CCNode *pChild)
{
    
    float ratio;
    float size;
    float paddingSize = 2;
    
    if (scrollDir == SCROLL_DIR_UP_DOWN)
    {
        ratio = getContentSize().height / pChild->getContentSize().height;
        size = roundf(getContentSize().height * ratio);
    }
    else
    {
        ratio = getContentSize().width / pChild->getContentSize().width;
        size = roundf(getContentSize().width * ratio);
    }
    
    m_pScrollBar = AceScrollBar::node(size, scrollDir);
    CCPoint barPos(0,0);
    
    if (scrollDir == SCROLL_DIR_UP_DOWN)
    {
        barPos = ccp(getContentSize().width - m_pScrollBar->getContentSize().width - paddingSize, getContentSize().height);
    }
    else
    {
        barPos = ccp(0, m_pScrollBar->getContentSize().height + paddingSize);
    }
    
    
    m_pScrollBar->setPosition(barPos);
    this->addChild(m_pScrollBar);
    
    if(m_bScrollBarVisible) {
        if(m_bInitScrollBarVisible) {
            m_pScrollBar->setVisible(true);
            m_pScrollBar->hide();
        } else {
            m_pScrollBar->setVisible(false);
        }
    } else {
        m_pScrollBar->setVisible(false);
    }
     
}

//void AceClippingScrollNode::setScrollChild(CCNode *pNode, bool isScrollable)
//{
//    this->removeAllChildrenWithCleanup(true);
//    
//    m_pScrollBar = NULL;
//    
//    // 계산의 편의성을 위하여 anchor를 좌상단으로 잡고 초기 위치 설정
//    /* //원본
//    pNode->setAnchorPoint(ccp(0, 1));
//    pNode->setPosition(ccp(0, getContentSize().height));
//     */
//    if (scrollDir == SCROLL_DIR_UP_DOWN)
//    {
//        pNode->setAnchorPoint(ccp(pNode->getAnchorPoint().x, 1));
//        pNode->setPosition(ccp(_resetPositionLock ? 0 : pNode->getPosition().x, getContentSize().height));
//    }
//    else
//    {
//        pNode->setAnchorPoint(ccp(1, pNode->getAnchorPoint().y));
//        pNode->setPosition(ccp(getContentSize().width, _resetPositionLock ? getContentSize().height : pNode->getPosition().y));
//    }
//    
//    this->addChild(pNode, 0, CLIPPING_SCROLL_NODE_CONTENT_TAG);
//    
//    if(!isScrollable) return;
//    
//    createScrollBar(pNode);
//    
//}

void AceClippingScrollNode::setScrollChildPos(CCPoint pos)
{
    CCNode *pChild = getScrollChild();
    if(!pChild) return;
    
    pChild->setPosition(pos);
    onScrollFinished();
}

void AceClippingScrollNode::setScrollChildBottom()
{
    CCNode *pChild = getScrollChild();
    if(!pChild) return;
    
    float height = getContentSize().height > pChild->getContentSize().height ? getContentSize().height : pChild->getContentSize().height;
    
    
    if(pChild->getPosition().y <= height) return;
    
    /* //원본
    pChild->setPosition(ccp(0, height));
     */
    pChild->setPosition(ccp(pChild->getPosition().x, height));
    
    onScrollFinished();
}

void AceClippingScrollNode::reset()
{
    
    if(m_pScrollBar) {
        this->removeChild(m_pScrollBar, true);
        m_pScrollBar = NULL;
    }
    
    
    CCNode *pChild = getScrollChild();
    if(!pChild) return;
    
    // 기존 액션 정지
    this->unschedule(schedule_selector(AceClippingScrollNode::deaccelerateScrolling));
    pChild->stopAllActions();
    
    if(bMaxContentSizeW)
    {
        //원본
        
        pChild->setAnchorPoint(ccp(0, 1));
        pChild->setPosition(ccp(0, getContentSize().height));
        
    }
    else
    {
        //요렇게 한이유는 클리핑노드안에 그리드를 사이즈 제한 걸어서 배치할경우 좌표가 틀어지는 현상이 있어서 다시 원본으로 원복시켰다...
//        pChild->setAnchorPoint(ccp(pChild->getAnchorPoint().x, 1));
//        pChild->setPosition(ccp( getResetPositionZero() ? 0 : pChild->getPosition().x, getContentSize().height));
        
        if (scrollDir == SCROLL_DIR_UP_DOWN)
        {
            pChild->setAnchorPoint(ccp(pChild->getAnchorPoint().x, 1));
            pChild->setPosition(ccp(pChild->getPosition().x, getContentSize().height));
        }
        else
        {
            if (_resetPositionLock)
            {
                pChild->setAnchorPoint(ccp(0, pChild->getAnchorPoint().y));
                pChild->setPosition(ccp(0, pChild->getPosition().y));
            }
            else
            {
                pChild->setAnchorPoint(ccp(pChild->getAnchorPoint().x, 1));
                pChild->setPosition(ccp( pChild->getPosition().x, getContentSize().height));
            }
        }
    }
    
    // 세로 스크롤시
    if(scrollDir == SCROLL_DIR_UP_DOWN)
    {
        // 스크롤 높이보다 스크롤 하위의 높이가 적다면 스크롤 적용안되게 수정
        // 스크롤 바도 안보이게
        if(this->getContentSize().height >= pChild->getContentSize().height)
        {
            this->setTouchEnabled(false);
        }
        else
        {
            this->setTouchEnabled(true);
            
            createScrollBar(pChild);
        }
    }
    else
    {
        if(this->getContentSize().width >= pChild->getContentSize().width)
        {
            this->setTouchEnabled(false);
        }
        else
        {
            this->setTouchEnabled(true);
            
            createScrollBar(pChild);
        }
    }
}

void AceClippingScrollNode::resetScrollBar()
{
    if(m_pScrollBar) {
        this->removeChild(m_pScrollBar, true);
        m_pScrollBar = NULL;
    }
    
    CCNode *pChild = getScrollChild();
    if(!pChild) return;
    
    createScrollBar(pChild);
}

void AceClippingScrollNode::onScrollFinished()
{
    
    CCNode *pChild = getScrollChild();
    CCPoint pos = pChild->getPosition();
    //CCLog("ChildPositionX = %f, Y = %f", pChild->getPositionX(), pChild->getPositionY());
    
    CCAction *pAction = NULL;
    /*
    if(pos.y < getContentSize().height) {
        pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(0, getContentSize().height)));
        
    } else {
        float height = getContentSize().height > pChild->getContentSize().height ? getContentSize().height : pChild->getContentSize().height;
        if(pos.y > height)
            pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(0, height)));
    }
     */
    
    if(scrollDir == SCROLL_DIR_UP_DOWN)
    {
        if(pos.y < getContentSize().height) {
            /* //원본
            pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(0, getContentSize().height)));
            */
            pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(pChild->getPositionX(), getContentSize().height)));
        } else {
            float height = getContentSize().height > pChild->getContentSize().height ? getContentSize().height : pChild->getContentSize().height;
            if(pos.y > height)
            {
                /* //원본
                pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(0, height)));
                 */
                
                pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(pChild->getPositionX(), height)));
                
                // [sj] 스크롤이 끝 부분일 때 콜백 호출 - 현재 페이스북 친구 초대에서 목록 더보여주기를 위해 추가
                if(m_pEndScrollTarget && m_pEndScrollCallback)
                {
                    (m_pEndScrollTarget->*m_pEndScrollCallback)();
                }
            }
        }
    }
    else
    {
        //return;
        
        if(pos.x > 0) {
            pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(0, pChild->getPositionY())));
            
        } else {
//            float width = getContentSize().width > pChild->getContentSize().width ? getContentSize().width : pChild->getContentSize().width;
//            CCLog("scroll touch end : %f %f %f", pos.x, pChild->getContentSize().width, getContentSize().width);
//            if(pChild->getContentSize().width >= getContentSize().width) {
            /*
                pChild->getContentSize().width 스크롤 안 child 영역
                getContentSize().width 는 전체 영역
            */
            
            // 스크롤 영역보다 하위의 영역이 작을 시, 스크롤 후 왼쪽으로 맞춤
            if(pChild->getContentSize().width < getContentSize().width)
            {
                pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(0, pChild->getPositionY())));
            }
            else
            {
                if(pos.x + pChild->getContentSize().width < getContentSize().width)
                {
                    pAction = CCEaseExponentialOut::create(CCMoveTo::create(m_aniTime, ccp(getContentSize().width - pChild->getContentSize().width, pChild->getPositionY())));
                }
            }
            
            
//            }
        }
    }
    
    if(pAction)
        pChild->runAction(pAction);
    
   
    if(m_pScrollBar)
        m_pScrollBar->hide();
    
    
    
    if (m_pTarget && m_pCallback) {
        (m_pTarget->*(m_pCallback))();
    }

    
}


void AceClippingScrollNode::update(float dt)
{
    
    if(!m_pScrollBar || !m_pScrollBar->isVisible()) return;
    
    CCNode *pChild = getScrollChild();
    
    /*
    float screenHeight = getContentSize().height;
    float contentHeight = pChild->getContentSize().height;
    
    float y = pChild->getPosition().y - screenHeight;
    if(y < 0) y = 0;
    else if(y > contentHeight - screenHeight) y = contentHeight - screenHeight;
     
     CCPoint barPos = m_pScrollBar->getPosition();
     barPos.y = screenHeight - ceilf((screenHeight - m_pScrollBar->getContentSize().height) * (y / (contentHeight - screenHeight)));
     */
    
    
    CCPoint barPos = m_pScrollBar->getPosition();
    if(scrollDir == SCROLL_DIR_UP_DOWN)
    {
        float screenHeight = getContentSize().height;
        float contentHeight = pChild->getContentSize().height;
        
        float y = pChild->getPosition().y - screenHeight;
        if(y < 0) y = 0;
        else if(y > contentHeight - screenHeight) y = contentHeight - screenHeight;
        
        barPos.y = screenHeight - ceilf((screenHeight - m_pScrollBar->getContentSize().height) * (y / (contentHeight - screenHeight)));
    }
    else
    {
        float screenWidth = getContentSize().width;
        float contentWidth = pChild->getContentSize().width;
        
        float x = pChild->getPosition().x;
        if(x < screenWidth - contentWidth) x = screenWidth - contentWidth;
        else if(x > 0) x = 0;
        
        barPos.x = ceilf((screenWidth - m_pScrollBar->getContentSize().width) * (x / (screenWidth - contentWidth)));
    }
    
    m_pScrollBar->setPosition(barPos);
}


void AceClippingScrollNode::deaccelerateScrolling(float dt)
{
    if(m_iState == kClippingScrollNodeStateIdle) {
        // 다시 터치가 되었을 경우 stop
        this->unschedule(schedule_selector(AceClippingScrollNode::deaccelerateScrolling));
        return;
    }
    
    CCNode *pChild = getScrollChild();
    
    float resistance = getResistance(pChild);
    m_scrollDistance = ccpMult(m_scrollDistance, resistance);
    
    if( getCheckScrollLimit() && !checkScrollRange( m_scrollDistance.x ) ) return;
    
    pChild->setPosition(ccpAdd(pChild->getPosition(), m_scrollDistance));
    //CCLog("ChildPositionX = %f, Y = %f", pChild->getPositionX(), pChild->getPositionY());
    
    m_scrollDistance = ccpMult(m_scrollDistance, CLIPPING_SCROLL_NODE_DEACCEL_RATE);
    
    /*
    if(fabsf(m_scrollDistance.y) <= CLIPPING_SCROLL_NODE_DEACCEL_DIST) {
        this->unschedule(schedule_selector(AceClippingScrollNode::deaccelerateScrolling));
        onScrollFinished();
    }
     */
    
    if(scrollDir == SCROLL_DIR_UP_DOWN)
    {
        if(fabsf(m_scrollDistance.y) <= CLIPPING_SCROLL_NODE_DEACCEL_DIST) {
            this->unschedule(schedule_selector(AceClippingScrollNode::deaccelerateScrolling));
            onScrollFinished();
        }
    }
    else
    {
        if(fabsf(m_scrollDistance.x) <= CLIPPING_SCROLL_NODE_DEACCEL_DIST) {
            this->unschedule(schedule_selector(AceClippingScrollNode::deaccelerateScrolling));
            onScrollFinished();
        }
    }
    
    if (m_pTarget && m_pCallback) {
        (m_pTarget->*(m_pCallback))();
    }
}

float AceClippingScrollNode::getResistance(CCNode *pChild)
{
    /*
    float h = getContentSize().height;
    CCPoint childPos = pChild->getPosition();
    
    // 스크롤 영역을 벗어나는 거리가 커질수록 저항값이 커져서 조금만 움직이도록 함
    if(childPos.y < h) {
        return childPos.y / (h * CLIPPING_SCROLL_NODE_RESISTANCE);
    } else if(childPos.y > pChild->getContentSize().height) {
        return (h - (childPos.y - pChild->getContentSize().height)) / (h * CLIPPING_SCROLL_NODE_RESISTANCE);
    }
     */
    
    if(scrollDir == SCROLL_DIR_UP_DOWN)
    {
//        CCLog("~~~~000");
        float h = getContentSize().height;
        CCPoint childPos = pChild->getPosition();
        
        // 스크롤 영역을 벗어나는 거리가 커질수록 저항값이 커져서 조금만 움직이도록 함
        if(childPos.y < h) {
//            CCLog("AAA");
            return childPos.y / (h * CLIPPING_SCROLL_NODE_RESISTANCE);
        } else if(childPos.y > pChild->getContentSize().height) {
//            CCLog("BBB");
            return (h - (childPos.y - pChild->getContentSize().height)) / (h * CLIPPING_SCROLL_NODE_RESISTANCE);
        }
    }
    else
    {
//        CCLog("~~~~111");
        float w = getContentSize().width;
        CCPoint childPos = pChild->getPosition();
        
//        CCLog("w = %f", w);
//        CCLog("childPos.x = %f", childPos.x);
        
        // 스크롤 영역을 벗어나는 거리가 커질수록 저항값이 커져서 조금만 움직이도록 함
        
        if(childPos.x > 0) {
//            CCLog("2222");
            //return childPos.x / (w * CLIPPING_SCROLL_NODE_RESISTANCE);
            return (w) / (w * CLIPPING_SCROLL_NODE_RESISTANCE);
        } else if(childPos.x + pChild->getContentSize().width < w) {
//            CCLog("3333");
            return (w) / (w * CLIPPING_SCROLL_NODE_RESISTANCE);
        }
        
        
    }
    
    return 1;
}

void AceClippingScrollNode::setInitScrollBarVisible(bool bVisible)
{
    m_bInitScrollBarVisible = bVisible;
}

void AceClippingScrollNode::setScrollBarVisible(bool bVisible)
{
    m_bScrollBarVisible = bVisible;
    
    
    if(m_pScrollBar && !m_bScrollBarVisible) {
        m_pScrollBar->setVisible(false);
    }
    
}

void AceClippingScrollNode::setPriority(int priority) {
    this->m_touchPriority = priority;
    this->setTouchPriority(priority);
    //this->registerWithTouchDispatcher();
}
void AceClippingScrollNode::setScrollTouch(CCTouch* pTouch)
{
    m_pScrollTouch = pTouch;
}

CCTouch* AceClippingScrollNode::getScrollTouch()
{
    return m_pScrollTouch;
}

bool AceClippingScrollNode::checkScrollRange(float moveDistanceX)
{
    if( scrollDir == SCROLL_DIR_LEFT_RIGHT )
    {
        CCNode *pChild = getScrollChild();
        if( pChild )
        {
            if( pChild->getPositionX() >= 0 &&
               moveDistanceX >= 0 )
            {
                pChild->setPositionX( 0 );
                return false;
            }
            else if( pChild->getPositionX() <= getContentSize().width - pChild->getContentSize().width &&
                    moveDistanceX <= 0 )
            {
                pChild->setPositionX( getContentSize().width - pChild->getContentSize().width );
                return false;
            }
        }
    }
    
    return true;
}
