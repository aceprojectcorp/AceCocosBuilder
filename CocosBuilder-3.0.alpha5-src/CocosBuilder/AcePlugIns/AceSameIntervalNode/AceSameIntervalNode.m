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

#import "AceSameIntervalNode.h"

@implementation AceSameIntervalNode



- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    
    
    return self;
}


- (void) draw
{
    //CGSize winSize = [[CCDirector sharedDirector] winSize];
    float totalW;
    float itemW;
    int itemCnt;
    int gapCnt;
    float gapW;
    float tmpW;
    
    CCArray* children = [self children];
    
    totalW = [self contentSize].width;
    itemCnt = (int)children.count;
    
    if(itemCnt > 1)
    {
        gapCnt = itemCnt - 1;
        itemW = [[children objectAtIndex:(int)0] contentSize].width;
        tmpW = totalW - (itemW * itemCnt);
        gapW = tmpW / gapCnt;
        
        for(int i=0; i<itemCnt; i++)
        {
            CCNode* pNode = [children objectAtIndex:(int)i];
            if(pNode)
            {
                CGPoint tmpPos = [pNode position];
                tmpPos.x = itemW * i + gapW * i;
                
                [pNode setPosition:tmpPos];
            }
        }
    }
}



@end
