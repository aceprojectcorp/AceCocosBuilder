//
//  AceClippingNode.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceAreaGraphLoader.h"




USING_NS_CC_EXT;

AceAreaGraph::AceAreaGraph()
{
    m_bStart = false;
    Init();
    CallBack_ClickPoint = NULL;
    CallBack_Drawing = NULL;
    
    m_touchPriority = -129;
   
}
AceAreaGraph::~AceAreaGraph()
{
    
}

bool AceAreaGraph::init()
{
    this->setTouchEnabled(true);
    return true;
}

void AceAreaGraph::SetCallBack_ClickPoint(void (*CallBack_ClickPoint)(int, float, float))
{
    this->CallBack_ClickPoint = CallBack_ClickPoint;
}

void AceAreaGraph::SetCallBack_Drawing(void (*CallBack_Drawing)(int, float, float))
{
    this->CallBack_Drawing = CallBack_Drawing;
}

void AceAreaGraph::SetDefaultData(int maxV, int minV, vector<float> data)
{
    m_iMaxValue = maxV;
    m_iMinValue = minV;
    
    m_vecData = data;

}

void TestCallBack_ClickPoint(int idx, float x, float y)
{
    CCLog("TestCallBack_ClickPoint %d %f %f", idx, x, y);
}
void TestCallBack_Drawing(int idx, float x, float y)
{
    CCLog("TestCallBack_Drawing %d %f %f", idx, x, y);
}
void AceAreaGraph::onEnter()
{
    
//    Start();
    
    
    this->schedule(schedule_selector(AceAreaGraph::Draw));
    
    CCLayer::onEnter();
    
    

}

void AceAreaGraph::onExit()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    this->unschedule(schedule_selector(AceAreaGraph::Draw));
    
    
    CCLayer::onExit();
}
void AceAreaGraph::setPriority(int priority) {
    this->m_touchPriority = priority;
    this->setTouchPriority(priority);
    //this->registerWithTouchDispatcher();
}

void AceAreaGraph::update(float delta)
{
    
}

void AceAreaGraph::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addStandardDelegate(this, m_touchPriority);
}


void AceAreaGraph::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
//    bool bIn = false;
//    
//    CCSetIterator it = pTouches->begin();
//    CCTouch * touch = (CCTouch*)(*it);
//    
//    CCPoint pp = touch->getLocation();
//    CCPoint objPoint = this->getParent()->convertToWorldSpace( getPosition() );
//    
//    CCPoint dP = pp- objPoint;
//    
//    if ( dP.x < m_fMaxDrawFlag + m_iLenPointToPoint && dP.y < m_iHeight + m_iLenPointToPoint &&
//        dP.x > -m_iLenPointToPoint && dP.y > -m_iLenPointToPoint )
//    {
//        bIn = true;
//    }
//    if (bIn == true)
//    {
//        int selected = (int)((dP.x+m_iLenPointToPoint/2.0f) / m_iLenPointToPoint );
//        m_iSelectedPointIdx = selected;
//        if ( CallBack_ClickPoint != NULL && m_pVertex_s != NULL && selected < m_iCntPoint )
//        {
//            CCPoint newP = m_pVertex_s[selected<<1];
//            CallBack_ClickPoint(selected, newP.x, newP.y );
//        }
//    }
//    else
//    {
////        Reset();
//    }
    
    
}
void AceAreaGraph::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    //CCSetIterator it = pTouches->begin();
    //CCTouch * touch = (CCTouch*)(*it);
    
    //CCPoint deltaPoint = touch->getDelta();
    
    
    //CCLog("---2----   %f , %f ", deltaPoint.x, deltaPoint.y);
    bool bIn = false;
    
    CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(*it);
    
    CCPoint pp = touch->getLocation();
    CCPoint objPoint = this->getParent()->convertToWorldSpace( getPosition() );
    
    CCPoint dP = pp- objPoint;
    
    if ( dP.x < m_fMaxDrawFlag + m_iLenPointToPoint && dP.y < m_iHeight + m_iLenPointToPoint &&
        dP.x > -m_iLenPointToPoint && dP.y > -m_iLenPointToPoint )
    {
        bIn = true;
    }
    if (bIn == true)
    {
        int selected = (int)((dP.x+m_iLenPointToPoint/2.0f) / m_iLenPointToPoint );
        m_iSelectedPointIdx = selected;
        if ( CallBack_ClickPoint != NULL && m_pVertex_s != NULL && selected < m_iCntPoint )
        {
            CCPoint newP = m_pVertex_s[selected<<1];
            CallBack_ClickPoint(selected, newP.x, newP.y );
        }
    }
    else
    {
        //        Reset();
    }
}
void AceAreaGraph::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    // CCLog("---3----");
}
void AceAreaGraph::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    // CCLog("---4----");
}


void AceAreaGraph::Init()
{
    m_iCntPoint = 0;
    m_pVertex_s = NULL;
    m_bReset = false;
    m_iSelectedPointIdx = 0;
    
    this->setAnchorPoint(CCPoint(0.5f, 0.5f));
   
}


