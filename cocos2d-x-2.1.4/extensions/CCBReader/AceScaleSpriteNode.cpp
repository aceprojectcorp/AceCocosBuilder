//
//  AceScaleSpriteNode.cpp
//  MLB
//
//  Created by 허정목 on 2014. 7. 30..
//
//

#include "AceScaleSpriteNode.h"

USING_NS_CC_EXT;

void AceScaleSpriteNode::onEnter()
{
    CCNode::onEnter();
    
    resize();
}

void AceScaleSpriteNode::resize()
{
    CCArray* children = this->getChildren();
    int size = children->count();
    for(int i=0; i<size; i++)
    {
        CCSprite* pNode = (CCSprite*)children->objectAtIndex(i);
        
        if(pNode)
        {
            float scaleX = 0;
            float scaleY = 0;
            
            CCSize mySize = this->getContentSize();
            CCSize childSize = pNode->getContentSize();
            
            scaleX = mySize.width / childSize.width;
            scaleY = mySize.height / childSize.height;
            
            pNode->setScaleX(scaleX);
            pNode->setScaleY(scaleY);
        }
    }
}