//
//  AceClippingNode.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceCoverPageScrollLoader.h"
#include "AceScaleSpriteNode.h"




USING_NS_CC_EXT;

AceCoverPageScroll::AceCoverPageScroll()
: m_bPress( false )
, m_bStartMove( false )
, m_bPlus( false )

, _pStartMoveCallbackTarget( NULL )
, _startMoveCallback( NULL )
, _pCallbackTarget( NULL )
, _callbackO( NULL )
, _pOpacityTarget( NULL )
, _opacityCallbackO( NULL )
, _bIsMoving( false )
, _bDrag( false )
, _bScrolling( false )
{
    Init();
    m_bPlus = false;
    CallBack_IsChanged = NULL;
    
    m_touchPriority = -129;
    
    m_iShowCnt = 3;
    
    m_fMoveY = 0.0f;
    
    m_nextCur = 0;
    
    m_bFirst = true;
    
    m_fMinimumTouchLengthToSlide = 10.0f;
    m_iState = 0;
}
AceCoverPageScroll::~AceCoverPageScroll()
{
    
}

void AceCoverPageScroll::SetCallBack_IsChanged(void (*CallBack_IsChanged)(int))
{
    this->CallBack_IsChanged = CallBack_IsChanged;
    
}

void TestCallBackFunk(int a)
{
//    CCLog("AceCoverPageScroll %d" , a);
}

bool AceCoverPageScroll::init()
{
    if(!CCLayer::init())
        return false;
    
    this->setAnchorPoint(CCPointZero);
    
    this->setTouchEnabled(true);
    
    this->scheduleUpdate();
    return true;
}

void AceCoverPageScroll::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    //pDirector->getTouchDispatcher()->addStandardDelegate(this, -150);
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority ,false);
}



void AceCoverPageScroll::onEnter()
{
    CCLayer::onEnter();
    
    //setTouchPriority(this->getTouchPriority());
    
    Start();
    
    
    //this->schedule(schedule_selector(AceCoverPageScroll::Draw));
    
    
    


}
void AceCoverPageScroll::setPriority(int priority) {
    this->m_touchPriority = priority;
    this->setTouchPriority(priority);
    //this->registerWithTouchDispatcher();
}

void AceCoverPageScroll::setStartMoveCallback(CCNode *pTarget, SEL_CallFunc callback)
{
    _pStartMoveCallbackTarget = pTarget;
    _startMoveCallback = callback;
}

void AceCoverPageScroll::setCallback(CCNode *pTarget, SEL_CallFuncO callbackO)
{
    _pCallbackTarget = pTarget;
    _callbackO = callbackO;
}

void AceCoverPageScroll::setOpacityCallbackO(CCNode* pTarget, SEL_CallFuncO callbackO)
{
    _pOpacityTarget = pTarget;
    _opacityCallbackO = callbackO;
}

void AceCoverPageScroll::onExit()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    //this->unschedule(schedule_selector(AceCoverPageScroll::Draw));
    
    
    CCLayer::onExit();
}


void AceCoverPageScroll::update(float delta)
{
    //CCLayer::update(delta);
    Draw(delta);
    
}

void AceCoverPageScroll::claimTouch(CCTouch* pTouch)
{
    CCTargetedTouchHandler *handler = (CCTargetedTouchHandler*)CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this);
    if(handler) {
        CCSet *claimedTouches = handler->getClaimedTouches();
        if(!claimedTouches->containsObject(pTouch)) {
            claimedTouches->addObject(pTouch);
        } else {
            CCLOGERROR("ScrollLayer::claimTouch is already claimed!");
        }
    }
}

void AceCoverPageScroll::cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent)
{
    // Throw Cancel message for everybody in TouchDispatcher.
    CCSet* touchSet = new CCSet();
    touchSet->addObject(pTouch);
    touchSet->autorelease();
    
    //m_bStealingTouchInProgress = true;
    CCDirector::sharedDirector()->getTouchDispatcher()->touchesCancelled(touchSet, pEvent);
    //m_bStealingTouchInProgress = false;
    
    //< after doing this touch is already removed from all targeted handlers
    
    // Squirrel away the touch
    claimTouch(pTouch);
    
}


