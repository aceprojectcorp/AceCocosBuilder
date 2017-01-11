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
#import "AceTicker.h"

@implementation AceTicker

@synthesize moveDir;
@synthesize speed;
@synthesize stopDelay;


- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    moveDir = TICKER_DIR_LEFT;
    self.speed = 0;
    self.stopDelay = 0;
    
    m_bFirst = true;
    
    self.anchorPoint = CGPointMake(0.5, 0.5);
    
    [self schedule:@selector(update:)];
    
    return self;
}

-(void)draw
{
    [super draw];
    
    
}

-(void)update:(ccTime)delta
{
    float dx = speed * delta;
    
    CCArray* pArray = [self children];
    int tmpSize = (int)[pArray count];
    CCNode *pNode;
    for(int i=0; i<tmpSize; i++)
    {
        pNode = [pArray objectAtIndex:i];
        if(pNode)
        {
            [pNode setAnchorPoint:CGPointMake(0, 0)];
            CGPoint pos = pNode.position;
            
            switch(moveDir)
            {
                case TICKER_DIR_LEFT :
                    pos.x -= dx;
                    break;
                case TICKER_DIR_RIGHT :
                    pos.x += dx;
                    break;
                case TICKER_DIR_UP :
                    pos.y += dx;
                    break;
                case TICKER_DIR_DOWN :
                    pos.y -= dx;
                    break;
            }
            
            
            pNode.position = pos;
            
            bool bEnd = false;
           
            
            bEnd = [self isMoveEnd:pNode pos:pos];
            
            
            if(bEnd)
            {
                //[self unscheduleUpdate];
                [self unschedule:@selector(update:)];
                
                CCFiniteTimeAction* pAction1 = [CCDelayTime actionWithDuration:stopDelay];
                CCFiniteTimeAction* pAction2 = [CCCallFunc actionWithTarget:self selector:@selector(startTicker)];
                
                [self runAction:[CCSequence actionOne:pAction1 two:pAction2]];
            }
        }
    }
    
    //[self modeCheck];
}

-(bool) isMoveEnd:(CCNode*)pNode pos:(CGPoint)pos;
{
    bool val = false;
    
    switch(moveDir)
    {
        case TICKER_DIR_LEFT :
            if(pos.x + pNode.contentSize.width < 0) val = true;
            break;
        case TICKER_DIR_RIGHT :
            if(pos.x > [self contentSize].width) val = true;
            break;
        case TICKER_DIR_UP :
            if(pos.y > [self contentSize].height) val = true;
            break;
        case TICKER_DIR_DOWN :
            if(pos.y + pNode.contentSize.height < 0) val = true;
            break;
    }
    
    return val;
}

-(void)startTicker
{
    CCArray* pArray = [self children];
    int tmpSize = (int)[pArray count];
    CCNode *pNode;
    for(int i=0; i<tmpSize; i++)
    {
        pNode = [pArray objectAtIndex:i];
        if(pNode)
        {
            CGPoint pos = pNode.position;
            
            if(!m_bFirst)
            {
                //pos.x = self.contentSize.width;
                switch(moveDir)
                {
                    case TICKER_DIR_LEFT :
                        pos.x = self.contentSize.width;
                        break;
                    case TICKER_DIR_RIGHT :
                        pos.x = 0 - pNode.contentSize.width;
                        break;
                    case TICKER_DIR_UP :
                        pos.y = 0 - pNode.contentSize.height;
                        break;
                    case TICKER_DIR_DOWN :
                        pos.y = self.contentSize.height;
                        break;
                }
            }
            
            pNode.position = pos;
        }
    }

    //[self scheduleUpdate];
    [self schedule:@selector(update:)];

    m_bFirst = false;
}



@end
