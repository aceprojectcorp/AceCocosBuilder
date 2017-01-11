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
#import "AceNode.h"

@implementation AceNode

@synthesize contentSizeRefresh;
//@synthesize m_opacity;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.contentSizeRefresh = false;
    //self.m_opacity = 255;
    
    //[self setOpacity:opacity];
    
    return self;
}

/*
-(void) setOpacity:(CCNode*)object opacity:(GLubyte)opacity
{
    CCArray* childs = NULL;
    CCNode* child = NULL;
    if(object)
    {
        childs = [object children];
    }
    
    if(childs)
    {
        int size = (int)childs.count;
        for(int i=0; i<size; i++)
        {
            bool bProtocol = [[childs objectAtIndex:(int)i] conformsToProtocol:@protocol(CCRGBAProtocol)];
            if(bProtocol)
            {
                CCNodeRGBA* pNode = [childs objectAtIndex:(int)i];
                pNode.cascadeOpacityEnabled = true;
                [pNode setOpacity:opacity];
            }
            
            CCNode* singleObject = child;
            if(singleObject && [singleObject children].count > 0)
            {
                [self setOpacity:singleObject opacity:opacity];
            }
        }
    }
}
*/

- (void) draw
{
    [super draw];
    
    CCArray* children = [self children];
    int size = (int)children.count;
    if(contentSizeRefresh)
    {
        if(size > 0)
        {
            CCNode* pNode = [children objectAtIndex:(int)0];
            
            [self setContentSize:[pNode contentSize]];
        }
        
        contentSizeRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] refreshProperty:@"contentSize"];
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    
    
   



    /*
    CCNodeRGBA* child;
    for(int i=0; i<size; i++)
    {
        child = [children objectAtIndex:(int)i];
        [self setOpacity:child opacity:m_opacity];
    }
    */
   
}

/*
-(void) setOpacity
{
    
     _displayedOpacity = _realOpacity = opacity;
     
     if( _cascadeOpacityEnabled ) {
        GLubyte parentOpacity = 255;
        if( [_parent conformsToProtocol:@protocol(CCRGBAProtocol)] && [(id<CCRGBAProtocol>)_parent isCascadeOpacityEnabled] )
            parentOpacity = [(id<CCRGBAProtocol>)_parent displayedOpacity];
        [self updateDisplayedOpacity:parentOpacity];
     }
     
    
    CCArray* children = [self children];
    CCNode* child;
    int size = (int)[children count];
    for(int i=0; i<size; i++)
    {
        child = [children objectAtIndex:(int)i];
        [child setOpacity:opacity];
    }
}
 */


@end
