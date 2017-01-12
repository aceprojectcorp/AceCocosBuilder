//
//  AceFlipActionNode.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 31..
//
//

#include "AceFlipActionNode.h"

USING_NS_CC_EXT;

int stateCount;

AceFlipActionNode::AceFlipActionNode()
: frontNode(NULL)
, backNode(NULL)
, pCallTarget(NULL)
, pCallBackFlip(NULL)
, _bFront(true)
, m_bDirty(true)
{
    setFlipping( false );
    stateCount = 0;
    m_posDirty.x = -9999999.0f;
    m_posDirty.y = -9999999.0f;
    m_bHasScroll = false;
}

/*
bool AceFlipActionNode::init()
{
    if(!CCLayer::init())
        return false;
    this->setAnchorPoint(CCPointZero);
    
    this->setTouchEnabled(true);
    
    this->scheduleUpdate();
    return true;
   
}


void AceFlipActionNode::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -1 ,false);
    
}
bool AceFlipActionNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    this->flip();
    return true;
}
void AceFlipActionNode::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void AceFlipActionNode::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
*/

void AceFlipActionNode::onEnter()
{
    CCNode::onEnter();
    //CCLayer::onEnter();
    
    _nRemainRepeat = _nRepeat;
    
    setFlipNode();
}


void AceFlipActionNode::visit()
{
    
    if ( m_bHasScroll == false )
    {
        glDepthFunc(GL_ALWAYS);
        
        if(getFlipping())
        {
            kmGLMatrixMode(KM_GL_PROJECTION);
            kmGLPushMatrix();
            kmGLLoadIdentity();
            
            CCPoint pos = m_obPosition;
            pos = this->getParent()->convertToWorldSpace(m_obPosition);
            //CCLog("m_obPosition x : %f, y : %f", m_obPosition.x, m_obPosition.y);
            //CCLog("pos x : %f, y : %f", pos.x, pos.y);
            
            
            if ( m_posDirty.x != pos.x || m_posDirty.y != pos.y )
            {
                m_posDirty = pos;
                m_bDirty = true;
            }
            
            if(m_bDirty)
            {
                updatePerspectiveMatrix();
                m_bDirty = false;
            }
            
            kmGLMultMatrix(&m_perspectiveMat);
            
            kmGLMatrixMode(KM_GL_MODELVIEW);
            kmGLPushMatrix();
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            //CCLog("%.2f, %.2f -- %.2f, %.2f, %.2f", size.width, size.height, pos.x, pos.y , m_fVertexZ);
            
            //pos = this->getParent()->convertToWorldSpace(m_obPosition);
            float scaleX = 1.0f;
            float scaleY = 1.0f;
            
            for (CCNode *p = this->getParent(); p != NULL; p = p->getParent())
            {
                scaleX *= p->getScaleX();
                scaleY *= p->getScaleY();
            }
            
            //CCLog("X : %f, Y : %f", scaleX, scaleY);
            
            //pos = this->getParent()->convertToWorldSpace(m_obPosition);
            
            
            pos.x -= size.width * 0.5;
            pos.y -= size.height * 0.5;
            
            
            pos.x /= scaleX;
            pos.y /= scaleY;
            
            // visit에서 translate가 되기 때문에 가운데에서 움직이지 않게 하기 위해서 역방향 이동을 해줘서 상쇄시킴
            //kmGLScalef(scaleX,scaleY,1.0f);
            kmGLTranslatef(-pos.x, -pos.y, 0.0f);
            
        }
        
        CCNode::visit();
        
        if(getFlipping())
        {
            kmGLMatrixMode(KM_GL_PROJECTION);
            kmGLPopMatrix();
            
            kmGLMatrixMode(KM_GL_MODELVIEW);
            kmGLPopMatrix();
        }
        
        glDepthFunc(GL_LEQUAL);
    }
    else
    {
        kmGLMatrixMode(KM_GL_PROJECTION);
        kmGLPushMatrix();
        kmGLLoadIdentity();
        updatePerspectiveMatrix();
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCPoint pos = this->getParent()->convertToWorldSpace(m_obPosition);
        
        if ( m_posDirty.x != pos.x || m_posDirty.y != pos.y )
        {
            m_posDirty = pos;
            updatePerspectiveMatrix();
        }
        
        kmGLMultMatrix(&m_perspectiveMat);
        kmGLMatrixMode(KM_GL_MODELVIEW);
        kmGLPushMatrix();
        
        //CCLog("%.2f, %.2f -- %.2f, %.2f, %.2f", size.width, size.height, pos.x, pos.y , m_fVertexZ);
        pos.x -= size.width * 0.5;
        pos.y -= size.height * 0.5;
        kmGLTranslatef(-pos.x, -pos.y, 0.0f);
        
        CCNode::visit();
        
        kmGLMatrixMode(KM_GL_PROJECTION);
        kmGLPopMatrix();
        kmGLMatrixMode(KM_GL_MODELVIEW);
        kmGLPopMatrix();
    }
}

