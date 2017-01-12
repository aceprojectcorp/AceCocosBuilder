//
//  AceClippingNode.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceBarGraphLoader.h"


USING_NS_CC_EXT;

USING_NS_CC;

AceBarGraph::AceBarGraph()
{
    m_bStart = false;
    m_bScroll = false;
    m_bTouchStart = false;
    m_bRight = false;
    m_fClipX = 0.0f;
    m_fScrollMoveX = 0.0f;
    m_funSetBarLabel = NULL;
    m_funIsChanged = NULL;
    m_iNowCur = -1;
    
    _pTarget = NULL;
    _callback = NULL;
    
    Init();
    
    m_touchPriority = -129;
   
}
AceBarGraph::~AceBarGraph()
{
    
}

void AceBarGraph_TestFun_SetBarLabel(AceBarGraph *thiz)
{
    for ( int i = 0 ; i < thiz->m_vecData.size() ; i ++ )
    {
        
        CCPoint c = thiz->GetBarPosition(i);
        //CCLog("%f %f --", c.x, c.y);
        c.x += thiz->m_fOneW / 2.0f;
        
        char num[256];
        sprintf(num, "%d" , (int)thiz->m_vecData[i]);
        
        CCLabelTTF *label = CCLabelTTF::create(num, "Helvetica", 15);
        label->setColor(ccc3(255, 255,255));
        if ( thiz->m_vecData[i] > 0 )
        {
            label->setPosition(CCPoint(c.x, thiz->m_iCenterHeight - 20));
        }
        else
        {
            label->setPosition(CCPoint(c.x, thiz->m_iCenterHeight + 20));
        }
        
        thiz->addChild(label);
    }

}
void AceBarGraph_TestFun_IsChanged(int oldIdx, int newIdx, AceBarGraph * thiz)
{
    thiz->SetBarColor(oldIdx, (float)thiz->m_barColor.r , (float)thiz->m_barColor.g , (float)thiz->m_barColor.b , thiz->m_fBarA);
    thiz->SetBarColor(newIdx, (float)1 , (float)1 , (float)1 , (float)1);
}

bool AceBarGraph::init()
{
    this->setTouchEnabled(true);    
    return true;
}
void AceBarGraph::visit()
{
    // glScissor는 월드 좌표계로 설정해야하기 때문에 현재 노드의 위치 및 크기를 변환함
    if ( m_bScroll == true )
    {
        CCPoint pos = this->convertToWorldSpace(CCPointZero);
        CCSize size = getContentSize();
        
        glEnable(GL_SCISSOR_TEST);
        
        // 직접 glScissor를 사용하면 android의 auto scale 모드 때문에 안됨
        CCEGLView::sharedOpenGLView()->setScissorInPoints(pos.x + m_fClipX, pos.y, m_iScrollW, m_iHeight);
        
        CCLayer::visit();
        
        glDisable(GL_SCISSOR_TEST);
    }
    else
    {
        CCLayer::visit();
    }
}



void AceBarGraph::SetDefaultData(int maxV, int minV, vector<int> data)
{
    int cnt = (int)data.size();
    float oneW = (float)m_iWidth / (float)m_iCntPoint;
    m_iWidth = (int)(oneW * cnt);
    
    m_iMaxValue = maxV;
    m_iMinValue = minV;
    
    m_vecData = data;

    m_vecColor.clear();
    
    float r = (float)m_barColor.r / 255.0f;
    float g = (float)m_barColor.g / 255.0f;
    float b = (float)m_barColor.b / 255.0f;
    float a = (float)m_fBarA;
    
    for ( int i = 0 ; i < m_vecData.size() ; i ++ )
    {
        m_vecColor.push_back(ccc4f(r,g,b,a));
    }
}

void AceBarGraph::SetBarLabelFun(void (*f)(AceBarGraph * thiz))
{
    m_funSetBarLabel = f;
}
void AceBarGraph::SetIsChangedFun(void (*f)(int oldIdx, int newIdx, AceBarGraph * thiz))
{
    m_funIsChanged = f;
}

