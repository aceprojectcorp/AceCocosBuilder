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

@interface Ace3DPlayer : CCNode
{
    _Translation m_translation;
    _Rotation m_rotation;
    _Object m_object;
    _TranslationRotation m_translationRotation;
    _ResultScreen m_resultScreen;
    
    BOOL objectPositionRefresh;
    float m_object_x;
    float m_object_y;
    float m_object_z;
}

@property (nonatomic,assign) _Translation m_translation;
@property (nonatomic,assign) _Rotation m_rotation;
@property (nonatomic,assign) _Object m_object;
@property (nonatomic,assign) _TranslationRotation m_translationRotation;
@property (nonatomic,assign) _ResultScreen m_resultScreen;

@property (nonatomic,assign) BOOL objectPositionRefresh;
@property (nonatomic,assign) float m_object_x;
@property (nonatomic,assign) float m_object_y;
@property (nonatomic,assign) float m_object_z;

-(void) calc3DPosition:(_Camera)camera screen:(_Screen)screen gridDepth:(float)gridDepth;

@end
