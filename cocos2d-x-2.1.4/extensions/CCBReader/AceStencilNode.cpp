//
//  AceClippingNode.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceStencilNode.h"
#include "AceScaleSpriteNode.h"

USING_NS_CC_EXT;

void AceStencilNode::onEnter()
{
    CCClippingNode::onEnter();

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

bool AceStencilNode::init()
{
    //CocosBuilder에서는 괜찮은데...
    //cocos2d-x에서는 stencil을 미리 생성해놓지 않으면, CCClippingNode의 onEnter()안에 m_pStencil->onEnter()에서 에러가 난다.
    //그래서 미리 생성해두기
    CCClippingNode::init(CCSprite::create());
    
    return true;
}

void AceStencilNode::visit()
{
    CCClippingNode::visit();
    
    makeStencil();
}

AceStencilNode* AceStencilNode::node()
{
    AceStencilNode *pNode = new AceStencilNode();
    if(pNode && pNode->init()) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceStencilNode::makeStencil()
{
    CCArray* children = this->getChildren();
    int size = (int)children->count();
    
    //자식이 있을때만...
    if (size > 0)
    {
        //AceStencilNode의 첫번째 자식을 MaskNode로 사용한다.
        CCNode* pMaskNode = (CCNode*)children->objectAtIndex((int)0);
        
        //stencil로 사용된 node가 AceScaleSpriteNode일 경우
        AceScaleSpriteNode *pScaleSpriteNode = dynamic_cast<AceScaleSpriteNode*>(pMaskNode);
        if (pScaleSpriteNode && pScaleSpriteNode->getChildrenCount())
        {
//            pMaskNode = (CCNode*)pScaleSpriteNode->getChildren()->objectAtIndex(0);
            this->setAlphaThreshold(0);
        }
 
        //stencil로 사용된 node가 CCLayerRGBA를 상속받았으면, 알파 임계값을 1로 주자.
        CCLayerRGBA *pLayerRGBA = dynamic_cast<CCLayerRGBA*>(pMaskNode);
        if (pLayerRGBA)
        {
            //알파 임계값을 설정. (1 ~ 0까지 설정가능. 1 = 100%, 0 = 0%)
            //예: 0으로 설정하면, 알파가 0%(알파값 255)인 부분까지를 경계로 설정.
            //예: 1로 설정하면, 알파가 100%(알파값 0)인 부분까지를 경계로 설정.
            //예: 0.5f로 설정하면, 알파가 50%(알파값 128)인 부분까지를 경계로 설정.
            this->setAlphaThreshold(1);
        }
        
        //stencil로 사용된 node가 CCNodeRGBA를 상속받았으면, 알파 임계값을 0으로 주자.
        CCNodeRGBA *pNodeRGBA = dynamic_cast<CCNodeRGBA*>(pMaskNode);
        if (pNodeRGBA)
        {
            //알파 임계값을 설정. (1 ~ 0까지 설정가능. 1 = 100%, 0 = 0%)
            //예: 0으로 설정하면, 알파가 0%(알파값 255)인 부분까지를 경계로 설정.
            //예: 1로 설정하면, 알파가 100%(알파값 0)인 부분까지를 경계로 설정.
            //예: 0.5f로 설정하면, 알파가 50%(알파값 128)인 부분까지를 경계로 설정.
            this->setAlphaThreshold(0);
        }
        
        
        //현재 셋팅된 스텔실과 다를때만...
        if (pMaskNode != m_pStencil)
        {
            //스텐실 설정
            this->setStencil(pMaskNode);
        }
    }
    
}