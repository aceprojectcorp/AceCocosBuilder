/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
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
 *
 */


#import "CCLabelTTF.h"
#import "Support/CGPointExtension.h"
#import "ccMacros.h"
#import "CCShaderCache.h"
#import "CCGLProgram.h"
#import "Support/CCFileUtils.h"
#import "ccDeprecated.h"

#ifdef __CC_PLATFORM_IOS
#import "Platforms/iOS/CCDirectorIOS.h"
#import <CoreText/CoreText.h>
#endif

#if CC_USE_LA88_LABELS
#define SHADER_PROGRAM kCCShader_PositionTextureColor
#else
#define SHADER_PROGRAM kCCShader_PositionTextureA8Color
#endif

@interface CCLabelTTF ()
- (NSString*) getFontName:(NSString*)fontName;
@end

@implementation CCLabelTTF

// -
+ (id) labelWithString:(NSString*)string fontName:(NSString*)name fontSize:(CGFloat)size
{
	return [[[self alloc] initWithString:string fontName:name fontSize:size]autorelease];
}

// hAlignment
+ (id) labelWithString:(NSString*)string fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment
{
	return [[[self alloc] initWithString:string  fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:kCCVerticalTextAlignmentTop lineBreakMode:kCCLineBreakModeWordWrap]autorelease];
}

// hAlignment, vAlignment
+ (id) labelWithString:(NSString*)string fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment vAlignment:(CCVerticalTextAlignment) vertAlignment
{
	return [[[self alloc] initWithString:string fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:vertAlignment]autorelease];
}

// hAlignment, lineBreakMode
+ (id) labelWithString:(NSString*)string fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment lineBreakMode:(CCLineBreakMode)lineBreakMode
{
	return [[[self alloc] initWithString:string fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:kCCVerticalTextAlignmentTop lineBreakMode:lineBreakMode]autorelease];
}

// hAlignment, vAlignment, lineBreakMode
+ (id) labelWithString:(NSString*)string fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment vAlignment:(CCVerticalTextAlignment) vertAlignment lineBreakMode:(CCLineBreakMode)lineBreakMode
{
	return [[[self alloc] initWithString:string fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:vertAlignment lineBreakMode:lineBreakMode]autorelease];
}

- (id) init
{
    //haru - 기본언어는 디폴트로 설정.
    _language = LANGUAGE_DEFAULT;
    return [self initWithString:@"" fontName:@"Helvetica" fontSize:12];
}

- (id) initWithString:(NSString*)str fontName:(NSString*)name fontSize:(CGFloat)size
{
	return [self initWithString:str fontName:name fontSize:size dimensions:CGSizeZero hAlignment:kCCTextAlignmentLeft vAlignment:kCCVerticalTextAlignmentTop lineBreakMode:kCCLineBreakModeWordWrap];
}

// hAlignment
- (id) initWithString:(NSString*)str fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment
{
	return [self initWithString:str fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:kCCVerticalTextAlignmentTop lineBreakMode:kCCLineBreakModeWordWrap];
}

// hAlignment, vAlignment
- (id) initWithString:(NSString*)str fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment vAlignment:(CCVerticalTextAlignment) vertAlignment
{
	return [self initWithString:str fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:vertAlignment lineBreakMode:kCCLineBreakModeWordWrap];
}

// hAlignment, lineBreakMode
- (id) initWithString:(NSString*)str fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment lineBreakMode:(CCLineBreakMode)lineBreakMode
{
	return [self initWithString:str fontName:name fontSize:size dimensions:dimensions hAlignment:alignment vAlignment:kCCVerticalTextAlignmentTop lineBreakMode:lineBreakMode];
}

// hAlignment, vAligment, lineBreakMode
- (id) initWithString:(NSString*)str  fontName:(NSString*)name fontSize:(CGFloat)size dimensions:(CGSize)dimensions hAlignment:(CCTextAlignment)alignment vAlignment:(CCVerticalTextAlignment) vertAlignment lineBreakMode:(CCLineBreakMode)lineBreakMode
{
	if( (self=[super init]) ) {

		// shader program
		self.shaderProgram = [[CCShaderCache sharedShaderCache] programForKey:SHADER_PROGRAM];

		_dimensions = dimensions;
		_hAlignment = alignment;
		_vAlignment = vertAlignment;
		_fontName = [[self getFontName: name] copy];
		_fontSize = size;
		_lineBreakMode = lineBreakMode;

		[self setString:str];
	}
	return self;
}

- (void) setString:(NSString*)str
{
	NSAssert( str, @"Invalid string" );

	if( _string.hash != str.hash ) {
		[_string release];
		_string = [str copy];

		[self updateTexture];
	}
}

- (void) setString_kr:(NSString*)str
{
    NSAssert( str, @"Invalid string" );

    if( _string_kr.hash != str.hash ) {
        [_string_kr release];
        _string_kr = [str copy];

        [self updateTexture];
    }
}

