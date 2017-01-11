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
#import "AcePriorityMenu.h"

@implementation AcePriorityMenu

@synthesize priority;
@synthesize swallowTouches;
@synthesize checkParent;
@synthesize positionRefresh;


- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.priority = -129;
    self.swallowTouches = true;
    self.checkParent = false;
    self.positionRefresh = false;

    //[[CocosBuilderAppDelegate appDelegate] refreshProperty:@"position"];
    //[[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
    //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    
    return self;
}

-(void) draw
{
    [super draw];
    
    
    
    
    if(positionRefresh)
    {
        positionRefresh = false;
        
        CGPoint nowPosition = [self position];
        if(nowPosition.x == 0 && nowPosition.y == 0)
        {
            nowPosition.x = 0.1;
            nowPosition.y = 0.1;
            
            [self setPosition:nowPosition];
            
            //[self setContentSize:CGSizeMake(100, 100)];
        }
        
        
        
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"position"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        

    }
    
    /*
    CGPoint nowPosition = [self position];
    if(nowPosition.x == 0 && nowPosition.y == 0)
    {
        nowPosition.x = 1;
        nowPosition.y = 1;
        
        [self setPosition:nowPosition];
        
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"position"];
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    */
}



@end
