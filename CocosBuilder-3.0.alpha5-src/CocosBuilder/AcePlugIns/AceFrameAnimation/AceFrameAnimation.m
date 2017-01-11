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
#import "AceFrameAnimation.h"

@implementation AceFrameAnimation

@synthesize m_fps;
@synthesize nowFrameIdx;
@synthesize bLoop;
@synthesize bPlay;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    
    self.m_fps = 30;
    self.nowFrameIdx = 0;
    self.bLoop = true;
    self.bPlay = false;
    
    delay = 0;
    prevFrameIdx = -1;
    bPrevPlay = bPlay;
    
    [self childReset];
    
    [self schedule:@selector(update:)];
    
    return self;
}

-(void)update:(ccTime)delta
{
    CCArray *children = [self children];
    int size = (int)children.count;
    
    if(bPrevPlay != bPlay)
    {
        bPrevPlay = bPlay;
        delay = 0;
        prevFrameIdx = -1;
        nowFrameIdx = 0;
        
        if(bPlay) [self childReset];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    if(bPlay && delay == 0 && (int)nowFrameIdx < size)
    {
        //prevFrame
        if(prevFrameIdx != -1)
        {
            CCNode* prevNode = [children objectAtIndex:(int)prevFrameIdx];
            [prevNode setVisible:false];
        }
        
        //nowFrame
        CCNode* nowNode = [children objectAtIndex:(int)nowFrameIdx];
        [nowNode setVisible:true];
        
        prevFrameIdx = (int)nowFrameIdx;
        
        nowFrameIdx++;
        if(bLoop)
        {
            if((int)nowFrameIdx >= size)
            {
                nowFrameIdx = 0;
            }
        }
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    delay += delta;
    if(delay > 1 / m_fps)
    {
        delay = 0;
    }
    
    
}

-(void) childReset
{
    CCArray* children = [self children];
    CCNode* pNode;
    int size = (int)children.count;
    for(int i=0; i<size; i++)
    {
        pNode = [children objectAtIndex:(int)i];
        [pNode setVisible:false];
    }
}


@end
