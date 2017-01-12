//
//  AceFlipActionNode.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 31..
//
//

#ifndef ScrollViewTest_AceFlipActionNode_h
#define ScrollViewTest_AceFlipActionNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceFlipActionNode
//: public cocos2d::CCLayer
: public CCNode
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceFlipActionNode, create);
    
    
    AceFlipActionNode();
    
    
    
    virtual void onEnter();
    virtual void visit();
    
    /*
    virtual bool init();
    void registerWithTouchDispatcher(void);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    */
    
    

public:
    float _fTime;
    
    CCNode* frontNode;
    CCNode* backNode;
    int _nChildCnt;
    bool _bFront;
    
    bool _bLeft;
    bool _bRight;
    
    
    int _nRepeat;
    int _nRemainRepeat;
    bool _bFlipping;
    
    bool m_bDirty;
    CCPoint m_posDirty;
    kmMat4 m_perspectiveMat;
    
    CCOrbitCamera* _pFirstCamera;
    
private:
    // 플립이 끝나면 호출
    CCObject*       pCallTarget;
    SEL_CallFuncO   pCallBackFlip;
    
public:
    void SetCallFuncFlip(CCObject* _pTarget, SEL_CallFuncO _pFunc)
    {
        pCallTarget = _pTarget;
        pCallBackFlip = _pFunc;
    }
    
public:
    void updatePerspectiveMatrix();
    
    void setFlipNode();
    
    void doFrontFlip();
    void doBackFlip();
    void finishedFlip();
    
    void flip();
    bool getFlipping();
    void setFront(const bool isFront, const bool isRefresh = false);
    bool getFront() const { return _bFront; }
private:
    float getAngleX() const;
    float getAngleZ(int type) const;
    float getDeltaAngleZ() const;
    
    bool checkTwoNode() const;
    void setVisibleNode();
    void setFlipping(bool isFlipping);
    
    
public:
    bool m_bHasScroll;
    
    
    
    
};

NS_CC_EXT_END

#endif