- (void) setString_jp:(NSString*)str
{
    NSAssert( str, @"Invalid string" );

    if( _string_jp.hash != str.hash ) {
        [_string_jp release];
        _string_jp = [str copy];

        [self updateTexture];
    }
}

- (void) setString_ch:(NSString*)str
{
    NSAssert( str, @"Invalid string" );

    if( _string_ch.hash != str.hash ) {
        [_string_ch release];
        _string_ch = [str copy];

        [self updateTexture];
    }
}


-(NSString*) string
{
	return _string;
}

-(NSString*) string_kr
{
    return _string_kr;
}

-(NSString*) string_jp
{
    return _string_jp;
}

-(NSString*) string_ch
{
    return _string_ch;
}


- (NSString*) getFontName:(NSString*)fontName
{
	// Custom .ttf file ?
    //if ([[fontName lowercaseString] hasSuffix:@".ttf"]) //jambam 원본
    if ([[fontName lowercaseString] hasSuffix:@".ttf"] || [[fontName lowercaseString] hasSuffix:@".otf"]) //jambam 수정
    {
        // This is a file, register font with font manager
        NSString* fontFile = [[CCFileUtils sharedFileUtils] fullPathForFilename:fontName];
        NSURL* fontURL = [NSURL fileURLWithPath:fontFile];
        CTFontManagerRegisterFontsForURL((CFURLRef)fontURL, kCTFontManagerScopeProcess, NULL);

		return [[fontFile lastPathComponent] stringByDeletingPathExtension];
    }

    return fontName;
}

- (void)setFontName:(NSString*)fontName
{
    fontName = [self getFontName:fontName];
    
	if( fontName.hash != _fontName.hash ) {
		[_fontName release];
		_fontName = [fontName copy];
		
		// Force update
		if( _string )
			[self updateTexture];
	}
}

- (void)setFontName_kr:(NSString*)fontName
{
    fontName = [self getFontName:fontName];
    
    if( fontName.hash != _fontName_kr.hash ) {
        [_fontName_kr release];
        _fontName_kr = [fontName copy];
        
        // Force update
        if( _string_kr )
            [self updateTexture];
    }
}

- (void)setFontName_jp:(NSString*)fontName
{
    fontName = [self getFontName:fontName];
    
    if( fontName.hash != _fontName_jp.hash ) {
        [_fontName_jp release];
        _fontName_jp = [fontName copy];
        
        // Force update
        if( _string_jp )
            [self updateTexture];
    }
}

- (void)setFontName_ch:(NSString*)fontName
{
    fontName = [self getFontName:fontName];
    
    if( fontName.hash != _fontName_ch.hash ) {
        [_fontName_ch release];
        _fontName_ch = [fontName copy];
        
        // Force update
        if( _string_ch )
            [self updateTexture];
    }
}

- (NSString*)fontName
{
    return _fontName;
}

- (NSString*)fontName_kr
{
    return _fontName_kr;
}

- (NSString*)fontName_jp
{
    return _fontName_jp;
}

- (NSString*)fontName_ch
{
    return _fontName_ch;
}

- (void) setFontSize:(float)fontSize
{
	if( fontSize != _fontSize ) {
		_fontSize = fontSize;
		
		// Force update
		if( _string )
			[self updateTexture];
	}
}

- (void) setFontSize_kr:(float)fontSize
{
    if( fontSize != _fontSize_kr ) {
        _fontSize_kr = fontSize;
        
        // Force update
        if( _string_kr )
            [self updateTexture];
    }
}

- (void) setFontSize_jp:(float)fontSize
{
    if( fontSize != _fontSize_jp ) {
        _fontSize_jp = fontSize;
        
        // Force update
        if( _string_jp )
            [self updateTexture];
    }
}

- (void) setFontSize_ch:(float)fontSize
{
    if( fontSize != _fontSize_ch ) {
        _fontSize_ch = fontSize;
        
        // Force update
        if( _string_ch )
            [self updateTexture];
    }
}

- (float) fontSize
{
    return _fontSize;
}

- (float) fontSize_kr
{
    return _fontSize_kr;
}

- (float) fontSize_jp
{
    return _fontSize_jp;
}

- (float) fontSize_ch
{
    return _fontSize_ch;
}


-(void) setDimensions:(CGSize) dim
{
    if( dim.width != _dimensions.width || dim.height != _dimensions.height)
	{
        _dimensions = dim;
        
		// Force update
		if( _string )
			[self updateTexture];
    }
}

-(CGSize) dimensions
{
    return _dimensions;
}

-(void) setHorizontalAlignment:(CCTextAlignment)alignment
{
    if (alignment != _hAlignment)
    {
        _hAlignment = alignment;
        
        // Force update
		if( _string )
			[self updateTexture];

    }
}

