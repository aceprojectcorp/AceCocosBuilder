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


#include <vector>
using namespace std;

#import "cocos2d.h"

#include "../Ace3DMath/ZVector.h"
#include "../Ace3DMath/ZMatrix.h"


@interface AceBarGraph : CCLayer
{
    bool m_bScroll;
    bool m_bRight;
    int m_iScrollW;
    
    int m_iSelectedIdx;
    
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
    
    bool m_bReset;
    
    float m_fSpeed;
    ////////////////////////////////////
    float m_fOneW;
    
    //int m_iCenterValue;
    int m_iMaxValue;
    int m_iMinValue;
    
    CGPoint *m_pBackVertex_s;
    CGPoint *m_pLineVertex_s;
    CGPoint *m_pVertex_s;
    int m_iCntVertex;
    
    int m_idxVertex;
    float m_fNowDrawFlag;
    float m_fNowDrawGraph;
    float m_fMaxDrawFlag;
    float m_fSeta;
    
    /////////////////////////////////
    vector<int> m_vecData;
    
}




-(void)_update:(ccTime)delta;
-(void) draw:(ccTime)d;
-(void) reset;
-(void) DrawLine:(CGPoint)pp1 p2:(CGPoint)pp2 color:(ccColor4F)col width:(float)w;
@end