// default implements are used to call script callback if exist
bool AceCoverPageScroll::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(!isVisible())
        return false;
    
    CCNode *pParent = NULL;
    for (pParent = this->m_pParent; pParent != NULL; pParent = pParent->getParent())
    {
        if(pParent->isVisible() == false)
            return false;
    }
    
    CCTouch * touch = (CCTouch*)(pTouch);
    
    
    // 터치 영역 확인
    CCPoint touchPoint = this->convertTouchToNodeSpace(touch);
    
    CCSize size = this->getContentSize();
    
    //CCLog("---ccTouchBegan---%d %d (%d %d : %d %d)", (int)deltaPoint.x, (int)deltaPoint.y ,
          //(int)size.width, (int)size.height, (int)touchPoint.x, (int)touchPoint.y);
    
    CCRect r = CCRectMake(0, 0, size.width, size.height);
    if(!r.containsPoint(touchPoint))
    {
        return false;
    }
    
    m_touchPoint = touchPoint;
    m_iState = 0;
    
    m_bPress = true;
    m_fAngleAtPress = 0.0f;
    m_bStartMove = true;

    
    return true;
}
void AceCoverPageScroll::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    
    float fValue = touchPoint.x - m_touchPoint.x;
    //CCLog("---ccTouchMoved---");
    //CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    
    if ( m_iState == 0 )
    {
        if ( (fabsf(fValue) >= m_fMinimumTouchLengthToSlide) )
        {
            m_iState = 1;
            m_touchPoint = touchPoint;
            cancelAndStoleTouch(pTouch, pEvent);
        }
    }
    else
    {
        _bDrag = true;
        _bScrolling = true;
        //CCSetIterator it = pTouches->begin();
        CCTouch * touch = (CCTouch*)(pTouch);
        //CCPoint touchPoint = touch->getLocation();
        CCPoint deltaPoint = touch->getDelta();
        
        float moveValue = deltaPoint.x * m_fScrollSpeed / 500.0f;
        
        m_fLocationMove += moveValue;
        
        bool isPlus = true;
        if ( moveValue < 0.0f )
        {
            isPlus = false;
        }
        if ( isPlus != m_bPlus )
        {
            m_bPlus = isPlus;
            m_fAngleAtPress = moveValue;
        }
        else
        {
            m_fAngleAtPress += moveValue;
        }
    }
    
    
    return ;
}
void AceCoverPageScroll::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    


    //CCLog("---ccTouchEnded---");
    _bDrag = false;
    m_bPress = false;
    
    return ;
}
void AceCoverPageScroll::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLog("---ccTouchCancelled---");
      return ;
}
//void AceCoverPageScroll::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
//{
//    m_bPress = true;
//    m_fAngleAtPress = 0.0f;
//    m_bStartMove = true;
//    //CCLog("---1----");
//}
//void AceCoverPageScroll::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
//{
//    CCSetIterator it = pTouches->begin();
//    CCTouch * touch = (CCTouch*)(*it);
//    //CCPoint touchPoint = touch->getLocation();
//    CCPoint deltaPoint = touch->getDelta();
//    
//    float moveValue = deltaPoint.x * m_fScrollSpeed / 500.0f;
//    
//    m_fLocationMove += moveValue;
//    
//    bool isPlus = true;
//    if ( moveValue < 0.0f )
//    {
//        isPlus = false;
//    }
//    if ( isPlus != m_bPlus )
//    {
//        m_bPlus = isPlus;
//        m_fAngleAtPress = moveValue;
//    }
//    else
//    {
//        m_fAngleAtPress += moveValue;
//    }
//    
//    
//    //CCLog("---2----   %f , %f ", deltaPoint.x, deltaPoint.y);
//}
//void AceCoverPageScroll::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
//{
//    m_bPress = false;
//    // CCLog("---3----");
//   
//}
//void AceCoverPageScroll::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
//{
//    // CCLog("---4----");
//}


