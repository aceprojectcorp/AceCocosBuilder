//
//  AceFrameAnimation.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#include "AceFrameAnimation.h"

USING_NS_CC_EXT;

void AceFrameAnimation::onEnter()
{
    CCNode::onEnter();
    
    delay = 0;
    prevFrameIdx = -1;
    nowFrameIdx = 0;
    
    bPlay = true;
    
    childReset();
    
    proc(1 / 60.0f);
    
    schedule(schedule_selector(AceFrameAnimation::update));
}

void AceFrameAnimation::update(float dt)
{
    if(!bPlay)return;
    
    proc(dt);
}

void AceFrameAnimation::proc(float dt)
{
    CCArray* children = this->getChildren();
    int size = (int)children->count();
    
    if(delay == 0 && (int)nowFrameIdx < size)
    {
        //prevFrame
        if(prevFrameIdx != -1)
        {
            CCNode* prevNode = dynamic_cast<CCNode*>(children->objectAtIndex(prevFrameIdx));
            prevNode->setVisible(false);
        }
        
        //nowFrame
        CCNode* nowNode = dynamic_cast<CCNode*>(children->objectAtIndex(nowFrameIdx));
        nowNode->setVisible(true);
        
        prevFrameIdx = nowFrameIdx;
        
        nowFrameIdx++;
        if(bLoop)
        {
            if(nowFrameIdx >= size)
            {
                nowFrameIdx = 0;
            }
        }
    }
    
    delay += dt;
    if(delay > 1 / m_fps)
    {
        delay = 0;
    }
}

void AceFrameAnimation::play()
{
    this->bPlay = true;
}

void AceFrameAnimation::stop()
{
    this->bPlay = false;
}

bool AceFrameAnimation::isPlay()
{
    return this->bPlay;
}

void AceFrameAnimation::childReset()
{
    CCArray* children = this->getChildren();
    CCNode* pNode;
    int size = children->count();
    for(int i=0; i<size; i++)
    {
        pNode = dynamic_cast<CCNode*>(children->objectAtIndex(i));
        pNode->setVisible(false);
    }
}