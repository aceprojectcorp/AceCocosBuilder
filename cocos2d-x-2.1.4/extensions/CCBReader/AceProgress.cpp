//
//  AceProgress.cpp
//  MLB
//
//  Created by 승재 한 on 2014. 7. 21..
//
//

#include "AceProgress.h"


bool AceProgress::init() {
    if(!CCNode::init()) return false;
    
    progressTimer = NULL;
    
    return true;
}

void AceProgress::onEnter() {
    CCNode::onEnter();
    
    progressCallBackFunc = NULL;
    
//    CCArray* childArray = this->getChildren();
//    CCObject* childObject = NULL;
//    CCSprite* progressSprite = NULL;
//    CCARRAY_FOREACH(childArray, childObject) {
//        progressSprite = (CCSprite*)childObject;
//        progressSprite->setVisible(false);
//        break;
//    }
//    
//    if(progressSprite != NULL) {
//        progressTimer = CCProgressTimer::create(progressSprite);
//        progressTimer->setType(kCCProgressTimerTypeBar);
//        progressTimer->setPercentage(0.f);
//        progressTimer->setMidpoint(startPosition == START_LEFT ? ccp(0, 1) : ccp(1, 0));
//        progressTimer->setBarChangeRate(ccp(1, 0));
//        this->addChild(progressTimer);
//    }
    
    
//    if(!progressTimer)
    {
        CCArray* childArray = this->getChildren();
        CCObject* childObject = NULL;
        CCSprite* progressSprite = NULL;
        CCARRAY_FOREACH(childArray, childObject) {
            progressSprite = (CCSprite*)childObject;
            progressSprite->setVisible(false);
            break;
        }
        
        if(progressSprite != NULL) {
            progressTimer = CCProgressTimer::create(progressSprite);
            
            progressTimer->setType(progressType);
            progressTimer->setPercentage(0.f);
            
            if (progressType == kCCProgressTimerTypeBar)
            {
                progressTimer->setMidpoint(startPosition == START_LEFT ? ccp(0, 1) : ccp(1, 0));
                progressTimer->setBarChangeRate(ccp(1, 0));
            }
            
            this->addChild(progressTimer);
        }
    }
}

void AceProgress::playProgress() {
//    CCArray* childArray = this->getChildren();
//    CCObject* childObject = NULL;
//    CCSprite* progressSprite = NULL;
//    CCARRAY_FOREACH(childArray, childObject) {
//        progressSprite = (CCSprite*)childObject;
//        progressSprite->setVisible(false);
//        break;
//    }
//    
//    if(progressSprite != NULL) {
//        progressTimer = CCProgressTimer::create(progressSprite);
//        progressTimer->setType(kCCProgressTimerTypeBar);
//        progressTimer->setPercentage(0.f);
//        progressTimer->setMidpoint(startPosition == START_LEFT ? ccp(0, 1) : ccp(1, 0));
//        progressTimer->setBarChangeRate(ccp(1, 0));
//        this->addChild(progressTimer);
//    }
    CCProgressFromTo* progressFromTo = CCProgressFromTo::create(this->progressTime, this->beginValue, this->lastValue);
    CCSequence* progressSequence = CCSequence::create(progressFromTo, progressCallBackFunc, NULL);
    progressTimer->runAction(progressSequence);
}

void AceProgress::setCallback(SEL_CallFunc selector, CCObject *target, const char *callback) {
    if(strcmp(this->progressCallback.c_str(), callback) == 0) {
        progressCallBackFunc = CCCallFunc::create(target, selector);
    }
}