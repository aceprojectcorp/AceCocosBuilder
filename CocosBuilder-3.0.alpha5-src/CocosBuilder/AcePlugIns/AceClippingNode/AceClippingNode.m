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

#import "AceClippingNode.h"

@implementation AceClippingNode

- (void)onEnter
{
    [super onEnter];
    
    [self makeStencil];
}

- (id) init
{
    self = [super initWithStencil:[CCDrawNode node]];
    if (!self) return NULL;
        
    return self;
}

-(void) setContentSize:(CGSize)contentSize
{
    [super setContentSize:contentSize];
    
    [self makeStencil];
}

-(void) makeStencil
{
    CGPoint m_ClipRect[4];
    m_ClipRect[0] = ccp(0, 0);
    m_ClipRect[1] = ccp(0, [self contentSize].height);
    m_ClipRect[2] = ccp([self contentSize].width, [self contentSize].height);
    m_ClipRect[3] = ccp([self contentSize].width, 0);
    
    CCDrawNode *m_pStencil = (CCDrawNode*)_stencil;
    
    [m_pStencil clear];
    [m_pStencil drawPolyWithVerts:m_ClipRect count:4 fillColor:ccc4f(0, 0, 0, 1) borderWidth:0 borderColor:ccc4f(0, 0, 0, 1)];
}

@end