void AceAreaGraph::Start()
{

    if ( m_vecData.size() < 1 )
    {
        ////////////데이터 입력/////////////
        //m_iMaxValue = 100;
        //m_iMinValue = -50;
        
//        vector<float > d;
//        d.clear();
//        
//        d.push_back(70.0f);
//        d.push_back(20.0f);
//        d.push_back(40.0f);
//        d.push_back(60.0f);
//        d.push_back(100.0f);
//        d.push_back(70.0f);
//        d.push_back(50.0f);
//        d.push_back(10.0f);
//        d.push_back(0.0f);
//        d.push_back(-30.0f);
//        d.push_back(70.0f);
        ////////////////////////////////////
        
//        SetDefaultData(100, -50, d);
        m_vecData.push_back(0.0f);
        
    }
   
    
    if ( m_iCntPoint < m_vecData.size() )
    {
        //m_iCntPoint = (int)m_vecData.size();
    }
    if ( m_vecData.size() < m_iCntPoint )
    {
        m_iCntPoint = (int)m_vecData.size();
    }
    ////////////////////////////////
    
    //m_bReset = true;
    
    Reset();
    
    m_bStart = true;
}

void AceAreaGraph::Reset()
{
    m_bReset = false;
    
    m_idxVertex = 1;
    m_fNowDrawFlag = (float)0.0f;
    m_fMaxDrawFlag = (float)(m_iCntPoint - 1) * (float)m_iLenPointToPoint;
    m_iSelectedPointIdx = m_iCntPoint - 1;
    m_fNowDrawGraph = 0.0f;
    
    if ( m_pVertex_s != NULL )
    {
        delete [] m_pVertex_s;
        m_pVertex_s = NULL;
    }
    
    
    
    int iLenValue = m_iMaxValue - m_iMinValue;
    
    int useableH = m_iHeight - m_iMarginUp - m_iMarginDown;
    
    float drawStartY = (float)m_iMarginDown;
    
    float dy = (float)((float)useableH / (float)iLenValue );
    
    m_iCntVertex = ( m_iCntPoint - 1 ) * 2 + 2;
    
    //float values[] = { (float)m_iMaxValue / 2, (float)m_iMaxValue, };
    
    CCPoint *vertex_s = new CCPoint[m_iCntVertex];
    m_pVertex_s = vertex_s;
    
    
    vertex_s[0].x = 0.0f;
    vertex_s[0].y = drawStartY + (m_vecData[0] - m_iMinValue) * dy;
    vertex_s[1].x = 0.0f;
    vertex_s[1].y = drawStartY;
    
    
    
    CCPoint *pV = vertex_s + 2;
    float fL = (float)m_iLenPointToPoint;
    
    for ( int i = 1 ; i < m_iCntPoint ; i ++ )
    {
        pV[0].x = fL;
        pV[0].y = drawStartY + (m_vecData[i] - m_iMinValue) * dy;
        //pV[0].y = drawStartY + m_vecData[i] - m_iMinValue;
        pV[1].x = fL;
        pV[1].y = drawStartY;
        
        pV += 2;
        fL += (float)m_iLenPointToPoint;
    }

    if ( CallBack_ClickPoint == NULL )
    {
        CallBack_ClickPoint = TestCallBack_ClickPoint;
    }
    if ( CallBack_Drawing == NULL )
    {
        CallBack_Drawing = TestCallBack_Drawing;
    }
}

void AceAreaGraph::DrawLine(CCPoint pp1, CCPoint pp2, ccColor4F col, float w)
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

