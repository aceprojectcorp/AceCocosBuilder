//
//  AceScale9SpriteNode.cpp
//  MLB
//
//  Created by 허정목 on 2014. 5. 23..
//
//

#include "AceScale9SpriteNode.h"

USING_NS_CC_EXT;

void AceScale9SpriteNode::onEnter()
{
    CCNode::onEnter();
    
    CCArray* children = this->getChildren();
    int size = children->count();
    for(int i=0; i<size; i++)
    {
        CCScale9Sprite* pNode = (CCScale9Sprite*)children->objectAtIndex(i);

        if(pNode)
        {
            pNode->setContentSize(this->getContentSize());
            
        }

    }
    
}