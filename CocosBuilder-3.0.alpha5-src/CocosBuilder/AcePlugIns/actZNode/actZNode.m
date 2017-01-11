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
#import "actZNode.h"

#import "actMoveTo.h"
#import "actDelayTime.h"
#import "actPlace.h"
#import "actJumpTo.h"
#import "actBezierTo.h"
#import "actCardinalSplineTo.h"
#import "actCatmullRomTo.h"
#import "actScaleTo.h"
#import "actSkewTo.h"
#import "actRotationTo.h"
#import "actBlink.h"
#import "actShow.h"
#import "actHide.h"
#import "actToggleVisibility.h"
#import "actFadeIn.h"
#import "actFadeOut.h"
#import "actFadeTo.h"
#import "actTintTo.h"
#import "actOrbitCamera.h"

@implementation actZNode

@synthesize actionPlay;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.actionPlay = false;
    
    [self schedule:@selector(update:)];
    
    return self;
}

-(void) update:(ccTime)delta
{
    if(actionPlay)
    {
        actionPlay = false;
        
        [self actionStart];
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
        
        //[[CocosBuilderAppDelegate appDelegate] sequenceHandlerUpdate];
    }
    
    
}

-(void) parentStartInfoReset
{
    CCNode* pNode = [self parent];
    
    parentStartInfo.position = pNode.position;
    parentStartInfo.scaleX = pNode.scaleX;
    parentStartInfo.scaleY = pNode.scaleY;
    parentStartInfo.skewX = pNode.skewX;
    parentStartInfo.skewY = pNode.skewY;
    parentStartInfo.rotationX = pNode.rotationX;
    parentStartInfo.rotationY = pNode.rotationY;
    parentStartInfo.visible = pNode.visible;
}

-(void) parentReset
{
    CCNode* pNode = [self parent];
    
    pNode.position = parentStartInfo.position;
    pNode.scaleX = parentStartInfo.scaleX;
    pNode.scaleY = parentStartInfo.scaleY;
    pNode.skewX = parentStartInfo.skewX;
    pNode.skewY = parentStartInfo.skewY;
    pNode.rotationX = parentStartInfo.rotationX;
    pNode.rotationY = parentStartInfo.rotationY;
    pNode.visible = parentStartInfo.visible;
}

