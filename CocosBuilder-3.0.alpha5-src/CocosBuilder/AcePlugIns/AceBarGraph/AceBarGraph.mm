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
#import "AceBarGraph.h"

@implementation AceBarGraph


- (id) init
{

    self = [super init];
    if (!self) return NULL;
    
    /////////////////
    m_bScroll = false;
    m_bRight = false;
    
    m_iSelectedIdx = 0;
    
    m_iHeight = 200;
    m_iWidth = 200;
    
    m_iCenterHeight = 80;
    
    m_iCntPoint = 10;
 
    
    
    m_iMargin = 0;

    
    //////////////////
    
    m_fBackA = 0.5f;
    
    m_fLineA = 1.0f;
    m_fLineWidth = 2.0f;
    
    
    m_fBarA = 1.0f;
    
    
    m_pVertex_s = NULL;
    m_pBackVertex_s = NULL;
    m_pLineVertex_s = NULL;
    
    m_fSpeed = 100.0f;
    /////////////////////
    
    [self schedule:@selector(_update:)];
    
    return self;
}


-(void) onEnter
{
    
    
    [self reset];
    
    
    [super onEnter];
}

-(void) onEnterTransitionDidFinish
{
    [super onEnterTransitionDidFinish];
}


-(void) onExit
{
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
    
    [super onExit];
}

-(void) DrawLine:(CGPoint)pp1 p2:(CGPoint)pp2 color:(ccColor4F)col width:(float)w
{
    float oneS = w / 2.0f;
    
    
    CGPoint lines[2];
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
    
    zvec __up(0,1,0);
    zvec __fwd;//zvecFoward;
    
    if( line_1.y > 0.0f )
        __fwd = zvec(0, 0, 1);
    else
        __fwd = - zvec(0, 0, 1);
    
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


-(void)draw
{
    [super draw];
    
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
            
        }
        else
        {
            AceDrawStart();
            
            ////////////////////////////////////////////
            ccColor4F backCol = ccc4f((float)m_backColor.r / 255.0f,
                                      (float)m_backColor.g / 255.0f,
                                      (float)m_backColor.b / 255.0f,
                                      m_fBackA);
            if ( m_fBackA > 0.0f )
            {
                if ( m_iMargin == 0 )
                {
                    CGPoint backPoints[4];
                    
                    backPoints[0].x = 0.0f;
                    backPoints[0].y = 0.0f;
                    backPoints[1].x = 0.0f;
                    backPoints[1].y = m_iHeight;
                    backPoints[2].x = m_iWidth;
                    backPoints[2].y = 0.0f;
                    backPoints[3].x = m_iWidth;
                    backPoints[3].y = m_iHeight;
                    
                    ccDrawSolidPoly2((CGPoint*)backPoints, 4, backCol);
                }
                else if ( m_pBackVertex_s != NULL )
                {
                    CGPoint* pLastPoint = m_pBackVertex_s;
                    
                    
                    for ( int i = 0 ; i < m_iCntPoint ; i ++ )
                    {
                        ccDrawSolidPoly2((CGPoint*)pLastPoint, 4, backCol);
                        pLastPoint += 4;
                    }
                }
            }
            ////////////////////////////////////////////
            
            
            
            CGPoint* pLastPoint = m_pVertex_s;
            CGPoint* pLinePoint = m_pLineVertex_s;
            
            ccColor4F col = ccc4f((float)m_barColor.r / 255.0f,
                                  (float)m_barColor.g / 255.0f,
                                  (float)m_barColor.b / 255.0f,
                                  m_fBarA);
            
            ccColor4F colLine = ccc4f((float)m_lineColor.r / 255.0f,
                                  (float)m_lineColor.g / 255.0f,
                                  (float)m_lineColor.b / 255.0f,
                                  m_fLineA);

            
            for ( int i = 0 ; i < m_iCntPoint ; i ++ )
            {
                if ( m_iSelectedIdx != i )
                {
                    ccDrawSolidPoly2((CGPoint*)pLinePoint, 4, col);
                }
                else
                {
                    ccDrawSolidPoly2((CGPoint*)pLinePoint, 4, colLine);
                    ccDrawSolidPoly2((CGPoint*)pLastPoint, 4, col);
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
                
                CGPoint backPoints[4];
                
                backPoints[0].x = 0.0f;
                backPoints[0].y = startY;
                backPoints[1].x = 0.0f;
                backPoints[1].y = startY + m_fCenterLineWidth;
                backPoints[2].x = m_iWidth;
                backPoints[2].y = startY;
                backPoints[3].x = m_iWidth;
                backPoints[3].y = startY + m_fCenterLineWidth;
                
                
                ccDrawSolidPoly2((CGPoint*)backPoints, 4, colLine);

            }
            
            if ( m_bScroll == true )
            {
                colLine = ccc4f((float)1,
                                (float)0,
                                (float)0,
                                1.0f);
                
                
                CGPoint backPoints[2];
                
                backPoints[0].x = m_iScrollW;
                backPoints[0].y = 0;
                backPoints[1].x = m_iScrollW;
                backPoints[1].y = m_iHeight;
                
                [self DrawLine:backPoints[0] p2:backPoints[1] color:colLine width:1];
                
                
                
                

            }
            
        }
        
    }
    
}

