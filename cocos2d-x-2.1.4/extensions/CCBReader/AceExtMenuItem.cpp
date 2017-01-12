//
//  AceExtMenuItem.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#include "AceExtMenuItem.h"
#include "AcePriorityMenu.h"

#include "SimpleAudioEngine.h"

USING_NS_CC_EXT;

void AceExtMenuItem::onEnter()
{
    CCMenuItem::onEnter();
    
    this->am = NULL;
    
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
                setNormalNode(pNode);
                pos++;
            }
            else if(pos == 1)
            {
                setSelectedNode(pNode);
                pos++;
            }
            else if(pos == 2) // 비활성화 버튼 추가
            {
                setDisableNode(pNode);
                pos++;
            }
        }
    }
    
    setEnabled(true);
    //---
    
    //CCLog("menuItem.x = %f", this->getPosition().x);
    //CCLog("menuItem.y = %f", this->getPosition().y);
    //CCLog("menuItem.AnchorX = %f", this->getAnchorPoint().x);
    //CCLog("menuItem.AnchorY = %f", this->getAnchorPoint().y);
    
    /*
    ButtonCallBack* pBtnCallBack = new ButtonCallBack();
    pBtnCallBack->setCallBack(this);
    delete pBtnCallBack;
    */
    
    CCNode* pParent = NULL;
    for(pParent = this->m_pParent; pParent != NULL; pParent = pParent->getParent())
    {
        CCBAnimationManager* childAm = (CCBAnimationManager*)pParent->getUserObject();
        if(childAm != NULL)
        {
            this->am = childAm;
            break;
        }
    }
    
    
    
    
    
    //---tset
    //this->setPosition(m_pNormalNode->getPosition());
    //---
    
//    CCLog("AceExtMenuItem.pos = (%f, %f)", this->getPosition().x, this->getPosition().y);
}



/*
NODE_FACTORY_DEF(ExtMenuItem, extMenuItem)
{
    MenuHandlerPair handler = NodeFactoryUtils::getHandler(xmlNode, pContext);
    
    ExtMenuItem *pMenuItem = ExtMenuItem::create(handler.first, handler.second);
    if(!pMenuItem) return NULL;
    
    string btnId = NodeFactoryUtils::getString(xmlNode, "btnId", pContext);
    pMenuItem->setBtnId(btnId);
    
    string clickEffect = NodeFactoryUtils::getString(xmlNode, "clickEffect", pContext);
    if(!clickEffect.empty()) pMenuItem->setClickEffect(clickEffect);
    
    return pMenuItem;
}

CHILDREN_HANDLER_DEF(ExtMenuItem, extMenuItem)
{
    ExtMenuItem *pMenuItem = (ExtMenuItem*)pParent;
    
    if(children.size()) {
        pMenuItem->setNormalNode(children[0]);
    }
    
    if(children.size() > 1) {
        pMenuItem->setSelectedNode(children[1]);
    }
}
 */

bool AceExtMenuItem::init()
{
    
    m_pNormalNode = NULL;
    m_pSelectedNode = NULL;
    m_pDisableNode = NULL;
    
    bDisable = false;
    
    return true;
}

bool AceExtMenuItem::init(CCObject* target, SEL_MenuHandler selector)
{
    if(!CCMenuItem::initWithTarget(target, selector)) return false;
    
    m_pNormalNode = NULL;
    m_pSelectedNode = NULL;
    m_pDisableNode = NULL;
    
    bDisable = false;
    
    return true;
}