-(void) actionStart
{
    [self parentStartInfoReset];
    [[self parent] stopAllActions];
    
    CCArray* children = [self children];
    int size = (int)children.count;
    CCNode* child = NULL;
    NSMutableArray* actions = [[NSMutableArray alloc] init];
    
    
    
    for(int i=0; i<size; i++)
    {
        child = [children objectAtIndex:(int)i];
        
        if([child isKindOfClass:[actMoveTo class]])
        {
            actMoveTo* pNode = (actMoveTo*)child;
            float m_time = pNode.m_time;
            float m_x = pNode.m_x;
            float m_y = pNode.m_y;
            
            CCFiniteTimeAction* pAction = [CCMoveTo actionWithDuration:m_time position:CGPointMake(m_x, m_y)];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actDelayTime class]])
        {
            actDelayTime* pNode = (actDelayTime*)child;
            float m_time = pNode.m_time;
            
            CCFiniteTimeAction* pAction = [CCDelayTime actionWithDuration:m_time];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actJumpTo class]])
        {
            actJumpTo* pNode = (actJumpTo*)child;
            float m_time = pNode.m_time;
            float m_x = pNode.m_x;
            float m_y = pNode.m_y;
            float m_height = pNode.m_height;
            float m_jumps = pNode.m_jumps;
            
            CCFiniteTimeAction* pAction = [CCJumpTo actionWithDuration:m_time position:CGPointMake(m_x, m_y) height:m_height jumps:(int)m_jumps];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actBezierTo class]])
        {
            actBezierTo* pNode = (actBezierTo*)child;
            float m_time = pNode.m_time;
            float m_point1_x = pNode.m_point1_x;
            float m_point1_y = pNode.m_point1_y;
            float m_point2_x = pNode.m_point2_x;
            float m_point2_y = pNode.m_point2_y;
            float m_endPoint_x = pNode.m_endPoint_x;
            float m_endPoint_y = pNode.m_endPoint_y;
            
            ccBezierConfig bezier;
            bezier.controlPoint_1 = CGPointMake(m_point1_x, m_point1_y);
            bezier.controlPoint_2 = CGPointMake(m_point2_x, m_point2_y);
            bezier.endPosition = CGPointMake(m_endPoint_x, m_endPoint_y);
            CCFiniteTimeAction* pAction = [CCBezierTo actionWithDuration:m_time bezier:bezier];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actCardinalSplineTo class]])
        {
            actCardinalSplineTo* pNode = (actCardinalSplineTo*)child;
            float m_time = pNode.m_time;
            float m_tension = pNode.m_tension;
            NSString* m_points = pNode.m_points;
            
            CCPointArray* array = [self parsePoints:m_points];
            CCFiniteTimeAction* pAction = [CCCardinalSplineTo actionWithDuration:m_time points:array tension:m_tension];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actCatmullRomTo class]])
        {
            actCatmullRomTo* pNode = (actCatmullRomTo*)child;
            float m_time = pNode.m_time;
            float m_tension = pNode.m_tension;
            NSString* m_points = pNode.m_points;
            
            CCPointArray* array = [self parsePoints:m_points];
            CCFiniteTimeAction* pAction = [CCCatmullRomTo actionWithDuration:m_time points:array tension:m_tension];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actScaleTo class]])
        {
            
            actScaleTo* pNode = (actScaleTo*)child;
            float m_time = pNode.m_time;
            float m_scale_x = pNode.m_scale_x;
            float m_scale_y = pNode.m_scale_y;
            
            CCFiniteTimeAction* pAction = [CCScaleTo actionWithDuration:m_time scaleX:m_scale_x scaleY:m_scale_y];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actPlace class]])
        {
            
            actPlace* pNode = (actPlace*)child;
            float m_x = pNode.m_x;
            float m_y = pNode.m_y;
            
            CCFiniteTimeAction* pAction = [CCPlace actionWithPosition:CGPointMake(m_x, m_y)];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actSkewTo class]])
        {
            
            actSkewTo* pNode = (actSkewTo*)child;
            float m_time = pNode.m_time;
            float m_skew_x = pNode.m_skew_x;
            float m_skew_y = pNode.m_skew_y;
            
            CCFiniteTimeAction* pAction = [CCSkewTo actionWithDuration:m_time skewX:m_skew_x skewY:m_skew_y];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actRotationTo class]])
        {
            
            actRotationTo* pNode = (actRotationTo*)child;
            float m_time = pNode.m_time;
            float m_angle_x = pNode.m_angle_x;
            float m_angle_y = pNode.m_angle_y;
            
            CCFiniteTimeAction* pAction = [CCRotateTo actionWithDuration:m_time angleX:m_angle_x angleY:m_angle_y];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actBlink class]])
        {
            
            actBlink* pNode = (actBlink*)child;
            float m_time = pNode.m_time;
            float m_blinkCount = pNode.m_blinkCount;
            
            CCFiniteTimeAction* pAction = [CCBlink actionWithDuration:m_time blinks:m_blinkCount];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actShow class]])
        {
            CCFiniteTimeAction* pAction = [CCShow action];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actHide class]])
        {
            CCFiniteTimeAction* pAction = [CCHide action];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actToggleVisibility class]])
        {
            CCFiniteTimeAction* pAction = [CCToggleVisibility action];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actFadeIn class]])
        {
            actFadeIn* pNode = (actFadeIn*)child;
            float m_time = pNode.m_time;
            
            CCFiniteTimeAction* pAction = [CCFadeIn actionWithDuration:m_time];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actFadeOut class]])
        {
            actFadeOut* pNode = (actFadeOut*)child;
            float m_time = pNode.m_time;
            
            CCFiniteTimeAction* pAction = [CCFadeOut actionWithDuration:m_time];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actFadeTo class]])
        {
            actFadeTo* pNode = (actFadeTo*)child;
            float m_time = pNode.m_time;
            GLubyte m_opacity = pNode.m_opacity;
            
            CCFiniteTimeAction* pAction = [CCFadeTo actionWithDuration:m_time opacity:m_opacity];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actTintTo class]])
        {
            actTintTo* pNode = (actTintTo*)child;
            float m_time = pNode.m_time;
            GLubyte m_r = pNode.m_r;
            GLubyte m_g = pNode.m_g;
            GLubyte m_b = pNode.m_b;
            
            CCFiniteTimeAction* pAction = [CCTintTo actionWithDuration:m_time red:m_r green:m_g blue:m_b];
            
            [actions addObject:pAction];
        }
        else if([child isKindOfClass:[actOrbitCamera class]])
        {
            actOrbitCamera* pNode = (actOrbitCamera*)child;
            float m_time = pNode.m_time;
            float m_radius = pNode.m_radius;
            float m_deltaRadius = pNode.m_deltaRadius;
            float m_angleZ = pNode.m_angleZ;
            float m_deltaAngleZ = pNode.m_deltaAngleZ;
            float m_angleX = pNode.m_angleX;
            float m_deltaAngleX = pNode.m_deltaAngleX;
            
            CCFiniteTimeAction* pAction = [CCOrbitCamera actionWithDuration:m_time radius:m_radius deltaRadius:m_deltaRadius angleZ:m_angleZ deltaAngleZ:m_deltaAngleZ angleX:m_angleX deltaAngleX:m_deltaAngleX];
            
            [actions addObject:pAction];
        }
        

        
    }
    
    
    
    if([actions count] > 0)
    {
        CCCallFunc* callBack = [CCCallFunc actionWithTarget:self selector:@selector(parentReset)];
        [actions addObject:callBack];
        
        [[self parent] runAction:[CCSequence actionWithArray:actions]];
        
        
    }
}

