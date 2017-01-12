//
//  AceMultiNode.cpp
//  MLB
//
//  Created by 허정목 on 2014. 8. 11..
//
//

#include "AceMultiNode.h"

USING_NS_CC_EXT;

void AceMultiNode::onEnter()
{
    CCNode::onEnter();
    
    if(this->bMaxContentSizeW)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.width > maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
            
            this->setContentSize(mySize);
        }
    }
    
    if(this->bMaxContentSizeH)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.height > maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
            
            this->setContentSize(mySize);
        }
    }
    
    /*
    CCArray* tmpChildren = this->getChildren();
    int size = tmpChildren->count();
    if(size > 2)
    {
        CCNode* pNode;
        CCPoint tmpPos;
        CCPoint tmpAnch;
        
        //첫번째 오브젝트는 왼쪽으로 붙인다.
        pNode = (CCNode*)tmpChildren->objectAtIndex(0);
        tmpAnch = pNode->getAnchorPoint();
        tmpAnch.x = 0;
        pNode->setAnchorPoint(tmpAnch);
        tmpPos = pNode->getPosition();
        tmpPos.x = 0;
        pNode->setPosition(tmpPos);
        
        //두번째 오브젝트는 오른쪽으로 붙인다.
        pNode = (CCNode*)tmpChildren->objectAtIndex(1);
        tmpAnch = pNode->getAnchorPoint();
        tmpAnch.x = 1;
        pNode->setAnchorPoint(tmpAnch);
        tmpPos = pNode->getPosition();
        tmpPos.x = 0;
        pNode->setPosition(tmpPos);
    }
    */
    
    
    
    // 자식 노드들 위치 조정
    CCObject* pObject;
    CCPoint tmpPos;
    CCPoint tmpAnch;
    int i = 0;
    CCARRAY_FOREACH(getChildren(), pObject) {
        CCNode *pNode = static_cast<CCNode*>(pObject);
        if(!pNode) continue;
        
        //첫번째 오브젝트는 왼쪽으로 붙인다.
        if(i == 0)
        {
            tmpAnch = pNode->getAnchorPoint();
//            CCLog("[0] tmpAnch = %f, %f", tmpAnch.x, tmpAnch.y);
//            tmpAnch.x = 0;
//            pNode->setAnchorPoint(tmpAnch);
            tmpPos = pNode->getPosition();
//            CCLog("[0] tmpPos = %f, %f", tmpPos.x, tmpPos.y);
//            tmpPos.x = 0;
//            pNode->setPosition(tmpPos);
        }
        //두번째 오브젝트는 오른쪽으로 붙인다.
        else
        {
            tmpAnch = pNode->getAnchorPoint();
//            CCLog("[1] tmpAnch = %f, %f", tmpAnch.x, tmpAnch.y);
//            tmpAnch.x = 1;
//            pNode->setAnchorPoint(tmpAnch);
            tmpPos = pNode->getPosition();
//            CCLog("[1] tmpPos = %f, %f", tmpPos.x, tmpPos.y);
            tmpPos.x = this->getContentSize().width;
            pNode->setPosition(tmpPos);
        }
        
        i++;
    }
    
//    CCLog("[2] tmpAnch = %f, %f", this->getAnchorPoint().x, this->getAnchorPoint().y);
//    CCLog("[2] tmpPos = %f, %f", this->getPosition().x, this->getPosition().y);
}

