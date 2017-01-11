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

#include "../Ace3DMath/ZVector.h"
#include "../Ace3DMath/ZMatrix.h"

using namespace std;

#import "cocos2d.h"
#import "AceClippingNode.h"

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


//@interface AceCoverPageScroll : CCNode
@interface AceCoverPageScroll : CCLayer
{
    vector<Units> m_vecArray;
    
    bool m_bStartAction;
    bool m_bReset;
    
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
    
    CGPoint outVec;
   
    int m_iShowCnt;
    int m_iNeedMinCnt;
    
    int m_iOldShowCnt;
    
    float m_fMoveY;
}

@property (nonatomic,assign) bool  m_bStartAction;
@property (nonatomic,assign) bool  m_bReset;



-(void) actionInit:(ccTime)d;
-(void) reset;
-(void) start;
-(void) draw:(ccTime)d;
-(void) setChildrenOpacity:(CCNode *)pNode value:(int)v;
@end
