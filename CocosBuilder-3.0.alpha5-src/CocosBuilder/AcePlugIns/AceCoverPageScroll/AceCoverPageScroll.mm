/*
 * CocosBuilder: http://www.cocosbuilder.com
 *
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#import "CocosBuilderAppDelegate.h"
#import "AceCoverPageScroll.h"

@implementation AceCoverPageScroll


@synthesize m_bStartAction;
@synthesize m_bReset;





- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    m_vecArray.clear();
    
    
    m_bStartAction = false;
    m_bReset = false;
    
    m_pNodeArray = nil;
    
    
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
    
    outVec = ccp(-400, 600);
    
    m_iShowCnt = 3;
    
    m_fMoveY = 0.0f;
    
    [self start];
    
    self.anchorPoint = CGPointMake(0.5, 0.5);
    
    [self schedule:@selector(update:)];
    
    return self;
}

-(void)start
{
    m_pNodeArray = [self children];
    
    if ( m_pNodeArray != nil )
    {
        CCArray* pArray = m_pNodeArray;
        m_iChildCnt = (int)[pArray count];
        
        m_vecArray.clear();
        m_vecArray.resize(m_iChildCnt);
        
        [self sortAllChildren];
        
        for ( int i = 0 ; i < m_iChildCnt ; i ++ )
        {
            CCNode * pNode = [pArray objectAtIndex:i];
            if(pNode)
            {
                int d = pNode.depth;
                pNode.zOrder = d;
            }
        }
        
        [self sortAllChildren];

        for ( int i = 0 ; i < m_iChildCnt ; i ++ )
        {
            CCNode * pNode = [pArray objectAtIndex:i];
            if(pNode)
            {
                m_vecArray[i]._pNode = pNode;
            }
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
        
    }
    else
    {
        m_iChildCnt = 0;
    }
}

-(void)draw
{
    [super draw];
    
    
}

-(void) actionInit:(ccTime)d
{
    CCArray* pArray = m_pNodeArray;
    int tmpSize = (int)[pArray count];
    for(int i=0; i<tmpSize; i++)
    {
        CCNode * pNode = [pArray objectAtIndex:i];
        if(pNode)
        {
        }
    }
}

-(void)update:(ccTime)delta
{
    if ( m_iOldShowCnt != m_iShowCnt )
    {
        m_iOldShowCnt = m_iShowCnt;
        [self reset];
        return;
    }
    
    if ( m_bReset == true )
    {
        m_bReset = false;
        [self reset];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        [self draw:delta];
        return;
        
    }
    
    if ( m_bStartAction == true )
    {
        [self draw:delta];
    }
    //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    
    //[self modeCheck];
}

-(void) draw:(ccTime)d
{
    if ( m_iChildCnt < 1 )
        return;
    
    zvec fwdVec = vecForward;
    zvec rightVec = zvec(1, 0, 0);
    zvec upVec = vecUp;
    zmat4 zRolMat(m_fAngle, rightVec);
    
    float angleOne = m_fAngleOne;
    //float hAngle = angleOne / 2.0f;
    float angleFirst = -angleOne * (m_iShowCnt-1);
    
    m_fLocationAngle += -d * m_fScrollSpeed;
    
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
    
    if ( isChange == true )
    {
        if ( m_bLoop == false )
        {
            if ( m_iNowCur > m_iMaxCur )
            {
                m_iNowCur = m_iMaxCur;
                m_bStartAction = false;
                [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
            }
            else if ( m_iNowCur < 0 )
            {
                m_iNowCur = 0;
                m_bStartAction = false;
                [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
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
    }
    
    //---------------------------------------------------------
    
    //m_pNodeArray = [self children];
    //CCArray* pArray = m_pNodeArray;
    int tmpSize = m_iChildCnt;
    for(int i=0; i<tmpSize; i++)
    {
        zvec nVec = zvec(outVec.x + 100 * i, outVec.y, 0.0f);
        m_vecArray[i]._vPosition = nVec;
        m_vecArray[i]._fScale = 1.0f;
        m_vecArray[i]._iOpacity = 255;
        m_vecArray[i]._fZ = 1.0f;
        m_vecArray[i]._fA = 1.0f;
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
            int nKey = i % m_iChildCnt;
            useUnits[k] = nKey;
            k ++;
            
        }
    }
    
    //-------그리기 전 위치 지정-------------------------
    CGSize mySize = [self contentSize];
    float start_X = mySize.width / 2.0f;
    float start_Y = mySize.height / 2.0f + m_fMoveY;
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
                        //Color c = obj._spr.color;
                        //c.a = m_fMinAlpha + ( 1.0f - m_fMinAlpha ) * v;
                        //obj._spr.color = c;
                        //obj._spr.depth = (int)(z * 100.0f);
                        nVec.x += start_X;
                        nVec.y += start_Y;
                        float c = m_fMinAlpha + ( 1.0f - m_fMinAlpha ) * v;
                        m_vecArray[key]._fScale = vv;
                        m_vecArray[key]._vPosition = nVec;
                        m_vecArray[key]._iOpacity = (int)(255.0f * c);
                        m_vecArray[key]._fZ = z;
                        m_vecArray[key]._fA = c;
                    }
                    else
                    {
                        
                    }
                }
            }
        }
        angleFirst += angleOne;
        
    }
    
    delete  [] useUnits;
    
    for(int i=0; i<tmpSize; i++)
    {
        CCNode * pNode = m_vecArray[i]._pNode;
        if(pNode)
        {
            pNode.position = ccp(m_vecArray[i]._vPosition.x, m_vecArray[i]._vPosition.y);
            pNode.scaleX = m_vecArray[i]._fScale;
            pNode.scaleY = m_vecArray[i]._fScale;
            [self setChildrenOpacity:pNode value:(int)(m_vecArray[i]._fA * 255.0f)];
            pNode.zOrder = (int)(m_vecArray[i]._fZ * 100.0f);
            
        }

    }
    if ( isChange == true )
    {
        for(int i=0; i<tmpSize; i++)
        {
            
        }

    }

}
-(void) setChildrenOpacity:(CCNode *)pNode value:(int)v
{
    CCArray* pArray = [pNode children];
    int cnt = (int)[pArray count];
    for ( int i  = 0 ; i < cnt ; i ++ )
    {
        CCNode * n = [pArray objectAtIndex:i];
        if ( n )
        {
            if ( [n isKindOfClass:[CCSprite class]] )
            {
                CCSprite *s = (CCSprite *)n;
                s.opacity = v;
            }
        }
    }
}

-(void) reset
{
    
    [self start];
    m_fLocationAngle = 0.0f;
    
}
/*
 defaults delete com.cocosbuilder.CocosBuilder
 open -a CocosBuilder /Users/pat/work/MLBCocosBuilder/MLBCocosBuilder.ccbproj
 rm -r /Users/pat/work/BEngine/BEngineCocosBuilder/CocosBuilder.app
 cp -r /Users/pat/work/cocos/CocosBuilder-3.0.alpha5-src/build/CocosBuilder.app /Users/pat/work/BEngine/BEngineCocosBuilder/CocosBuilder.app
*/

@end
