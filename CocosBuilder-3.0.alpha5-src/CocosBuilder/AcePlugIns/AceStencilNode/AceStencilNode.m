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

#import "AceStencilNode.h"

@implementation AceStencilNode

- (void)onEnter
{
    [super onEnter];
    
    [self makeStencil];
}

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    return self;
}

-(void) visit
{
    [super visit];
    
    [self makeStencil];
}

-(void) makeStencil
{
    [self setAlphaThreshold:0];
    
    CCArray* children = [self children];
    int size = (int)[children count];
    
    //자식이 있을때만...
    if(size > 0)
    {
        //AceStencilNode의 첫번째 자식을 MaskNode로 사용한다.
        CCNode* pMaskNode = (CCNode*)[children objectAtIndex:(int)0];
        
        //현재 셋팅된 스텐실과 다를때만...
        if (pMaskNode != _stencil)
        {
            //스텐실 설정
            [self setStencil:pMaskNode];
        }
    }
    
}

@end
