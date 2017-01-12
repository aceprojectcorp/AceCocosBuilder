//
//  AceClippingNode.h
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#ifndef AceCoverPageScroll_h
#define AceCoverPageScroll_h

#include "cocos2d.h"
#include "cocos-ext.h"


#include "Ace3DMath/ZVector.h"
#include "Ace3DMath/ZMatrix.h"

using namespace std;

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


typedef struct tUnits
{
    CCNode* _pNode;
    float _fOldScaleX;
    float _fOldScaleY;
    
    zvec _vPosition;
    float _fScale;
    int   _iOpacity;
    float _fZ;
    float _fA;
}Units;

//class AceCoverPageScroll : public cocos2d::CCNode
class AceCoverPageScroll : public cocos2d::CCLayer
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceCoverPageScroll, create);
    
    AceCoverPageScroll();
    ~AceCoverPageScroll();
    
private:
    //NODE_FACTORY_DEC(ClippingNode);
    
    CCNode *_pStartMoveCallbackTarget;
    SEL_CallFunc _startMoveCallback;
    
    CCNode *_pCallbackTarget;
    SEL_CallFuncO _callbackO;
    
    CCNode *_pOpacityTarget;
    SEL_CallFuncO _opacityCallbackO;
    
    bool _bIsMoving;
    bool _bDrag;
    bool _bScrolling;
    
public:

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    virtual void draw();
    
    void registerWithTouchDispatcher(void);
    // default implements are used to call script callback if exist
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    // default implements are used to call script callback if exist
//    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
//    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
//    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    //터치 추가 작업----------------------
    float m_fMinimumTouchLengthToSlide;
    int m_iState;
    CCPoint m_touchPoint;
    void claimTouch(CCTouch* pTouch);
    void cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent);
    //--------------------------------

    void setPriority(int priority);
    int m_touchPriority; //jambam 추가
    
    void setStartMoveCallback(CCNode *pTarget, SEL_CallFunc callback);
    void setCallback(CCNode *pTarget, SEL_CallFuncO callbackO);
    bool getIsMoving() const { return _bIsMoving; }
    bool getIsDrag() const { return _bDrag; }
    bool getScrolling() const { return _bScrolling; }
    
    void setOpacityCallbackO(CCNode* pTarget, SEL_CallFuncO callbackO);
public:
    void Init();
    void Start();
    void Draw(float delta);
    void SetChildrenOpacity(CCNode *pNode, int v);
public:
    
    int FrontCur();
    
    vector<Units> m_vecArray;

    
    CCArray *m_pNodeArray;
    
    int m_iChildCnt;
    int m_iNowCur;
    int m_iMaxCur;
    float m_fLocationAngle;
    float m_fAngleAtPress;
    float m_fAngleOne;
    float m_fLowZ;
    float m_fLocationMove;
    
    float m_fAngle;
    float m_fLen;
    int   m_iDefaultCur;
    float m_fMaxSize;
    float m_fMinSize;
    float m_fScrollSpeed;
    float m_fAngleToMove;
    bool  m_bLoop;
    bool  m_bAutoScroll;
    float m_fAutoScrollSpeed;
    
    float m_fMinAlpha;
    
    CCPoint outVec;
    
    int m_iShowCnt;
    int m_iNeedMinCnt;
    
    int m_iOldShowCnt;
    
    float m_fMoveY;
    
    void (*CallBack_IsChanged)(int);
    void SetCallBack_IsChanged(void (*CallBack_IsChanged)(int ));
    
    bool m_bPress;
    bool m_bStartMove;
    bool m_bPlus;
    
    
    int m_nextCur;
    
    bool m_bFirst;
    bool m_bFirst2;
};

NS_CC_EXT_END

#endif
