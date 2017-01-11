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
#import "actOrbitCamera.h"

@implementation actOrbitCamera

@synthesize m_time;
@synthesize m_radius;
@synthesize m_deltaRadius;
@synthesize m_angleZ;
@synthesize m_deltaAngleZ;
@synthesize m_angleX;
@synthesize m_deltaAngleX;

@synthesize actionPlay;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    /*
    self.m_time = 1;
    self.m_radius = 1;
    self.m_deltaRadius = 0;
    self.m_angleZ = 0;
    self.m_deltaAngleZ = 0;
    self.m_angleX = 0;
    self.m_deltaAngleX = 0;
     */
    
    self.m_time = 1;
    self.m_radius = 1;
    self.m_deltaRadius = 0;
    self.m_angleZ = 0;
    self.m_deltaAngleZ = -90;
    self.m_angleX = 0;
    self.m_deltaAngleX = 0;
    
    
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

-(void) actionStart
{
    [self parentStartInfoReset];
    [self stopAllActions];
    
    

    
    
    

    float m_time = [self m_time];
    float m_radius = [self m_radius];
    float m_deltaRadius = [self m_deltaRadius];
    float m_angleZ = [self m_angleZ];
    float m_deltaAngleZ = [self m_deltaAngleZ];
    float m_angleX = [self m_angleX];
    float m_deltaAngleX = [self m_deltaAngleX];
    
    CCFiniteTimeAction* pAction = [CCOrbitCamera actionWithDuration:m_time radius:m_radius deltaRadius:m_deltaRadius angleZ:m_angleZ deltaAngleZ:m_deltaAngleZ angleX:m_angleX deltaAngleX:m_deltaAngleX];
    

    
    
    
        CCCallFunc* callBack = [CCCallFunc actionWithTarget:self selector:@selector(parentReset)];
    
    
    
        [self runAction:[CCSequence actions:pAction, callBack, nil]];
    
}

-(void) parentStartInfoReset
{
    parentStartInfo.position = [self position];
    parentStartInfo.scaleX = [self scaleX];
    parentStartInfo.scaleY = [self scaleY];
    parentStartInfo.skewX = [self skewX];
    parentStartInfo.skewY = [self skewY];
    parentStartInfo.rotationX = [self rotationX];
    parentStartInfo.rotationY = [self rotationY];
    parentStartInfo.visible = [self visible];
}

-(void) parentReset
{

    [self setPosition:parentStartInfo.position];
    [self setScaleX:parentStartInfo.scaleX];
    [self setScaleY:parentStartInfo.scaleY];
    [self setSkewX:parentStartInfo.skewX];
    [self setSkewY:parentStartInfo.skewY];
    [self setRotationX:parentStartInfo.rotationX];
    [self setRotationY:parentStartInfo.rotationY];
    [self setVisible:parentStartInfo.visible];
    
    [self stopAllActions];
}

@end
