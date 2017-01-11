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
#import "AceFlowLayer.h"

@implementation AceFlowLayer

@synthesize padingLeft;
@synthesize padingTop;
@synthesize gapY;
@synthesize m_align_left;
@synthesize m_align_center;
@synthesize m_align_right;
@synthesize contentSizeRefresh;

int stateCount;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    checkIdx = 1;
    
    self.padingLeft = 0;
    self.padingTop = 0;
    self.gapY = 15;
    self.m_align_left = false;
    self.m_align_center = true;
    self.m_align_right = false;
    self.contentSizeRefresh = false;
    
    stateCount = 0;
    
    return self;
}

-(void)draw
{
    [super draw];
    
    [self alignCheck];
    
    if(stateCount % 50 == 0)
    {
        CCArray* pArray = [self children];
        if(pArray)
        {
            [self repaint];
        }
    }
    
    stateCount++;
    if(stateCount > 999999)
    {
        stateCount = 0;
    }
    
    CCArray *children = [self children];
    CCNode *node;
    int size = (int)children.count;
    if(contentSizeRefresh)
    {
        if(size > 0)
        {
            float tmpW = 0;
            float tmpH = 0;
            
            for(int i=0; i<size; i++)
            {
                node = [children objectAtIndex:(int)i];
                tmpH += [node contentSize].height;
            }
            
            tmpW = [self contentSize].width;
            tmpH += (padingTop * 2) + (gapY * (size - 1));
            
            [self setContentSize:CGSizeMake(tmpW, tmpH)];
        }
        
        contentSizeRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
}

-(void)repaint
{
    CCArray* pArray = [self children];
    float width = self.contentSize.width;
    float height = padingTop * 2;
    
    int tmpSize = (int)[pArray count];
    CCNode *pNode;
    for(int i=0; i<tmpSize; i++)
    {
        pNode = [pArray objectAtIndex:i];
        if(pNode)
            height += pNode.contentSize.height + gapY;
    }
    
    height -= gapY;
    
    CGSize size = CGSizeMake(width, height);
    
    self.contentSize = size;
    
    float x = padingLeft;
    float y = size.height - padingTop;
    
    

    for(int i=0; i<tmpSize; i++)
    {
        pNode = [pArray objectAtIndex:i];
        if(pNode)
        {
            pNode.anchorPoint = CGPointMake(0, 1);
            
            if(m_align_left)
            {
                
            }
            else if(m_align_center)
            {
                x = [self contentSize].width * 0.5 - pNode.contentSize.width * 0.5;
            }
            else if(m_align_right)
            {
                x = [self contentSize].width - padingLeft - pNode.contentSize.width;
            }
            
            pNode.position = CGPointMake(x, y);
            
            y -= pNode.contentSize.height + gapY;
        }
    }
}

-(void)alignCheck
{
    bool tmpCheck[3] = {false, false, false};
    
    tmpCheck[0] = m_align_left;
    tmpCheck[1] = m_align_center;
    tmpCheck[2] = m_align_right;
    
    int trueCount = 0;
    for(int i=0; i<3; i++)
    {
        if(tmpCheck[i]){
            trueCount++;
        }
    }
    
    if(trueCount == 0)
    {
        switch(checkIdx)
        {
            case 0 :
                m_align_left = true;
                break;
            case 1 :
                m_align_center = true;
                break;
            case 2 :
                m_align_right = true;
                break;
        }
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    else
    {
        for(int i=0; i<3; i++)
        {
            if(tmpCheck[i] && i != checkIdx)
            {
                checkIdx = i;
                
                switch(checkIdx)
                {
                    case 0 :
                        m_align_left = true;
                        m_align_center = false;
                        m_align_right = false;
                        break;
                    case 1 :
                        m_align_left = false;
                        m_align_center = true;
                        m_align_right = false;
                        break;
                    case 2 :
                        m_align_left = false;
                        m_align_center = false;
                        m_align_right = true;
                        break;
                }
                
                [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
                break;
            }
        }
    }
}



@end
