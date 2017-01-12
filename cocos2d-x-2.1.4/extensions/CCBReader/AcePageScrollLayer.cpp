//
//  AcePageScrollLayer.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#include "AcePageScrollLayer.h"

USING_NS_CC_EXT;

enum {
    kScrollLayerStateIdle = 10,
    kScrollLayerStateSliding
};


bool AcePageScrollLayer::isStateIdle()
{
    return m_iState == kScrollLayerStateIdle;
}


void AcePageScrollLayer::onEnter()
{
    CCLayer::onEnter();
    
    if (!m_pageSize.width && !m_pageSize.height)
    {
        m_pageSize = this->getContentSize();
    }
    
//    setTouchEnabled(true);
    startPosX = this->getPosition().x;
    startPosY = this->getPosition().y;
    this->setTouchPriority(m_touchPriority);
    //updatePages();
    //this->setTouchPriority(-400);
    
    
    //---test
    CCArray* tmpChildren = this->getChildren();
    if (tmpChildren) {
        CCNode* child;
        for(int i=0; i<tmpChildren->count(); i++)
        {
            child = dynamic_cast<CCNode*>(tmpChildren->objectAtIndex(i));
            if(child != NULL)
            {
                addPage(child);
            }
        }
    }
    
    //---
}


AcePageScrollLayer::AcePageScrollLayer()
: m_pDelegate(NULL), m_pLayers(NULL), m_bStealingTouchInProgress(false), m_pScrollTouch(NULL), m_iState(kScrollLayerStateIdle), pCallTarget(NULL), pCallBackScroll(NULL), m_pageSize(CCSizeZero)
{
    // nothing
}

AcePageScrollLayer::~AcePageScrollLayer()
{
    CC_SAFE_RELEASE(m_pLayers);
    m_pDelegate = NULL;
    pCallTarget = NULL;
    pCallBackScroll = NULL;
    _pEndCallBack = NULL;
}

