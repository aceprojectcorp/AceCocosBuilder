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

#define COMPOSITE_LABEL_ALIGN_LEFT      0
#define COMPOSITE_LABEL_ALIGN_CENTER    1
#define COMPOSITE_LABEL_ALIGN_RIGHT     2

@interface AceCompositeLabel : CCNode
{
    //int m_align;
    BOOL m_align_left;
    BOOL m_align_center;
    BOOL m_align_right;
    BOOL contentSizeRefresh;
    
    float gapX;
    
    int checkIdx;
}

@property (nonatomic,assign) BOOL m_align_left;
@property (nonatomic,assign) BOOL m_align_center;
@property (nonatomic,assign) BOOL m_align_right;
@property (nonatomic,assign) BOOL contentSizeRefresh;
@property (nonatomic,assign) float gapX;



-(void)repaint;
-(void)alignCheck;


@end
