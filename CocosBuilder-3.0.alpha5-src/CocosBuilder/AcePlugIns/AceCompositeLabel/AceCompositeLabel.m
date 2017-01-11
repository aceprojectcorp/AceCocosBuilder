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
#import "AceCompositeLabel.h"

@implementation AceCompositeLabel

@synthesize m_align_left;
@synthesize m_align_center;
@synthesize m_align_right;
@synthesize contentSizeRefresh;
@synthesize gapX;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    checkIdx = 1;
    
    self.m_align_left = false;
    self.m_align_center = true;
    self.m_align_right = false;
    self.contentSizeRefresh = false;
    self.gapX = 20;
   
    return self;
}

-(void)draw
{
    [super draw];
    
    [self repaint];
    
    [self alignCheck];
    
    CCArray *children = [self children];
    CCNode *node;
    int size = (int)children.count;
    
    if(contentSizeRefresh)
    {
        if(size > 0)
        {
            float tmpW = 0;
            for(int i=0; i<size; i++)
            {
                node = [children objectAtIndex:(int)i];
                tmpW += [node contentSize].width;
            }
            
            tmpW += (gapX * (size - 1));
            
            [self setContentSize:CGSizeMake(tmpW, [self contentSize].height)];
        }
        
        contentSizeRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
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

-(void)repaint
{
    float width = 0;
    CCArray* childArray = [self children];
    int size = (int)[childArray count];
    CCNode* pNode;
    
    
    for(int i=0; i<size; i++)
    {
        pNode = [childArray objectAtIndex:i];
        if(pNode)
            width += pNode.contentSize.width;
    }
    
    width += (gapX * (size - 1));
    
    
    float x = 0;
    
    if(m_align_left)
    {
        
    }
    else if(m_align_center)
    {
        x = ([self contentSize].width - width) * 0.5;
    }
    else if(m_align_right)
    {
        x = ([self contentSize].width - width);
    }
    
    float y = [self contentSize].height * 0.5;
    
    for(int i=0; i<size; i++)
    {
        pNode = [childArray objectAtIndex:i];
        if(pNode)
        {
            pNode.anchorPoint = CGPointMake(0, 0.5);
            pNode.position = CGPointMake(x, y);
            
            x += pNode.contentSize.width + gapX;
        }
    }
   
}



@end
