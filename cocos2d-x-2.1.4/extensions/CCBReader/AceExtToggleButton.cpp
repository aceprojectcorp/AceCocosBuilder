//
//  AceExtToggleButton.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#include "AcePriorityMenu.h"
#include "AceExtToggleButton.h"

#include "SimpleAudioEngine.h"

USING_NS_CC_EXT;

void AceExtToggleButton::onEnter()
{
    CCMenuItem::onEnter();
    
    
    //---test
    
    /*
     if(strcmp(m_normalName->getCString(), "NULL") != 0)
     {
     CCNodeLoaderLibrary* nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
     cocos2d::extension::CCBReader* reader = new cocos2d::extension::CCBReader(nodeLoaderLibrary);
     CCNode* node = reader->readNodeGraphFromFile(m_normalName->getCString());
     reader->release();
     
     setNormalNode(node);
     }
     
     if(strcmp(m_selectedName->getCString(), "NULL") != 0)
     {
     CCNodeLoaderLibrary* nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
     cocos2d::extension::CCBReader* reader = new cocos2d::extension::CCBReader(nodeLoaderLibrary);
     CCNode* node = reader->readNodeGraphFromFile(m_selectedName->getCString());
     reader->release();
     
     setSelectedNode(node);
     }
     */
    
    /*
     CCObject* child;
     CCArray* children=getChildren();
     CCARRAY_FOREACH(children, child)
     {
     CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
     if (pNode)
     {
     pNode->setOpacityModifyRGB(bOpacityModifyRGB);
     }
     }
     */
    
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
                setOffNode(pNode);
                pos++;
            }
            else if(pos == 1)
            {
                setOnNode(pNode);
                pos++;
            }
        }
    }
    
    setEnabled(true);
    //---
 
    
    setOn(bSelected);
}

/*
NODE_FACTORY_DEF(ExtToggleButton, extToggleButton)
{
    MenuHandlerPair handler = NodeFactoryUtils::getHandler(xmlNode, pContext);
    
    ExtToggleButton *pButton = ExtToggleButton::create(handler.first, handler.second);
    if(!pButton) return NULL;
    
    string clickEffect = NodeFactoryUtils::getString(xmlNode, "clickEffect", pContext);
    if(!clickEffect.empty()) pButton->setClickEffect(clickEffect);
    
    bool selected = NodeFactoryUtils::getBool(xmlNode, "selected", false, pContext);
    pButton->setOn(selected);
    
    return pButton;
}
 

CHILDREN_HANDLER_DEF(ExtToggleButton, extToggleButton)
{
    ExtToggleButton *pButton = static_cast<ExtToggleButton*>(pParent);
    
    if(children.size()) {
        pButton->setOffNode(children[0]);
    }
    
    if(children.size() > 1) {
        pButton->setOnNode(children[1]);
    }
}
 */

bool AceExtToggleButton::init()
{
    
    m_pOffNode = NULL;
    m_pOnNode = NULL;
    
    return true;
}

bool AceExtToggleButton::init(CCObject *pTarget, SEL_MenuHandler selector)
{
    if(!CCMenuItem::initWithTarget(pTarget, selector)) return false;
    
    m_pOffNode = NULL;
    m_pOnNode = NULL;
    
    return true;
}

AceExtToggleButton* AceExtToggleButton::create(CCObject *pTarget, SEL_MenuHandler selector)
{
    AceExtToggleButton *pNode = new AceExtToggleButton();
    if(pNode && pNode->init(pTarget, selector)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceExtToggleButton::setOffNode(CCNode *pNode)
{
    /*
    if(m_pOffNode) {
        this->removeChild(m_pOffNode, true);
        m_pOffNode = NULL;
    }
     */
    
    if(!pNode) return;
    
    m_pOffNode = pNode;
    //this->addChild(pNode);
    
    //m_pOffNode->setAnchorPoint(ccp(0, 0));
    //m_pOffNode->setPosition(ccp(0, 0));
    
    m_pOffNode->setVisible(!m_bOn);
}

void AceExtToggleButton::setOnNode(CCNode *pNode)
{
    /*
    if(m_pOnNode) {
        this->removeChild(m_pOnNode, true);
        m_pOnNode = NULL;
    }
    */
    
    if(!pNode) return;
    
    m_pOnNode = pNode;
    //this->addChild(pNode);
    
    //m_pOnNode->setAnchorPoint(ccp(0, 0));
    //m_pOnNode->setPosition(ccp(0, 0));
    
    m_pOnNode->setVisible(m_bOn);
}

void AceExtToggleButton::activate()
{
    m_bOn = !m_bOn;
    
    if(m_pOffNode) m_pOffNode->setVisible(!m_bOn);
    if(m_pOnNode) m_pOnNode->setVisible(m_bOn);
    
    if( !m_clickEffect.empty() && !CCUserDefault::sharedUserDefault()->getBoolForKey( SOUND_PLAYER_UTILS_EFFECT_DISABLED ) )
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( m_clickEffect.c_str() );

    
    CCMenuItem::activate();
}

void AceExtToggleButton::setOn(bool bOn)
{
    if(m_bOn == bOn) return;
    
    m_bOn = bOn;
    
    if(m_pOffNode) m_pOffNode->setVisible(!m_bOn);
    if(m_pOnNode) m_pOnNode->setVisible(m_bOn);
}

bool AceExtToggleButton::isOn()
{
    return m_bOn;
}