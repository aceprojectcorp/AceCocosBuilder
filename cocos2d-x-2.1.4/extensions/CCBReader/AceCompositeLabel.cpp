//
//  AceCompositeLabel.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#include "AceCompositeLabel.h"

USING_NS_CC_EXT;

void AceCompositeLabel::onEnter()
{
    CCNode::onEnter();
    
    repaint();
}

/*
NODE_FACTORY_DEF(CompositeLabel, compositeLabel)
{
    int align = COMPOSITE_LABEL_ALIGN_CENTER;
    
    string strAlign = NodeFactoryUtils::getString(xmlNode, "halign", pContext);
    if(strAlign == "left") align = COMPOSITE_LABEL_ALIGN_LEFT;
    else if(strAlign == "right") align = COMPOSITE_LABEL_ALIGN_RIGHT;
    
    CompositeLabel *pLabel = CompositeLabel::node(align);
    return pLabel;
}
 */

bool AceCompositeLabel::init()
{
    m_align = COMPOSITE_LABEL_ALIGN_CENTER;
    
    return true;
}

bool AceCompositeLabel::init(int align)
{
    m_align = align;
    
    return true;
}

AceCompositeLabel* AceCompositeLabel::node(int align)
{
    AceCompositeLabel *pNode = new AceCompositeLabel();
    if(pNode && pNode->init(align)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceCompositeLabel::addChild(CCNode * child)
{
    CCNode::addChild(child);
    
    repaint();
}

void AceCompositeLabel::repaint()
{
    // children 위치 계산
    float width = 0;
    CCObject *pObject;
    CCNode *pNode;
    int size = this->getChildrenCount();
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
        pNode = static_cast<CCNode*>(pObject);
        if(pNode)
            width += pNode->getContentSize().width;
    }
    
    width += (m_gapX * (size - 1));
    
    float x = 0;
    switch(m_align) {
        case COMPOSITE_LABEL_ALIGN_LEFT :
            break;
        case COMPOSITE_LABEL_ALIGN_CENTER :
            x = (getContentSize().width - width) * 0.5;
            break;
        case COMPOSITE_LABEL_ALIGN_RIGHT :
            x = (getContentSize().width - width);
            break;
    }
    
    float y = getContentSize().height * 0.5;
    
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
        pNode = static_cast<CCNode*>(pObject);
        if(pNode) {
            pNode->setAnchorPoint(ccp(0, 0.5));
            pNode->setPosition(ccp(x, y));
            
            x += pNode->getContentSize().width + m_gapX;
        }
    }
}