//
//  AceSameIntervalNode.cpp
//  MLB
//
//  Created by 허정목 on 2014. 7. 31..
//
//

#include "AceSameIntervalNode.h"

USING_NS_CC_EXT;

void AceSameIntervalNode::onEnter()
{
    CCNode::onEnter();
    
    
    float totalW;
    float itemW;
    int itemCnt;
    int gapCnt;
    float gapW;
    float tmpW;
    
    CCArray* children = this->getChildren();
    
    totalW = this->getContentSize().width;
    itemCnt = children->count();
    
    if(itemCnt > 1)
    {
        CCNode* pNode = (CCNode*)children->objectAtIndex(0);
        gapCnt = itemCnt - 1;
        itemW = pNode->getContentSize().width;
        tmpW = totalW - (itemW * itemCnt);
        gapW = tmpW / gapCnt;
        
        for(int i=0; i<itemCnt; i++)
        {
            pNode = (CCNode*)children->objectAtIndex(i);
            if(pNode)
            {
                CCPoint tmpPos = pNode->getPosition();
                tmpPos.x = itemW * i + gapW * i;
                
                pNode->setPosition(tmpPos);
            }
        }
    }
}