void AceFlipActionNode::updatePerspectiveMatrix()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    float zeye = CCDirector::sharedDirector()->getZEye();
    
    kmScalar fovY = 60;
    kmScalar aspect = (GLfloat)size.width/size.height;
    kmScalar zNear = 0.1f;
    kmScalar zFar = zeye * 2;
    
    float xmin, xmax, ymin, ymax;
    
    ymax = zNear * tanf(kmDegreesToRadians(fovY / 2));
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    
    CCPoint pos = m_obPosition;
    pos = this->getParent()->convertToWorldSpace(m_obPosition);
    
    
    pos.x -= size.width * 0.5;
    pos.y -= size.height * 0.5;
    

    
    //CCLog("%.2f, %.2f -- %.2f, %.2f, %.2f", size.width, size.height, pos.x, pos.y , m_fVertexZ);
    
    
    float xoffset = pos.x;
    float yoffset = pos.y;
    
    float viewportHeight = size.height;
    float viewportWidth = size.width;
    
    float xo = xoffset * (ymax - ymin) / viewportHeight;
    float yo = yoffset * (xmax - xmin) / viewportWidth;
    
    float left = xmin - xo;
    float right = xmax - xo;
    float bottom = ymin - yo;
    float top = ymax - yo;
    
    m_perspectiveMat.mat[0] = 2 * zNear / (right - left);
    m_perspectiveMat.mat[4] = 0;
    m_perspectiveMat.mat[8] = (right + left) / (right - left);
    m_perspectiveMat.mat[12] = 0;
    
    m_perspectiveMat.mat[1] = 0;
    m_perspectiveMat.mat[5] = 2 * zNear / (top - bottom);
    m_perspectiveMat.mat[9] = (top + bottom) / (top - bottom);
    m_perspectiveMat.mat[13] = 0;
    
    m_perspectiveMat.mat[2] = 0;
    m_perspectiveMat.mat[6] = 0;
    m_perspectiveMat.mat[10] = -(zFar + zNear) / (zFar - zNear);
    m_perspectiveMat.mat[14] = -(2 * zFar * zNear) / (zFar - zNear);
    
    m_perspectiveMat.mat[3] = 0;
    m_perspectiveMat.mat[7] = 0;
    m_perspectiveMat.mat[11] = -1;
    m_perspectiveMat.mat[15] = 0;
    
}

void AceFlipActionNode::setFlipNode()
{
    CCArray* children = this->getChildren();
    _nChildCnt = children->count();
    if( _nChildCnt == 1 )
    {
        frontNode = dynamic_cast< CCNode* >( children->objectAtIndex( 0 ) );
    }
    else if( _nChildCnt == 2 )
    {
        frontNode = dynamic_cast< CCNode* >( children->objectAtIndex( 1 ) );
        backNode = dynamic_cast< CCNode* >( children->objectAtIndex( 0 ) );
    }
    
    if( _bFront )
    {
        if (!backNode) backNode->setVisible( true );
        if (!frontNode) frontNode->setVisible( false );
    }
    else
    {
        if (!frontNode) frontNode->setVisible( true );
        if (!backNode) backNode->setVisible( false );
    }
}

void AceFlipActionNode::doFrontFlip()
{
    if( _nChildCnt <= 0 || !frontNode ) return;
    if( _nChildCnt == 2 && !backNode ) return;
    if( getFlipping() ) return;
    setFlipping( true );
    
    float fAngleX = getAngleX();
    float fAnlgeZ = getAngleZ( 0 );
    float fDeltaAngleZ = getDeltaAngleZ();

    _pFirstCamera = CCOrbitCamera::create( _fTime, 1, 0, fAnlgeZ, fDeltaAngleZ, fAngleX, 0 );
    CCCallFunc *pCallfunc = CCCallFunc::create( this, callfunc_selector( AceFlipActionNode::doBackFlip ) );
    CCSequence *pSequence = NULL;
    if( checkTwoNode() )
    {
        CCHide *pHide = CCHide::create();
        pSequence = CCSequence::create( _pFirstCamera, pHide, pCallfunc, NULL );
        
        if( _bFront )
        {
            frontNode->runAction( pSequence );
        }
        else
        {
            backNode->runAction( pSequence );
        }
    }
    else
    {
        pSequence = CCSequence::create( _pFirstCamera, pCallfunc, NULL );
        frontNode->runAction( pSequence );
    }
}

