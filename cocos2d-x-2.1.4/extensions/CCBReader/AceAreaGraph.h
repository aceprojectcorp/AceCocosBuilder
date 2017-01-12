//
//  AceClippingNode.h
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#ifndef AceAreaGraph_h
#define AceAreaGraph_h

#include "cocos2d.h"
#include "cocos-ext.h"






#include "Ace3DMath/ZVector.h"
#include "Ace3DMath/ZMatrix.h"



using namespace std;

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;



//class AceCoverPageScroll : public cocos2d::CCNode
class AceAreaGraph : public cocos2d::CCLayer
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceAreaGraph, create);
    
    AceAreaGraph();
    ~AceAreaGraph();
    
private:
    //NODE_FACTORY_DEC(ClippingNode);
    
protected:

public:

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    virtual void draw();
    
    virtual void registerWithTouchDispatcher(void);
    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    int getSelectedIdx();
    
    void setPriority(int priority);
    int m_touchPriority;
public:
    void Init();
    void Start();
    void Draw(float delta);
    void Reset();
    
    void DrawLine(CCPoint p1, CCPoint p2, ccColor4F col, float w);
    
    
    bool m_bStart;
    
    int m_iHeight;
    int m_iMarginUp;
    int m_iMarginDown;
    
    float m_fSpeed;
    
    int m_iLenPointToPoint;
    int m_iCntPoint;
    
    ccColor3B m_backColor;
    float m_fBackA;
    
    ccColor3B m_lineColor;
    float m_fLineA;
    float m_fLineWidth;
    
    ccColor3B m_pointColor;
    float m_fPointA;
    float m_fPointSize;
    int   m_iPointSegs;
    
    /////////////////////////////////
    
    bool m_bReset;
    
    
    ////////////////////////////////////
    
    
    int m_iMaxValue;
    int m_iMinValue;
    
    
    CCPoint *m_pVertex_s;
    int m_iCntVertex;
    
    int m_idxVertex;
    float m_fNowDrawFlag;
    float m_fNowDrawGraph;
    float m_fMaxDrawFlag;
    float m_fSeta;
    
    
    /////////////////////////////////
    vector<float > m_vecData;
    
    //////////////////////
    
    int m_iSelectedPointIdx;
    
    /////////////////////
    
    void (*CallBack_ClickPoint)(int, float, float);//클릭했을 경우
    void (*CallBack_Drawing)(int, float, float);//그리고 있을 경우
    
    void SetCallBack_ClickPoint(void (*CallBack_ClickPoint)(int, float, float)); // 그래프를 클릭하면 가까운 점에 대한 콜백함수(선택 인덱스, x좌표, y좌표)
    void SetCallBack_Drawing(void (*CallBack_Drawing)(int, float, float));// 그래프 연출 동안 호출되는 콜백(인덱스, x좌표, y좌표)
        
    
    vector<float> GetPos_Y(int cnt);
    
    void SetDefaultData(int maxV, int minV, vector<float> data);
};

NS_CC_EXT_END

#endif
