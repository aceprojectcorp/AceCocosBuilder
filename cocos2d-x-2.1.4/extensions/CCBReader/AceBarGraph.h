//
//  AceClippingNode.h
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#ifndef AceBarGraph_h
#define AceBarGraph_h

#include "cocos2d.h"
#include "cocos-ext.h"



#include "Ace3DMath/ZVector.h"
#include "Ace3DMath/ZMatrix.h"



using namespace std;

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;



//class AceCoverPageScroll : public cocos2d::CCNode
class AceBarGraph : public cocos2d::CCLayer
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceBarGraph, create);
    
    AceBarGraph();
    ~AceBarGraph();
    
private:
    //NODE_FACTORY_DEC(ClippingNode);
    
protected:

public:

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    virtual void draw();
    virtual void visit();
    
    virtual void registerWithTouchDispatcher(void);
    // default implements are used to call script callback if exist
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    //int getSelectedIdx();
    
    void setPriority(int priority);
    int m_touchPriority;
    
    CCNode* _pTarget;
    SEL_CallFunc _callback;
public:
    void Init();
    void Start();

    void Reset();
    
    void DrawLine(CCPoint p1, CCPoint p2, ccColor4F col, float w);
    
    
    bool m_bStart;
    /////////////////////////////////////////////////////////
    bool m_bScroll;
    int m_iScrollW;
    bool m_bRight;
    
    int m_iHeight;
    int m_iWidth;
    
    int m_iCenterHeight;
    
    int m_iMargin;
    
    int m_iCntPoint;
    
    
    
    ccColor3B m_backColor;
    float m_fBackA;
    
    ccColor3B m_lineColor;
    float m_fLineA;
    float m_fLineWidth;
    
    ccColor3B m_centerLineColor;
    float m_fCenterLineA;
    float m_fCenterLineWidth;
    
    ccColor3B m_barColor;
    float m_fBarA;
    
    /////////////////////////////////
    int m_iSelectedIdx;
    
    bool m_bReset;
    float m_fSpeed;
    
    bool m_bTouchStart;
    float m_fScrollMoveX;
    float m_fClipX;
    ////////////////////////////////////
    float m_fOneW;
    
    /////////////////////////////////////
    int m_iMaxValue;
    int m_iMinValue;
    
    CCPoint *m_pBackVertex_s;
    CCPoint *m_pLineVertex_s;
    CCPoint *m_pVertex_s;
    int m_iCntVertex;
    
    int m_idxVertex;
    /////////////////////////////////////
    CCPoint GetBarPosition(int idx);
    
    /////////////////////////////////
    vector<int> m_vecData;
    vector<ccColor4F> m_vecColor;
    
    
    void (*m_funSetBarLabel)(AceBarGraph * thiz); //start 시에 호출
    void SetBarLabelFun(void (*f)(AceBarGraph * thiz));
    
    void (*m_funIsChanged)(int oldIdx, int newIdx, AceBarGraph * thiz);
    void SetIsChangedFun(void (*f)(int oldIdx, int newIdx, AceBarGraph * thiz));
    
    
    
    int m_iNowCur;
    //////////////////////
    
    
    void SetDefaultData(int maxV, int minV, vector<int> data);
    void SetBarColor(int idx, float r, float g, float b, float a);
    
    void setIsChanged(CCNode* pTaget, SEL_CallFunc callback);
    
    void NextCur(int idx);
};

NS_CC_EXT_END

#endif
