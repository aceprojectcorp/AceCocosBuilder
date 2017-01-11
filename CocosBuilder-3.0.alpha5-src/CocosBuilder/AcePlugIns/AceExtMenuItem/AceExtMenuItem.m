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
#import "AceExtMenuItem.h"


@implementation AceExtMenuItem

@synthesize m_selector;
@synthesize btnId;
@synthesize clickEffect;
@synthesize contentSizeRefresh;


//@synthesize ccbFile;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.m_selector = @"";
    self.btnId = @"";
    self.clickEffect = @"";
    self.contentSizeRefresh = false;

    
    prevSize = [self contentSize];
    
    
    

    //[self schedule:@selector(update:) interval:1];
    [self schedule:@selector(update:)];
    
    return self;
}

-(void)update:(ccTime)delta
{
    CCArray *children = [self children];
    CCNode *node;
    int tmpCount = (int)children.count;
    
    for(int i=0; i<tmpCount; i++)
    {
        node = [children objectAtIndex:(int)i];
        if(i == 0)
        {
            // content size 직접 영역 지정 [sj]
//            CGSize nowSize = CGSizeMake([node contentSize].width, [node contentSize].height);
//            [self setContentSize:nowSize];
        }
        
        //[node setPosition:CGPointMake([node contentSize].width / 2, [node contentSize].height / 2)];
    }
    
    if(contentSizeRefresh)
    {
        contentSizeRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        
    }
    
}




@end