AceExtMenuItem* AceExtMenuItem::create(CCObject* target, SEL_MenuHandler selector)
{
    AceExtMenuItem *pNode = new AceExtMenuItem();
    if(pNode && pNode->initWithTarget(target, selector)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceExtMenuItem::setNormalNode(CCNode *pNode)
{
    /*
    if(m_pNormalNode)
        this->removeChild(m_pNormalNode, true);
    */
    
    m_pNormalNode = pNode;
    
//    CCLog("AceExtMenuItem.setNormalNode.pos = (%f, %f)", m_pNormalNode->getPosition().x, m_pNormalNode->getPosition().y);
    
    //this->addChild(pNode);
    
    //m_pNormalNode->setAnchorPoint(ccp(0, 0));
    //m_pNormalNode->setPosition(ccp(0, 0));
    
    m_pNormalNode->setVisible(!m_bSelected);
}

void AceExtMenuItem::setSelectedNode(CCNode *pNode)
{
    /*
    if(m_pSelectedNode)
        this->removeChild(m_pSelectedNode, true);
    */
    
    m_pSelectedNode = pNode;
    //this->addChild(pNode);
    
    //m_pSelectedNode->setAnchorPoint(ccp(0, 0));
    //m_pSelectedNode->setPosition(ccp(0, 0));
    
    m_pSelectedNode->setVisible(m_bSelected);
}


void AceExtMenuItem::setDisableNode(CCNode* pNode)
{
    m_pDisableNode = pNode;
    bDisable = false;
    m_pDisableNode->setVisible(bDisable);
    
}


void AceExtMenuItem::selected()
{
    CCMenuItem::selected();
    
    if(!bDisable)
    {
        if (!m_bMyMode)
        {
            if (m_pSelectedNode)
            {
                m_pNormalNode->setVisible(false);
                m_pSelectedNode->setVisible(true);
                
                if(m_pDisableNode)
                {
                    m_pDisableNode->setVisible(false);
                }
                
                
                /* jambam 주석
                 if(am != NULL)
                 {
                 //am->runAnimationsForSequenceNamed("SELECT");
                 
                 CCLog("am->getSequences()->count() = %d", am->getSequences()->count());
                 
                 if(am->getSequences()->count() > 1)
                 {
                 am->runAnimationsForSequenceIdTweenDuration(1, 0);
                 }
                 
                 }
                 */
            }
        }
        else
        {
            if (m_pMyModeTarget && m_pMySelectedFunc)
            {
                (m_pMyModeTarget->*(m_pMySelectedFunc))(m_pNormalNode);
            }
        }
    }
}

void AceExtMenuItem::unselected()
{
    CCMenuItem::unselected();
    
    if(!bDisable)
    {
        if (!m_bMyMode)
        {
            if (m_pSelectedNode)
            {
                m_pNormalNode->setVisible(true);
                m_pSelectedNode->setVisible(false);
                
                if(m_pDisableNode)
                {
                    m_pDisableNode->setVisible(false);
                }
            }
        }
        else
        {
            if (m_pMyModeTarget && m_pMyUnSelectedFunc)
            {
                (m_pMyModeTarget->*(m_pMyUnSelectedFunc))(m_pNormalNode);
            }
        }
    }
}

// [sj] 버튼 비활성화시
void AceExtMenuItem::disableBtn(bool bRadioBtn)
{    
    if(m_pDisableNode)
    {
        bDisable = true;
        
        AcePriorityMenu* pMenu = (AcePriorityMenu*)this->getParent();
        if(!bRadioBtn) pMenu->setTouchEnabled(false);
        
        m_pNormalNode->setVisible(false);
        m_pSelectedNode->setVisible(false);
        m_pDisableNode->setVisible(true);
    }
}

void AceExtMenuItem::ableBtn()
{
    if(m_pDisableNode)
    {
        bDisable = false;
        
        AcePriorityMenu* pMenu = (AcePriorityMenu*)this->getParent();
        pMenu->setTouchEnabled(true);
        
        m_pNormalNode->setVisible(true);
        m_pSelectedNode->setVisible(false);
        m_pDisableNode->setVisible(false);
    }
}

void AceExtMenuItem::activate()
{
    if( !m_clickEffect.empty() && !CCUserDefault::sharedUserDefault()->getBoolForKey( SOUND_PLAYER_UTILS_EFFECT_DISABLED ) )
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( m_clickEffect.c_str() );
    
    
    if(m_btnId.length()) {
        //MsgManager::getInstance()->publish(BtnClickMsg(this, m_btnId));
    } else {
        if(m_pListener && m_pfnSelector) {
            (m_pListener->*m_pfnSelector)(this);
        }
    }
    
}

/*
CCBAnimationManager* AceExtMenuItem::getAnimationManager()
{
    return this->am;
}

void AceExtMenuItem::setAnimationManager(CCBAnimationManager* am)
{
    this->am = am;
}
*/
