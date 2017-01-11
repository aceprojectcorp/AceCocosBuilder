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
#import "AceFlipActionNode.h"

@implementation AceFlipActionNode

@synthesize _fTime;
@synthesize left;
@synthesize right;
@synthesize bFlip;


- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.bFlip = false;
    
    _fTime = 0.5;
    _nRepeat = 1;

    left = true;
    right = false;
    
    frontNode = NULL;
    backNode = NULL;
    
    nChildCnt = 0;
    _bFront = true;
    _bFlipping = false;
    
    [self schedule:@selector(run)];
    
    return self;
}

-(BOOL) checkTwoNode
{
    if( backNode &&
       nChildCnt == 2 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

-(void) run
{
    if( bFlip &&
       !_bFlipping )
    {
        _bFlipping = true;
        
        CCArray* children = [self children];
        nChildCnt = (int)[children count];
        if( nChildCnt == 1 )
        {
            frontNode = [children objectAtIndex:(int)0];
        }
        else if( nChildCnt == 2 )
        {
            frontNode = [children objectAtIndex:(int)1];
            backNode = [children objectAtIndex:(int)0];
            
            [ backNode setVisible:false ];
        }
        
        [ frontNode setVisible:true ];
        [ self doFrontFlip ];
        
        bFlip = false;
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        
        _nRemainRepeat = _nRepeat;
    }
}

// 두개의 노드 flip 시작.
-(void) doFrontFlip
{
    float fAngleX = [ self getAngleX ];
    float fAnlgeZ = [ self getAngleZ:0 ];
    float fDeltaAngleZ = [ self getDeltaAngleZ ];
    
    CCActionInterval* orbitCamera = [ CCOrbitCamera actionWithDuration:_fTime radius:1 deltaRadius:0 angleZ:fAnlgeZ deltaAngleZ:fDeltaAngleZ angleX:fAngleX deltaAngleX:0 ];
    CCCallFunc *pCallfunc = [ CCCallFunc actionWithTarget:self selector:@selector( doBackFlip ) ];
    CCSequence *pSequence = NULL;
    
    if( [ self checkTwoNode ] )
    {
        CCHide *pHide = [ CCHide action ];
        pSequence = [ CCSequence actions:orbitCamera, pHide, pCallfunc, nil ];
        
        if( _bFront )
        {
            [ frontNode runAction:pSequence ];
        }
        else
        {
            [ backNode runAction:pSequence ];
        }
    }
    else
    {
        pSequence = [ CCSequence actions:orbitCamera, pCallfunc, nil ];
        [ frontNode runAction:pSequence ];
    }
}

-(void) doBackFlip
{
    float fAngleX = [ self getAngleX ];
    float fAnlgeZ = [ self getAngleZ:1 ];
    float fDeltaAngleZ = [ self getDeltaAngleZ ];
    
    CCActionInterval* orbitCamera = [ CCOrbitCamera actionWithDuration:_fTime radius:1 deltaRadius:0 angleZ:fAnlgeZ deltaAngleZ:fDeltaAngleZ angleX:fAngleX deltaAngleX:0 ];
    CCShow *pShow = [ CCShow action ];
    CCCallFunc *pCallfunc = [ CCCallFunc actionWithTarget:self selector:@selector( finishedFlip ) ];
    CCSequence *pSequence = [ CCSequence actions:pShow, orbitCamera, pCallfunc, nil ];
    
    if( [ self checkTwoNode ] )
    {
        CCHide *pShow = [ CCShow action ];
        pSequence = [ CCSequence actions:pShow, orbitCamera, pCallfunc, nil ];
        
        if( _bFront )
        {
            [ backNode runAction:pSequence ];
        }
        else
        {
            [ frontNode runAction:pSequence ];
        }
    }
    else
    {
        pSequence = [ CCSequence actions:orbitCamera, pCallfunc, nil ];
        [ frontNode runAction:pSequence ];
    }
}

-(void) finishedFlip
{
    if( [ self checkTwoNode ] )
    {
        _bFront = _bFront ? false : true;
    }
    
    _nRemainRepeat -= 1;
    if( _nRemainRepeat == 0 )
    {
        _bFlipping = false;
    }
    else
    {
        [ self doFrontFlip ];
    }
}

-(float) getAngleX
{
    if( right )
    {
        return 180;
    }
    else
    {
        return 0;
    }
}

-(float) getAngleZ: (int)type
{
    if( [ self checkTwoNode ] )
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
            return 180;
        }
    }
}

-(float) getDeltaAngleZ
{
    if( [ self checkTwoNode ] )
    {
        return 90;
    }
    else
    {
        return 180;
    }
}

@end
