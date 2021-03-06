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

typedef enum {
    BLEND_TYPE_NORMAL,
    BLEND_TYPE_LINEAR_DODGE,
    BLEND_TYPE_SCREEN,
    BLEND_TYPE_MULTIPLY,
} _BlendType;

typedef enum {
    SCROLL_DIR_UP_DOWN,
    SCROLL_DIR_LEFT_RIGHT,
} _ScrollDir;

@interface AceClippingScrollNode : CCLayer
{
    float m_priority;
    _ScrollDir scrollDir;
    
    BOOL bMaxContentSizeW;
    float maxContentSizeW;
    BOOL bMaxContentSizeH;
    float maxContentSizeH;
    
    BOOL resetPositionLock;
}

@property (nonatomic,assign) BOOL bMaxContentSizeW;
@property (nonatomic,assign) float maxContentSizeW;
@property (nonatomic,assign) BOOL bMaxContentSizeH;
@property (nonatomic,assign) float maxContentSizeH;
@property (nonatomic,assign) float m_priority;
@property (nonatomic,assign) _ScrollDir scrollDir;
@property (nonatomic,assign) BOOL resetPositionLock;

@end
