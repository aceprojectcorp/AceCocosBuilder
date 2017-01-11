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

#import "cocos2d.h"
#import "Ace3DNode.h"

enum
{
    //뒷면
    GRID_LeftTop_Back,
    GRID_RightTop_Back,
    GRID_LeftBottom_Back,
    GRID_RightBottom_Back,
    
    //앞면
    GRID_LeftTop_Front,
    GRID_RightTop_Front,
    GRID_LeftBottom_Front,
    GRID_RightBottom_Front,
};

@interface Ace3DWorld : CCNode
{
    
    _Camera m_camera;
    _Screen m_screen;
    
    int gridMaxCount;
    
    Ace3DNode* gridPoints[8];
    
    
    BOOL bGridShow;
    float m_camera_a;
    float m_camera_b;
    float m_camera_c;
    float m_screen_s;
    
    float objMaxScale;
    float objMinScale;
    
    float gridStartX;
    float gridStartY;
    float gridWidth;
    float gridHeight;
    float gridDepth;
    
}

@property (nonatomic,assign) BOOL bGridShow;
@property (nonatomic,assign) float m_camera_a;
@property (nonatomic,assign) float m_camera_b;
@property (nonatomic,assign) float m_camera_c;
@property (nonatomic,assign) float m_screen_s;

@property (nonatomic,assign) float objMaxScale;
@property (nonatomic,assign) float objMinScale;

@property (nonatomic,assign) float gridStartX;
@property (nonatomic,assign) float gridStartY;
@property (nonatomic,assign) float gridWidth;
@property (nonatomic,assign) float gridHeight;
@property (nonatomic,assign) float gridDepth;


-(_Camera) getCamera;
-(void) setCamera:(_Camera)camera;
-(_Screen) getScreen;
-(void) setScreen:(_Screen)screen;

-(void) initGrid;
-(void) calcGrid;
-(void) calcChild3DNode;
-(Ace3DNode*) getGridPoint:(int)idx;



@end
