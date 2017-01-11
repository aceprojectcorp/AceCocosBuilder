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
#import "AceMaskNode.h"

@implementation AceMaskNode

@synthesize maskRefresh;

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    self.maskRefresh = false;
    
    clippingNode = NULL;
    
    [self refresh];
    
    return self;
}

-(void) draw
{
    [super draw];
    
    if(maskRefresh)
    {
        [self refresh];
        
        maskRefresh = false;
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    

    //---test
    CCArray* children = [self children];
    int size = (int)[children count];
    if(size > 2)
    {
        CCSprite* pMaskSprite = (CCSprite*)[children objectAtIndex:(int)0];
        CCSprite* pOriginSprite = (CCSprite*)[children objectAtIndex:(int)1];
        CCSprite* pOriginSprite2 = (CCSprite*)[children objectAtIndex:(int)2];
        
        glColorMask(false, false, false, true);
        glClearStencil(0);
        glEnable(GL_STENCIL_TEST);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        glStencilFunc(GL_ALWAYS, 0x1, 0x1);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
        
        
        //마스크 영역을 그려줍니다...
        ccBlendFunc bfMask;
        bfMask.src = GL_ZERO;
        bfMask.dst = GL_ONE_MINUS_SRC_ALPHA;
        [pMaskSprite setBlendFunc:bfMask];
        [pMaskSprite draw];
        
        glColorMask(true, true, true, true);
        
        glStencilFunc(GL_EQUAL, 0x1, 0x1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        
        // 마스킹될 영역을 그립니다.
        //ccBlendFunc bfTexture;
        //bfTexture.src = GL_ONE_MINUS_DST_ALPHA;
        //bfTexture.dst = GL_DST_ALPHA;
        //[pOriginSprite setBlendFunc:bfTexture];
        //[pOriginSprite draw];
        
        ccBlendFunc bfTexture2;
        bfTexture2.src = GL_ONE_MINUS_DST_ALPHA;
        bfTexture2.dst = GL_DST_ALPHA;
        [pOriginSprite2 setBlendFunc:bfTexture2];
        [pOriginSprite draw];
        
        glDisable(GL_STENCIL_TEST);
    }
    //---
}


-(void) refresh
{
    CCArray* children = [self children];
    int size = (int)[children count];
    if(size >= 2)
    {
        CCSprite* pMaskSprite = (CCSprite*)[children objectAtIndex:(int)0];
        CCSprite* pOriginSprite = (CCSprite*)[children objectAtIndex:(int)1];
        
        ccBlendFunc bfMask;
        bfMask.src = GL_ZERO;
        bfMask.dst = GL_ONE_MINUS_SRC_ALPHA;
        [pMaskSprite setBlendFunc:bfMask];
        //[pMaskSprite visit];
        
        ccBlendFunc bfTexture;
        bfTexture.src = GL_ONE_MINUS_DST_ALPHA;
        bfTexture.dst = GL_DST_ALPHA;
        [pOriginSprite setBlendFunc:bfTexture];
        //[pOriginSprite visit];
        
        
        
        
        
        /*
        [pMaskSprite setVisible:false];
        [pOriginSprite setVisible:false];
        
        CCTexture2D* texture = [pMaskSprite texture];
        clippingNode = [CCClippingNode clippingNodeWithStencil:[CCSprite spriteWithTexture:texture]];
        clippingNode.alphaThreshold = 0;
        texture = [pOriginSprite texture];
        [clippingNode addChild:[CCSprite spriteWithTexture:texture]];
        [self addChild:clippingNode];
        */
    }
}

/*
-(CCSprite*) maskedSpriteWithSprite:(CCSprite*)pTextureSprite pMaskSprite:(CCSprite*)pMaskSprite
{
    int maskWidth = [pMaskSprite contentSize].width;
    int maskHeight = [pMaskSprite contentSize].height;
    CCRenderTexture* rt = [CCRenderTexture renderTextureWithWidth:maskWidth height:maskHeight];
    
    ccBlendFunc bfMask;
    bfMask.src = GL_ONE;
    bfMask.dst = GL_ZERO;
    [pMaskSprite setBlendFunc:bfMask];
    
    [[pMaskSprite texture] setAliasTexParameters];
    
    ccBlendFunc bfTexture;
    bfTexture.src = GL_DST_ALPHA;
    bfTexture.dst = GL_ZERO;
    [pTextureSprite setBlendFunc:bfTexture];
    
    [rt begin];
    [pMaskSprite visit];
    [pTextureSprite visit];
    [rt end];
    
    CCSprite* pOutcome = [CCSprite spriteWithTexture:[[rt sprite] texture]];
    [pOutcome setFlipY:true];
    
    return pOutcome;
}
*/


@end