void AceBarGraph::SetBarColor(int idx, float r, float g, float b, float a)
{
    if ( (unsigned int)idx < m_vecColor.size())
    {
        m_vecColor[idx] = ccc4f(r,g,b,a);
    }
}
void AceBarGraph::NextCur(int idx)
{
    float oneW = m_fOneW + m_iMargin;
    m_fScrollMoveX += -idx * oneW;
    
    CCPoint myPos = getPosition();
    myPos.x += m_fScrollMoveX;
    m_fClipX -= m_fScrollMoveX;
    setPosition(myPos);
    
    m_fScrollMoveX = 0.0f;

    
}

void AceBarGraph::setIsChanged(CCNode* pTaget, SEL_CallFunc callback)
{
    _pTarget = pTaget;
    _callback = callback;
}
/*
void TestCallBack_ClickPoint(int idx, float x, float y)
{
    CCLog("TestCallBack_ClickPoint %d %f %f", idx, x, y);
}
void TestCallBack_Drawing(int idx, float x, float y)
{
    CCLog("TestCallBack_Drawing %d %f %f", idx, x, y);
}
 */
void AceBarGraph::onEnter()
{

//   Start();

    
    
    
    CCLayer::onEnter();
    
    

}

void AceBarGraph::onExit()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    
    CCLayer::onExit();
}
void AceBarGraph::setPriority(int priority) {
    this->m_touchPriority = priority;
    this->setTouchPriority(priority);
    //this->registerWithTouchDispatcher();
}

void AceBarGraph::update(float delta)
{
    
}

void AceBarGraph::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    //pDirector->getTouchDispatcher()->addStandardDelegate(this, m_touchPriority);
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority ,false);
}
bool AceBarGraph::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    int touchRectW = m_iWidth;
    
    if ( m_bScroll == true )
    {
        touchRectW = m_iScrollW;
    }
    
    bool bIn = false;
    
    //CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(pTouch);
    
    CCSize mySize = getContentSize();
    CCPoint myAnchor = getAnchorPoint();
    
    mySize.width *= myAnchor.x;
    mySize.height *= myAnchor.y;
    
    CCPoint pp = touch->getLocation();
    CCPoint myPoint = getPosition() - mySize;
    CCPoint objPoint = this->getParent()->convertToWorldSpace( myPoint );
    objPoint.x += m_fClipX;
    
    CCPoint dP = pp - objPoint;
    
    if ( (unsigned int)dP.x < touchRectW && (unsigned int)dP.y < m_iHeight )
    {
        bIn = true;
    }
    if (bIn == true)
    {
        m_bTouchStart = true;
        
    }
    else
    {
        m_bTouchStart = false;
        return false;
        //Reset();
    }

    
    return true;
    
}
void AceBarGraph::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(pTouch);
    
    CCPoint deltaPoint = touch->getDelta();
    if ( m_bScroll == true )
    {
        
        if (m_bTouchStart == true )
        {
            m_fScrollMoveX += deltaPoint.x;
        }
    }
    
    
    return ;
}
void AceBarGraph::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    //CCLog("---ccTouchEnded---");
    
    m_bTouchStart = false;
    
    return ;
}
void AceBarGraph::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    //CCLog("---ccTouchCancelled---");
    
    return ;
}

void AceBarGraph::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    int touchRectW = m_iWidth;
    
    if ( m_bScroll == true )
    {
        touchRectW = m_iScrollW;
    }
    
    bool bIn = false;
    
    CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(*it);
    
    CCPoint pp = touch->getLocation();
    CCPoint myPoint = getPosition();
    CCPoint objPoint = this->getParent()->convertToWorldSpace( myPoint );
    objPoint.x += m_fClipX;
    
    CCPoint dP = pp - objPoint;
    
    if ( (unsigned int)dP.x < touchRectW && (unsigned int)dP.y < m_iHeight )
    {
        bIn = true;
    }
    if (bIn == true)
    {
        m_bTouchStart = true;
        
    }
    else
    {
        m_bTouchStart = false;
        //Reset();
    }

    
}
void AceBarGraph::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(*it);

    CCPoint deltaPoint = touch->getDelta();
    if ( m_bScroll == true )
    {
        
        if (m_bTouchStart == true )
        {
            m_fScrollMoveX += deltaPoint.x;
        }
    }
    
}
void AceBarGraph::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    m_bTouchStart = false;
    // CCLog("---3----");
}
void AceBarGraph::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    // CCLog("---4----");
}


