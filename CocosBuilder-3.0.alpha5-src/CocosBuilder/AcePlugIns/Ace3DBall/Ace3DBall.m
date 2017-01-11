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
#import "Ace3DBall.h"
#import "Ace3DWorld.h"



@implementation Ace3DBall

@synthesize m_translation;
@synthesize m_rotation;
@synthesize m_object;
@synthesize m_translationRotation;
@synthesize m_resultScreen;

@synthesize objectPositionRefresh;
@synthesize m_object_x;
@synthesize m_object_y;
@synthesize m_object_z;

@synthesize ballCenterRefresh;

@synthesize bFire;
@synthesize tmpPower;
@synthesize tmpAngle;
@synthesize tmpAngleZ;
@synthesize tmpG;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    objectPositionRefresh = false;
    
    m_object_x = 0;
    m_object_y = 0;
    m_object_z = 0;
    
    ballCenterRefresh = false;
    
    m_translation.dx = 0;
    m_translation.dy = 0;
    m_translation.dz = 0;
    
    m_rotation.x = 0;
    m_rotation.y = 0;
    m_rotation.z = 0;
    
    m_object.x = m_object_x;
    m_object.y = m_object_y;
    m_object.z = m_object_z;
    
    m_object.z = 159;
    
    bFire = false;
    tmpPower = 10;
    tmpAngle = 30;
    tmpAngleZ = 90;
    tmpG = 0.1;
    
    m_power = tmpPower;
    m_angle = tmpAngle;
    m_angle_z = tmpAngleZ;
    m_g = tmpG;
    
    bBallStart = false;
    bMoveBallDown = false;
    moveBallZ = MOVEBALL_Z;
    
    
    return self;
}

