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
    VALUE_TYPE_INT,
    VALUE_TYPE_FLOAT,
    VALUE_TYPE_STRING,
} _ValueType;

typedef enum {
    A_EQUAL_B,          //a == b
    A_NOT_EQUAL_B,      //a != b
    A_BIG_B,            //a > b
    A_SMALL_B,          //a < b
    A_BIG_OR_EQUAL_B,   //a >= b
    A_SMALL_OR_EQUAL_B, //a <= b
} _CompareType;

@interface cs_if : CCNode
{
    _ValueType valueType;
    _CompareType compareType;
    float aValue_int;
    float bValue_int;
    float aValue_float;
    float bValue_float;
    NSString* aValue_string;
    NSString* bValue_string;
    
    BOOL bTrue;
    BOOL bFalse;
    
    int checkIdx;
}

@property (nonatomic,assign) _ValueType valueType;
@property (nonatomic,assign) _CompareType compareType;
@property (nonatomic,assign) float aValue_int;
@property (nonatomic,assign) float bValue_int;
@property (nonatomic,assign) float aValue_float;
@property (nonatomic,assign) float bValue_float;
@property (nonatomic,assign) NSString* aValue_string;
@property (nonatomic,assign) NSString* bValue_string;

@property (nonatomic,assign) BOOL bTrue;
@property (nonatomic,assign) BOOL bFalse;

-(void) run;
-(bool) valueCompare;
-(bool) trueFalseCheck;
@end