void AceBarGraph::Init()
{
    m_iSelectedIdx = -1;
    m_iCntPoint = 0;
    
    m_pLineVertex_s = NULL;
    m_pBackVertex_s = NULL;
    m_pVertex_s = NULL;
    
    
    m_bReset = false;
    
    
    this->setAnchorPoint(CCPoint(0.5f, 0.5f));
   
}


void AceBarGraph::Start()
{

    if ( m_vecData.size() < 1 )
    {
        ////////////데이터 입력/////////////
        //m_iMaxValue = 100;
        //m_iMinValue = -50;
        
        
        //m_iCenterHeight =  80;
       /*
        vector<int > d;
        d.clear();
        
        d.push_back(70.0f);
        d.push_back(20.0f);
        d.push_back(40.0f);
        d.push_back(60.0f);
        d.push_back(100.0f);
        d.push_back(70.0f);
        d.push_back(50.0f);
        d.push_back(-50.0f);
        d.push_back(0.0f);
        d.push_back(-30.0f);
        d.push_back(-10.0f);
        d.push_back(70.0f);
        d.push_back(20.0f);
        d.push_back(40.0f);
        d.push_back(60.0f);
        d.push_back(100.0f);
        d.push_back(70.0f);
        d.push_back(50.0f);
        d.push_back(-50.0f);
        d.push_back(0.0f);
        d.push_back(-30.0f);
        d.push_back(-10.0f);
        d.push_back(70.0f);
        d.push_back(20.0f);
        d.push_back(40.0f);
        d.push_back(60.0f);
        d.push_back(100.0f);
        d.push_back(70.0f);
        d.push_back(50.0f);
        d.push_back(-50.0f);
        d.push_back(0.0f);
        d.push_back(-30.0f);
        d.push_back(-10.0f);
        d.push_back(70.0f);
        d.push_back(20.0f);
        d.push_back(40.0f);
        d.push_back(60.0f);
        d.push_back(100.0f);
        d.push_back(70.0f);
        d.push_back(50.0f);
        d.push_back(-50.0f);
        d.push_back(0.0f);
        d.push_back(-30.0f);
        d.push_back(-10.0f);
        d.push_back(70.0f);
        d.push_back(20.0f);
        d.push_back(40.0f);
        d.push_back(60.0f);
        d.push_back(100.0f);
        d.push_back(70.0f);
        d.push_back(50.0f);
        d.push_back(-50.0f);
        d.push_back(0.0f);
        d.push_back(-30.0f);
        d.push_back(-10.0f);
        d.push_back(70.0f);
        d.push_back(20.0f);
        d.push_back(40.0f);
        d.push_back(60.0f);
        d.push_back(100.0f);
        d.push_back(70.0f);
        d.push_back(50.0f);
        d.push_back(-50.0f);
        d.push_back(0.0f);
        d.push_back(-30.0f);
        d.push_back(-10.0f);
        ////////////////////////////////////
        
        SetDefaultData(100, -50, d);
        
        */
        
    }
   

    m_iCntPoint = (int)m_vecData.size();
    ////////////////////////////////
    
    //m_bReset = true;
    
    Reset();
    
    m_bStart = true;
}

