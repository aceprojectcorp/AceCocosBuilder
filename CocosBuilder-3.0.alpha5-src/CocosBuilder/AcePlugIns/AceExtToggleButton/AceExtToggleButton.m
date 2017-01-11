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
#import "AceExtToggleButton.h"

@implementation AceExtToggleButton

@synthesize m_cbFunc;
@synthesize clickEffect;
@synthesize selected;
@synthesize contentSizeRefresh;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.m_cbFunc = @"";
    self.clickEffect = @"";
    self.selected = false;
    self.contentSizeRefresh = false;

    [self schedule:@selector(update:)];
    
    return self;
}

-(void)update:(ccTime)delta
{
    CCArray *children = [self children];
//    CCNode *node;
    int size = (int)children.count;
//    if(size > 0)
//    {
//        for(int i=0; i<size; i++)
//        {
//            node = [children objectAtIndex:(int)i];
//            if(i == 0)
//            {
//                [self setContentSize:CGSizeMake([node contentSize].width, [node contentSize].height)];
//            }
//            
//            //[node setPosition:CGPointMake([node contentSize].width / 2, [node contentSize].height / 2)];
//        }
//    }
    
    //CCNode* normalNode = [children objectAtIndex:(int)0];
    //CCNode* selectedNode = [children objectAtIndex:(int)1];
    
    CCNode* normalNode = NULL;
    CCNode* selectedNode = NULL;
    
    if(size == 1)
    {
        normalNode = [children objectAtIndex:(int)0];
    }
    else if(size > 1)
    {
        normalNode = [children objectAtIndex:(int)0];
        selectedNode = [children objectAtIndex:(int)1];
    }
    
    if(selected)
    {
        if(normalNode)
        {
            [normalNode setVisible:false];
        }
        if(selectedNode)
        {
            [selectedNode setVisible:true];
        }
    }
    else
    {
        if(normalNode)
        {
            [normalNode setVisible:true];
        }
        if(selectedNode)
        {
            [selectedNode setVisible:false];
        }
    }
    
    if(contentSizeRefresh)
    {
        contentSizeRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
}

@end
