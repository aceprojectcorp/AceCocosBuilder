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
#import "InspectorSize.h"
#import "AceGridLayer.h"


@implementation AceGridLayer

//@synthesize cellNodeName;
@synthesize row;
@synthesize col;
@synthesize padingLeft;
@synthesize padingTop;
@synthesize gapX;
@synthesize gapY;
@synthesize cellWidth;
@synthesize cellHight;
@synthesize autoResize;
@synthesize contentSizeRefresh;
@synthesize bMaxContentSizeW;
@synthesize maxContentSizeW;
@synthesize bMaxContentSizeH;
@synthesize maxContentSizeH;
@synthesize bAddWidth;


- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    //self.cellNodeName = @"NULL";
    self.row = 2;
    self.col = 2;
    self.padingLeft = 5;
    self.padingTop = 5;
    self.cellWidth = 25;
    self.cellHight = 25;
    self.gapX = 5;
    self.gapY = 15;
    self.autoResize = true;
    self.contentSizeRefresh = false;
    self.bMaxContentSizeW = false;
    self.maxContentSizeW = 0;
    prevMaxContentSizeW = 0;
    self.bMaxContentSizeH = false;
    self.maxContentSizeH = 0;
    prevMaxContentSizeH = 0;
    
    self.bAddWidth = false;
    
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
    
    prevAutoResize = autoResize;
    prevSize = [self contentSize];
    

    
    return self;
}