void AceBarGraph::Reset()
{
    m_bReset = false;
    
    m_idxVertex = 1;
    
    m_fOneW = (float)(m_iWidth - (m_iCntPoint-1) * m_iMargin) / (float)m_iCntPoint;
    float oneW = m_fOneW + m_iMargin;
    
    
    
    
    if ( m_pVertex_s != NULL )
    {
        delete [] m_pVertex_s;
        m_pVertex_s = NULL;
    }
    if ( m_pBackVertex_s != NULL )
    {
        delete [] m_pBackVertex_s;
        m_pBackVertex_s = NULL;
    }
    if ( m_pLineVertex_s != NULL )
    {
        delete [] m_pLineVertex_s;
        m_pLineVertex_s = NULL;
    }
    
    
    
    //int iLenValue = m_iMaxValue - m_iMinValue;
    
    //float useableH = (float)m_iHeight / iLenValue;
    
    
    m_iCntVertex = m_iCntPoint * 4;
    CCPoint *vertex_s = new CCPoint[m_iCntVertex];
    m_pLineVertex_s = vertex_s;
    
    CCPoint *pV = vertex_s;
    float fL = (float)0.0f;
    float drawStartY = (float)m_iCenterHeight;
    float upDD = (float)(m_iHeight - m_iCenterHeight) / (float)m_iMaxValue;
    float downDD = (float)m_iCenterHeight / (float)-m_iMinValue;
    for ( int i = 0 ; i < m_iCntPoint ; i ++ )
    {
        int v = m_vecData[i];
        if ( v > 0 )
        {
            float vv = (upDD * v + m_iCenterHeight) - m_iCenterHeight;
            pV[0].x = fL;
            pV[0].y = drawStartY;
            pV[1].x = fL;
            pV[1].y = drawStartY + vv;
            pV[2].x = fL + m_fOneW;
            pV[2].y = drawStartY;
            pV[3].x = fL + m_fOneW;
            pV[3].y = drawStartY + vv;
        }
        else if ( v < 0 )
        {
            float vv = v * downDD;
            pV[0].x = fL;
            pV[0].y = drawStartY;
            pV[1].x = fL;
            pV[1].y = drawStartY + vv;
            pV[2].x = fL + m_fOneW;
            pV[2].y = drawStartY;
            pV[3].x = fL + m_fOneW;
            pV[3].y = drawStartY + vv;
        }

        pV += 4;
        fL += (float)oneW;
    }
    //////////////////////////////////////////////
    vertex_s = new CCPoint[m_iCntVertex];
    m_pVertex_s = vertex_s;
    
    pV = vertex_s;
    fL = (float)m_fLineWidth;
    float lineOneW = m_fOneW - (m_fLineWidth * 2.0f);
    for ( int i = 0 ; i < m_iCntPoint ; i ++ )
    {
        int v = m_vecData[i];
        if ( v >= 0 )
        {
            float vv = (upDD * v + m_iCenterHeight) - m_iCenterHeight - m_fLineWidth;
            pV[0].x = fL;
            pV[0].y = drawStartY;
            pV[1].x = fL;
            pV[1].y = drawStartY + vv;
            pV[2].x = fL + lineOneW;
            pV[2].y = drawStartY;
            pV[3].x = fL + lineOneW;
            pV[3].y = drawStartY + vv;
        }
        else if ( v < 0 )
        {
            float vv = v * downDD + m_fLineWidth;
            pV[0].x = fL;
            pV[0].y = drawStartY;
            pV[1].x = fL;
            pV[1].y = drawStartY + vv;
            pV[2].x = fL + lineOneW;
            pV[2].y = drawStartY;
            pV[3].x = fL + lineOneW;
            pV[3].y = drawStartY + vv;
        }
        
        pV += 4;
        fL += (float)oneW;
    }
    //////////////////////////////////////////////
    if ( m_iMargin != 0 )
    {
        vertex_s = new CCPoint[m_iCntVertex];
        m_pBackVertex_s = vertex_s;
        CCPoint *pV = vertex_s;
        float fL = (float)0.0f;
        for ( int i = 0 ; i < m_iCntPoint ; i ++ )
        {
            pV[0].x = fL;
            pV[0].y = 0.0f;
            pV[1].x = fL;
            pV[1].y = 0.0f + m_iHeight;
            pV[2].x = fL + m_fOneW;
            pV[2].y = 0.0f;
            pV[3].x = fL + m_fOneW;
            pV[3].y = 0.0f + m_iHeight;
            
            pV += 4;
            fL += (float)oneW;
        }
        
    }
    //////////////////////////////////////////////
    
    if (m_bRight == true)
    {
        float lastX = (float)m_iWidth - m_iScrollW;
        m_fClipX = lastX;
        CCPoint myPos = getPosition();
        myPos.x -= lastX;
        setPosition(myPos);
        //m_iNowCur = (int)m_vecData.size() - 1;
    }
    
    //////////////////////////////////////////////
    if ( m_funSetBarLabel == NULL )
    {
        SetBarLabelFun(AceBarGraph_TestFun_SetBarLabel);
    }
    if ( m_funSetBarLabel != NULL )
    {
        m_funSetBarLabel(this);
    }
    
    if ( m_funIsChanged == NULL )
    {
        SetIsChangedFun(AceBarGraph_TestFun_IsChanged);
    }
}

