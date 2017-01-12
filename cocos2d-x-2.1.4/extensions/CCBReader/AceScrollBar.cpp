//
//  AceScrollBar.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 2..
//
//

#include "AceScrollBar.h"
#include "AceClippingScrollNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SCROLL_BAR_ROUND_SIZE     4
#define SCROLL_BAR_HIDE_SPEED       1

bool AceScrollBar::init(float fSize, int mode)
{
    //float roundHeight = SCROLL_BAR_ROUND_HEIGHT * AppContext::sharedContext()->getUIScale();
    float roundSize = SCROLL_BAR_ROUND_SIZE;
    
    if(fSize < roundSize * 2)
        fSize = roundSize * 2;
    
    //common/scrollbar.png
    //"leelibs/barV.png"
    const char scrollbarPath[64] = "common/scrollbar.png";
    CCSprite *pSprite = CCSprite::create(scrollbarPath);
    CCSize imgSize = pSprite->getContentSize();
    
    if (mode == SCROLL_DIR_UP_DOWN)
    {
        this->setContentSize(CCSize(imgSize.width, fSize));
        this->setAnchorPoint(ccp(0, 1));
        
        // head
        pSprite = CCSprite::create(scrollbarPath, CCRect(0, 0, imgSize.width, roundSize));
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(ccp(0, fSize - roundSize));
        this->addChild(pSprite);
        
        // body
        pSprite = CCSprite::create(scrollbarPath, CCRect(0, roundSize, imgSize.width, fSize - roundSize * 2));
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(ccp(0, roundSize));
        this->addChild(pSprite);
        
        // tail
        pSprite = CCSprite::create(scrollbarPath, CCRect(0, imgSize.height - roundSize, imgSize.width, roundSize));
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(ccp(0, 0));
        this->addChild(pSprite);
    }
    else
    {
        this->setContentSize(CCSize(fSize, imgSize.width));
        this->setAnchorPoint(ccp(0, 0));
        
        // head
        pSprite = CCSprite::create(scrollbarPath, CCRect(0, 0, imgSize.width, roundSize));
        pSprite->setRotation(90);
        pSprite->setAnchorPoint(ccp(1, 0));
        pSprite->setPosition(ccp(0, 0));
        this->addChild(pSprite);
        
        // body
        pSprite = CCSprite::create(scrollbarPath, CCRect(0, roundSize, imgSize.width, fSize - roundSize * 2));
        pSprite->setRotation(90);
        pSprite->setAnchorPoint(ccp(1, 0));
        pSprite->setPosition(ccp(roundSize, 0));
        this->addChild(pSprite);
        
        // tail
        pSprite = CCSprite::create(scrollbarPath, CCRect(0, imgSize.height - roundSize, imgSize.width, roundSize));
        pSprite->setRotation(90);
        pSprite->setAnchorPoint(ccp(1, 0));
        pSprite->setPosition(ccp(fSize - roundSize, 0));
        this->addChild(pSprite);
    }
    
    return true;
}

AceScrollBar* AceScrollBar::node(float fSize, int mode)
{
    AceScrollBar *pNode = new AceScrollBar();
    if(pNode && pNode->init(fSize, mode)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceScrollBar::setOpacity(GLubyte opacity)
{
    CCObject *pObj;
    CCARRAY_FOREACH(getChildren(), pObj) {
        CCRGBAProtocol *pNode = dynamic_cast<CCRGBAProtocol*>(pObj);
        if(!pNode) continue;
        
        pNode->setOpacity(opacity);
    }
}

void AceScrollBar::setOpacityModifyRGB(bool bValue)
{
    CC_UNUSED_PARAM(bValue);
}

void AceScrollBar::show()
{
    this->stopAllActions();
    setOpacity(255);
    setVisible(true);
}

void AceScrollBar::hide()
{
    this->stopAllActions();
    this->runAction(CCSequence::createWithTwoActions(CCEaseExponentialIn::create(CCFadeOut::create(SCROLL_BAR_HIDE_SPEED)), CCHide::create()));
}