-(CCPointArray*) parsePoints:(NSString*) m_points
{
    //point가 몇개 셋팅되어있는지 검색한다.
    int size = 0;
    for(int i=0; i<[m_points length]; i++)
    {
        if([[m_points substringWithRange:NSMakeRange(i, 1)] isEqualToString:@"("])
        {
            size++;
        }
    }
    
    CCPointArray* array = [CCPointArray arrayWithCapacity:(int)size];
    
    //(0, 0)
    int x_pos = 0;
    int x_length = 0;
    int y_pos = 0;
    int y_length = 0;
    bool bXLengthCheck = false;
    bool bYLengthCheck = false;
    for(int i=0; i<[m_points length]; i++)
    {
        if([[m_points substringWithRange:NSMakeRange(i, 1)] isEqualToString:@"("])
        {
            x_pos = i + 1;
            bXLengthCheck = true;
        }
        else if([[m_points substringWithRange:NSMakeRange(i, 1)] isEqualToString:@","])
        {
            bXLengthCheck = false;
            
            y_pos = i + 1;
            bYLengthCheck = true;
        }
        else if([[m_points substringWithRange:NSMakeRange(i, 1)] isEqualToString:@")"])
        {
            bYLengthCheck = false;
            
            NSString* xString = [m_points substringWithRange:NSMakeRange(x_pos, x_length)];
            NSString* yString = [m_points substringWithRange:NSMakeRange(y_pos, y_length)];
            
            CGPoint tmpPoint = CGPointMake([xString floatValue], [yString floatValue]);
            [array addControlPoint:tmpPoint];
            
            x_length = 0;
            y_length = 0;
        }
        else if([[m_points substringWithRange:NSMakeRange(i, 1)] isEqualToString:@" "])
        {
            if(bYLengthCheck)
            {
                y_pos++;
            }
        }
        else
        {
            if(bXLengthCheck)
            {
                x_length++;
            }
            
            if(bYLengthCheck)
            {
                y_length++;
            }
        }
    }
    
    return array;
}

/*
-(void) networkTest
{
    //CFReadStreamRef myReadStream = CFReadStreamCreateWithFile(<#CFAllocatorRef alloc#>, <#CFURLRef fileURL#>)
}
 */

@end