void AceBarGraph::DrawLine(CCPoint pp1, CCPoint pp2, ccColor4F col, float w)
{
    float oneS = w / 2.0f;
    
    
    CCPoint lines[2];
    lines[0] = pp1;
    lines[1] = pp2;
    
    zvec p1 = zvec(lines[0].x, lines[0].y, 0.0f);
    zvec p2 = zvec(lines[1].x, lines[1].y, 0.0f);
    
    zvec line_1 = p2 - p1;
    line_1.make_unit();
    zvec right_1= zvec(1.0f, 0,0 );
    
    float dot = right_1.dot(line_1);
    float angle = acosf(dot);
    
    //CCLog("- angle %f %f" , dot, angle);
    //TestLine(lines, m_fLineWidth );
    
    zvec __up = zvecUp;
    zvec __fwd;//zvecFoward;
    
    if( line_1.y > 0.0f )
        __fwd = zvecFoward;
    else
        __fwd = - zvecFoward;
    
    float newPoli[6][2];
    zmat4 matRot(angle * z180PI, __fwd);
    zvec newUp = (matRot * __up) * oneS;
    
    //CCLog("- angle %f %f %f %f" , dot, angle, newUp.x, newUp.y );
    
    newPoli[2][0] = (float)lines[1].x;
    newPoli[2][1] = (float)lines[1].y;
    newPoli[3][0] = (float)lines[0].x;
    newPoli[3][1] = (float)lines[0].y;
    
    
    
    newPoli[0][0] = newPoli[2][0] + newUp.x;
    newPoli[0][1] = newPoli[2][1] + newUp.y;
    
    newPoli[4][0] = newPoli[2][0] - newUp.x;
    newPoli[4][1] = newPoli[2][1] - newUp.y;
    
    newPoli[1][0] = newPoli[3][0] + newUp.x;
    newPoli[1][1] = newPoli[3][1] + newUp.y;
    
    newPoli[5][0] = newPoli[3][0] - newUp.x;
    newPoli[5][1] = newPoli[3][1] - newUp.y;
    
    
    ccColor4F newCol = col;
    
    ccColor4F cols[6];
    
    cols[2] = ccc4f(newCol.r,newCol.g,newCol.b,newCol.a);
    cols[3] = ccc4f(newCol.r,newCol.g,newCol.b,newCol.a);
    
    
    cols[0] = ccc4f(newCol.r,newCol.g,newCol.b,0);
    cols[1] = ccc4f(newCol.r,newCol.g,newCol.b,0);
    cols[4] = ccc4f(newCol.r,newCol.g,newCol.b,0);
    cols[5] = ccc4f(newCol.r,newCol.g,newCol.b,0);
    
    AceDrawArrays( &newPoli[0][0], &cols[0].r, 6 , GL_TRIANGLE_STRIP);
}