-(void) draw
{
    [super draw];
    
    glEnable(GL_LINE_SMOOTH);
    
    
    CGSize mySize = [self contentSize];
    float startX = 0;
    float startY = 0;
    float endX = 0;
    float endY = 0;
    
    //--- 그리드 그리기
    for(int i=0; i<self.row; i++)
    {
        for(int j=0; j<self.col; j++)
        {
            if(bMaxContentSizeW || bMaxContentSizeH)
            {
                float newGapX = 0;
                if(col - 1 == 0)
                {
                    newGapX = 0;
                }
                else
                {
                    float tmpMyWidth = [self contentSize].width;
                    if(tmpMyWidth > maxContentSizeW)
                    {
                        tmpMyWidth = maxContentSizeW;
                    }
                    newGapX = (tmpMyWidth - (col*cellWidth)) / (col-1);
                }
                
                float newGapY = 0;
                if(row - 1 == 0)
                {
                    newGapY = 0;
                }
                else
                {
                    float tmpMyHeight = [self contentSize].height;
                    if(tmpMyHeight > maxContentSizeH)
                    {
                        tmpMyHeight = maxContentSizeH;
                    }
                    newGapY = (tmpMyHeight - (row*cellHight)) / (row-1);
                }
                
                if(bMaxContentSizeW)
                {
                    startX = (cellWidth + newGapX) * j;
                }
                else
                {
                    startX = padingLeft + (cellWidth + gapX) * j;
                }
                endX = startX + cellWidth;
                
                if(bMaxContentSizeH)
                {
                    startY = mySize.height - ((cellHight + newGapY)*i);
                }
                else
                {
                    startY = mySize.height - padingTop - ((cellHight + gapY)*i);
                }
                endY = startY - cellHight;
            }
            
            else
            {
                startX = padingLeft + (cellWidth + gapX) * j;
                endX = startX + cellWidth;
                startY = mySize.height - padingTop - ((cellHight + gapY)*i);
                endY = startY - cellHight;
            }
            
            ccDrawRect(ccp(startX, startY), ccp(endX, endY));
        }
    }
    
    //--- 아이템의 위치를 다시 정렬해준다.
    [self refresh];
    
    
    //--- 사이즈가 변경되면 컨텐츠 사이즈를 자동으로 수정해준다...(최대 가로 사이즈 제한, 최대 세로 사이즈 제한이 체크되어있을때만 수동으로 컨텐츠 사이즈를 변경할수있다.)
    float tmpMyWidth = padingLeft*2 + col*cellWidth + (col?col-1:0)*gapX;
    if(bMaxContentSizeW)
    {
        if(tmpMyWidth > maxContentSizeW || [self contentSize].width > maxContentSizeW)
        {
            tmpMyWidth = maxContentSizeW;
        }
        else
        {
            tmpMyWidth = [self contentSize].width;
        }
    }
    float tmpMyHeight = padingTop*2 + row*cellHight + (row?row-1:0)*gapY;
    if(bMaxContentSizeH)
    {
        if(tmpMyHeight > maxContentSizeH || [self contentSize].height > maxContentSizeH)
        {
            tmpMyHeight = maxContentSizeH;
        }
        else
        {
            tmpMyHeight = [self contentSize].height;
        }
    }
    if([self contentSize].width != tmpMyWidth || [self contentSize].height != tmpMyHeight)
    {
        CGSize tmpSize;
        tmpSize.width = tmpMyWidth;
        tmpSize.height = tmpMyHeight;
        [self setContentSize:tmpSize];
        
        /*
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
         */
        //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    
    if([self contentSize].width != prevSize.width || [self contentSize].height != prevSize.height)
    {
        prevSize = [self contentSize];
        /*
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
         */
        //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
}

-(void) refresh
{
    CGSize mySize = [self contentSize];
    float startX = 0;
    float startY = 0;

    CCArray* tmpChildren = [self children];
    int size = (int)tmpChildren.count;
    
    int tmpRow = 0;
    int tmpCol = 0;
    for(int i=0; i<size; i++)
    {
        if(bMaxContentSizeW || bMaxContentSizeH)
        {
            float newGapX = 0;
            if(col - 1 == 0)
            {
                newGapX = 0;
            }
            else
            {
                float tmpMyWidth = [self contentSize].width;
                if(tmpMyWidth > maxContentSizeW)
                {
                    tmpMyWidth = maxContentSizeW;
                }
                newGapX = (tmpMyWidth - (col*cellWidth)) / (col-1);
            }
            
            float newGapY = 0;
            if(row - 1 == 0)
            {
                newGapY = 0;
            }
            else
            {
                float tmpMyHeight = [self contentSize].height;
                if(tmpMyHeight > maxContentSizeH)
                {
                    tmpMyHeight = maxContentSizeH;
                }
                newGapY = (tmpMyHeight - (row*cellHight)) / (row-1);
            }
            
            if(bMaxContentSizeW)
            {
                startX = (cellWidth + newGapX) * tmpCol;
            }
            else
            {
                startX = padingLeft + (cellWidth + gapX) * tmpCol;
            }
            
            if(bMaxContentSizeH)
            {
                startY = mySize.height - ((cellHight + newGapY)*tmpRow);
            }
            else
            {
                startY = mySize.height - padingTop - ((cellHight + gapY)*tmpRow);
            }
        }
        else
        {
            startX = padingLeft + (cellWidth + gapX) * tmpCol;
            startY = mySize.height - padingTop - ((cellHight + gapY)*tmpRow);
        }
        
        startX += cellWidth*0.5f;
        startY -= cellHight*0.5f;
        
        CCNode* pNode = [tmpChildren objectAtIndex:(int)i];
        if(pNode)
        {
            [pNode setPosition:CGPointMake(startX, startY)];
        }
        
        
        if(bAddWidth)
        {
            tmpRow++;
            if(tmpRow >= self.row)
            {
                tmpRow = 0;
                tmpCol++;
            }
        }
        else
        {
            tmpCol++;
            if(tmpCol >= self.col)
            {
                tmpCol = 0;
                tmpRow++;
            }
        }
        
        
        
    }
    
    /*
    for(int i=0; i<self.row; i++)
    {
        for(int j=0; j<self.col; j++)
        {
            if(pos == size) break;
            
            if(bMaxContentSizeW || bMaxContentSizeH)
            {
                float newGapX = 0;
                if(col - 1 == 0)
                {
                    newGapX = 0;
                }
                else
                {
                    float tmpMyWidth = [self contentSize].width;
                    if(tmpMyWidth > maxContentSizeW)
                    {
                        tmpMyWidth = maxContentSizeW;
                    }
                    newGapX = (tmpMyWidth - (col*cellWidth)) / (col-1);
                }
                
                float newGapY = 0;
                if(row - 1 == 0)
                {
                    newGapY = 0;
                }
                else
                {
                    float tmpMyHeight = [self contentSize].height;
                    if(tmpMyHeight > maxContentSizeH)
                    {
                        tmpMyHeight = maxContentSizeH;
                    }
                    newGapY = (tmpMyHeight - (row*cellHight)) / (row-1);
                }
                
                if(bMaxContentSizeW)
                {
                    startX = (cellWidth + newGapX) * j;
                }
                else
                {
                    startX = padingLeft + (cellWidth + gapX) * j;
                }
                
                if(bMaxContentSizeH)
                {
                    startY = mySize.height - ((cellHight + newGapY)*i);
                }
                else
                {
                    startY = mySize.height - padingTop - ((cellHight + gapY)*i);
                }
            }
            else
            {
                startX = padingLeft + (cellWidth + gapX) * j;
                startY = mySize.height - padingTop - ((cellHight + gapY)*i);
            }
            
            startX += cellWidth*0.5f;
            startY -= cellHight*0.5f;
            
            CCNode* pNode = [tmpChildren objectAtIndex:(int)pos];
            if(pNode)
            {
                [pNode setPosition:CGPointMake(startX, startY)];
            }
            
            
            pos++;
        }
    }
     */
}

 //수정
/*
-(void)draw
{
 
 
    [super draw];
 
 
    glEnable(GL_LINE_SMOOTH);
    
    if(row == 0) row = 99;
    if(col == 0) col = 99;
    
    if(bMaxContentSizeW || bMaxContentSizeH)
    {
        float totalW;
        float itemW;
        int itemCntW;
        int gapCntW;
        float gapW;
        float tmpW;
        
        float totalH;
        float itemH;
        int itemCntH;
        int gapCntH;
        float gapH;
        float tmpH;
        
        if([self contentSize].width >= maxContentSizeW)
        {
            totalW = maxContentSizeW;
        }
        else
        {
            totalW = padingLeft*2 + cellWidth*col + gapX*(col-1);
        }
        itemCntW = col;
        
        gapCntW = itemCntW - 1;
        itemW = cellWidth;
        tmpW = totalW - (itemW * col);
        gapW = tmpW / gapCntW;
        
        
        
        
        if([self contentSize].height >= maxContentSizeH)
        {
            totalH = maxContentSizeH;
        }
        else
        {
            totalH = padingTop*2 + cellHight*row + gapY*(row-1);
        }
        itemCntH = row;
        
        gapCntH = itemCntH - 1;
        itemH = cellHight;
        tmpH = totalH - (itemH * row);
        gapH = tmpH / gapCntH;
        
        
        
        int tmpCol = 0;
        int tmpRow = 0;
        int count = col * row;
        //float height = [self contentSize].height;
        float height = totalH;
        float startX;
        float startY;
        float endX;
        float endY;
        for(int i=0; i<count; i++)
        {
            //float startX = itemW * tmpCol + gapW * tmpCol;
            //float startY = height - padingTop - tmpRow * (cellHight + gapY) - (cellHight);
            if(bMaxContentSizeW)
            {
                startX = itemW * tmpCol + gapW * tmpCol;
            }
            else
            {
                startX = padingLeft + tmpCol * (cellWidth + gapX);
            }
            
            if(bMaxContentSizeH)
            {
                startY = height - itemH * tmpRow - gapH * tmpRow;
            }
            else
            {
                startY = height - padingTop - tmpRow * (cellHight + gapY);
            }
            
            endX = startX + cellWidth;
            endY = startY + cellHight;
            
            ccDrawRect(ccp(startX, startY), ccp(endX, endY));
            
            tmpCol++;
            if(tmpCol >= self.col)
            {
                tmpCol = 0;
                tmpRow++;
            }
        }
        
    }
    else
    {
        //그리드 그리기
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                ccDrawRect(ccp(padingLeft + (self.cellWidth + gapX) * j, self.contentSize.height - padingTop - (cellHight + gapY) * i), ccp(padingLeft + self.cellWidth + (self.cellWidth + gapX) * j, self.contentSize.height - padingTop - self.cellHight - (cellHight + gapY) * i));
            }
        }
    }
    
    [self refresh];
    
}
 */

/* //원본
-(void)draw
{
    
    
    [super draw];
    
    
    glEnable(GL_LINE_SMOOTH);
    
    if(row == 0) row = 99;
    if(col == 0) col = 99;
    
    //그리드 그리기
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            ccDrawRect(ccp(padingLeft + (self.cellWidth + gapX) * j, self.contentSize.height - padingTop - (cellHight + gapY) * i), ccp(padingLeft + self.cellWidth + (self.cellWidth + gapX) * j, self.contentSize.height - padingTop - self.cellHight - (cellHight + gapY) * i));
        }
    }
    
    [self refresh];
    
}
*/

/*
//---수정
-(void) refresh
{
    CGSize tmpSize = prevSize;
    if(bMaxContentSizeW || bMaxContentSizeH)
    {
        CGSize mySize = [self contentSize];
        if([self contentSize].width >= maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
        }
        if([self contentSize].height >= maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
        }
        
        [self setContentSize:mySize];
    }
    else
    {
        if(autoResize)
        {
            tmpSize = [self calculateSize];
            [self setContentSize:tmpSize];
        }
    }
    
    int tmpRow = 0;
    int tmpCol = 0;
    float height = [self contentSize].height;
    
    
    
    CCArray* tmpChildren = [self children];
    if(tmpChildren)
    {
        if(bMaxContentSizeW || bMaxContentSizeH)
        {
            float totalW;
            float itemW;
            int itemCntW;
            int gapCntW;
            float gapW;
            float tmpW;
            
            float totalH;
            float itemH;
            int itemCntH;
            int gapCntH;
            float gapH;
            float tmpH;
            
            if([self contentSize].width >= maxContentSizeW)
            {
                totalW = maxContentSizeW;
            }
            else
            {
                totalW = [self contentSize].width;
            }
            itemCntW = col;
            
            gapCntW = itemCntW - 1;
            itemW = cellWidth;
            tmpW = totalW - (itemW * self.col);
            gapW = tmpW / gapCntW;

            
            
            if([self contentSize].height >= maxContentSizeH)
            {
                totalH = maxContentSizeH;
            }
            else
            {
                totalH = [self contentSize].height;
            }
            itemCntH = row;
            
            gapCntH = itemCntH - 1;
            itemH = cellHight;
            tmpH = totalH - (itemH * row);
            gapH = tmpH / gapCntH;
            
            
            int tmpCol = 0;
            int tmpRow = 0;
            for(int i=0; i<(int)tmpChildren.count; i++)
            {
                CCNode* pNode = [tmpChildren objectAtIndex:(int)i];
                if(pNode)
                {
                    CGPoint tmpPos = [pNode position];
                    //tmpPos.x = itemW * tmpCol + gapW * tmpCol + (cellWidth * 0.5);
                    //tmpPos.y = height - padingTop - tmpRow * (cellHight + gapY) - (cellHight * 0.5);
                    if(bMaxContentSizeW)
                    {
                        tmpPos.x = itemW * tmpCol + gapW * tmpCol + (cellWidth * 0.5);
                    }
                    else
                    {
                        tmpPos.x = padingLeft + tmpCol * (cellWidth + gapX) + (cellWidth * 0.5);
                    }
                    
                    if(bMaxContentSizeH)
                    {
                        tmpPos.y = height - itemH * tmpRow - gapH * tmpRow - (cellHight * 0.5);
                    }
                    else
                    {
                        tmpPos.y = height - padingTop - tmpRow * (cellHight + gapY) - (cellHight * 0.5);
                    }
                    
                    [pNode setPosition:tmpPos];
                    
                    tmpCol++;
                    if(tmpCol >= self.col)
                    {
                        tmpCol = 0;
                        tmpRow++;
                    }
                }
            }
           
        }
        else
        {
            int count = (int)[tmpChildren count];
            CCNode* pNode;
            for(int i=0; i<count; i++)
            {
                pNode = [tmpChildren objectAtIndex:i];
                if(!pNode) continue;
                
                float x = padingLeft + tmpCol * (cellWidth + gapX) + (cellWidth * 0.5);
                float y = height - padingTop - tmpRow * (cellHight + gapY) - (cellHight * 0.5);
                
                [pNode setPosition:CGPointMake(x, y)];
                
                tmpCol++;
                if(tmpCol >= self.col)
                {
                    tmpCol = 0;
                    tmpRow++;
                }
            }
        }
    }
    
    
    
    
    
    
    if( bMaxContentSizeW && (maxContentSizeW != prevMaxContentSizeW) && [self contentSize].width > maxContentSizeW)
    {
        prevMaxContentSizeW = maxContentSizeW;
        CGSize mySize = [self contentSize];
        mySize.width = maxContentSizeW;
        [self setContentSize:mySize];
        
        prevSize = mySize;
        
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    else
    {
        if(prevSize.width != tmpSize.width || prevSize.height != tmpSize.height)
        {
            prevSize = tmpSize;
            [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
            //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        }
        
        if(contentSizeRefresh)
        {
            contentSizeRefresh = false;
            [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
            [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        }
    }
}
 */

/* //원본
-(void) refresh
{
    CGSize tmpSize = prevSize;
    if(autoResize)
    {
        tmpSize = [self calculateSize];
        [self setContentSize:tmpSize];
    }
    
    int tmpRow = 0;
    int tmpCol = 0;
    float height = [self contentSize].height;
    
    
    
    CCArray* tmpChildren = [self children];
    if(tmpChildren)
    {
        int count = (int)[tmpChildren count];
        CCNode* pNode;
        for(int i=0; i<count; i++)
        {
            pNode = [tmpChildren objectAtIndex:i];
            if(!pNode) continue;
            
            float x = padingLeft + tmpCol * (cellWidth + gapX) + (cellWidth * 0.5);
            float y = height - padingTop - tmpRow * (cellHight + gapY) - (cellHight * 0.5);
            
            [pNode setPosition:CGPointMake(x, y)];
            
            tmpCol++;
            if(tmpCol >= self.col)
            {
                tmpCol = 0;
                tmpRow++;
            }
        }
    }
    
    
    
    
    if(prevSize.width != tmpSize.width || prevSize.height != tmpSize.height)
    {
        prevSize = tmpSize;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    if(contentSizeRefresh)
    {
        contentSizeRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
}
 */

//---수정
-(CGSize) calculateSize
{
    CGSize size = [self contentSize];
    
    int count = (int)[[self children] count];
    if(autoResize)
    {
        int r = count / col;
        if(bAddWidth)
        {
            r = count / row;
            if(count % row) r++;
        }
        else
        {
            if(count % col) r++;
        }
        
        
        if(bMaxContentSizeW && [self contentSize].width >= maxContentSizeW)
        {
            size.width = maxContentSizeW;
        }
        else
        {
            if(bAddWidth) size.width = padingLeft * 2 + cellWidth * r + gapX * (r ? r - 1 : 0);
            else size.width = padingLeft * 2 + cellWidth * col + gapX * (col ? col - 1 : 0);
        }
        
        if(bMaxContentSizeH && [self contentSize].height >= maxContentSizeH)
        {
            size.height = maxContentSizeH;
        }
        else
        {
            if(bAddWidth) size.height = padingTop * 2 + cellHight * row + gapY * (row ? row - 1 : 0);
            else size.height = padingTop * 2 + cellHight * r + gapY * (r ? r - 1 : 0);
        }
    }
    
    return size;
}

/* //원본
-(CGSize) calculateSize
{
    CGSize size = [self contentSize];
    
    int count = (int)[[self children] count];
    if(autoResize)
    {
        int r = count / col;
        if(count % col) r++;
        
        size.width = padingLeft * 2 + cellWidth * col + gapX * (col ? col - 1 : 0);
        size.height = padingTop * 2 + cellHight * r + gapY * (r ? r - 1 : 0);
    }
    
    return size;
}
*/

@end
