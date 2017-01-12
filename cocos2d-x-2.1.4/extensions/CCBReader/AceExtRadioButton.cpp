//
//  AceExtRadioButton.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#include "AcePriorityMenu.h"
#include "AceExtRadioButton.h"

#include "SimpleAudioEngine.h"

USING_NS_CC_EXT;

AceExtRadioButton::AceExtRadioButton()
: bSelected(false)
, bRevitalize(true)
{
    
}

AceExtRadioButton::~AceExtRadioButton()
{
    
}

void AceExtRadioButton::onEnter()
{
    CCMenuItem::onEnter();
    
    //---test
    CCObject* child;
    CCArray* children = getChildren();
    int pos = 0;
    CCARRAY_FOREACH(children, child)
    {
        CCNode* pNode = dynamic_cast<CCNode*>(child);
        if (pNode != NULL)
        {
            if(pos == 0)
            {
                this->setNormalNode(pNode);
                pos++;
            }
            else if(pos == 1)
            {
                this->setSelectedNode(pNode);
                pos++;
            }
            else if(pos == 2)
            {
                this->setDisableNode(pNode);
                pos++;
            }
        }
    }
    
    setEnabled(true);
    //---
    
    initWithTarget(this, menu_selector(AceExtRadioButton::clkicked));
    
    
    setSelected(bSelected);
}

/*
NODE_FACTORY_DEF(ExtRadioButton, extRadioButton)
{
    MenuHandlerPair handler = NodeFactoryUtils::getHandler(xmlNode, pContext);
    
    ExtRadioButton *pButton = ExtRadioButton::create(handler.first, handler.second);
    if(!pButton) return NULL;
    
    string clickEffect = NodeFactoryUtils::getString(xmlNode, "clickEffect", pContext);
    if(!clickEffect.empty()) pButton->setClickEffect(clickEffect);
    
    bool isSelected = NodeFactoryUtils::getBool(xmlNode, "selected", false, pContext);
    
    pButton->setSelected(isSelected);
    
    return pButton;
}

CHILDREN_HANDLER_DEF(ExtRadioButton, extRadioButton)
{
    ExtRadioButton *pButton = (ExtRadioButton*)pParent;
    
    if(children.size()) {
        pButton->setNormalNode(children[0]);
    }
    
    if(children.size() > 1) {
        pButton->setSelectedNode(children[1]);
    }
}
 */

AceExtRadioButton* AceExtRadioButton::create(CCObject *pTarget, SEL_MenuHandler selector)
{
    AceExtRadioButton *pNode = new AceExtRadioButton();
    if(pNode && pNode->initWithTarget(pTarget, selector)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceExtRadioButton::setSelected(bool isSelected)
{
    if(m_bSelected == isSelected) return;
    
    m_bSelected = isSelected;
    
    if(m_pNormalNode) m_pNormalNode->setVisible(!m_bSelected);
    if(m_pSelectedNode) m_pSelectedNode->setVisible(m_bSelected);
}

void AceExtRadioButton::activate(bool isEffect)
{
    setSelected(true);
    
    CCObject *pObject;
    CCARRAY_FOREACH(this->getParent()->getChildren(), pObject) {
        AceExtRadioButton *pChild = dynamic_cast<AceExtRadioButton*>(pObject);
        
        if(pChild && pChild != this && bRevitalize == true) {
//            CCLog("pChild %d", pChild->getTag());
//            pChild->setVisible(false);
            pChild->unselected();
            pChild->setSelected(false);
        }
    }
    
    if(m_bEnabled)
    {
        if( isEffect && !m_clickEffect.empty() && !CCUserDefault::sharedUserDefault()->getBoolForKey( SOUND_PLAYER_UTILS_EFFECT_DISABLED ) )
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( m_clickEffect.c_str() );
        
        if(m_pListener && m_pfnSelector) {
            (m_pListener->*m_pfnSelector)(this);
        }
    }
}

void AceExtRadioButton::clkicked(CCObject* pSender)
{
//    CCLog("라디오 버튼을 클릭했다...");
}