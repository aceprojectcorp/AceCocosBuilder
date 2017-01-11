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
#import "AceProgress.h"

@implementation AceProgress

@synthesize progressTime;
@synthesize lastValue;
@synthesize progressCallback;
@synthesize playProgress;
// 프로그래스 하위 스프라이트를 안보이게 한 후 프로그래스바를 생성, 프로그래바 종료 후 하위 스프라이트를 다시 보여주는 방식
- (id)init {
    self = [super init];
    if (!self) return NULL;
    
    self.progressTime = 0.5f;
    self.lastValue = 100.f;
    
    self.progressCallback = @"";
    self.startPosition = 0;
    
    self.playProgress = NO;
    
    [self schedule:@selector(update:)];
    
    return self;
}
// 프로그래스바 실행
- (void)actionProgress {
    [self initProgress];
    
    if(progressTime < 0.0f) self.progressTime = 0.5f;
    
    if(lastValue > 100.f) self.lastValue = 100.f;
    else if(lastValue < 0) self.lastValue = 1.f;
    
    CCArray* array = self.children;
    CCNode* node = nil;
    CCSprite* progressSprite = nil;
    CCARRAY_FOREACH(array, node) {
        progressSprite = (CCSprite*)node;
        [node setVisible:NO];
        break;
    }
    
    if(progressSprite != nil) {
        CCProgressTimer* progressTimer = [CCProgressTimer progressWithSprite:progressSprite];
        [progressTimer setType:kCCProgressTimerTypeBar];
        [progressTimer setPercentage:0];
        [progressTimer setMidpoint:self.startPosition == 0 ? ccp(0, 1) : ccp(1, 0)]; // 0, 1 좌->우 / 1, 0 우->좌
        [progressTimer setBarChangeRate:ccp(1, 0)];
        [progressTimer setTag:0];
        [self addChild:progressTimer];
        
        CCProgressFromTo* progressFromTo = [CCProgressFromTo actionWithDuration:self.progressTime from:0 to:lastValue];
        CCCallFunc* callFunc = [CCCallFunc actionWithTarget:self selector:@selector(initProgress)];
        [progressTimer runAction:[CCSequence actions:progressFromTo, callFunc, nil]];
    }
}
// 프로그래스바 액션 종료 후 지우기
- (void)initProgress {
    [self stopAllActions];
    
    CCArray* array = self.children;
    CCNode* node = nil;
    CCARRAY_FOREACH(array, node) {
        if(node.tag == 0) {
            [self removeChild:node cleanup:YES];
            break;
        }
    }
    
    array = self.children;
    node = nil;
    CCARRAY_FOREACH(array, node) {
        [node setVisible:YES];
    }
    
    [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
}

- (void)update:(ccTime)delta {
    if(self.playProgress) {
        self.playProgress = NO;
        
        [self actionProgress];
    }
}

- (void) dealloc {
    [super dealloc];
}

@end