#include "../Ace3DMath/ZVector.h"

-(void)_update:(ccTime)delta
{
    if ( m_bReset == true )
    {
        m_bReset = false;
        
        [self reset];
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    else
    {
        float speed = m_fSpeed * delta;
        /*
        if ( m_fNowDrawFlag < m_fMaxDrawFlag)
        {
            m_fNowDrawFlag += speed;
            m_fSeta = m_fNowDrawFlag / m_fMaxDrawFlag;
            float pit = m_fSeta * zPI / 2.0f;
            float sin_s = sinf(pit);
            //sin_s = sqrtf(sin_s);
            m_fNowDrawGraph = sin_s * m_fMaxDrawFlag;
            m_idxVertex = 1 + (int)(m_fNowDrawGraph / (float)m_iLenPointToPoint);
            
        }
        else
        {
            m_idxVertex = m_iCntPoint + 1;
          
         m_fNowDrawGraph = m_fMaxDrawFlag;
        }
         */
    }
}

-(void) draw:(ccTime)d
{
    
}

-(void) reset
{
    m_bReset = false;
    
    m_iMaxValue = 100;
    m_iMinValue = -100;
    
    m_idxVertex = 1;
    
    m_fOneW = (float)(m_iWidth - (m_iCntPoint-1) * m_iMargin) / (float)m_iCntPoint;
    float oneW = m_fOneW + m_iMargin;
    
    
    m_fNowDrawFlag = (float)0.0f;
    m_fMaxDrawFlag = (float)(m_iCntPoint - 1) * (float)m_fOneW;
    m_fNowDrawGraph = 0.0f;
    
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

    int iLenValue = m_iMaxValue - m_iMinValue;
    
    int useableH = iLenValue;
    
    m_vecData.clear();
    for ( int i = 0 ; i < m_iCntPoint ; i ++ )
    {
        int rand_v = (int)(rand() % useableH) + m_iMinValue;
        m_vecData.push_back(rand_v);
        
    }
    
    
    m_iCntVertex = m_iCntPoint * 4;
    CGPoint *vertex_s = new CGPoint[m_iCntVertex];
    m_pLineVertex_s = vertex_s;
    
    CGPoint *pV = vertex_s;
    float fL = (float)0.0f;
    float upD = (float)(m_iHeight - m_iCenterHeight) / 100.0f;
    float downD = (float)m_iCenterHeight / 100.0f;
    float drawStartY = (float)m_iCenterHeight;
    for ( int i = 0 ; i < m_iCntPoint ; i ++ )
    {
        int v = m_vecData[i];
        if ( v > 0 )
        {
            float vv = v * upD;
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
            float vv = v * downD;
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
    vertex_s = new CGPoint[m_iCntVertex];
    m_pVertex_s = vertex_s;
    
    pV = vertex_s;
    fL = (float)m_fLineWidth;
    float lineOneW = m_fOneW - (m_fLineWidth * 2.0f);
    for ( int i = 0 ; i < m_iCntPoint ; i ++ )
    {
        int v = m_vecData[i];
        if ( v > 0 )
        {
            float vv = v * upD - m_fLineWidth;
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
            float vv = v * downD + m_fLineWidth;
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
        vertex_s = new CGPoint[m_iCntVertex];
        m_pBackVertex_s = vertex_s;
        CGPoint *pV = vertex_s;
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
    
    /*
     
    
    //float dy = (float)((float)useableH / (float)iLenValue );
    
    m_iCntVertex = ( m_iCntPoint - 1 ) * 2 + 2;
    
    //float values[] = { (float)m_iMaxValue / 2, (float)m_iMaxValue, };
    
    CGPoint *vertex_s = new CGPoint[m_iCntVertex];
    m_pVertex_s = vertex_s;
    
    
    vertex_s[0].x = 0.0f;
    vertex_s[0].y = drawStartY + m_vecData[0];
    vertex_s[1].x = 0.0f;
    vertex_s[1].y = drawStartY;
    
    
    
    CGPoint *pV = vertex_s + 2;
    float fL = (float)m_iLenPointToPoint;
    
    for ( int i = 1 ; i < m_iCntPoint ; i ++ )
    {
        pV[0].x = fL;
        pV[0].y = drawStartY + m_vecData[i];
        pV[1].x = fL;
        pV[1].y = drawStartY;
        
        pV += 2;
        fL += (float)m_iLenPointToPoint;
    }
     */
}



@end
