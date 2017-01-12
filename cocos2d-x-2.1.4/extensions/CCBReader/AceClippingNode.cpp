//
//  AceClippingNode.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 25..
//
//

#include "AceClippingNode.h"

USING_NS_CC_EXT;

void AceClippingNode::onEnter()
{
    CCClippingNode::onEnter();

    makeStencil();
}

void AceClippingNode::setContentSize(const CCSize & size)
{
    CCClippingNode::setContentSize(size);
    
    makeStencil();
}

/*
NODE_FACTORY_DEF(ClippingNode, clippingNode)
{
    ClippingNode *pClippingNode = ClippingNode::node();
    if(pClippingNode) {
        float widthRatio = NodeFactoryUtils::getFloat(xmlNode, "widthRatio", 1, pContext);
        pClippingNode->setWidthRatio(widthRatio);
    }
    
    return pClippingNode;
}
 */

bool AceClippingNode::init()
{
    CCClippingNode::init(CCDrawNode::create());
    
    m_widthRatio = 1;

    return true;
}

AceClippingNode* AceClippingNode::node()
{
    AceClippingNode *pNode = new AceClippingNode();
    if(pNode && pNode->init()) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceClippingNode::makeStencil()
{
    CCPoint m_ClipRect[4];
    m_ClipRect[0] = ccp(0, 0);
    m_ClipRect[1] = ccp(0, this->getContentSize().height);
    m_ClipRect[2] = ccp(this->getContentSize().width, this->getContentSize().height);
    m_ClipRect[3] = ccp(this->getContentSize().width, 0);
    
    ((CCDrawNode*)m_pStencil)->clear();
    ((CCDrawNode*)m_pStencil)->drawPolygon(m_ClipRect, 4, ccc4f(0, 0, 0, 1), 0, ccc4f(0, 0, 0, 1));

}