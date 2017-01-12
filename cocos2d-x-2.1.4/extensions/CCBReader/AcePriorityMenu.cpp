//
//  AcePriorityMenu.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#include "AcePriorityMenu.h"

// 창현 레더메인 버튼을 위해 추가
#include "AceExtRadioButton.h"

USING_NS_CC_EXT;

bool AcePriorityMenu::isTouch = false;


void AcePriorityMenu::onEnter()
{
    CCMenu::onEnter();
    
    
    
//    CCLog("AcePriorityMenu.pos = (%f, %f)", this->getPosition().x, this->getPosition().y);
}

/*
NODE_FACTORY_DEF(PriorityMenu, priorityMenu)
{
    int priority = NodeFactoryUtils::getInt(xmlNode, "priority", kCCMenuHandlerPriority, pContext);
    bool swallowTouches = NodeFactoryUtils::getBool(xmlNode, "swallowTouches", true, pContext);
    
    PriorityMenu *pMenu = PriorityMenu::create(priority, swallowTouches);
    if(!pMenu) return NULL;
    
    pMenu->ignoreAnchorPointForPosition(false);
    
    bool checkParent = NodeFactoryUtils::getBool(xmlNode, "checkParent", false, pContext);
    pMenu->setCheckParent(checkParent);
    
    bool visible = NodeFactoryUtils::getBool(xmlNode, "visible", true, pContext);
    pMenu->setVisible(visible);
    
    return pMenu;
}
*/

bool AcePriorityMenu::init()
{
    if(!CCMenu::init()) return false;
    
    
    
    return true;
}

bool AcePriorityMenu::init(int priority, bool swallowTouches)
{
    m_priority = priority;
    m_swallowTouches = swallowTouches;
    
    if(!CCMenu::init()) return false;
    
    return true;
}

AcePriorityMenu* AcePriorityMenu::create(int priority, bool swallowTouches)
{
    AcePriorityMenu *pMenu = new AcePriorityMenu();
    if(pMenu && pMenu->init(priority, swallowTouches)) {
        pMenu->autorelease();
        return pMenu;
    }
    
    CC_SAFE_DELETE(pMenu);
    return NULL;
}

void AcePriorityMenu::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_priority, m_swallowTouches);
}

bool AcePriorityMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
//    if (isTouch) return false;
    
    // 안드로이드에서 동시에 두개의 터치를 막기 위함
    //    if(AppContext::sharedContext()->isTouching()) return false;
    
    CC_UNUSED_PARAM(event);
    if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !isEnabled())
    {
        return false;
    }
    
    CCPoint touchLocation = touch->getLocation();
    
    CCNode *pParent = NULL;
    for (pParent = this->m_pParent; pParent != NULL; pParent = pParent->getParent())
    {
        if (pParent->isVisible() == false) return false;
        
        if(m_checkParent) {
            CCPoint local = pParent->convertToNodeSpace(touchLocation);
            CCSize size = pParent->getContentSize();
            
            CCRect r = CCRectMake(0, 0, size.width, size.height);
            
            if(!r.containsPoint(local)) return false;
        }
    }
    
    CCMenuItem* currentItem = this->itemForTouch(touch);
    
    if (currentItem)
    {
        AceExtRadioButton *pRadioBtn = dynamic_cast<AceExtRadioButton*>(currentItem);
        if (pRadioBtn)
        {
            m_bRadioTouchMovedLive = true;
            
            if (!pRadioBtn->getRevitalize())
            {
                return false;
            }
            
            CCMenuItem* tempItem = getRadioChildItem();
            if (tempItem)
            {
                tempItem->unselected();
            }
            else
            {
                tempItem = NULL;
            }
            
            m_pOriginItem = tempItem;
        }
        else if (m_bTouchMovedLive && !m_pOriginItem)
        {
            m_pOriginItem = currentItem;
        }
        
        m_pSelectedItem = currentItem;
        
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        
//        isTouch = true;
        //        AppContext::sharedContext()->setTouching(true);
        return true;
    }
    return false;
}

void AcePriorityMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
//    CCLog("AAAAAAAA");
//    CCMenu::ccTouchEnded(touch, event);
    
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
    
    m_eState = kCCMenuStateWaiting;
//    isTouch = false;
    
    if (m_pSelectedItem)
    {
        if (m_pOriginItem)
        {
            if (m_bTouchMovedLive)
            {
                m_pOriginItem = m_pSelectedItem;
            }
            else if (m_pOriginItem == m_pSelectedItem)
            {
                m_pOriginItem = NULL;
                if (m_bRadioTouchMovedLive && m_bRadioNotDoubleTouch)
                {
                    return;
                }
            }
        }   
        
        m_pSelectedItem->unselected();
        
        AceExtRadioButton* pRadioBtn = dynamic_cast<AceExtRadioButton*>(m_pSelectedItem);
        if (pRadioBtn)
        {
            pRadioBtn->activate(true);
        }
        else
        {
            m_pSelectedItem->activate();
        }
    }
    //    AppContext::sharedContext()->setTouching(false);
}

void AcePriorityMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
//    CCLog("BBBBBBB");
    // 창현 - 라디오버튼일때 조건
    // Revitalize가 false로 꺼져있을때 선택불가
    // 영역 바깥으로 갈경우 선택불가
    AceExtRadioButton* pTempCurrent = dynamic_cast<AceExtRadioButton*>(m_pSelectedItem);
    if (pTempCurrent && (!pTempCurrent->getRevitalize() || m_bRadioTouchMovedLive))
    {
        CC_UNUSED_PARAM(touch);
        CC_UNUSED_PARAM(event);
        CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
        m_eState = kCCMenuStateWaiting;
        return;
    }
    else if (m_bTouchMovedLive)
    {
        if ( m_pSelectedItem != m_pOriginItem )
        {
            m_pSelectedItem->unselected();
            m_pSelectedItem = NULL;
        }
        
        ccTouchEnded(touch, event);
        return;
    }
    
    CCMenu::ccTouchCancelled(touch, event);
    
//    isTouch = false;
    //    AppContext::sharedContext()->setTouching(false);
}

void AcePriorityMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
//    CCLog("CCCCCCC");
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    CCMenuItem *currentItem = this->itemForTouch(touch);
    
    
//    isTouch = false;
    
    if (currentItem != m_pSelectedItem)
    {
        // 창현 - 라디오버튼일때 조건
        // Revitalize가 false로 꺼져있을때 선택불가
        // 영역 바깥으로 갈경우 선택불가
        AceExtRadioButton* pTempCurrent = dynamic_cast<AceExtRadioButton*>(currentItem);
        if (pTempCurrent && !pTempCurrent->getRevitalize()) {return;}
        
        if ( currentItem == NULL )
        {
            if (m_bRadioTouchMovedLive || m_bTouchMovedLive)
            {
                return;
            }
        }
        
        if (m_pSelectedItem)
        {
            m_pSelectedItem->unselected();
        }
        
        m_pSelectedItem = currentItem;
        
        if (m_pSelectedItem)
        {
            m_pSelectedItem->selected();
        }
    }
    //    AppContext::sharedContext()->setTouching(false);
}

void AcePriorityMenu::setPriority(int mPriority)
{
    this->m_priority = mPriority;
    this->setTouchPriority(this->m_priority);
}

CCMenuItem* AcePriorityMenu::getRadioChildItem()
{
    CCObject *pObject;
    CCARRAY_FOREACH(this->getChildren(), pObject) {
        AceExtRadioButton *pChild = dynamic_cast<AceExtRadioButton*>(pObject);
        if(pChild && pChild->getRevitalize() && pChild->isSelected())
        {
            return pChild;
        }
    }
    return NULL;
}

void AcePriorityMenu::reset()
{
    m_eState = kCCMenuStateWaiting;
}