void AceCoverPageScroll::Init()
{
    m_vecArray.clear();
    
    
    m_pNodeArray = NULL;
    
    
    m_iChildCnt = 0;
    m_iNowCur = 0;
    m_iMaxCur = 0;
    m_fLocationAngle = 0.0f;
    m_fAngleAtPress = 0.0f;
    m_fAngleOne = 10.0f;
    m_fLowZ = 0.0f;
    
    m_fLocationMove = 0.0f;
    
    
    m_fAngle = 0.0f;
    m_fLen = 200.0f;
    m_iDefaultCur = 0;
    m_fMaxSize = 1.0f;
    m_fMinSize = 0.5f;
    m_fScrollSpeed = 10.0f;
    m_fAngleToMove = 10.0f;
    m_bLoop = false;
    m_bAutoScroll = false;
    m_fAutoScrollSpeed = 50.0f;
    
    m_fMinAlpha = 0.5f;
    
    outVec = ccp(-400, 800);
    
    m_bFirst2 = true;
    
    this->setAnchorPoint(CCPoint(0.5f, 0.5f));
    //setPosition(1400, 400);
}



void AceCoverPageScroll::Start()
{
    m_pNodeArray = this->getChildren();
    
    if ( m_pNodeArray !=  NULL )
    {
        CCArray* pArray = m_pNodeArray;
        m_iChildCnt = (int)pArray->count();
        
        m_vecArray.clear();
        m_vecArray.resize(m_iChildCnt);
        
        for ( int i = 0 ; i < m_iChildCnt ; i ++ )
        {
            CCNode * pNode = dynamic_cast< CCNode* >(pArray->objectAtIndex(i));
            if(pNode)
            {
                int d = pNode->m_iDepth;
                pNode->setZOrder(d);
            }
        }
        
        this->sortAllChildren();
        
        for ( int i = 0 ; i < m_iChildCnt ; i ++ )
        {
            CCNode * pNode = dynamic_cast< CCNode* >(pArray->objectAtIndex(i));
            if(pNode)
            {
                m_vecArray[i]._pNode = pNode;
            }
        }
        
        for(int i=0; i<m_iChildCnt; i++)
        {
            zvec nVec = zvec(outVec.x + 100 * i, outVec.y, 0.0f);
            m_vecArray[i]._vPosition = nVec;
            m_vecArray[i]._fScale = 1.0f;
            m_vecArray[i]._iOpacity = 255;
            m_vecArray[i]._fZ = 0.0f;
            m_vecArray[i]._fA = 1.0f;
        }
        
        m_iMaxCur = m_iChildCnt - 1;
        
        if ( m_iDefaultCur > m_iMaxCur )
        {
            m_iDefaultCur = m_iMaxCur;
        }
        if ( m_iDefaultCur < 0 )
        {
            m_iDefaultCur = 0;
        }
        m_iNowCur = m_iDefaultCur;
        
        if ( m_iShowCnt < 3 )
            m_iShowCnt = 3;
        
        m_iShowCnt = (int)(m_iShowCnt/2) * 2 + 1;
        m_iNeedMinCnt = m_iShowCnt + m_iShowCnt - 1;
        
        m_iOldShowCnt = m_iShowCnt;
        
        m_fAngleOne = 360.0f / (float)m_iNeedMinCnt;
        
        m_bFirst = true;
        
    }
    else
    {
        m_iChildCnt = 0;
    }
    
    
    Draw( -0.1f);
    
    //[self addChild(<#cocos2d::CCNode *child#>)
    
    

    if ( CallBack_IsChanged == NULL )
    {
        SetCallBack_IsChanged(TestCallBackFunk);
    }
    
    
}



