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

#import "AceSprite.h"

@implementation AceSprite

@synthesize blendType;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.blendType = BLEND_TYPE_NORMAL;
    
    //setCascadeOpacityEnabled(true);
    //self._cascadeOpacityEnabled = true;
    //[self setCascadeOpacityEnabled:false];
    
    
    return self;
}

-(void) draw
{
    [super draw];
    
    //ccGLBlendFunc( _blendFunc.src, _blendFunc.dst );
     //ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    switch(blendType)
    {
        case BLEND_TYPE_NORMAL :
            _blendFunc.src = GL_ONE;
            _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
            break;
        case BLEND_TYPE_LINEAR_DODGE :
            _blendFunc.src = GL_ONE;
            _blendFunc.dst = GL_ONE;
            break;
        case BLEND_TYPE_SCREEN :
            _blendFunc.src = GL_ONE;
            _blendFunc.dst = GL_ONE_MINUS_SRC_COLOR;
            break;
        case BLEND_TYPE_MULTIPLY :
            _blendFunc.src = GL_DST_COLOR;
            _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
            break;
    }
}


@end