-(void) visit
{
    Ace3DWorld* tmpWorld = (Ace3DWorld*)[self parent];
    _Camera tmpCamera = [tmpWorld getCamera];
    _Screen tmpScreen = [tmpWorld getScreen];
    float tmpDepth = tmpWorld.gridDepth;
    
    
    
    CGPoint nowPosition = [self position];
    _Object tmpObject = [self get2Dto3DPosition:nowPosition.x posY2D:nowPosition.y tmpCamera:tmpCamera tmpScreen:tmpScreen];
    [self setM_object:tmpObject];
    [self calc3DPosition:tmpCamera screen:tmpScreen gridDepth:tmpDepth];
    
    m_object_x = tmpObject.x;
    m_object_y = tmpObject.y;
    m_object_z = tmpObject.z;
    if(objectPositionRefresh)
    {
        //[[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    /*
    if(bFire)
    {
        bFire = false;
        [self initFoMulSun];
        bBallStart = true;
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    
    if(objectPositionRefresh)
    {
        objectPositionRefresh = false;
        
        Ace3DWorld* tmpWorld = (Ace3DWorld*)[self parent];
        _Camera tmpCamera = [tmpWorld getCamera];
        _Screen tmpScreen = [tmpWorld getScreen];
        float tmpDepth = tmpWorld.gridDepth;
        [self calc3DPosition:tmpCamera screen:tmpScreen gridDepth:tmpDepth];
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    */
    
    /*
    if(ballCenterRefresh)
    {
        ballCenterRefresh = false;
        
        Ace3DWorld* tmpWorld = (Ace3DWorld*)[self parent];
        _Camera tmpCamera = [tmpWorld getCamera];
        _Screen tmpScreen = [tmpWorld getScreen];
        float tmpDepth = tmpWorld.gridDepth;
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
     */
    
    /*
    if(bBallStart)
    {
        //x, z축 포물선 이동
        m_object.x += m_sz;
        m_object.y += m_sx * 0.01;
        m_object.z += m_sy;
        m_sy -= m_g;
        
        Ace3DWorld* tmpWorld = (Ace3DWorld*)[self parent];
        _Camera tmpCamera = [tmpWorld getCamera];
        _Screen tmpScreen = [tmpWorld getScreen];
        float tmpDepth = tmpWorld.gridDepth;
        [self calc3DPosition:tmpCamera screen:tmpScreen gridDepth:tmpDepth];
        
        if(m_sy < m_Start_sy*-1)
        {
            [self nextFoMulSun];
        }
        
        if(m_sy <= 0 && !bMoveBallDown)
        {
            bMoveBallDown = true;
            moveBallZ = MOVEBALL_Z;
        }
    }
    */
    
    
    [super visit];
}

-(void) initFoMulSun
{
    bFire = false;
    
    posX = m_resultScreen.u;
    posY = m_resultScreen.v;
    
    m_power = tmpPower;
    m_angle = tmpAngle;
    m_angle_z = tmpAngleZ;
    m_g = tmpG;
    
    m_sx = m_power * cosf(DegreeToRadian(m_angle));
    m_sy = m_power * sinf(DegreeToRadian(m_angle));
    m_sz = m_power * cosf(DegreeToRadian(m_angle_z));
    m_Start_sy = m_sy;
    
    bMoveBallDown = false;
    moveBallZ = MOVEBALL_Z;
}

-(void) nextFoMulSun
{
    m_power *= 0.5;
    /*
    if(m_angle > 10)
    {
        m_angle *= 0.3;
    }
     */
    
    m_sx = m_power * cosf(DegreeToRadian(m_angle));
    m_sy = m_power * sinf(DegreeToRadian(m_angle));
    m_sz = m_power * cosf(DegreeToRadian(m_angle_z));
    m_Start_sy = m_sy;
    
    bMoveBallDown = false;
    moveBallZ = MOVEBALL_Z;
    
    if(m_power < 0.1 || m_angle < 0.1)
    {
        bBallStart = false;
        m_sy = m_Start_sy;
        objectPositionRefresh = true;
    }
}

-(void) removeTail:(CCNode*)pSender
{
    [pSender removeFromParentAndCleanup:true];
}

-(void) calc3DPosition:(_Camera)camera screen:(_Screen)screen gridDepth:(float)gridDepth
{
    /*
     if(!bBallStart)
     {
         m_object.x = m_object_x;
         m_object.y = m_object_y;
         m_object.z = m_object_z;
     }
    */
    
    
    
    //xxx = x(cos@y cos@z) + y(sin@x sin@y cos@z - cos@x sin@z) + z(cos@x sin@y cos@z + sin@x sin@z)
    m_translationRotation.xxx = (m_object.x + m_translation.dx) *
    (cosf(DegreeToRadian(m_rotation.y)) *
     cosf(DegreeToRadian(m_rotation.z))) +
    (m_object.y + m_translation.dy) *
    (sinf(DegreeToRadian(m_rotation.x)) *
     sinf(DegreeToRadian(m_rotation.y)) *
     cosf(DegreeToRadian(m_rotation.z)) -
     cosf(DegreeToRadian(m_rotation.x)) *
     sinf(DegreeToRadian(m_rotation.z))) +
    (m_object.z + m_translation.dz) *
    (cosf(DegreeToRadian(m_rotation.x)) *
     sinf(DegreeToRadian(m_rotation.y)) *
     cosf(DegreeToRadian(m_rotation.z)) +
     sinf(DegreeToRadian(m_rotation.x)) *
     sinf(DegreeToRadian(m_rotation.z)));
    
    //yyy = x(cos@y sin@z) + y(sin@x sin@y sin@z + cos@x cos@z) + z(cos@x sin@y sin@z - sin@x cos@z)
    m_translationRotation.yyy = (m_object.x + m_translation.dx) *
    (cosf(DegreeToRadian(m_rotation.y)) *
     sinf(DegreeToRadian(m_rotation.z))) +
    (m_object.y + m_translation.dy) *
    (sinf(DegreeToRadian(m_rotation.x)) *
     sinf(DegreeToRadian(m_rotation.y)) *
     sinf(DegreeToRadian(m_rotation.z)) +
     cosf(DegreeToRadian(m_rotation.x)) *
     cosf(DegreeToRadian(m_rotation.z))) +
    (m_object.z + m_translation.dz) *
    (cosf(DegreeToRadian(m_rotation.x)) *
     sinf(DegreeToRadian(m_rotation.y)) *
     sinf(DegreeToRadian(m_rotation.z)) -
     sinf(DegreeToRadian(m_rotation.x)) *
     cosf(DegreeToRadian(m_rotation.z)));
    
    //zzz = -x sin@y + y(sin@x cos@y) + z(cos@x cos@y)
    m_translationRotation.zzz = -(m_object.x + m_translation.dx) *
    sinf(DegreeToRadian(m_rotation.y)) +
    (m_object.y + m_translation.dy) *
    (sinf(DegreeToRadian(m_rotation.x)) *
     cosf(DegreeToRadian(m_rotation.y))) +
    (m_object.z + m_translation.dz) *
    (cosf(DegreeToRadian(m_rotation.x)) *
     cosf(DegreeToRadian(m_rotation.y)));
    
    //u = x - (x-a)(y-s) / (y-b)
    if((m_translationRotation.yyy - camera.b) !=0)
    {
        m_resultScreen.u = m_translationRotation.xxx - (m_translationRotation.xxx - camera.a) * (m_translationRotation.yyy - screen.s) / (m_translationRotation.yyy - camera.b);
    }
    
    //v = z - (z-c)(y-s) / (y-b)
    if((m_translationRotation.yyy - camera.b) != 0)
    {
        m_resultScreen.v = m_translationRotation.zzz - (m_translationRotation.zzz - camera.c) * (m_translationRotation.yyy - screen.s) / (m_translationRotation.yyy - camera.b);
    }
    
    Ace3DWorld* tmpWorld = (Ace3DWorld*)[self parent];
    
    float maxScale = tmpWorld.objMaxScale;
    float minScale = tmpWorld.objMinScale;
    float nowZ = (m_object.y - gridDepth) * -1;
    float maxZ = gridDepth * 2;
    float tmpScale = (nowZ / maxZ) * maxScale;
    if(tmpScale < minScale)
    {
        tmpScale = minScale;
    }
    [self setScale:tmpScale];
    
    [self setPosition:CGPointMake(m_resultScreen.u, m_resultScreen.v)];
    
    //[[CocosBuilderAppDelegate appDelegate] refreshProperty:@"position"];
    
    /*
     if(bBallStart)
     {
     CCArray* children = [self children];
     int size = (int)children.count;
     if(size > 1)
     {
     CCNode* pNode = [children objectAtIndex:(int)1];
     CCNode* copyNode = (CCNode*)[pNode copy];
     [copyNode setAnchorPoint:CGPointMake(0.5, 0.5)];
     [copyNode setScale:0.7 * tmpScale];
     [copyNode setPosition:CGPointMake(m_resultScreen.u, m_resultScreen.v)];
     [[self parent] addChild:copyNode];
     
     CCFiniteTimeAction* pAction = [CCFadeOut actionWithDuration:0.3];
     CCFiniteTimeAction* pCallBack = [CCCallFuncN actionWithTarget:self selector:@selector(removeTail:)];
     [copyNode runAction:[CCSequence actions:pAction, pCallBack, nil]];
     }
     }
     */
    
    
    if(bBallStart)
    {
        CCArray* children = [self children];
        int size = (int)children.count;

        if(size > 0)
        {
            CCSprite* pNode = (CCSprite*)[children objectAtIndex:(int)0];
            CCTexture2D* tmpTexture = [pNode texture];
            CCSprite* copySprite = [CCSprite spriteWithTexture:tmpTexture];
            [copySprite setAnchorPoint:CGPointMake(0.5, 0.5)];
            [copySprite setScale:0.7 * tmpScale];
            [copySprite setPosition:CGPointMake(m_resultScreen.u, m_resultScreen.v)];
            if(bMoveBallDown)
            {
                [[self parent] addChild:copySprite z:moveBallZ++];
            }
            else
            {
                [[self parent] addChild:copySprite z:moveBallZ--];
            }
            
            
            
            CCFiniteTimeAction* pAction = [CCFadeOut actionWithDuration:0.2];
            CCFiniteTimeAction* pCallBack = [CCCallFuncN actionWithTarget:self selector:@selector(removeTail:)];
            [copySprite runAction:[CCSequence actions:pAction, pCallBack, nil]];
        }
    }
    
}

-(_Object) get2Dto3DPosition:(float)posX2D posY2D:(float)posY2D tmpCamera:(_Camera)tmpCamera tmpScreen:(_Screen)tmpScreen
{
    _Object tmpObject;
    
    
    float tmpX;
    float tmpY;
    float tmpZ = m_object.z;
    
    /*
     //posY2D = tmpZ - (tmpZ - tmpEye.c) * (tmpY - tmpScreen.s) / (tmpY - tmpEye.b);
     시작 : v = z - (z-c)(y-s) / (y-b)
     
     v : posY2D
     z : tmpZ
     c : tmpEye.c
     y : tmpY
     s : tmpScreen.s
     b = tmpEye.b
     
     결과 : y = (s(z-c) + b(v-z)) / (v - c)
     */
    tmpY = (tmpScreen.s * (tmpZ - tmpCamera.c) + tmpCamera.b * (posY2D - tmpZ)) / (posY2D - tmpCamera.c);
    
    /*
     //posX2D = tmpX - (tmpX - tmpEye.a) * (tmpY - tmpScreen.s) / (tmpY - tmpEye.b);
     시작 : u = x - (x-a)(y-s) / (y-b)
     
     u : posX2D
     x = tmpX
     a = tmpEye.a
     y = tmpY
     s = tmpScreen.s
     b = tmpEye.b
     
     결과 : x = (u(y-b) - a(y-s)) / (s - b)
     */
    tmpX = (posX2D * (tmpY - tmpCamera.b) - tmpCamera.a * (tmpY - tmpScreen.s)) / (tmpScreen.s - tmpCamera.b);
    
    tmpObject.x = tmpX;
    tmpObject.y = tmpY;
    tmpObject.z = tmpZ;
    
    return tmpObject;
}


@end