void AceFlipActionNode::doBackFlip()
{
    if( !getFlipping() ) return;
    
    float fAngleX = getAngleX();
    float fAnlgeZ = getAngleZ( 1 );
    float fDeltaAngleZ = getDeltaAngleZ();
    
    CCActionInterval* pOrbitCamera = CCOrbitCamera::create( _fTime, 1, 0, fAnlgeZ, fDeltaAngleZ, fAngleX, 0 );
    CCDelayTime *pDelayTime = CCDelayTime::create( _fTime );
    CCCallFunc *pCallfunc = CCCallFunc::create( this, callfunc_selector( AceFlipActionNode::finishedFlip ) );
    CCSequence *pSequence = NULL;
    
    if( checkTwoNode() )
    {
        CCShow *pShow = CCShow::create();
        pSequence = CCSequence::create( pShow, pOrbitCamera, pDelayTime, pCallfunc, NULL );
        
        setVisibleNode();
        if( _bFront )
        {
            frontNode->runAction( _pFirstCamera->reverse() );
            backNode->runAction( pSequence );
        }
        else
        {
            backNode->runAction( _pFirstCamera->reverse() );
            frontNode->runAction( pSequence );
        }
    }
    else
    {
        pSequence = CCSequence::create( pOrbitCamera, pDelayTime, pCallfunc, NULL );
        frontNode->runAction( pSequence );
    }
}

void AceFlipActionNode::finishedFlip()
{
    if( !getFlipping() ) return;
    
    if( checkTwoNode() )
    {
        _bFront = _bFront ? false : true;
        
        if (pCallTarget && pCallBackFlip) {
            // 추가적인 정보가 필요할경우 CCArray에 추가해서 보내기
            CCArray* pArray = CCArray::create();
            pArray->addObject(this);
            
            (pCallTarget->*(pCallBackFlip))(pArray);
        }
    }
    
    _nRemainRepeat -= 1;
    if( _nRemainRepeat <= 0 )
    {
        setFlipping( false );
        _nRemainRepeat = _nRepeat;
    }
    else
    {
        doFrontFlip();
    }
}

void AceFlipActionNode::flip()
{
    setFlipping( false );
    doFrontFlip();
}

float AceFlipActionNode::getAngleX() const
{
    if( _bRight )
    {
        return 180.f;
    }
    else
    {
        return 0;
    }
}

float AceFlipActionNode::getAngleZ(int type) const
{
    if( checkTwoNode() )
    {
        if( type == 0 )
        {
            return 0;
        }
        else
        {
            return 270.f;
        }
    }
    else
    {
        if( type == 0 )
        {
            return 0;
        }
        else
        {
            return 180.f;
        }
    }
}

float AceFlipActionNode::getDeltaAngleZ() const
{
    if( checkTwoNode() )
    {
        return 90;
    }
    else
    {
        return 180;
    }
}

bool AceFlipActionNode::checkTwoNode() const
{
    if( _nChildCnt &&
       backNode )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AceFlipActionNode::setVisibleNode()
{
    if( _bFront )
    {
        backNode->setVisible( true );
        frontNode->setVisible( false );
    }
    else
    {
        frontNode->setVisible( true );
        backNode->setVisible( false );
    }
}

bool AceFlipActionNode::getFlipping()
{
    return _bFlipping;
}

void AceFlipActionNode::setFlipping(bool isFlipping)
{
    _bFlipping = isFlipping;
}

void AceFlipActionNode::setFront(const bool isFront, const bool isRefresh)
{
    if( isRefresh )
    {
        float fAngleX = getAngleX();
        float fAnlgeZ = getAngleZ( 0 );
        float fDeltaAngleZ = getDeltaAngleZ();
        CCActionInterval* pOrbitCamera = CCOrbitCamera::create( 0, 1, 0, fAnlgeZ, fDeltaAngleZ, fAngleX, 0 );
        backNode->runAction( pOrbitCamera );
        CCLog("_bFront %d", _bFront);
        if( !_bFront )
        {
            setVisibleNode();
        }
    }
    
    _bFront = isFront;
}