void AceAreaGraph::draw()
{
    //CCLayer::draw();
    if ( m_bStart == false )
        return;
    
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
            if ( m_idxVertex == m_iCntPoint + 1 )
            {
                int drawCnt = m_iCntVertex;
                
                ccColor4F col = ccc4f((float)m_backColor.r / 255.0f,
                                      (float)m_backColor.g / 255.0f,
                                      (float)m_backColor.b / 255.0f,
                                      m_fBackA);
                AceDrawStart();
                
                ccDrawSolidPoly2((CCPoint*)m_pVertex_s, drawCnt, col);
                
                /*
                glLineWidth(m_fLineWidth);
                
                ccDrawColor4F( (float)m_lineColor.r / 255.0f,
                              (float)m_lineColor.g / 255.0f,
                              (float)m_lineColor.b / 255.0f,
                              m_fLineA);
                
                
                ccDrawLines(m_pVertex_s, m_iCntPoint, 1);
                
                ccDrawColor4F( (float)m_pointColor.r / 255.0f,
                              (float)m_pointColor.g / 255.0f,
                              (float)m_pointColor.b / 255.0f,
                              m_fPointA);
                */
                ccColor4F newCol = ccc4f((float)m_lineColor.r / 255.0f,
                                         (float)m_lineColor.g / 255.0f,
                                         (float)m_lineColor.b / 255.0f,
                                         m_fLineA);
                //AceDrawStart();
                for ( int i = 0 ; i < m_iCntPoint - 1; i ++ )
                {
                    int idx_s = i<<1;
                    CCPoint p1 = m_pVertex_s[idx_s];
                    CCPoint p2 = m_pVertex_s[idx_s + 2];
                    
                    DrawLine(p1, p2, newCol, m_fLineWidth);
                }
                
                for ( int i = 0 ; i < m_iCntPoint ; i ++ )
                {
                    ccDrawSolidCircle(m_pVertex_s[i<<1], m_fPointSize, m_iPointSegs);
                }
                ccGLBlendResetToCache();
            }
            else
            {
                int drawCnt = ( m_idxVertex ) * 2 + 2;
                
                CCPoint* tempPoint_s = new CCPoint[drawCnt];
                memcpy(tempPoint_s, m_pVertex_s, sizeof(CCPoint)*drawCnt );
                
                glLineWidth(m_fLineWidth);
                
                
                float dx = m_fNowDrawGraph - (float)((m_idxVertex-1) * m_iLenPointToPoint);
                CCPoint* pLastPoint = &tempPoint_s[drawCnt-4];
                pLastPoint[2].x = pLastPoint[0].x + dx;
                pLastPoint[3].x = pLastPoint[1].x + dx;
                
                float dy = dx / (float)m_iLenPointToPoint;
                float ddy = ((float)(m_pVertex_s[drawCnt-2].y - pLastPoint[0].y)) * dy;
                pLastPoint[2].y = ddy + pLastPoint[0].y;
                
                ccColor4F col = ccc4f((float)m_backColor.r / 255.0f,
                                      (float)m_backColor.g / 255.0f,
                                      (float)m_backColor.b / 255.0f,
                                      m_fBackA);
                
                AceDrawStart();
                
                ccDrawSolidPoly2((CCPoint*)tempPoint_s, drawCnt, col);
                
                /*
                ccDrawColor4F( (float)m_lineColor.r / 255.0f,
                              (float)m_lineColor.g / 255.0f,
                              (float)m_lineColor.b / 255.0f,
                              m_fLineA);
                
                ccDrawLines(tempPoint_s, m_idxVertex + 1, 1);
                */
                ccColor4F newCol = ccc4f((float)m_lineColor.r / 255.0f,
                                         (float)m_lineColor.g / 255.0f,
                                         (float)m_lineColor.b / 255.0f,
                                         m_fLineA);
                //AceDrawStart();
                for ( int i = 0 ; i < m_idxVertex; i ++ )
                {
                    int idx_s = i<<1;
                    CCPoint p1 = tempPoint_s[idx_s];
                    CCPoint p2 = tempPoint_s[idx_s + 2];
                    
                    DrawLine(p1, p2, newCol, m_fLineWidth);
                }

                
                ccDrawColor4F( (float)m_pointColor.r / 255.0f,
                              (float)m_pointColor.g / 255.0f,
                              (float)m_pointColor.b / 255.0f,
                              m_fPointA);
                
                
                for ( int i = 0 ; i < m_idxVertex  + 1; i ++ )
                {
                    ccDrawSolidCircle(tempPoint_s[i<<1], m_fPointSize, m_iPointSegs);
                }
                
                
                delete [] tempPoint_s;
                
                ccGLBlendResetToCache();
            }
            
        }

    }
    
    
}
void AceAreaGraph::Draw(float delta)
{
    //CCNode::draw();
    
    if ( m_iCntPoint > 0 )
    {
        float speed = m_fSpeed * delta;
        
        if ( m_fNowDrawFlag < m_fMaxDrawFlag)
        {
            m_fNowDrawFlag += speed;
            m_fSeta = m_fNowDrawFlag / m_fMaxDrawFlag;
            float pit = m_fSeta * zPI / 2.0f;
            float sin_s = sinf(pit);
            //sin_s = sqrtf(sin_s);
            m_fNowDrawGraph = sin_s * m_fMaxDrawFlag;
            m_idxVertex = 1 + (int)(m_fNowDrawGraph / (float)m_iLenPointToPoint);
            
            if ( CallBack_Drawing != NULL )
            {
                int nIdx = m_idxVertex;
                float resultFlag = m_fNowDrawFlag;
                if ( resultFlag > m_fMaxDrawFlag )
                    resultFlag = m_fMaxDrawFlag;
                CallBack_Drawing(nIdx, resultFlag, 0.0f);
            }
            
        }
        else
        {
            m_idxVertex = m_iCntPoint + 1;
            m_fNowDrawGraph = m_fMaxDrawFlag;
        }

    }
    
}
int AceAreaGraph::getSelectedIdx()
{
    return m_iSelectedPointIdx;
}

vector<float> AceAreaGraph::GetPos_Y(int cnt)
{
    vector<float> y_s;
    int useableH = m_iHeight - m_iMarginUp - m_iMarginDown;
    float oneH = (float)useableH / (float)(cnt + 1);
    for ( int i = 0 ; i < cnt + 1 ; i ++ )
    {
        y_s.push_back((float)oneH * i + m_iMarginDown);
    }
    return y_s;
}
