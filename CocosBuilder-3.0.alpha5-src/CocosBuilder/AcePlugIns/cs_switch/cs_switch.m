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

#import "cs_switch.h"
#import "cs_switch_case.h"

@implementation cs_switch

@synthesize valueType;
@synthesize value_string;


- (id) init
{
    self = [super init];
    if (!self) return NULL;
    
    valueType = VALUE_TYPE_STRING;
    value_string = @"";
    
    [self schedule:@selector(run)];
    
    return self;
}

-(void) run
{
    CCArray* children = [self children];
    int size = (int)[children count];
    
    cs_switch_case* pNode = NULL;
    
    int defaultPos = -1;
    bool bDefaultView = true;
    for(int i=0; i<size; i++)
    {
        pNode = [children objectAtIndex:(int)i];
        [pNode setVisible:false];

        if([[pNode getValue] isEqualToString:@"default"])
        {
            defaultPos = i;
        }
        else
        {
            if(valueType == VALUE_TYPE_INT)
            {
                int tmpValue = [[pNode getValue] intValue];
                if([value_string intValue] == tmpValue)
                {
                    [pNode setVisible:true];
                    bDefaultView = false;
                }
            }
            else
            {
                NSString* tmpValue = [pNode getValue];
                if([value_string isEqualToString:tmpValue])
                {
                    [pNode setVisible:true];
                    bDefaultView = false;
                }
            }
        }
    }
    
    if(bDefaultView && defaultPos != -1)
    {
        [pNode setVisible:true];
    }
}



@end