- (CCTextAlignment) horizontalAlignment
{
    return _hAlignment;
}

-(void) setVerticalAlignment:(CCVerticalTextAlignment)verticalAlignment
{
    if (_vAlignment != verticalAlignment)
    {
        _vAlignment = verticalAlignment;
        
		// Force update
		if( _string )
			[self updateTexture];
    }
}

- (CCVerticalTextAlignment) verticalAlignment
{
    return _vAlignment;
}

- (void) dealloc
{
	[_string release];
	[_fontName release];

	[super dealloc];
}

- (NSString*) description
{
	// XXX: _string, _fontName can't be displayed here, since they might be already released

	return [NSString stringWithFormat:@"<%@ = %p | FontSize = %.1f>", [self class], self, _fontSize];
}

// Helper
- (BOOL) updateTexture
{				
	CCTexture2D *tex;
	if( _dimensions.width == 0 || _dimensions.height == 0 )
    {
        //haru - 언어설정에 따라서 뿌려주자.
        switch ([super getLanguage]) {
            case LANGUAGE_KOREAN:
                if (_string_kr == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string_kr
                                                 fontName:_fontName_kr
                                                 fontSize:_fontSize_kr  * CC_CONTENT_SCALE_FACTOR()];
                break;
            case LANGUAGE_JAPANESE:
                if (_string_jp == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string_jp
                                                 fontName:_fontName_jp
                                                 fontSize:_fontSize_jp  * CC_CONTENT_SCALE_FACTOR()];
                break;
            case LANGUAGE_CHINESE:
                if (_string_ch == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string_ch
                                                 fontName:_fontName_ch
                                                 fontSize:_fontSize_ch  * CC_CONTENT_SCALE_FACTOR()];
                break;
            default:
                if (_string == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string
                                                 fontName:_fontName
                                                 fontSize:_fontSize  * CC_CONTENT_SCALE_FACTOR()];
                break;
        }
    }
	else
    {
        //haru - 언어설정에 따라서 뿌려주자.
        switch (_language) {
            case LANGUAGE_KOREAN:
                if (_string_kr == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string_kr
                                                 fontName:_fontName_kr
                                                 fontSize:_fontSize_kr  * CC_CONTENT_SCALE_FACTOR()
                                               dimensions:CC_SIZE_POINTS_TO_PIXELS(_dimensions)
                                               hAlignment:_hAlignment
                                               vAlignment:_vAlignment
                                            lineBreakMode:_lineBreakMode
                       ];
                break;
            case LANGUAGE_JAPANESE:
                if (_string_jp == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string_jp
                                                 fontName:_fontName_jp
                                                 fontSize:_fontSize_jp  * CC_CONTENT_SCALE_FACTOR()
                                               dimensions:CC_SIZE_POINTS_TO_PIXELS(_dimensions)
                                               hAlignment:_hAlignment
                                               vAlignment:_vAlignment
                                            lineBreakMode:_lineBreakMode
                       ];
                break;
            case LANGUAGE_CHINESE:
                if (_string_ch == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string_ch
                                                 fontName:_fontName_ch
                                                 fontSize:_fontSize_ch  * CC_CONTENT_SCALE_FACTOR()
                                               dimensions:CC_SIZE_POINTS_TO_PIXELS(_dimensions)
                                               hAlignment:_hAlignment
                                               vAlignment:_vAlignment
                                            lineBreakMode:_lineBreakMode
                       ];
                break;
            default:
                if (_string == nil) return false;
                
                tex = [[CCTexture2D alloc] initWithString:_string
                                                 fontName:_fontName
                                                 fontSize:_fontSize  * CC_CONTENT_SCALE_FACTOR()
                                               dimensions:CC_SIZE_POINTS_TO_PIXELS(_dimensions)
                                               hAlignment:_hAlignment
                                               vAlignment:_vAlignment
                                            lineBreakMode:_lineBreakMode
                       ];
                break;
        }
    }
    
	if( !tex )
		return NO;

#ifdef __CC_PLATFORM_IOS
	// iPad ?
	if( UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad ) {
		if( CC_CONTENT_SCALE_FACTOR() == 2 )
			[tex setResolutionType:kCCResolutioniPadRetinaDisplay];
		else
			[tex setResolutionType:kCCResolutioniPad];
	}
	// iPhone ?
	else
	{
		if( CC_CONTENT_SCALE_FACTOR() == 2 )
			[tex setResolutionType:kCCResolutioniPhoneRetinaDisplay];
		else
			[tex setResolutionType:kCCResolutioniPhone];
	}
#endif
	
	[self setTexture:tex];
	[tex release];
	
	CGRect rect = CGRectZero;
	rect.size = [_texture contentSize];
	[self setTextureRect: rect];
	
	return YES;
}
@end
