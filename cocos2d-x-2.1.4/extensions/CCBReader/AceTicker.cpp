//
//  AceTicker.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#include "AceTicker.h"

USING_NS_CC_EXT;

bool AceTicker::init()
{
    if(!AceClippingNode::init()) return false;
    
    moveDir = TICKER_DIR_LEFT;
    m_speed = 0;
    m_stopDelay = 0;
    
    m_bFirst = true;
    
    _bIsStop = false;
    
    return true;
}

void AceTicker::onEnter()
{
    CCNode::onEnter();
    
    _bIsStop = m_stopDelay > 0 ? true : false;
    
    if( moveDir == TICKER_DIR_LEFT )
    {
        CCObject *pObj = NULL;
        CCARRAY_FOREACH(m_pChildren, pObj)
        {
            CCNode *pNode = (CCNode*)pObj;
            if(!pNode) continue;
            
            pNode->setPosition( ccp( TICKER_LEFT_START_POS_X, pNode->getPositionY() ) );
        }
    }
    
    schedule( schedule_selector( AceTicker::update ) );
}

/*
NODE_FACTORY_DEF(Ticker, ticker)
{
    float uiScale = AppContext::sharedContext()->getUIScale();
    
    float speed = NodeFactoryUtils::getFloat(xmlNode, "speed", 0, pContext) * uiScale;
    float stopDelay = NodeFactoryUtils::getFloat(xmlNode, "stopDelay", 0, pContext);
    
    int mode = TICKER_MODE_SHORT;
    string strMode = NodeFactoryUtils::getString(xmlNode, "mode", pContext);
    if(strMode == "FULL") mode = TICKER_MODE_FULL;
    
    Ticker *pTicker = Ticker::create(speed, stopDelay, mode);
    
    return pTicker;
}
 */

bool AceTicker::init(float speed, float stopDelay, int mode)
{
    if(!AceClippingNode::init()) return false;
    
    moveDir = TICKER_DIR_LEFT;
    m_speed = speed;
    m_stopDelay = stopDelay;
    
    m_bFirst = true;
    
    _bIsStop = m_stopDelay > 0 ? true : false;

    return true;
}

AceTicker* AceTicker::create(float speed, float stopDelay, int mode)
{
    AceTicker *pNode = new AceTicker();
    if(pNode && pNode->init(speed, stopDelay, mode)) {
        pNode->autorelease();
        return pNode;
    }
    
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void AceTicker::addChild(CCNode *pChild)
{
    AceClippingNode::addChild(pChild);
    
    if(pChild->getContentSize().width > getContentSize().width) {
        CCFiniteTimeAction *pAction1 = CCDelayTime::create(m_stopDelay);
        CCFiniteTimeAction *pAction2 = CCCallFunc::create(this, callfunc_selector(AceTicker::startTicker));
        
        this->runAction(CCSequence::createWithTwoActions(pAction1, pAction2));
    }
}

void AceTicker::update(float dt)
{
    float dx = m_speed * dt;
    
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
        CCNode *pNode = (CCNode*)pObject;
        if(!pNode) continue;
        
        CCPoint pos = pNode->getPosition();
        
        switch(moveDir)
        {
            case TICKER_DIR_LEFT :
            {
                pos.x -= dx;
                if( pos.x <= TICKER_LEFT_START_POS_X &&
                   _bIsStop &&
                   m_stopDelay > 0 )
                {
                    this->unschedule( schedule_selector( AceTicker::update ) );
                    CCFiniteTimeAction *pAction1 = CCDelayTime::create( m_stopDelay );
                    CCFiniteTimeAction *pAction2 = CCCallFunc::create( this, callfunc_selector( AceTicker::restart ) );
                    this->runAction( CCSequence::create( pAction1, pAction2, NULL ) );

                    continue;
                }
            }
                
                break;
            case TICKER_DIR_RIGHT :
                pos.x += dx;
                break;
            case TICKER_DIR_UP :
                pos.y += dx;
                break;
            case TICKER_DIR_DOWN :
                pos.y -= dx;
                break;
        }
        
        pNode->setPosition(pos);
        
        bool bEnd = isMoveEnd(pNode, pos);
        
        if( bEnd )
        {
            //this->unscheduleUpdate();
            
//            CCLog("m_stopDelay %f", m_stopDelay);
//            CCFiniteTimeAction *pAction1 = CCDelayTime::create(m_stopDelay);
            CCFiniteTimeAction *pAction = CCCallFunc::create(this, callfunc_selector(AceTicker::startTicker));
            this->runAction( pAction );
        }
    }
}

bool AceTicker::isMoveEnd(CCNode* pNode, CCPoint pos)
{
    bool val = false;
    
    switch(moveDir)
    {
        case TICKER_DIR_LEFT :
            if(pos.x + pNode->getContentSize().width < 0) val = true;
            break;
        case TICKER_DIR_RIGHT :
            if(pos.x > this->getContentSize().width) val = true;
            break;
        case TICKER_DIR_UP :
            if(pos.y > this->getContentSize().height) val = true;
            break;
        case TICKER_DIR_DOWN :
            if(pos.y + pNode->getContentSize().height < 0) val = true;
            break;
    }
    
    return val;
}

void AceTicker::startTicker()
{
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(m_pChildren, pObject)
    {
        CCNode *pNode = (CCNode*)pObject;
        if(!pNode) continue;
        
        CCPoint pos = pNode->getPosition();
        
        if(!m_bFirst)
        {
            //pos.x = getContentSize().width;
            switch(moveDir)
            {
                case TICKER_DIR_LEFT :
                    pos.x = this->getContentSize().width;
                    break;
                case TICKER_DIR_RIGHT :
                    pos.x = 0 - pNode->getContentSize().width;
                    break;
                case TICKER_DIR_UP :
                    pos.y = 0 - pNode->getContentSize().height;
                    break;
                case TICKER_DIR_DOWN :
                    pos.y = this->getContentSize().height;
                    break;
            }
        }

        pNode->setPosition(pos);
    }
    
    //scheduleUpdate();
    if( moveDir == TICKER_DIR_LEFT &&
       !m_bFirst )
    {
        _bIsStop = true;
    }
    m_bFirst = false;
}

void AceTicker::restart()
{
    if( moveDir == TICKER_DIR_LEFT )
    {
        _bIsStop = false;
        this->schedule( schedule_selector( AceTicker::update ) );
    }
}

