//
//  Ace3DBall.cpp
//  MLB
//
//  Created by 허정목 on 2014. 3. 3..
//
//

#include "Ace3DBall.h"
#include "Ace3DWorld.h"

USING_NS_CC_EXT;

bool Ace3DBall::init()
{
    if(!Ace3DNode::init()) return false;
    
    return true;
}

void Ace3DBall::onEnter()
{
    Ace3DNode::onEnter();
    
    bMoveBallDown = false;
    moveBallZ = MOVEBALL_Z;
}

void Ace3DBall::visit()
{
    CCNode::visit();
    
    kmGLPushMatrix();
    glLineWidth(1);
    
    //---test
    /*
    if(bFoMulSunVisible)
    {
        CCPoint pos_0;
        CCPoint pos_1;
        
        //도착지점까지의 직선 거리 그리기
        ccDrawColor4B(255, 0, 0, 255);
        
        pos_0 = srcPoint;
        pos_1 = dstPoint;
        
        ccDrawLine(pos_0, pos_1);
        
        //도착지점까지의 포물선 그리기
        ccDrawColor4B(255, 255, 0, 255);
        
        std::list<CCPoint>::iterator iter = parabolaPositions.begin();
        while(iter != parabolaPositions.end())
        {
            pos_1.x = (iter)->x;
            pos_1.y = (iter)->y;
            
            ccDrawLine(pos_0, pos_1);
            
            pos_0 = pos_1;
            
            iter++;
        }
    }
     */
    //---
    
    kmGLPopMatrix();
}

void Ace3DBall::createTail()
{
    //---test
    //return;
    //---
    
    //---멀티해상도때문에 추가된 3D월드 좌표 보정
     CCSize designedResolution = CCSize(960, 640);
     CCSize frameSize = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize();
     float fScaleX = (float)frameSize.width / designedResolution.width;
     float fScaleY = (float)frameSize.height / designedResolution.height;
     float ratio;
     if( fScaleX > fScaleY )
     {
         ratio = frameSize.width / designedResolution.width / fScaleY;
         designedResolution.width *= ratio;
     }
     else
     {
         ratio = frameSize.height / designedResolution.height / fScaleX;
         designedResolution.height *= ratio;
     }
     float addWidth = (designedResolution.width - 960) * 0.5;
     float addHeight = (designedResolution.height - 640) * 0.5;
    //---
    
    CCArray* children = this->getChildren();
    int size = (int)children->count();
    
    if(size > 0)
    {
        CCSprite* tmpSpr = (CCSprite*)children->objectAtIndex(0); //sprite
        
        
        
//        CCNode* ccbNode = (CCNode*)children->objectAtIndex(0);
//        CCArray* ccbNodeChildren = ccbNode->getChildren();
//        CCNode* frameAniNode = (CCNode*)ccbNodeChildren->objectAtIndex(0);
//        CCArray* frameAniNodeChildren = frameAniNode->getChildren();
//        CCSprite* pSprite = (CCSprite*)frameAniNodeChildren->objectAtIndex(0);
        
        
        CCTexture2D* tmpTexture = tmpSpr->getTexture();
        CCSprite* copySprite = CCSprite::createWithTexture(tmpTexture);
        copySprite->setAnchorPoint(CCPointMake(0.5f, 0.5f));
        copySprite->setScale(0.7f * scale3D);
        copySprite->setPosition(CCPointMake(m_resultScreen.u + addWidth, m_resultScreen.v + addHeight));
        if(bMoveBallDown)
        {
            this->getParent()->addChild(copySprite, moveBallZ++);
        }
        else
        {
            this->getParent()->addChild(copySprite, moveBallZ--);
        }
        //copySprite->runAction(CCSequence::create(CCFadeOut::create(0.2f), CCCallFuncN::create(this, callfuncN_selector(Ace3DBall::removeTail)), NULL));
        copySprite->runAction(CCSequence::create(CCFadeOut::create(0.2f), CCCallFuncN::create(this, callfuncN_selector(Ace3DBall::removeTail)), NULL));
    }
}

void Ace3DBall::removeTail(cocos2d::CCObject *pSender)
{
    CCSprite *pBallTail = (CCSprite*)pSender;
    pBallTail->removeFromParentAndCleanup(true);
}
