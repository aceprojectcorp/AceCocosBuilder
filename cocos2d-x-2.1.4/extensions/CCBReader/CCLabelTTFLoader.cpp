#include "CCLabelTTFLoader.h"



#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FONTNAME "fontName"
//haru - labelTTF 다국어 지원용 프로퍼티 추가
#define PROPERTY_FONTNAME_KR "fontName_kr"
#define PROPERTY_FONTNAME_JP "fontName_jp"
#define PROPERTY_FONTNAME_CH "fontName_ch"
#define PROPERTY_FONTSIZE "fontSize"
//haru - labelTTF 다국어 지원용 프로퍼티 추가
#define PROPERTY_FONTSIZE_KR "fontSize_kr"
#define PROPERTY_FONTSIZE_JP "fontSize_jp"
#define PROPERTY_FONTSIZE_CH "fontSize_ch"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_STRING "string"
//haru - labelTTF 다국어 지원용 프로퍼티 추가
#define PROPERTY_STRING_KR "string_kr"
#define PROPERTY_STRING_JP "string_jp"
#define PROPERTY_STRING_CH "string_ch"
#define PROPERTY_DIMENSIONS "dimensions"

NS_CC_EXT_BEGIN

void CCLabelTTFLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((CCLabelTTF *)pNode)->setColor(pCCColor3B);
    } else {
        CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((CCLabelTTF *)pNode)->setOpacity(pByte);
    } else {
        CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((CCLabelTTF *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTNAME) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_DEFAULT)
        {
            ((CCLabelTTF *)pNode)->setFontName(pFontTTF);
        }
    }
    //haru - labelTTF 다국어 지원용 프로퍼티 추가
    else if(strcmp(pPropertyName, PROPERTY_FONTNAME_KR) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_KOREAN)
        {
            ((CCLabelTTF *)pNode)->setFontName(pFontTTF);
        }
    } else if(strcmp(pPropertyName, PROPERTY_FONTNAME_JP) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_JAPANESE)
        {
            ((CCLabelTTF *)pNode)->setFontName(pFontTTF);
        }
    } else if(strcmp(pPropertyName, PROPERTY_FONTNAME_CH) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_CHINESE)
        {
            ((CCLabelTTF *)pNode)->setFontName(pFontTTF);
        }
    } else {
        CCNodeLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pText, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_DEFAULT)
        {
            ((CCLabelTTF *)pNode)->setString(pText);
        }
    }
    //haru - labelTTF 다국어 지원용 프로퍼티 추가
    else if(strcmp(pPropertyName, PROPERTY_STRING_KR) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_KOREAN)
        {
            ((CCLabelTTF *)pNode)->setString(pText);
        }
    } else if(strcmp(pPropertyName, PROPERTY_STRING_JP) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_JAPANESE)
        {
            ((CCLabelTTF *)pNode)->setString(pText);
        }
    } else if(strcmp(pPropertyName, PROPERTY_STRING_CH) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_CHINESE)
        {
            ((CCLabelTTF *)pNode)->setString(pText);
        }
    } else {
        CCNodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTSIZE) == 0) {
        ((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
    }
    //haru - labelTTF 다국어 지원용 프로퍼티 추가
    else if(strcmp(pPropertyName, PROPERTY_FONTSIZE_KR) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_KOREAN)
        {
            ((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
        }
    } else if(strcmp(pPropertyName, PROPERTY_FONTSIZE_JP) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_JAPANESE)
        {
            ((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
        }
    } else if(strcmp(pPropertyName, PROPERTY_FONTSIZE_CH) == 0) {
        if (((CCLabelTTF *)pNode)->getLanguage() == LANGUAGE_CHINESE)
        {
            ((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
        }
    } else {
        CCNodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_HORIZONTALALIGNMENT) == 0) {
        ((CCLabelTTF *)pNode)->setHorizontalAlignment(CCTextAlignment(pIntegerLabeled));
    } else if(strcmp(pPropertyName, PROPERTY_VERTICALALIGNMENT) == 0) {
        ((CCLabelTTF *)pNode)->setVerticalAlignment(CCVerticalTextAlignment(pIntegerLabeled));
    } else {
        CCNodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DIMENSIONS) == 0) {
        ((CCLabelTTF *)pNode)->setDimensions(pSize);
    } else {
        CCNodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

NS_CC_EXT_END