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

#import "TexturePropertySetter.h"
#import "CocosBuilderAppDelegate.h"
#import "CCBGlobals.h"
#import "CCBWriterInternal.h"
#import "ResourceManager.h"
#import "CCBFileUtil.h"
#import "CCNode+NodeInfo.h"

@implementation TexturePropertySetter

+ (void) setSpriteFrameForNode:(CCNode*)node andProperty:(NSString*) prop withFile:(NSString*)spriteFile andSheetFile:(NSString*)spriteSheetFile
{
    CCSpriteFrame* spriteFrame = NULL;
    
    //haru - 언어설정에 따라서, spriteSheetFile과 spriteFile 경로를 바꿔주자.
    CCSprite *sprite = (CCSprite*)node;
    switch ([sprite getLanguage])
    {
        case LANGUAGE_KOREAN:
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_en/" withString:@"/local_ko/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_jp/" withString:@"/local_ko/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_ch/" withString:@"/local_ko/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_en/" withString:@"/local_ko/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_jp/" withString:@"/local_ko/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_ch/" withString:@"/local_ko/"];
            break;
     
        case LANGUAGE_JAPANESE:
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_en/" withString:@"/local_jp/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_ko/" withString:@"/local_jp/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_ch/" withString:@"/local_jp/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_en/" withString:@"/local_jp/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_ko/" withString:@"/local_jp/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_ch/" withString:@"/local_jp/"];
            break;
            
        case LANGUAGE_CHINESE:
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_en/" withString:@"/local_ch/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_ko/" withString:@"/local_ch/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_jp/" withString:@"/local_ch/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_en/" withString:@"/local_ch/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_ko/" withString:@"/local_ch/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_jp/" withString:@"/local_ch/"];
            break;
            
        default:
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_ko/" withString:@"/local_en/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_jp/" withString:@"/local_en/"];
            spriteSheetFile = [spriteSheetFile stringByReplacingOccurrencesOfString:@"/local_ch/" withString:@"/local_en/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_ko/" withString:@"/local_en/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_jp/" withString:@"/local_en/"];
            spriteFile = [spriteFile stringByReplacingOccurrencesOfString:@"/local_ch/" withString:@"/local_en/"];
            break;
    }
        
    //haru - spriteSheetFile와 spriteFile 경로를 sprite에 저장
    [node setValue:[spriteSheetFile copy] forKey:@"spriteSheetFile"];
    [node setValue:[spriteFile copy] forKey:@"spriteFile"];
    
    if (spriteSheetFile && ![spriteSheetFile isEqualToString:@""] && ![spriteSheetFile isEqualToString:kCCBUseRegularFile]
        && spriteFile && ![spriteFile isEqualToString:@""])
    {
        // Load the sprite sheet and get the frame
        @try
        {
            // Convert to absolute path
            spriteSheetFile = [[ResourceManager sharedManager] toAbsolutePath:spriteSheetFile];
            
            // To resolution independent image
            spriteSheetFile = [CCBFileUtil toResolutionIndependentFile:spriteSheetFile];
            
            [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:spriteSheetFile];
            
            spriteFrame = [[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:spriteFile];
        }
        @catch (NSException *exception) {
            spriteFrame = NULL;
        }
    }
    else if (spriteFile && ![spriteFile isEqualToString:@""])
    {
        // Create a sprite frame for the single image file
        NSString* fileName = [[ResourceManager sharedManager] toAbsolutePath:spriteFile];
        
        @try
        {
            fileName = [CCBFileUtil toResolutionIndependentFile:fileName];
            CCTexture2D* texture = [[CCTextureCache sharedTextureCache] addImage:fileName];
            
            if (texture)
            {
                CGRect bounds = CGRectMake(0, 0, texture.contentSize.width, texture.contentSize.height);
                
                spriteFrame = [CCSpriteFrame frameWithTexture:texture rect:bounds];
            }
        }
        @catch (NSException *exception) {
            spriteFrame = NULL;
        }
    }
    
    if (!spriteFrame)
    {
        // Texture is missing
        CCTexture2D* texture = [[CCTextureCache sharedTextureCache] addImage:@"missing-texture.png"];
        CGRect bounds = CGRectMake(0, 0, texture.contentSize.width, texture.contentSize.height);
        
        spriteFrame = [CCSpriteFrame frameWithTexture:texture rect:bounds] ;
    }

    // Actually set the sprite frame
    [node setValue:spriteFrame forKey:prop];
}

+ (void) setTextureForNode:(CCNode*)node andProperty:(NSString*) prop withFile:(NSString*) spriteFile
{
    CCTexture2D* texture = NULL;
    
    if (spriteFile && ![spriteFile isEqualToString:@""])
    {
        @try
        {
            NSString* fileName = [[ResourceManager sharedManager] toAbsolutePath:spriteFile];
            
            texture = [[CCTextureCache sharedTextureCache] addImage:fileName];
        }
        @catch (NSException *exception)
        {
            texture = NULL;
        }
    }
    
    if (!texture) texture = [[CCTextureCache sharedTextureCache] addImage:@"missing-texture.png"];
    
    [node setValue:texture forKey:prop];
}

//---jambam 추가
+ (void) setTextureForNode:(CCNode*)node andProperty:(NSString*) prop withFile:(NSString*) spriteFile andSheetFile:(NSString*)spriteSheetFile
{
    CCTexture2D* texture = NULL;
    
    if (spriteSheetFile && ![spriteSheetFile isEqualToString:@""] && ![spriteSheetFile isEqualToString:kCCBUseRegularFile]
        && spriteFile && ![spriteFile isEqualToString:@""])
    {
        // Load the sprite sheet and get the frame
        @try
        {
            // Convert to absolute path
            spriteSheetFile = [[ResourceManager sharedManager] toAbsolutePath:spriteSheetFile];
            
            // To resolution independent image
            spriteSheetFile = [CCBFileUtil toResolutionIndependentFile:spriteSheetFile];
            
            [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:spriteSheetFile];
            CCSpriteFrame* spriteFrame = [[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:spriteFile];
            
            //texture = [[CCTextureCache sharedTextureCache] addImage:fileName];
            texture = [spriteFrame texture];
        }
        @catch (NSException *exception) {
            texture = NULL;
        }
    }
    else if (spriteFile && ![spriteFile isEqualToString:@""])
    {
        @try
        {
            NSString* fileName = [[ResourceManager sharedManager] toAbsolutePath:spriteFile];
            
            texture = [[CCTextureCache sharedTextureCache] addImage:fileName];
        }
        @catch (NSException *exception)
        {
            texture = NULL;
        }
    }
    
    if (!texture) texture = [[CCTextureCache sharedTextureCache] addImage:@"missing-texture.png"];
    
    [node setValue:texture forKey:prop];
}
//---

+ (void) setFontForNode:(CCNode*)node andProperty:(NSString*) prop withFile:(NSString*) fontFile
{
    NSString* absPath = NULL;
    
    if (!fontFile || [fontFile isEqualToString:@""])
    {
        absPath = @"missing-font.fnt";
    }
    else
    {
        absPath = [[ResourceManager sharedManager] toAbsolutePath:fontFile];
        absPath = [CCBFileUtil toResolutionIndependentFile:absPath];
    }
    
    @try
    {
        [node setValue:absPath forKey:prop];
    }
    @catch (NSException *exception)
    {
        [node setValue:@"missing-font.fnt" forKey:prop];
    }
    
    if (!fontFile || [fontFile isEqualToString:@""]) fontFile = @"missing-font.fnt";
    [node setExtraProp:fontFile forKey:prop];
}

+ (NSString*) fontForNode:(CCNode*)node andProperty:(NSString*) prop
{
    NSString* fntFile = [node extraPropForKey:prop];
    if ([fntFile isEqualToString:@"missing-font.fnt"]) return NULL;
    return fntFile;
}

+ (void) setTtfForNode:(CCNode*)node andProperty:(NSString*) prop withFont:(NSString*) fontName
{
    NSString* fullName = fontName;
    //if ([[fontName lowercaseString] hasSuffix:@".ttf"]) //jambam 원본
    if ([[fontName lowercaseString] hasSuffix:@".ttf"] || [[fontName lowercaseString] hasSuffix:@".otf"]) //jambam 수정
    {
        fullName = [[ResourceManager sharedManager] toAbsolutePath:fontName];
    }
    if (!fullName) fullName = @"";
//    NSLog(@"라벨로그시작 %@, %@, %@", prop, fullName, fontName);
    [node setValue:fullName forKey:prop];
    
    if (!fontName) fontName = @"";
    [node setExtraProp:fontName forKey:prop];
//    NSLog(@"라벨로그끝");
}

+ (NSString*) ttfForNode:(CCNode*)node andProperty:(NSString*) prop
{
    NSString* fntFile = [node extraPropForKey:prop];
    if ([fntFile isEqualToString:@""]) return NULL;
    return fntFile;
}

@end
