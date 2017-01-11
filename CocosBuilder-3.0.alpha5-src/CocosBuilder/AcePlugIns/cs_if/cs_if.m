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

#import "cs_if.h"
#import "cs_if_true.h"
#import "cs_if_false.h"


@implementation cs_if

@synthesize valueType;
@synthesize compareType;
@synthesize aValue_int;
@synthesize bValue_int;
@synthesize aValue_float;
@synthesize bValue_float;
@synthesize aValue_string;
@synthesize bValue_string;

@synthesize bTrue;
@synthesize bFalse;

#define TRUEFALSETYPE_FALSE 0
#define TRUEFALSETYPE_TRUE 1

- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    valueType = VALUE_TYPE_INT;
    compareType = A_EQUAL_B;
    aValue_int = 0;
    bValue_int = 0;
    aValue_float = 0;
    bValue_float = 0;
    aValue_string = @"";
    bValue_string = @"";
    
    checkIdx = 0;
    
    [self schedule:@selector(run)];
    
    return self;
}

-(void) run
{
    CCArray* children = [self children];
    int size = (int)[children count];

    cs_if_true* trueNode = NULL;
    cs_if_true* falseNode = NULL;
    
    for(int i=0; i<size; i++)
    {
        cs_if_true* pNode = [children objectAtIndex:(int)i];
        
        int truefalseType = [pNode getTruefalse];
        if(truefalseType == TRUEFALSETYPE_TRUE)
        {
            trueNode = pNode;
        }
        else
        {
            falseNode = pNode;
        }
    }
    
    //bool val = [self valueCompare];
    bool val = [self trueFalseCheck];
    if(val)
    {
        if(trueNode) [trueNode setVisible:true];
        if(falseNode) [falseNode setVisible:false];
    }
    else
    {
        if(trueNode) [trueNode setVisible:false];
        if(falseNode) [falseNode setVisible:true];
    }
    
    [self trueFalseCheck];
}

-(bool) trueFalseCheck
{
    bool val = false;
    bool tmpCheck[2] = {false, false};
    
    tmpCheck[0] = bTrue;
    tmpCheck[1] = bFalse;
    
    int trueCount = 0;
    for(int i=0; i<2; i++)
    {
        if(tmpCheck[i])
        {
            trueCount++;
        }
    }
    
    if(trueCount == 0)
    {
        switch(checkIdx)
        {
            case 0 :
                bTrue = true;
                break;
            case 1 :
                bFalse = true;
                break;
        }
        
        [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
    }
    else
    {
        for(int i=0; i<2; i++)
        {
            if(tmpCheck[i] && i != checkIdx)
            {
                checkIdx = i;
                
                switch(checkIdx)
                {
                    case 0 :
                        bTrue = true;
                        bFalse = false;
                        break;
                    case 1 :
                        bTrue = false;
                        bFalse = true;
                        break;
                }
                
                [[CocosBuilderAppDelegate appDelegate] updateInspectorFromSelection];
                
                break;
            }
        }
    }
    
    if(bTrue) val = true;
    else val = false;
    
    return val;
}

-(bool) valueCompare
{
    bool val = false;
    
    switch(valueType)
    {
        case VALUE_TYPE_INT :
            switch(compareType)
        {
            case A_EQUAL_B :           //a == b
                if(aValue_int == bValue_int) val = true;
                break;
            case A_NOT_EQUAL_B :       //a != b
                if(aValue_int != bValue_int) val = true;
                break;
            case A_BIG_B :             //a > b
                if(aValue_int > bValue_int) val = true;
                break;
            case A_SMALL_B :           //a < b
                if(aValue_int < bValue_int) val = true;
                break;
            case A_BIG_OR_EQUAL_B :    //a >= b
                if(aValue_int >= bValue_int) val = true;
                break;
            case A_SMALL_OR_EQUAL_B :  //a <= b
                if(aValue_int <= bValue_int) val = true;
                break;
        }
            break;
        case VALUE_TYPE_FLOAT :
            switch(compareType)
        {
            case A_EQUAL_B :           //a == b
                if(aValue_float == bValue_float) val = true;
                break;
            case A_NOT_EQUAL_B :       //a != b
                if(aValue_float != bValue_float) val = true;
                break;
            case A_BIG_B :             //a > b
                if(aValue_float > bValue_float) val = true;
                break;
            case A_SMALL_B :           //a < b
                if(aValue_float < bValue_float) val = true;
                break;
            case A_BIG_OR_EQUAL_B :    //a >= b
                if(aValue_float >= bValue_float) val = true;
                break;
            case A_SMALL_OR_EQUAL_B :  //a <= b
                if(aValue_float <= bValue_float) val = true;
                break;
        }
            break;
        case VALUE_TYPE_STRING :
            switch(compareType)
        {
            case A_EQUAL_B :           //a == b
                if([aValue_string isEqualToString:bValue_string]) val = true;
                break;
            case A_NOT_EQUAL_B :       //a != b
                if(![aValue_string isEqualToString:bValue_string]) val = true;
                break;
        }
            break;
    }
    
    return val;
}


@end
