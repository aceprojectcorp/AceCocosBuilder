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

#import "Ace3DWorld.h"


#define ArrayLength(x) (sizeof(x)/sizeof((x[0])))

@implementation Ace3DWorld

@synthesize bGridShow;
@synthesize m_camera_a;
@synthesize m_camera_b;
@synthesize m_camera_c;
@synthesize m_screen_s;
@synthesize objMaxScale;
@synthesize objMinScale;
@synthesize gridStartX;
@synthesize gridStartY;
@synthesize gridWidth;
@synthesize gridHeight;
@synthesize gridDepth;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    
    gridMaxCount = 8;
    
    
    bGridShow = true;
    
    
    m_camera_a = 480;
    m_camera_b = -10;
    m_camera_c = 500;
    m_screen_s = -4;
    objMaxScale = 1.0f;
    objMinScale = 0.3f;
    gridStartX = 480;
    gridStartY = 400;
    gridWidth = 250;
    gridHeight = 250;
    gridDepth = 6;
    m_camera.a = m_camera_a;
    m_camera.b = m_camera_b;
    m_camera.c = m_camera_c;
    m_screen.s = m_screen_s;
    
    
    [self initGrid];
    [self calcGrid];
    
    
    return self;
}

-(void)visit
{
    
    
    if(bGridShow)
    {
        m_camera.a = m_camera_a;
        m_camera.b = m_camera_b;
        m_camera.c = m_camera_c;
        m_screen.s = m_screen_s;
        [self initGrid];
        [self calcGrid];
        
        
        kmGLPushMatrix();
        glLineWidth(1);
        
        
        
        CGPoint pos_0;
        CGPoint pos_1;
        
        _ResultScreen tmpResultScreen;
        
        //---뒷면
        ccDrawColor4B(255, 0, 0, 255);
        //LeftTop ~ RightTop
        pos_0 = CGPointMake([gridPoints[GRID_LeftTop_Back] m_resultScreen].u, [gridPoints[GRID_LeftTop_Back] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightTop_Back] m_resultScreen].u, [gridPoints[GRID_RightTop_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        
        //LeftTop ~ LeftBottom
        pos_0 = CGPointMake([gridPoints[GRID_LeftTop_Back] m_resultScreen].u, [gridPoints[GRID_LeftTop_Back] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_LeftBottom_Back] m_resultScreen].u, [gridPoints[GRID_LeftBottom_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //LeftBottom ~ RightBottom
        pos_0 = CGPointMake([gridPoints[GRID_LeftBottom_Back] m_resultScreen].u, [gridPoints[GRID_LeftBottom_Back] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightBottom_Back] m_resultScreen].u, [gridPoints[GRID_RightBottom_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //RightBottom ~ RightTop
        pos_0 = CGPointMake([gridPoints[GRID_RightBottom_Back] m_resultScreen].u, [gridPoints[GRID_RightBottom_Back] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightTop_Back] m_resultScreen].u, [gridPoints[GRID_RightTop_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        
        //---앞면
        ccDrawColor4B(0, 255, 0, 255);
        //LeftTop ~ RightTop
        pos_0 = CGPointMake([gridPoints[GRID_LeftTop_Front] m_resultScreen].u, [gridPoints[GRID_LeftTop_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightTop_Front] m_resultScreen].u, [gridPoints[GRID_RightTop_Front] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //LeftTop ~ LeftBottom
        pos_0 = CGPointMake([gridPoints[GRID_LeftTop_Front] m_resultScreen].u, [gridPoints[GRID_LeftTop_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_LeftBottom_Front] m_resultScreen].u, [gridPoints[GRID_LeftBottom_Front] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //LeftBottom ~ RightBottom
        pos_0 = CGPointMake([gridPoints[GRID_LeftBottom_Front] m_resultScreen].u, [gridPoints[GRID_LeftBottom_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightBottom_Front] m_resultScreen].u, [gridPoints[GRID_RightBottom_Front] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //RightBottom ~ RightTop
        pos_0 = CGPointMake([gridPoints[GRID_RightBottom_Front] m_resultScreen].u, [gridPoints[GRID_RightBottom_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightTop_Front] m_resultScreen].u, [gridPoints[GRID_RightTop_Front] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //---옆면
        ccDrawColor4B(0, 0, 255, 255);
        //LeftTopFront ~ LeftTopBack
        pos_0 = CGPointMake([gridPoints[GRID_LeftTop_Front] m_resultScreen].u, [gridPoints[GRID_LeftTop_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_LeftTop_Back] m_resultScreen].u, [gridPoints[GRID_LeftTop_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //LeftBottomFront ~ LeftBottomBack
        pos_0 = CGPointMake([gridPoints[GRID_LeftBottom_Front] m_resultScreen].u, [gridPoints[GRID_LeftBottom_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_LeftBottom_Back] m_resultScreen].u, [gridPoints[GRID_LeftBottom_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //RightBottomFront ~ RightBottomBack
        pos_0 = CGPointMake([gridPoints[GRID_RightBottom_Front] m_resultScreen].u, [gridPoints[GRID_RightBottom_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightBottom_Back] m_resultScreen].u, [gridPoints[GRID_RightBottom_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        //RightTopFront ~ RightTopBack
        pos_0 = CGPointMake([gridPoints[GRID_RightTop_Front] m_resultScreen].u, [gridPoints[GRID_RightTop_Front] m_resultScreen].v);
        pos_1 = CGPointMake([gridPoints[GRID_RightTop_Back] m_resultScreen].u, [gridPoints[GRID_RightTop_Back] m_resultScreen].v);
        ccDrawLine(pos_0, pos_1);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        kmGLPopMatrix();
    }
    
    [self calcChild3DNode];
    
    [super visit];
     
    
}


-(_Camera) getCamera
{
    return m_camera;
}

-(void) setCamera:(_Camera)camera
{
    m_camera = camera;
}

-(_Screen) getScreen
{
    return m_screen;
}

-(void) setScreen:(_Screen)screen
{
    m_screen = screen;
}

-(void) initGrid
{
    //CGSize winSize = [[CCDirector sharedDirector] winSize];
    CGSize winSize = CGSizeMake(960, 640);
    //gridStartX = winSize.width * 0.5;
    //gridStartY = winSize.height * 0.5;
    
    
    float tmpPos[] =
    {
        //x                             y                           z
        //뒷면
        -1,                             1,                          1,     //LeftTop_Back
        1,                             1,                          1,      //RightTop_Back
        -1,                             1,                           -1,     //LeftBottom_Back
        1,                             1,                          -1,      //RightBottom_Back
        
        //앞면
        -1,                            -1,                          1,     //LeftTop_Front
        1,                            -1,                          1,      //RightTop_Front
        -1,                            -1,                          -1,     //LeftBottom_Front
        1,                            -1,                          -1,      //RightBottom_Front
    };
    
    
    
    int size = gridMaxCount;
    float tmpX = 0;
    float tmpY = 0;
    float tmpZ = 0;
    for(int i=0; i<size; i++)
    {
        gridPoints[i] = [[Ace3DNode alloc] init];

        tmpX = gridStartX + tmpPos[i * 3 + 0] * gridWidth / 2;
        tmpY = tmpPos[i * 3 + 1] * gridDepth;
        tmpZ = gridStartY + tmpPos[i * 3 + 2] * gridHeight / 2;
        
        _Translation tmpTranslation;
        tmpTranslation.dx = 0;
        tmpTranslation.dy = 0;
        tmpTranslation.dz = 0;
        [gridPoints[i] setM_translation:tmpTranslation];
        
        _Rotation tmpRotation;
        tmpRotation.x = 0;
        tmpRotation.y = 0;
        tmpRotation.z = 0;
        [gridPoints[i] setM_rotation:tmpRotation];
        
        _Object tmpObject;
        tmpObject.x = tmpX;
        tmpObject.y = tmpY;
        tmpObject.z = tmpZ;
        [gridPoints[i] setM_object:tmpObject];
        
        [gridPoints[i] setM_object_x:tmpX];
        [gridPoints[i] setM_object_y:tmpY];
        [gridPoints[i] setM_object_z:tmpZ];
    }
    
}

-(void) calcGrid
{
    int size = gridMaxCount;
    for(int i=0; i<size; i++)
    {
        [gridPoints[i] calc3DPosition:m_camera screen:m_screen gridDepth:gridDepth];
    }
}

-(void) calcChild3DNode
{
    /*
    CCArray* children = [self children];
    int size = (int)children.count;
    CCNode* child = NULL;
    for(int i=0; i<size; i++)
    {
        child = [children objectAtIndex:(int)i];
        
        if([child isKindOfClass:[Ace3DNode class]])
        {
            Ace3DNode* pNode = (Ace3DNode*)child;
            [pNode calc3DPosition:m_camera screen:m_screen gridDepth:gridDepth];
        }
    }
     */
}

-(Ace3DNode*) getGridPoint:(int)idx
{
    return gridPoints[idx];
}






@end
