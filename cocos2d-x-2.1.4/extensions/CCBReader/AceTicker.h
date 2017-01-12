//
//  AceTicker.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#ifndef ScrollViewTest_AceTicker_h
#define ScrollViewTest_AceTicker_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AceClippingNode.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

#define TICKER_LEFT_START_POS_X         30.f

typedef enum {
    TICKER_DIR_LEFT,
    TICKER_DIR_RIGHT,
    TICKER_DIR_UP,
    TICKER_DIR_DOWN,
} _MoveDir;


class AceTicker
: public AceClippingNode
{
public:
    virtual bool init();
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceTicker, create);
    
private:
    //NODE_FACTORY_DEC(Ticker);    
public:
    _MoveDir moveDir;
    float m_speed;
    float m_stopDelay;
    
    bool m_bFirst;
private:
    bool _bIsStop;
public:
    bool init(float speed, float stopDelay, int mode);
    static AceTicker* create(float speed, float stopDelay, int mode);
    
    void addChild(CCNode *pChild);
protected:
    void update(float dt);
    
    void startTicker();
    bool isMoveEnd(CCNode* pNode, CCPoint pos);
private:
    void restart();
   
};

NS_CC_EXT_END

#endif
