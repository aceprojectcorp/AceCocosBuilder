//
//  AceExtMenu.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#include "AceExtMenu.h"

USING_NS_CC_EXT;

void AceExtMenu::onEnter()
{
    CCMenu::onEnter();
    
    
}

/*
NODE_FACTORY_DEF(ExtMenu, extMenu)
{
    ExtMenu *pMenu = ExtMenu::menu();
    if(!pMenu) return NULL;
    
    bool visible = NodeFactoryUtils::getBool(xmlNode, "visible", true, pContext);
    pMenu->setVisible(visible);
    
    return pMenu;
}
 */

bool AceExtMenu::init()
{
    if(!CCMenu::init()) return false;
    
    //this->setPosition(CCPointZero);
    //this->setAnchorPoint(CCPointZero);
    
    return true;
}

AceExtMenu* AceExtMenu::menu()
{
    AceExtMenu *pMenu = new AceExtMenu();
    if(pMenu && pMenu->init()) {
        pMenu->autorelease();
        return pMenu;
    }
    
    CC_SAFE_DELETE(pMenu);
    return NULL;
}

// CCMenu의 itemForTouch 메소드는 menuItem의 rect를 비교할때 항상 origin을 zero로 비교 하기 때문에 해당 부분을 없앰
CCMenuItem* AceExtMenu::itemForTouch(CCTouch * touch)
{
    /*
    CCPoint touchLocation = touch->getLocation();
    
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild && pChild->isVisible() && ((HighlightButton*)pChild)->isEnabled())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                CCRect r = ((HighlightButton*)pChild)->getTouchRect();
                
                if(r.containsPoint(local))
                    return (CCMenuItem*)pChild;
            }
        }
        
    }
     */
    
    return NULL;
}

bool AceExtMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    if (m_eState != kCCMenuStateWaiting || ! m_bVisible)
    {
        return false;
    }
    
    for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    m_pSelectedItem = this->itemForTouch(touch);
    if (m_pSelectedItem)
    {
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        return true;
    }
    return false;
}

void AceExtMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    CCMenuItem *currentItem = this->itemForTouch(touch);
    if (currentItem != m_pSelectedItem)
    {
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
}