void AceBarGraph::draw()
{
    //CCLayer::draw();
    if ( m_bStart == false )
        return;
    
    AceDrawStart();
    
    if ( m_iCntPoint > 0 )
    {
        if ( m_idxVertex > 0 && m_bReset == false )
        {
            /*
             if ( m_idxVertex == 1 )
             {
             ccDrawSolidCircle(m_pVertex_s[0], 4, 15);
             m_fNowDrawFlag = (float)m_iLenPointToPoint;
             }
             else*/
            if ( m_bScroll == true)
            {
                if ( m_bTouchStart == true)
                {
                    if ( m_fScrollMoveX != 0.0f )
                    {
                        CCPoint myPos = getPosition();
                        myPos.x += m_fScrollMoveX;
                        m_fClipX -= m_fScrollMoveX;
                        setPosition(myPos);
                        
                        m_fScrollMoveX = 0.0f;
                    }
                }
                else
                {
                    if ( m_bRight == false )
                    {
                        float oneW = m_fOneW + m_iMargin;
                        float tag = m_fClipX;
                        int newCur = -1;
                        //if ( m_fScrollMoveX == 0.0f)
                        {
                            float flag = (tag+(float)m_iMargin) / oneW;
                            newCur = (int)flag;
                            float cur = (float)((int)(flag + 0.5f)) * oneW;
                            
                            m_fScrollMoveX = m_fClipX - cur;
                            if ( m_fScrollMoveX != 0.0f )
                            {
                                CCPoint myPos = getPosition();
                                myPos.x += m_fScrollMoveX;
                                m_fClipX -= m_fScrollMoveX;
                                setPosition(myPos);
                                
                                m_fScrollMoveX = 0.0f;
                            }
                        }
                        //float newScrollW = ((int)(m_iScrollW / oneW)) * oneW - m_iMargin;
                        float newScrollW = m_fOneW;
                        float lastX = m_iWidth - newScrollW;
                        if ( lastX < 0.0f )
                        {
                            lastX = 0.0f;
                        }
                        if ( m_fClipX > lastX )
                        {
                            m_fScrollMoveX = -(lastX) + m_fClipX;
                        }
                        if ( m_fClipX < 0.0f )
                        {
                            m_fScrollMoveX = m_fClipX;
                        }
                        if ( m_fScrollMoveX != 0.0f )
                        {
                            CCPoint myPos = getPosition();
                            myPos.x += m_fScrollMoveX;
                            m_fClipX -= m_fScrollMoveX;
                            setPosition(myPos);
                            
                            m_fScrollMoveX = 0.0f;
                        }
                        if ( newCur >= 0 && newCur < (int)m_vecData.size() )
                        {
                            if ( newCur != m_iNowCur )
                            {
                                int oldCur = m_iNowCur;
                                m_iNowCur = newCur;
                                if ( m_funIsChanged != NULL )
                                {
                                    m_funIsChanged(oldCur, m_iNowCur, this);
                                }
                                
                                if( _pTarget &&
                                   _callback )
                                {
                                    ( _pTarget->*_callback )();
                                }
                            }
                        }
                    }
                    else
                    {
                        float newX = m_iWidth - (m_fClipX + m_iScrollW);
                        float oneW = m_fOneW + m_iMargin;
                        int newCur = -1;
                        //float tag = m_fClipX + m_iScrollW;
                        //if ( m_fScrollMoveX == 0.0f)
                        {
                            float flag = (newX+(float)m_iMargin) / oneW;
                            newCur = (int)flag;
                            float cur = (float)((int)(flag + 0.5f)) * oneW;
                            m_fScrollMoveX = m_fClipX - (m_iWidth - cur - m_iScrollW);
                            if ( m_fScrollMoveX != 0.0f )
                            {
                                CCPoint myPos = getPosition();
                                myPos.x += m_fScrollMoveX;
                                m_fClipX -= m_fScrollMoveX;
                                setPosition(myPos);
                                
                                m_fScrollMoveX = 0.0f;
                            }
                        }
                        newX = m_iWidth - (m_fClipX + m_iScrollW);
                        //float newScrollW = ((int)(m_iScrollW / oneW)) * oneW - m_iMargin;
                        float newScrollW = m_fOneW;
                        float lastX = m_iWidth - newScrollW;
                        if ( lastX < 0.0f )
                        {
                            lastX = 0.0f;
                        }
                        if ( newX > lastX )
                        {
                            m_fScrollMoveX = (lastX) - newX;
                        }
                        if ( newX < 0.0f )
                        {
                            m_fScrollMoveX = -newX;
                        }
                        if ( m_fScrollMoveX != 0.0f )
                        {
                            CCPoint myPos = getPosition();
                            myPos.x += m_fScrollMoveX;
                            m_fClipX -= m_fScrollMoveX;
                            setPosition(myPos);
                            
                            m_fScrollMoveX = 0.0f;
                        }
                        if ( newCur >= 0 && newCur < (int)m_vecData.size() )
                        {
                            newCur =(int)m_vecData.size() - 1 - newCur;
                            if ( newCur != m_iNowCur )
                            {
                                int oldCur = m_iNowCur;
                                m_iNowCur = newCur;
                                if ( m_funIsChanged != NULL )
                                {
                                    m_funIsChanged(oldCur, m_iNowCur, this);
                                }
                                
                                if( _pTarget &&
                                   _callback )
                                {
                                    ( _pTarget->*_callback )();
                                }
                            }
                        }

                    }
                }
                
            }
            
            if ( m_idxVertex == m_iCntPoint + 1 )
            {
                
            }
            else
            {
                ////////////////////////////////////////////
                ccColor4F backCol = ccc4f((float)m_backColor.r / 255.0f,
                                          (float)m_backColor.g / 255.0f,
                                          (float)m_backColor.b / 255.0f,
                                          m_fBackA);
                if ( m_fBackA > 0.0f )
                {
                    if ( m_iMargin == 0 )
                    {
                        CCPoint backPoints[4];
                        
                        backPoints[0].x = 0.0f;
                        backPoints[0].y = 0.0f;
                        backPoints[1].x = 0.0f;
                        backPoints[1].y = m_iHeight;
                        backPoints[2].x = m_iWidth;
                        backPoints[2].y = 0.0f;
                        backPoints[3].x = m_iWidth;
                        backPoints[3].y = m_iHeight;
                        
                        ccDrawSolidPoly2((CCPoint*)backPoints, 4, backCol);
                    }
                    else if ( m_pBackVertex_s != NULL )
                    {
                        CCPoint* pLastPoint = m_pBackVertex_s;
                        
                        
                        for ( int i = 0 ; i < m_iCntPoint ; i ++ )
                        {
                            ccDrawSolidPoly2((CCPoint*)pLastPoint, 4, backCol);
                            pLastPoint += 4;
                        }
                    }
                }
                ////////////////////////////////////////////
                
                
                
                CCPoint* pLastPoint = m_pVertex_s;
                CCPoint* pLinePoint = m_pLineVertex_s;
            
                
                ccColor4F colLine = ccc4f((float)m_lineColor.r / 255.0f,
                                          (float)m_lineColor.g / 255.0f,
                                          (float)m_lineColor.b / 255.0f,
                                          m_fLineA);
                
                
                for ( int i = 0 ; i < m_iCntPoint ; i ++ )
                {
                    ccColor4F col = m_vecColor[i];
                    if ( m_iSelectedIdx != i )
                    {
                        ccDrawSolidPoly2((CCPoint*)pLinePoint, 4, col);
                    }
                    else
                    {
                        if ( m_fLineA != 0.0f )
                        {
                            ccDrawSolidPoly2((CCPoint*)pLinePoint, 4, colLine);
                            ccDrawSolidPoly2((CCPoint*)pLastPoint, 4, col);
                        }
                        else
                        {
                            ccDrawSolidPoly2((CCPoint*)pLinePoint, 4, col);
                        }
                    }
                    
                    pLastPoint += 4;
                    pLinePoint += 4;
                }
                
                if ( m_fCenterLineA != 0.0f )
                {
                    colLine = ccc4f((float)m_centerLineColor.r / 255.0f,
                                    (float)m_centerLineColor.g / 255.0f,
                                    (float)m_centerLineColor.b / 255.0f,
                                    m_fCenterLineA);
                    
                    float startY = m_iCenterHeight - m_fCenterLineWidth / 2.0f;
                    
                    CCPoint backPoints[4];
                    
                    backPoints[0].x = 0.0f;
                    backPoints[0].y = startY;
                    backPoints[1].x = 0.0f;
                    backPoints[1].y = startY + m_fCenterLineWidth;
                    backPoints[2].x = m_iWidth;
                    backPoints[2].y = startY;
                    backPoints[3].x = m_iWidth;
                    backPoints[3].y = startY + m_fCenterLineWidth;
                    
                    
                    ccDrawSolidPoly2((CCPoint*)backPoints, 4, colLine);
                    
                }
                
                
            }
            
        }

    }
    ccGLBlendResetToCache();
    
}

CCPoint AceBarGraph::GetBarPosition(int idx)
{
    int size = (int)m_vecData.size();
    if ( size <= idx )
    {
        return CCPoint(-1, -1);
    }
    
    int cur = idx * 4 + 1;
    CCPoint p = m_pVertex_s[cur];
    
    //p.x -= m_fClipX;
    
    return p;
}

