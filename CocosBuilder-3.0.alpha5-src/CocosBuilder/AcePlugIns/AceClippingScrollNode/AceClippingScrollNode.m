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

#import "AceClippingScrollNode.h"

@implementation AceClippingScrollNode

@synthesize m_priority;
@synthesize scrollDir;
@synthesize bMaxContentSizeW;
@synthesize maxContentSizeW;
@synthesize bMaxContentSizeH;
@synthesize maxContentSizeH;
@synthesize resetPositionLock;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.m_priority = -129;
    self.scrollDir = SCROLL_DIR_UP_DOWN;
    self.bMaxContentSizeW = false;
    self.maxContentSizeW = 0;
    self.bMaxContentSizeH = false;
    self.maxContentSizeH = 0;
    self.resetPositionLock = false;
    
    if(self.bMaxContentSizeW)
    {
        CGSize mySize = [self contentSize];
        if(mySize.width > maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
            
            [self setContentSize:mySize];
        }
    }
    
    if(self.bMaxContentSizeH)
    {
        CGSize mySize = [self contentSize];
        if(mySize.height > maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
            
            [self setContentSize:mySize];
        }
    }
    
    
    return self;
}


- (void) visit
{
    //glScissor는 월드 좌표계로 설정해야 하기 때문에 현재 노드의 위치 및 크기를 변환함
    CGPoint pos = [self convertToWorldSpace:CGPointZero];
    
    CGPoint tmp = [self convertToWorldSpace:CGPointMake([self contentSize].width, [self contentSize].height)];
    
    CGSize size = CGSizeMake(tmp.x - pos.x, tmp.y - pos.y);
    
    glEnable(GL_SCISSOR_TEST);
    
    //직접 glScissor를 사용하면 android의 auto scale 모드 때문에 안됨
    glScissor(pos.x, pos.y, size.width, size.height);
    
    [super visit];
    
    glDisable(GL_SCISSOR_TEST);
    
    if([self isIgnoriAnchorPoint])
    {
        [self setIgnoreAnchorPointForPosition:false];
    }
}


@end