AcePageScrollLayer* AcePageScrollLayer::layer()
{
    AcePageScrollLayer *pLayer = new AcePageScrollLayer();
    if(pLayer && pLayer->init()) {
        pLayer->autorelease();
        return pLayer;
    }
    
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool AcePageScrollLayer::init()
{
    if(!CCLayer::init()) return false;
    
    m_touchPriority = kCCMenuHandlerPriority - 1;
    
    setTouchEnabled(true);
    
    m_bStealTouches = true;
    
    // Set default minimum touch length to scroll.
    m_fMinimumTouchLengthToSlide = 30.0f;
    m_fMinimumTouchLengthToChangePage = 100.0f;
    
    m_fMarginOffset = CCDirector::sharedDirector()->getWinSize().width;
    
    // Set up the starting variables
    m_uCurrentScreen = 0;
    
    // 페이지를 담을 array생성 retain을 안해주면 autoleased된 상태이기 때문에 삭제되기 때문에 꼭 retain 해주고 destructor에서 release해줌
    m_pLayers = CCArray::createWithCapacity(5);
    m_pLayers->retain();
    
    m_checkParent = false;
    
    m_bEdgeMoveStop = true;
    
    
    return true;
}

void AcePageScrollLayer::updatePages()
{
    // Loop through the array and add the screens if needed.
    int i = 0;
    CCSize contentSize(0, this->getContentSize().height);
    CCObject* object = NULL;
    CCARRAY_FOREACH(m_pLayers, object)
    {
        CCNode* node = (CCNode*)object;
        //layer->setAnchorPoint(ccp(0,0));
        
        node->setPosition(ccp(i * m_pageSize.width, node->getPositionY()));
        
        contentSize.width += m_pageSize.width;
        
        if (!node->getParent())
            addChild(node);
        i++;
    }
    
    this->setContentSize(contentSize);
    
    if (!m_bEdgeMoveStop)
    {
        setTouchEnabled(true);
    }
    else
    {
        if (getChildrenCount() > 1)
        {
            setTouchEnabled(true);
        }
        else
        {
            setTouchEnabled(false);
        }
    }
    
}

void AcePageScrollLayer::addPage(CCNode *pNode)
{
    // CCArray의 경우 addObject할 때 retain 됨
    m_pLayers->addObject(pNode);
    
    updatePages();
}

void AcePageScrollLayer::removeAll()
{
    m_pLayers->removeAllObjects();
    
    this->removeAllChildrenWithCleanup(true);
    
    //    updatePages();
    
    //    selectPage(0);
    //    setPosition(CCPointZero);
    m_uCurrentScreen = 0;
    
    m_pScrollTouch = NULL;
    m_iState = kScrollLayerStateIdle;
    m_fStartSwipe = 0;
}

CCNode* AcePageScrollLayer::getCurrentChild()
{
    if ( 0 < getChildrenCount() &&
         m_uCurrentScreen < getChildrenCount() )
    {
        return (CCNode*)getChildren()->objectAtIndex(m_uCurrentScreen);
    }
    
    return NULL;
}

unsigned int AcePageScrollLayer::getTotalScreens() const
{
    return m_pLayers->count();
}

unsigned int AcePageScrollLayer::pageNumberForPosition(const CCPoint& position)
{
    float pageFloat = - this->getPosition().x / (m_pageSize.width);
    int pageNumber = (int)ceilf(pageFloat);
    if ((float)pageNumber - pageFloat  >= 0.5f)
        pageNumber--;
    
    pageNumber = MAX(0, pageNumber);
    pageNumber = MIN((int)m_pLayers->count() - 1, pageNumber);
    
    return (unsigned int)pageNumber;
}

void AcePageScrollLayer::moveToPageEnded()
{
    if(m_pDelegate)
        m_pDelegate->scrollLayerScrolledToPageNumber(this, m_uCurrentScreen);
    
    if(m_iState == kScrollLayerStateSliding)
    {
        m_iState = kScrollLayerStateIdle;
    }
    
    if( pCallTarget && _pEndCallBack )
    {
        ( pCallTarget->*_pEndCallBack )();
    }
}

CCPoint AcePageScrollLayer::positionForPageWithNumber(unsigned int pageNumber)
{
    //return ccp(pageNumber * -1.f * this->getContentSize().width, 0.0f);
    return ccp(startPosX + pageNumber * -1.f * m_pageSize.width, this->getPosition().y);
}

void AcePageScrollLayer::moveToPage(unsigned int pageNumber, int direction)
{
    if (pageNumber >= m_pLayers->count())
    {
        CCLOGERROR("CCScrollLayer::moveToPage: %d - wrong page number, out of bounds.", pageNumber);
        return;
    }
    
    CCAction *changePage = CCSequence::createWithTwoActions(CCMoveTo::create(0.3f, positionForPageWithNumber(pageNumber)), CCCallFunc::create(this, callfunc_selector(AcePageScrollLayer::moveToPageEnded)));
    
    
    runAction(changePage);
    m_uCurrentScreen = pageNumber;
    
    if (pCallTarget && pCallBackScroll) {
        CCArray* pArray = CCArray::create();
        pArray->addObject(this);
        pArray->addObject(CCInteger::create(direction));
        
        (pCallTarget->*(pCallBackScroll))(pArray);
    }
}

void AcePageScrollLayer::selectPage(unsigned int pageNumber)
{
    if (pageNumber >= m_pLayers->count())
    {
        CCLOGERROR("CCScrollLayer::selectPage: %d - wrong page number, out of bounds.", pageNumber);
        return;
    }
    
    setPosition(positionForPageWithNumber(pageNumber));
    m_uCurrentScreen = pageNumber;
    
}

void AcePageScrollLayer::registerWithTouchDispatcher()
{
    // ccmenu 보다 먼저 터치 이벤트를 받음
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, false);
}

void AcePageScrollLayer::claimTouch(CCTouch* pTouch)
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

void AcePageScrollLayer::cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent)
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

void AcePageScrollLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
//    CCLog("AcePageScrollLayer.ccTouchesBegan~~~$$");
}

bool AcePageScrollLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
    
    CCNode *pParent = NULL;
    for (pParent = this->m_pParent; pParent != NULL; pParent = pParent->getParent())
    {
        if (pParent->isVisible() == false)
        {
            return false;
        }
        
        if(m_checkParent) {
            CCPoint local = pParent->convertToNodeSpace(touchPoint);
            CCSize size = pParent->getContentSize();
            
            CCRect r = CCRectMake(0, 0, size.width, size.height);
            
            if(!r.containsPoint(local)) return false;
        }
    }
    
    if (!m_pScrollTouch)
        m_pScrollTouch = pTouch;
    else
        return false;
    
    m_fStartSwipe = touchPoint.x;
    m_iState = kScrollLayerStateIdle;
    
    return true;
}

void AcePageScrollLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pScrollTouch != pTouch)
        return;
    
    CCPoint touchPoint = pTouch->getLocation();
    
    float desiredX = (m_uCurrentScreen * -1.f * (m_pageSize.width)) + touchPoint.x - m_fStartSwipe;
    unsigned int page = pageNumberForPosition(ccp(desiredX, 0));
    float offset = desiredX - positionForPageWithNumber(page).x;
    
    // 처음 / 마지막 페이지에서 더 이상 스크롤 안되게 적용
    if (m_bEdgeMoveStop)
    {
        if( ( page == 0 && offset > 0 ) || ( page == m_pLayers->count() - 1 && offset < 0 ) )
        {
            setPosition(ccp(startPosX + desiredX - offset, this->getPosition().y));
            return;
        }
    }
    
    // If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
    // Of course only if we not already in sliding mode
    if ((m_iState != kScrollLayerStateSliding)
        && (fabsf(touchPoint.x - m_fStartSwipe) >= m_fMinimumTouchLengthToSlide))
    {
        m_iState = kScrollLayerStateSliding;
        
        // Avoid jerk after state change.
        m_fStartSwipe = touchPoint.x;
        
        // 맨처음 들어오는 터치 x는 touchPoint.x - m_fStartSwipe이고 그이후부터 터치가 시작되므로
        // 아래와 같이 desiredX를 초기화 해줌
        desiredX = (m_uCurrentScreen * -1.f * (m_pageSize.width));
        
        if (m_bStealTouches)
            cancelAndStoleTouch(pTouch, pEvent);
        
        if (m_pDelegate)
            m_pDelegate->scrollLayerScrollingStarted(this);
    }
    
    if (m_iState == kScrollLayerStateSliding)
    {
//        float desiredX = (m_uCurrentScreen * -1.f * (m_pageSize.width)) + touchPoint.x - m_fStartSwipe;
//        unsigned int page = pageNumberForPosition(ccp(desiredX, 0));
//        float offset = desiredX - positionForPageWithNumber(page).x;
        
        if ((page == 0 && offset > 0) || (page == m_pLayers->count() - 1 && offset < 0))
        {
            offset -= m_fMarginOffset * (offset / CCDirector::sharedDirector()->getWinSize().width);
            //offset -= m_fMarginOffset * (offset / this->getContentSize().width);
        }
        else
        {
            offset = 0;
        }
        //setPosition(ccp(desiredX - offset, 0);
        setPosition(ccp(startPosX + desiredX - offset, this->getPosition().y));
    }
}

void AcePageScrollLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pScrollTouch != pTouch)
        return;
    
    m_pScrollTouch = NULL;
    
    if(m_iState == kScrollLayerStateSliding) {
        
        int direction = 0;
        
        CCPoint touchPoint = pTouch->getLocation();
        
        unsigned int selectedPage = m_uCurrentScreen;
        float delta = touchPoint.x - m_fStartSwipe;
        if (fabs(delta) >= m_fMinimumTouchLengthToChangePage)
        {
            selectedPage = pageNumberForPosition(this->getPosition());
            if (selectedPage == m_uCurrentScreen)
            {
                if (delta < 0.f)
                {
                    direction = 1;
                    
                    if (selectedPage < m_pLayers->count() - 1)
                        selectedPage++;
                }
                else if (delta > 0.f)
                {
                    direction = -1;
                    
                    if (selectedPage > 0)
                        selectedPage--;
                }
            }
        }
        moveToPage(selectedPage, direction);
    }
}

void AcePageScrollLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    // Do not cancel touch, if this method is called from cancelAndStoleTouch:
    if (m_bStealingTouchInProgress)
        return;
    
    if (m_pScrollTouch == pTouch)
    {
        m_pScrollTouch = NULL;
        selectPage(m_uCurrentScreen);
    }
}

CCNode* AcePageScrollLayer::nodeForTouch(CCTouch *touch)
{
    CCPoint touchLocation = touch->getLocation();
    
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = static_cast<CCNode*>(pObject);
            if (pChild && pChild->isVisible())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                
                CCSize size = pChild->getContentSize();
                
                //CCRect r = CCRectMake(0, 0, size.width, size.height);
                CCRect r = CCRectMake(pChild->getPosition().x, pChild->getPosition().y, size.width, size.height);
                
                if(r.containsPoint(local))
                    return pChild;
            }
        }
        
    }
    
    return NULL;
    
}