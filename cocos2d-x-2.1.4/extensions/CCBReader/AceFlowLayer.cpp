//
//  AceFlowLayer.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#include "AceFlowLayer.h"

USING_NS_CC_EXT;

void AceFlowLayer::onEnter()
{
    CCNode::onEnter();
    
    refresh();
}

/*
NODE_FACTORY_DEF(FlowLayer, flowLayer)
{
    float uiScale = AppContext::sharedContext()->getUIScale();
    
    float paddingTop = NodeFactoryUtils::getFloat(xmlNode, "paddingTop", 0, pContext) * uiScale;
    float paddingLeft = NodeFactoryUtils::getFloat(xmlNode, "paddingLeft", 0, pContext) * uiScale;
    float gapY = NodeFactoryUtils::getFloat(xmlNode, "gapY", 0, pContext) * uiScale;
    
    FlowLayer *pLayer = FlowLayer::create(CCPoint(paddingLeft, paddingTop), gapY);
    return pLayer;
}
*/

/*
CHILDREN_HANDLER_DEF(FlowLayer, flowLayer)
{
    CCArray *pArray = NodeFactoryUtils::convertVectorToCCArray(children);
    if(!pArray) return;
    
    ((FlowLayer*)pParent)->addNodes(pArray);
}
 */

bool AceFlowLayer::init()
{
    m_align = COMPOSITE_LABEL_ALIGN_CENTER;
    m_padding = CCPointMake(0, 0);
    m_gap = 0;
    return true;
}

bool AceFlowLayer::init(CCPoint padding, float gap)
{
    m_align = COMPOSITE_LABEL_ALIGN_CENTER;
    m_padding = padding;
    m_gap = gap;
    return true;
}

AceFlowLayer* AceFlowLayer::create(CCPoint padding, float gap)
{
    AceFlowLayer *pNode = new AceFlowLayer();
    if(pNode && pNode->init(padding, gap)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}


void AceFlowLayer::addNodes(CCArray *pArray)
{
    if(!pArray || !pArray->count()) return;
    
    CCObject *pObject;
    CCARRAY_FOREACH(pArray, pObject)
    {
        CCNode *pNode = static_cast<CCNode*>(pObject);
        if(!pNode) continue;
        
        addChild(pNode);
    }
    
    refresh();
}

void AceFlowLayer::refresh()
{
    CCSize size = calculateSize(getChildren());
    setContentSize(size);
    
    float x = m_padding.x;
    float y = size.height - m_padding.y;
    CCObject *pObject;
    CCARRAY_FOREACH(getChildren(), pObject)
    {
        CCNode *pNode = static_cast<CCNode*>(pObject);
        if(!pNode) continue;
        
        pNode->setAnchorPoint(ccp(0, 1));
        
        switch(m_align) {
            case COMPOSITE_LABEL_ALIGN_LEFT :
                break;
            case COMPOSITE_LABEL_ALIGN_CENTER :
                x = this->getContentSize().width * 0.5 - pNode->getContentSize().width * 0.5;
                break;
            case COMPOSITE_LABEL_ALIGN_RIGHT :
                x = this->getContentSize().width - m_padding.x - pNode->getContentSize().width;
                break;
        }
        
        pNode->setPosition(ccp(x, y));
        
        y -= pNode->getContentSize().height + m_gap;
    }
}

CCSize AceFlowLayer::calculateSize(CCArray *pArray)
{
    float width = getContentSize().width;
    float height = m_padding.y * 2;
    
    CCObject* pObject;
    CCARRAY_FOREACH(pArray, pObject) {
        CCNode *pNode = static_cast<CCNode*>(pObject);
        if(!pNode) continue;
        
        height += pNode->getContentSize().height + m_gap;
    }
    
    height -= m_gap;
    
    return CCSize(width, height);
}