void AceCoverPageScroll::draw()
{
   
    int tmpSize = m_iChildCnt;
    
    if ( tmpSize <  1)
        return;
    
    CCSize size = this->getContentSize();
    float start_X = size.width / 2.0f;
    float start_Y = size.height / 2.0f + m_fMoveY;
    
    for(int i=0; i<tmpSize; i++)
    {
        CCNode * pNode = m_vecArray[i]._pNode;
        if(pNode)
        {
            if ( pNode->getPositionX() != m_vecArray[i]._vPosition.x + start_X
                || pNode->getPositionY() != m_vecArray[i]._vPosition.y + start_Y )
            {
                pNode->setPosition(m_vecArray[i]._vPosition.x + start_X , m_vecArray[i]._vPosition.y + start_Y);
                pNode->setScaleX(m_vecArray[i]._fScale);
                pNode->setScaleY(m_vecArray[i]._fScale);
                this->SetChildrenOpacity(pNode, (int)(m_vecArray[i]._fA * 255.0f));
                pNode->setZOrder((int)(m_vecArray[i]._fZ * 100.0f));
            }
        }
    }
    
    if ( m_bFirst == true )
    {
        m_bFirst = false;
        this->sortAllChildren();
    }
}
void AceCoverPageScroll::Draw(float delta)
{
    //CCNode::draw();
    
    if ( m_iChildCnt < 1 )
        return;
 
    
    //------------------------------------------------------
    if ( m_bAutoScroll == true )
    {
        m_fLocationAngle += m_fAutoScrollSpeed * delta;
    }
    //m_fLocationAngle += -delta * m_fScrollSpeed;
    //--------드래그에 따른 위치 조정----------------------------
    m_fLocationAngle += m_fLocationMove;
    m_fLocationMove = 0.0f;
    
    //---------------이동할게 없을 경우 리턴----------------------------
    if ( delta < 0.0f)
    {
        delta *= -1.0f;
    }
    else if ( fabs(m_fLocationAngle) < 0.01f && m_nextCur == 0 )
    {
        if ( m_bFirst2 == false )
        {
            //CCLog("==return==");
            return;
        }
        else
        {
            m_bFirst2 = false;
        }
    }
    
    
    zvec fwdVec = vecForward;
    zvec rightVec = zvec(1, 0, 0);
    zvec upVec = vecUp;
    zmat4 zRolMat(m_fAngle, rightVec);
    
    float angleOne = m_fAngleOne;
    float hAngle = angleOne / 2.0f;
    float angleFirst = -angleOne * (m_iShowCnt-1);
    
    //-----------인덱스 건너 뛰기------------------------------
    if ( m_bPress == false )
    {
        if (m_nextCur != 0)
        {
            {
                m_bStartMove = true;
                
                if ( m_nextCur > 0 )
                {
                    m_fLocationAngle += -(m_nextCur+1) * angleOne * 0.1f;
                    m_fAngleAtPress = -m_fAngleToMove;
                    
                }
                else
                {
                    m_fLocationAngle += -(m_nextCur-1)* angleOne * 0.1f;;
                    m_fAngleAtPress = m_fAngleToMove;
                }
                
                m_nextCur = 0;
            }
        }
    }
    else
    {
        m_nextCur = 0;
    }
    
    
    //--------양쪽 끝일 경우 더 이상 스크롤 안되도록 ---------------
    bool bRightEndPosition = false;
    bool bLeftEndPosition = false;
    if ( m_bLoop == false )
    {
        if ( m_iNowCur < 1 )
        {
            if ( m_fLocationAngle >= hAngle )
            {
                m_fLocationAngle = hAngle - 0.1f;
            }
            bLeftEndPosition = true;
        }
        if ( m_iNowCur > m_iMaxCur - 1 )
        {
            if ( m_fLocationAngle <= -hAngle )
            {
                m_fLocationAngle = - (hAngle - 0.1f);
            }
            bRightEndPosition = true;
        }
    }
    
    
    //-------------------------------------------------------
    bool isChange = false;
    
    while ( m_fLocationAngle < -angleOne )
    {
        m_fLocationAngle += angleOne;
        isChange = true;
        m_iNowCur ++;
    }
    
    while ( m_fLocationAngle > angleOne )
    {
        m_fLocationAngle += -angleOne;
        isChange = true;
        m_iNowCur --;
    }
    
    if ( m_bPress == false && m_bAutoScroll == false )
    {
        float absLocationAngle = fabs(m_fLocationAngle);
        //CCLog ("loc %f " , absLocationAngle );
        //----------살짝 드래그시 다음으로 넘길 것인가--------------------------
        if ( bRightEndPosition == false  && bLeftEndPosition == false )
        {
            if ( absLocationAngle < 0.1f )
            {
                //absLocationAngle = 0.0f;
            }
            if ( absLocationAngle >  angleOne - 0.1f )
            {
                if ( m_fLocationAngle > 0.0f )
                {
                    m_fLocationAngle = 0.0f;
                    m_iNowCur --;
                    isChange = true;
                    CCLog(" right " );
                    m_fAngleAtPress = 0.0f;
                }
                else
                {
                    m_fLocationAngle = 0.0f;
                    m_iNowCur ++;
                    isChange = true;
                    CCLog(" left " );
                    m_fAngleAtPress = 0.0f;
                }
            }
        }
        
        //-----------드래그가 중간에 멈추면 가까운 곳으로 이동---------------------
        float dAngle = m_fAngleAtPress;
        float absDeltaAngle = fabs(dAngle);
        //Debug.Log(" abs " + dAngle );
        
        if ( m_bStartMove == true  )
        {
            if( _pStartMoveCallbackTarget && _startMoveCallback &&
               !_bIsMoving )
            {
                _bIsMoving = true;
                ( _pStartMoveCallbackTarget->*_startMoveCallback )();
            }
        }
            
        if ( m_bStartMove == true && ( bRightEndPosition == false || bLeftEndPosition == false )
            && (absDeltaAngle >= m_fAngleToMove && absDeltaAngle <= hAngle)
            )
        {
            
            if ( dAngle > 0.0f )
            {
                if ( bLeftEndPosition == true )
                {
                    m_fLocationAngle += ( 0.0f - m_fLocationAngle ) * 0.3f;
                    //CCLog("angled %f %f 1  " , absDeltaAngle, m_fLocationAngle);
                }
                else if ( m_fLocationAngle < 0.0f )
                {
                    m_fLocationAngle += ( 0.0f - m_fLocationAngle ) * 0.3f;
                    //CCLog("angled %f %f 2  " , absDeltaAngle, m_fLocationAngle);
                }
                else
                {
                    m_fLocationAngle += ( angleOne - m_fLocationAngle ) * 0.3f;
                    //CCLog("angled %f %f 3  " , absDeltaAngle, m_fLocationAngle);
                }
                
            }
            else if ( dAngle < 0.0f )
            {
                if ( bRightEndPosition == true )
                {
                    m_fLocationAngle += ( 0.0f - m_fLocationAngle ) * 0.3f;
                    //CCLog("angled %f %f 1  " , absDeltaAngle, m_fLocationAngle);
                }
                else if ( m_fLocationAngle < 0.0f )
                {
                    m_fLocationAngle += ( -angleOne - m_fLocationAngle ) * 0.3f;
                    //CCLog("angled %f %f 2  " , absDeltaAngle, m_fLocationAngle);
                }
                else
                {
                    m_fLocationAngle += ( 0.0f - m_fLocationAngle ) * 0.3f;
                    //CCLog("angled %f %f 3  " , absDeltaAngle, m_fLocationAngle);
                }
                
            }
            absLocationAngle = fabs(m_fLocationAngle);
            if ( absLocationAngle < 0.1f || absLocationAngle > angleOne - 1.0f)
            {
                m_bStartMove = false;
                _bScrolling = false;
            }
        }
        else
        {
            //---------평상시 드래그 이동 후 가까운 곳으로 자동 이동--------------------
            m_nextCur = 0;
            m_bStartMove = false;
            _bScrolling = false;
            m_fAngleAtPress = 0.0f;
            absLocationAngle = fabs(m_fLocationAngle);
            float absAngle =  absLocationAngle - hAngle;
            
            if ( absAngle <  0 )
            {
                m_fLocationAngle += ( 0.0f - m_fLocationAngle ) * 0.3f;
            }
            else
            {
                float tAngle = angleOne;
                if ( m_fLocationAngle < 0.0f )
                    tAngle *= -1.0f;
                
                float toLen = tAngle - m_fLocationAngle;
                m_fLocationAngle += toLen * 0.3f;
                
            }
        }
        
        //--------------조금 남았을 경우 그냥 다음으로 넘기자-------------
        if ( isChange != true )
        {
            absLocationAngle = fabs(m_fLocationAngle);
            if ( absLocationAngle <= angleOne && absLocationAngle > angleOne - 1.0f )
            {
                isChange = true;
                if ( m_fLocationAngle < 0.0f )
                {
                    m_iNowCur ++;
                }
                else
                {
                    m_iNowCur --;
                }
                m_fLocationAngle = 0.0f;
            }
        }
    }
    
    if ( isChange == true )
    {
        if ( m_bLoop == false )
        {
            if ( m_iNowCur > m_iMaxCur )
            {
                m_iNowCur = m_iMaxCur;
                
            }
            else if ( m_iNowCur < 0 )
            {
                m_iNowCur = 0;
                
            }
            else
            {
                //ChangeDraw();
            }
            
        }
        else
        {
            if ( m_iNowCur > m_iMaxCur )
            {
                m_iNowCur -= m_iChildCnt;
            }
            else if ( m_iNowCur < 0 )
            {
                m_iNowCur += m_iChildCnt;
            }
            
            //ChangeDraw();

        }
        
        m_nextCur = 0;
    }
    
    //---------------------------------------------------------
   
    int tmpSize = m_iChildCnt;
    for(int i=0; i<tmpSize; i++)
    {
        zvec nVec = zvec(outVec.x + 100 * i, outVec.y, 0.0f);
        m_vecArray[i]._vPosition = nVec;
        m_vecArray[i]._fScale = 1.0f;
        m_vecArray[i]._iOpacity = 255;
        m_vecArray[i]._fZ = 1.0f;
        m_vecArray[i]._fA = 1.0f;
        
        //m_vecArray[i]._pNode->setZOrder((int)(-1));
    }
    
    int iMin = m_iNowCur - (m_iShowCnt-1);
    int iMax = m_iNowCur + m_iShowCnt;
    
    //int useUnits[5] = { 0, };
    int * useUnits = new int[m_iNeedMinCnt];
    int k = 0;
    
    if ( m_bLoop == false )
    {
        for ( int i = iMin ; i < iMax ; i ++ )
        {
            int nKey = i;
            if ( nKey >= 0 && nKey < m_iChildCnt )
            {
                useUnits[k] = nKey;
            }
            else
            {
                useUnits[k] = -1;
            }
            k ++;
        }
    }
    else
    {
        for ( int i = iMin ; i < iMax ; i ++ )
        {
            int nKey = (i + m_iChildCnt) % m_iChildCnt;
            useUnits[k] = nKey;
            k ++;
            
        }
    }
    
    //-------그리기 전 위치 지정-------------------------
    float dSize = m_fMaxSize - m_fMinSize;
    float dZ = 1.0f / (1.0f - m_fLowZ);
    
    for(int i=0; i<m_iNeedMinCnt; i++)
    {
        int key = useUnits[i];
        if ( key >= 0 )
        {
            CCNode * pNode = m_vecArray[key]._pNode;
            if(pNode)
            {
                zmat4 yRolMat(m_fLocationAngle + angleFirst, upVec);
                zmat4 yzRolMat = zRolMat * yRolMat;
                zvec  newVec = yzRolMat * fwdVec;
                float z = newVec.z;
                if ( z >= 0.0f )
                {
                    zvec nVec = newVec * m_fLen;
                    float v = ( z - m_fLowZ ) * dZ;
                    float vv = m_fMinSize + dSize * v;
                    if ( vv > 0.0f )
                    {
                      
                        float c = m_fMinAlpha + ( 1.0f - m_fMinAlpha ) * v;
                        m_vecArray[key]._fScale = vv;
                        m_vecArray[key]._vPosition = nVec;
                        m_vecArray[key]._iOpacity = (int)(255.0f * c);
                        m_vecArray[key]._fZ = z;
                        m_vecArray[key]._fA = c;
                    }
                    else
                    {
                        //m_vecArray[key]._iOpacity = (int)(-1);
                        //pNode->setZOrder((int)(0));
                        m_vecArray[key]._fZ = z;
                    }
                }
                else
                {
                    //pNode->setZOrder((int)(0));
                    m_vecArray[key]._fZ = z;
                }
            }
        }
        angleFirst += angleOne;
        
    }
    
    delete  [] useUnits;
    
    
    
    if ( isChange == true )
    {
        int newCur = FrontCur();
        if ( CallBack_IsChanged != NULL )
        {
            CallBack_IsChanged(newCur);
        }
        
        /*
        _bIsMoving = false;
        if( _pCallbackTarget && _callbackO )
        {
            ( _pCallbackTarget->*_callbackO )( CCInteger::create( newCur ) );
        }
         */
    }
    else
    {
        
    }
    
    float abs_ = fabs(m_fLocationAngle);
    if ( _bIsMoving == true && abs_ < 0.01f )
    {
        _bIsMoving = false;
        if( _pCallbackTarget && _callbackO )
        {
            int newCur = FrontCur();
            ( _pCallbackTarget->*_callbackO )( CCInteger::create( newCur ) );
        }
    }
    
}
int AceCoverPageScroll::FrontCur()
{
    float angle = m_fLocationAngle;
    float angleOne = m_fAngleOne;
    float hAngle = angleOne / 2.0f;
    int res = 0;
    if ( angle < hAngle && angle > -hAngle)
    {
        res =  m_iNowCur;
    }
    else if ( angle < 0.0f )
    {
        res =  m_iNowCur + 1;
    }
    else
    {
        res =  m_iNowCur - 1;
    }
    
    if ( res > m_iMaxCur )
    {
        res -= m_iChildCnt;
    }
    else if ( res < 0 )
    {
        res += m_iChildCnt;
    }
    
    return res;
    
}
void AceCoverPageScroll::SetChildrenOpacity(CCNode *pNode, int v)
{
    if ( pNode == NULL )
        return;
    
    /*
    
    if ( v > 0 && v < 255 )
    {
        //AceDrawStart();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        CCPoint pos = pNode->getPosition();
        CCSize  siz = pNode->getContentSize();
        CCPoint endPos = CCPoint(pos.x + siz.width, pos.y + siz.height);
        CCPoint anc = pNode->getAnchorPoint();
    
        ccDrawSolidRect(pos, endPos, ccc4f(0,0,0, 1.0f-(float)v/255.0f));
        
    }
    
    */
    
    if( _pOpacityTarget &&
       _opacityCallbackO )
    {
        CCArray* pArray = CCArray::create();
        pArray->addObject( pNode );
        pArray->addObject( CCInteger::create( v ) );
        ( _pOpacityTarget->*_opacityCallbackO )( pArray );
    }
//    CCLog("pNodeaaaaa %d", pNode->getParent()->getChildrenCount());
//    CCSprite* pDimmedSprite = dynamic_cast< CCSprite* >( pNode->getChildByTag( TAG_DIMDDED ) );
//    if( pDimmedSprite )
//    {
//        pNode->enableChildrenOpacity( true );
//        pDimmedSprite->setOpacity( 255 - v );
//    }
//    if ( v > 0 )
//    {
//        if ( v < 255 )
//        {
//            pNode->enableChildrenOpacity(true);
//            pNode->setOpacityChildren2(v);
//        }
//        else
//        {
//            pNode->setOpacityChildren2(v);
//            pNode->enableChildrenOpacity(false);
//        }
//    }
    
    
    /*
     CCArray* pArray = pNode->getChildren();
    if ( pArray == NULL )
        return;

    int cnt = (int)pArray->count();
    for ( int i  = 0 ; i < cnt ; i ++ )
    {
        CCNode * n = dynamic_cast<CCNode *>(pArray->objectAtIndex(i));
        if ( n )
        {
            CCSprite *s = dynamic_cast<CCSprite *>(n);
            if ( s )
            {
                CCSprite *s = (CCSprite *)n;
                s->setOpacity(v);
            }
        }
    }
     */

}

