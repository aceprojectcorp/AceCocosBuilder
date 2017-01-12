#include "CCNodeLoader.h"
#include "CCBSelectorResolver.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBAnimationManager.h"
#include "CCData.h"
#include "CCNode+CCBRelativePositioning.h"

//---jambam
//#include "g_Grobal.h"
//---

using namespace std;

NS_CC_EXT_BEGIN

CCNodeLoader::CCNodeLoader()
{
    m_pCustomProperties = new CCDictionary();
}

CCNodeLoader::~CCNodeLoader()
{
    CC_SAFE_RELEASE(m_pCustomProperties);
}

CCDictionary* CCNodeLoader::getCustomProperties()
{
    return m_pCustomProperties;
}

CCNode * CCNodeLoader::loadCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    CCNode * ccNode = this->createCCNode(pParent, pCCBReader);

    //this->parseProperties(ccNode, pParent, pCCBReader);

    return ccNode;
}

void CCNodeLoader::parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) //jambam 원본
{
    int numRegularProps = pCCBReader->readInt(false);
    int numExturaProps = pCCBReader->readInt(false);
    int propertyCount = numRegularProps + numExturaProps;

    for(int i = 0; i < propertyCount; i++) {
        bool isExtraProp = (i >= numRegularProps);
        int type = pCCBReader->readInt(false);
        std::string propertyName = pCCBReader->readCachedString();

        // Check if the property can be set for this platform
        bool setProp = false;
        
        int platform = pCCBReader->readByte();
        if(platform == kCCBPlatformAll) 
        {
            setProp = true;
        }
        // Cocos2d-x is using touch event callback for all platforms,
        // it's different from cocos2d-iphone which uses mouse event for Mac port.
        // So we just need to touch event by using kCCBPlatformIOS.
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if(platform == kCCBPlatformIOS)
        {
            setProp = true;
        }
// #elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//         if(platform == kCCBPlatformMac)
//         {
//             setProp = true;
//         }
// #endif
        
        // Forward properties for sub ccb files
        if (dynamic_cast<CCBFile*>(pNode) != NULL)
        {
            CCBFile *ccbNode = (CCBFile*)pNode;
            if (ccbNode->getCCBFileNode() && isExtraProp)
            {
                pNode = ccbNode->getCCBFileNode();
                
                // Skip properties that doesn't have a value to override
                CCArray *extraPropsNames = (CCArray*)pNode->getUserObject();
                CCObject* pObj = NULL;
                bool bFound = false;
                CCARRAY_FOREACH(extraPropsNames, pObj)
                {
                    CCString* pStr = (CCString*)pObj;
                    if (0 == pStr->compare(propertyName.c_str()))
                    {
                        bFound = true;
                        break;
                    }
                }
                setProp &= bFound;
            }
        }
        else if (isExtraProp && pNode == pCCBReader->getAnimationManager()->getRootNode())
        {
            CCArray *extraPropsNames = (CCArray*)pNode->getUserObject();
            if (! extraPropsNames)
            {
                extraPropsNames = CCArray::create();
                pNode->setUserObject(extraPropsNames);
            }
            
            extraPropsNames->addObject(CCString::create(propertyName));
        }

        switch(type) 
        {
            case kCCBPropTypePosition: 
            {
                CCPoint position = this->parsePropTypePosition(pNode, pParent, pCCBReader, propertyName.c_str());
                if (setProp) 
                {
                    this->onHandlePropTypePosition(pNode, pParent, propertyName.c_str(), position, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePoint: 
            {
                CCPoint point = this->parsePropTypePoint(pNode, pParent, pCCBReader);
                if (setProp) 
                {
                    this->onHandlePropTypePoint(pNode, pParent, propertyName.c_str(), point, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePointLock: 
            {
                CCPoint pointLock = this->parsePropTypePointLock(pNode, pParent, pCCBReader);
                if (setProp) 
                {
                    this->onHandlePropTypePointLock(pNode, pParent, propertyName.c_str(), pointLock, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSize: {
                CCSize size = this->parsePropTypeSize(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeSize(pNode, pParent, propertyName.c_str(), size, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeScaleLock: 
            {
                float * scaleLock = this->parsePropTypeScaleLock(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeScaleLock(pNode, pParent, propertyName.c_str(), scaleLock, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(scaleLock);
                break;
            }
            case kCCBPropTypeFloat: 
            {
                float f = this->parsePropTypeFloat(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloat(pNode, pParent, propertyName.c_str(), f, pCCBReader);
                }
                break;
            }
	    case kCCBPropTypeFloatXY:
	      {
                float * xy =  this->parsePropTypeFloatXY(pNode, pParent, pCCBReader);
                if(setProp)
                {
                    this->onHandlePropTypeFloatXY(pNode, pParent, propertyName.c_str(), xy, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(xy);
                break;
	      }

            case kCCBPropTypeDegrees: 
            {
                float degrees = this->parsePropTypeDegrees(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeDegrees(pNode, pParent, propertyName.c_str(), degrees, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatScale: 
            {
                float floatScale = this->parsePropTypeFloatScale(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatScale(pNode, pParent, propertyName.c_str(), floatScale, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeInteger: 
            {
                int integer = this->parsePropTypeInteger(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeInteger(pNode, pParent, propertyName.c_str(), integer, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeIntegerLabeled: 
            {
                int integerLabeled = this->parsePropTypeIntegerLabeled(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeIntegerLabeled(pNode, pParent, propertyName.c_str(), integerLabeled, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatVar: 
            {
                float * floatVar = this->parsePropTypeFloatVar(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatVar(pNode, pParent, propertyName.c_str(), floatVar, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(floatVar);
                break;
            }
            case kCCBPropTypeCheck: 
            {
                bool check = this->parsePropTypeCheck(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeCheck(pNode, pParent, propertyName.c_str(), check, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSpriteFrame: {
                CCSpriteFrame * ccSpriteFrame = this->parsePropTypeSpriteFrame(pNode, pParent, pCCBReader, propertyName.c_str()); //jambam 원본
                
                
                if(setProp) 
                {
                    this->onHandlePropTypeSpriteFrame(pNode, pParent, propertyName.c_str(), ccSpriteFrame, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeAnimation: 
            {
                CCAnimation * ccAnimation = this->parsePropTypeAnimation(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeAnimation(pNode, pParent, propertyName.c_str(), ccAnimation, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeTexture: 
            {
                CCTexture2D * ccTexture2D = this->parsePropTypeTexture(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeTexture(pNode, pParent, propertyName.c_str(), ccTexture2D, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeByte: 
            {
                unsigned char byte = this->parsePropTypeByte(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeByte(pNode, pParent, propertyName.c_str(), byte, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor3: 
            {
                ccColor3B color3B = this->parsePropTypeColor3(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeColor3(pNode, pParent, propertyName.c_str(), color3B, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor4FVar: 
            {
                ccColor4F * color4FVar = this->parsePropTypeColor4FVar(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeColor4FVar(pNode, pParent, propertyName.c_str(), color4FVar, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(color4FVar);
                break;
            }
            case kCCBPropTypeFlip: {
                bool * flip = this->parsePropTypeFlip(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFlip(pNode, pParent, propertyName.c_str(), flip, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(flip);
                break;
            }
            case kCCBPropTypeBlendmode: 
            {
                ccBlendFunc blendFunc = this->parsePropTypeBlendFunc(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeBlendFunc(pNode, pParent, propertyName.c_str(), blendFunc, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFntFile: 
            {
                std::string fntFile = pCCBReader->getCCBRootPath() + this->parsePropTypeFntFile(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFntFile(pNode, pParent, propertyName.c_str(), fntFile.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFontTTF: {
                std::string fontTTF = this->parsePropTypeFontTTF(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFontTTF(pNode, pParent, propertyName.c_str(), fontTTF.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeString: {
                std::string string = this->parsePropTypeString(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeString(pNode, pParent, propertyName.c_str(), string.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeText: {
                std::string text = this->parsePropTypeText(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeText(pNode, pParent, propertyName.c_str(), text.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeBlock: {
                BlockData * blockData = this->parsePropTypeBlock(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeBlock(pNode, pParent, propertyName.c_str(), blockData, pCCBReader);
                }
                CC_SAFE_DELETE(blockData);
                break;
            }
            case kCCBPropTypeBlockCCControl: {
                BlockCCControlData * blockCCControlData = this->parsePropTypeBlockCCControl(pNode, pParent, pCCBReader);
                if(setProp && blockCCControlData != NULL) {
                    this->onHandlePropTypeBlockCCControl(pNode, pParent, propertyName.c_str(), blockCCControlData, pCCBReader);
                }
                CC_SAFE_DELETE(blockCCControlData);
                break;
            }
            case kCCBPropTypeCCBFile: {
                CCNode * ccbFileNode = this->parsePropTypeCCBFile(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeCCBFile(pNode, pParent, propertyName.c_str(), ccbFileNode, pCCBReader);
                }
                break;
            }
            default:
                ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(type);
                break;
        }
    }
}

CCPoint CCNodeLoader::parsePropTypePosition(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    CCSize containerSize = pCCBReader->getAnimationManager()->getContainerSize(pParent);
    
    CCPoint pt = getAbsolutePosition(ccp(x,y), type, containerSize, pPropertyName);
    pNode->setPosition(pt);
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCArray *baseValue = CCArray::create(CCBValue::create(x),
                                             CCBValue::create(y),
                                             CCBValue::create(type),
                                             NULL);
        pCCBReader->getAnimationManager()->setBaseValue(baseValue, pNode, pPropertyName);
    }

    return pt;
}

CCPoint CCNodeLoader::parsePropTypePoint(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    return CCPoint(x, y);
}

CCPoint CCNodeLoader::parsePropTypePointLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    return CCPoint(x, y);
}

CCSize CCNodeLoader::parsePropTypeSize(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float width = pCCBReader->readFloat();
    float height = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);

    CCSize containerSize = pCCBReader->getAnimationManager()->getContainerSize(pParent);

    switch (type) 
    {
        case kCCBSizeTypeAbsolute: 
        {
            /* Nothing. */
            break;
        }
        case kCCBSizeTypeRelativeContainer: 
        {
            width = containerSize.width - width;
            height = containerSize.height - height;
            break;
        }
        case kCCBSizeTypePercent: 
        {
            width = (int)(containerSize.width * width / 100.0f);
            height = (int)(containerSize.height * height / 100.0f);
            break;
        }
        case kCCBSizeTypeHorizontalPercent: 
        {
            width = (int)(containerSize.width * width / 100.0f);
            break;
        }
        case kCCBSizeTypeVerticalPercent: 
        {
            height = (int)(containerSize.height * height / 100.0f);
            break;
        }
        case kCCBSizeTypeMultiplyResolution:
        {
            float resolutionScale = CCBReader::getResolutionScale();
            
            width *= resolutionScale;
            height *= resolutionScale;
            break;
        }
        default:
        {
            CCLog("Unknown CCB type.");
        }
            break;
    }
    
    return CCSize(width, height);
}



float * CCNodeLoader::parsePropTypeFloatXY(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    float * floatXY = new float[2];
    floatXY[0] = x;
    floatXY[1] = y;

    return floatXY;
}

float * CCNodeLoader::parsePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    //---test
    if(type == kCCBScaleTypePercent)
    {
        int aaa;
        aaa = 0;
    }
    //---
    
    //setRelativeScale(pNode, x, y, type, pPropertyName); //jambam 원본
    setRelativeScale(pNode, x, y, type, pPropertyName, pParent); //jambam 추가
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCArray *baseValue = CCArray::create(CCBValue::create(x),
                                             CCBValue::create(y),
                                             CCBValue::create(type),
                                             NULL);
        pCCBReader->getAnimationManager()->setBaseValue(baseValue, pNode, pPropertyName);
    }
    
    if (type == kCCBScaleTypeMultiplyResolution) 
    {
        x *= pCCBReader->getResolutionScale();
        y *= pCCBReader->getResolutionScale();
    }
    //---jambam 추가
    else if(type == kCCBScaleTypePercent)
    {
        CCSize parentSize = pParent->getContentSize();
        CCSize pNodeSize = pNode->getContentSize();
        
        x = ((parentSize.width * x) / 100) / pNodeSize.width;
        y = ((parentSize.height * y) / 100) / pNodeSize.height;
        
//        CCLog("fScaleX = %f", y);
//        CCLog("fScaleY = %f", y);
    }
    //---
    
    float * scaleLock = new float[2];
    scaleLock[0] = x;
    scaleLock[1] = y;

    return scaleLock;
}

float CCNodeLoader::parsePropTypeFloat(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readFloat();
}

float CCNodeLoader::parsePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float ret = pCCBReader->readFloat();
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCBValue *value = CCBValue::create(ret);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    
    return ret;
}

float CCNodeLoader::parsePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    float f = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);
    
    if(type == kCCBScaleTypeMultiplyResolution) 
    {
        f *= pCCBReader->getResolutionScale();
    }

    return f;
}

int CCNodeLoader::parsePropTypeInteger(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readInt(true);
}

int CCNodeLoader::parsePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readInt(true);
}

float * CCNodeLoader::parsePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    float f = pCCBReader->readFloat();
    float fVar = pCCBReader->readFloat();
    
    float * arr = new float[2];
    arr[0] = f;
    arr[1] = fVar;
    
    return arr;
}

bool CCNodeLoader::parsePropTypeCheck(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    bool ret = pCCBReader->readBool();
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCBValue *value = CCBValue::create(ret);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    
    return ret;
}

//haru - 임시로 replace함수 구현.
void CCNodeLoader::ReplaceString( std::string & strSrc, const char * pszBefore, const char * pszAfter )
{
    size_t iPos = strSrc.find( pszBefore );
    size_t iBeforeLen = strlen( pszBefore );
    while( iPos < std::string::npos )
    {
        strSrc.replace( iPos, iBeforeLen, pszAfter );
        iPos = strSrc.find( pszBefore, iPos );
    }
}

CCSpriteFrame * CCNodeLoader::parsePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName)   //jambam 원본
{
    std::string spriteSheet = pCCBReader->readCachedString();
    std::string spriteFile = pCCBReader->readCachedString();

    //haru - 언어설정에 따라서, spriteSheetFile과 spriteFile 경로를 바꿔주자.
    CCSprite *sprite = (CCSprite*)pNode;
    switch (sprite->getLanguage())
    {
        case LANGUAGE_KOREAN:
            ReplaceString(spriteSheet, "/local_en/", "/local_ko/");
            ReplaceString(spriteSheet, "/local_jp/", "/local_ko/");
            ReplaceString(spriteSheet, "/local_ch/", "/local_ko/");
            ReplaceString(spriteFile, "/local_en/", "/local_ko/");
            ReplaceString(spriteFile, "/local_jp/", "/local_ko/");
            ReplaceString(spriteFile, "/local_ch/", "/local_ko/");
            break;
            
        case LANGUAGE_JAPANESE:
            ReplaceString(spriteSheet, "/local_en/", "/local_jp/");
            ReplaceString(spriteSheet, "/local_ko/", "/local_jp/");
            ReplaceString(spriteSheet, "/local_ch/", "/local_jp/");
            ReplaceString(spriteFile, "/local_en/", "/local_jp/");
            ReplaceString(spriteFile, "/local_ko/", "/local_jp/");
            ReplaceString(spriteFile, "/local_ch/", "/local_jp/");
            break;
            
        case LANGUAGE_CHINESE:
            ReplaceString(spriteSheet, "/local_en/", "/local_ch/");
            ReplaceString(spriteSheet, "/local_ko/", "/local_ch/");
            ReplaceString(spriteSheet, "/local_jp/", "/local_ch/");
            ReplaceString(spriteFile, "/local_en/", "/local_ch/");
            ReplaceString(spriteFile, "/local_ko/", "/local_ch/");
            ReplaceString(spriteFile, "/local_jp/", "/local_ch/");
            break;
            
        default:
            ReplaceString(spriteSheet, "/local_ko/", "/local_en/");
            ReplaceString(spriteSheet, "/local_jp/", "/local_en/");
            ReplaceString(spriteSheet, "/local_ch/", "/local_en/");
            ReplaceString(spriteFile, "/local_ko/", "/local_en/");
            ReplaceString(spriteFile, "/local_jp/", "/local_en/");
            ReplaceString(spriteFile, "/local_ch/", "/local_en/");
            break;
    }
        
    //jambam 추가
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    std::string newPath;
    
    //---test
//    CCLog(" ");
//    CCLog(" ");
//    CCLog(" ");
//    if(strcmp(spriteFile.c_str(), "server/test/ksg/images/comp/comp_clan_maching_start_01/maching_ground_eff_01.png") == 0)
//    {
//        
//        CCLog("~~~~~~~~~~~이건 뭐지?");
//    }
//        
    //---
    
    CCSpriteFrame *spriteFrame = NULL;
    if (spriteFile.length() != 0)
    {
        CCLog("<<---spriteFile = %s", spriteFile.c_str());
        
        if (spriteSheet.length() == 0)
        {
            spriteFile = pCCBReader->getCCBRootPath() + spriteFile; //jambam 원본
            
            
            //jambam 추가 : 다운로드 받은 파일을 체크해보고 없으면 패키징된 파일을 불러온다.
#ifndef USE_LOCAL_RESOURCE
            newPath = writablePath + spriteFile;
//            CCLog("newPath = %s", newPath.c_str());
            if(CCFileUtils::sharedFileUtils()->isFileExist(newPath))
            {
                spriteFile = newPath;
//                CCLog("CCNodeLoader.parsePropTypeSpriteFrame.다운로드 받은 파일 로딩 : %s", spriteFile.c_str());

            }
            else
            {
//                CCLog("CCNodeLoader.parsePropTypeSpriteFrame.패키징된 받은 파일 로딩 : %s", spriteFile.c_str());
            }
#endif
            
            CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(spriteFile.c_str());
            if(texture != NULL) {
                CCRect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                spriteFrame = CCSpriteFrame::createWithTexture(texture, bounds);
            }
        }
        else 
        {
            CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            spriteSheet = pCCBReader->getCCBRootPath() + spriteSheet;     //jambam 원본
            
#ifndef USE_LOCAL_RESOURCE
            //jambam 추가 : 다운로드 받은 파일을 체크해보고 없으면 패키징된 파일을 불러온다.
            newPath = writablePath + spriteSheet;
//            CCLog("newPath = %s", newPath.c_str());
            if(CCFileUtils::sharedFileUtils()->isFileExist(newPath))
            {
                spriteSheet = newPath;
//                CCLog("CCNodeLoader.parsePropTypeSpriteFrame.다운로드 받은 파일 로딩 : %s", spriteSheet.c_str());
            }
            else
            {
//                CCLog("CCNodeLoader.parsePropTypeSpriteFrame.패키징된 받은 파일 로딩 : %s", spriteSheet.c_str());
            }
#endif
            // Load the sprite sheet only if it is not loaded
            if (pCCBReader->getLoadedSpriteSheet().find(spriteSheet) == pCCBReader->getLoadedSpriteSheet().end())
            {
                frameCache->addSpriteFramesWithFile(spriteSheet.c_str());
                pCCBReader->getLoadedSpriteSheet().insert(spriteSheet);
            }
            
            spriteFrame = frameCache->spriteFrameByName(spriteFile.c_str());
        }
        
        if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
        {
            pCCBReader->getAnimationManager()->setBaseValue(spriteFrame, pNode, pPropertyName);
        }
    }
    
    return spriteFrame;
}

CCAnimation * CCNodeLoader::parsePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    std::string animationFile = pCCBReader->getCCBRootPath() + pCCBReader->readCachedString();
    std::string animation = pCCBReader->readCachedString();

    CCAnimation * ccAnimation = NULL;
    
    // Support for stripping relative file paths, since ios doesn't currently
    // know what to do with them, since its pulling from bundle.
    // Eventually this should be handled by a client side asset manager
    // interface which figured out what resources to load.
    // TODO Does this problem exist in C++?
    animation = CCBReader::lastPathComponent(animation.c_str());
    animationFile = CCBReader::lastPathComponent(animationFile.c_str());
    
    if (animation.length() > 0) 
    {
        CCAnimationCache * animationCache = CCAnimationCache::sharedAnimationCache();
        animationCache->addAnimationsWithFile(animationFile.c_str());
        
        ccAnimation = animationCache->animationByName(animation.c_str());
    }
    return ccAnimation;
}

CCTexture2D * CCNodeLoader::parsePropTypeTexture(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader)
{
    std::string spriteFile = pCCBReader->getCCBRootPath() + pCCBReader->readCachedString();

    // [sj] 다운받은 이미지 경로 확인
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    std::string newPath;
    
    newPath = writablePath + spriteFile;

    if(CCFileUtils::sharedFileUtils()->isFileExist(newPath)) spriteFile = newPath;
    //
    
    if (spriteFile.length() > 0)
    {
        return CCTextureCache::sharedTextureCache()->addImage(spriteFile.c_str());
    }
    else 
    {
        return NULL;
    }
}

unsigned char CCNodeLoader::parsePropTypeByte(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    unsigned char ret = pCCBReader->readByte();
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        pCCBReader->getAnimationManager()->setBaseValue(CCBValue::create(ret), pNode, pPropertyName);
    }
    
    return ret;
}

ccColor3B CCNodeLoader::parsePropTypeColor3(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    unsigned char red = pCCBReader->readByte();
    unsigned char green = pCCBReader->readByte();
    unsigned char blue = pCCBReader->readByte();
    
    ccColor3B color = { red, green, blue };
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        ccColor3BWapper *value = ccColor3BWapper::create(color);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    return color;
}

ccColor4F * CCNodeLoader::parsePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float red = pCCBReader->readFloat();
    float green = pCCBReader->readFloat();
    float blue = pCCBReader->readFloat();
    float alpha = pCCBReader->readFloat();
    float redVar = pCCBReader->readFloat();
    float greenVar = pCCBReader->readFloat();
    float blueVar = pCCBReader->readFloat();
    float alphaVar = pCCBReader->readFloat();
    
    ccColor4F * colors = new ccColor4F[2];
    colors[0].r = red;
    colors[0].g = green;
    colors[0].b = blue;
    colors[0].a = alpha;
    
    colors[1].r = redVar;
    colors[1].g = greenVar;
    colors[1].b = blueVar;
    colors[1].a = alphaVar;
    
    return colors;
}

bool * CCNodeLoader::parsePropTypeFlip(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    bool flipX = pCCBReader->readBool();
    bool flipY = pCCBReader->readBool();

    bool * arr = new bool[2];
    arr[0] = flipX;
    arr[1] = flipY;

    return arr;
}

ccBlendFunc CCNodeLoader::parsePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    int source = pCCBReader->readInt(false);
    int destination = pCCBReader->readInt(false);
    
    ccBlendFunc blendFunc;
    blendFunc.src = source;
    blendFunc.dst = destination;
    
    return blendFunc;
}

std::string CCNodeLoader::parsePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readCachedString();
}

std::string CCNodeLoader::parsePropTypeString(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

std::string CCNodeLoader::parsePropTypeText(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

std::string CCNodeLoader::parsePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    std::string fontTTF = pCCBReader->readCachedString();

    // CCString * ttfEnding = CCString::create(".ttf");

    // TODO Fix me if it is wrong
    /* If the fontTTF comes with the ".ttf" extension, prepend the absolute path. 
     * System fonts come without the ".ttf" extension and do not need the path prepended. */
    /*
    if(CCBReader::endsWith(CCBReader::toLowerCase(fontTTF), ttfEnding)){
        fontTTF = CCBReader::concat(pCCBReader->getCCBRootPath(), fontTTF);
    }
     */

    return fontTTF;
}

BlockData * CCNodeLoader::parsePropTypeBlock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    std::string selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(!pCCBReader->isJSControlled()) {
            
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                target = pCCBReader->getAnimationManager()->getRootNode();
            } else if(selectorTarget == kCCBTargetTypeOwner) {
                target = pCCBReader->getOwner();
            }
            
            if(target != NULL) {
                if(selectorName.length() > 0) {
                    SEL_MenuHandler selMenuHandler = 0;
                    
                    CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);
                    
                    if(targetAsCCBSelectorResolver != NULL) {
                        selMenuHandler = targetAsCCBSelectorResolver->onResolveCCBCCMenuItemSelector(target, selectorName.c_str());
                    }
                    if(selMenuHandler == 0) {
                        CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                        if(ccbSelectorResolver != NULL) {
                            selMenuHandler = ccbSelectorResolver->onResolveCCBCCMenuItemSelector(target, selectorName.c_str());
                        }
                    }
                    
                    if(selMenuHandler == 0) {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    } else {
                        BlockData * blockData = new BlockData();
                        blockData->mSELMenuHandler = selMenuHandler;
                        
                        blockData->mTarget = target;
                        
                        return blockData;
                    }
                } else {
                    CCLOG("Unexpected empty selector.");
                }
            } else {
                CCLOG("Unexpected NULL target for selector.");
            }
        } else {
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                pCCBReader->addDocumentCallbackNode(pNode);
                pCCBReader->addDocumentCallbackName(selectorName);
                
            } else {
                pCCBReader->addOwnerCallbackNode(pNode);
                pCCBReader->addOwnerCallbackName(selectorName);
            }
        }
    }

    return NULL;
}

BlockCCControlData * CCNodeLoader::parsePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    std::string selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);
    int controlEvents = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        
        if(!pCCBReader->isJSControlled()) {
            CCObject * target = NULL;
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                target = pCCBReader->getAnimationManager()->getRootNode();
            } else if(selectorTarget == kCCBTargetTypeOwner) {
                target = pCCBReader->getOwner();
            }
            
            if(target != NULL) {
                if(selectorName.length() > 0) {
                    SEL_CCControlHandler selCCControlHandler = 0;
                    
                    CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);
                    
                    if(targetAsCCBSelectorResolver != NULL) {
                        selCCControlHandler = targetAsCCBSelectorResolver->onResolveCCBCCControlSelector(target, selectorName.c_str());
                    }
                    if(selCCControlHandler == 0) {
                        CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                        if(ccbSelectorResolver != NULL) {
                            selCCControlHandler = ccbSelectorResolver->onResolveCCBCCControlSelector(target, selectorName.c_str());
                        }
                    }
                    
                    if(selCCControlHandler == 0) {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    } else {
                        BlockCCControlData * blockCCControlData = new BlockCCControlData();
                        blockCCControlData->mSELCCControlHandler = selCCControlHandler;
                        
                        blockCCControlData->mTarget =  target;
                        blockCCControlData->mControlEvents = controlEvents;
                        
                        return blockCCControlData;
                    }
                } else {
                    CCLOG("Unexpected empty selector.");
                }
            } else {
                CCLOG("Unexpected NULL target for selector.");
            }
        } else {
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                pCCBReader->addDocumentCallbackNode(pNode);
                pCCBReader->addDocumentCallbackName(selectorName);
                
            } else {
                pCCBReader->addOwnerCallbackNode(pNode);
                pCCBReader->addOwnerCallbackName(selectorName);
            }
        }
    }

    return NULL;
}

CCNode * CCNodeLoader::parsePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    std::string ccbFileName = pCCBReader->getCCBRootPath() + pCCBReader->readCachedString();
    
    //CCLog("<---rootPath = %s", pCCBReader->getCCBRootPath().c_str());
    //CCLog("<---readCachedString = %s", pCCBReader->readCachedString().c_str());

    /* Change path extension to .ccbi. */
    std::string ccbFileWithoutPathExtension = CCBReader::deletePathExtension(ccbFileName.c_str());
    ccbFileName = ccbFileWithoutPathExtension + ".ccbi";
    
    //---jambam 추가
    //ccbFileName = "ccbi/" + ccbFileName;
    //---
    
    
    
    
//    CCLog("<-ccbFileName = %s", ccbFileName.c_str());
    
    // Load sub file
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(ccbFileName.c_str());
    
    
    //잉...
    //jambam 추가 : 다운로드 받은 파일을 체크해보고 없으면 패키징된 파일을 불러온다.
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    std::string newPath;
    //newPath = writablePath + path;
#ifndef USE_LOCAL_RESOURCE
    newPath = writablePath + ccbFileName;
    //CCLog("newPath = %s", newPath.c_str());
    if(CCFileUtils::sharedFileUtils()->isFileExist(newPath))
    {
        path = newPath;
        //CCLog("CCNodeLoader.parsePropTypeCCBFile.다운로드 받은 파일 로딩 : %s", path.c_str());
    }
    else
    {
        //CCLog("CCNodeLoader.parsePropTypeCCBFile.패키징된 받은 파일 로딩 : %s", path.c_str());
    }
#endif
    
    //CCLog("<---path = %s", path.c_str());
    
    unsigned long size = 0;
    unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);

    CCBReader * ccbReader = new CCBReader(pCCBReader);
    ccbReader->autorelease();
    ccbReader->getAnimationManager()->setRootContainerSize(pParent->getContentSize());
    
    CCData *data = new CCData(pBytes, size);
    CC_SAFE_DELETE_ARRAY(pBytes);

    data->retain();
    ccbReader->mData = data;
    ccbReader->mBytes = data->getBytes();
    ccbReader->mCurrentByte = 0;
    ccbReader->mCurrentBit = 0;
    CC_SAFE_RETAIN(pCCBReader->mOwner);
    ccbReader->mOwner = pCCBReader->mOwner;
    
    if (NULL != ccbReader->mOwner) {
        CCLOG("DDD");
    }
    
    ccbReader->getAnimationManager()->mOwner = ccbReader->mOwner;

    // The assignments below are done in the CCBReader constructor.
//     ccbReader->mOwnerOutletNames = pCCBReader->mOwnerOutletNames;
//     ccbReader->mOwnerOutletNodes = pCCBReader->mOwnerOutletNodes;
//     ccbReader->mOwnerOutletNodes->retain();
//     ccbReader->mOwnerCallbackNames = pCCBReader->mOwnerCallbackNames;
//     ccbReader->mOwnerCallbackNodes = pCCBReader->mOwnerCallbackNodes;
//     ccbReader->mOwnerCallbackNodes->retain();

    data->release();
    
    CCNode * ccbFileNode = ccbReader->readFileWithCleanUp(false, pCCBReader->getAnimationManagers());
    
    //---jambam
    //ccbFileNode->mAnimationManager = ccbReader->getAnimationManager();
    //g_Grobal* g = g_Grobal::sharedGrobal();
    //g->AnimationManagerRegister(ccbFileNode, ccbReader->getAnimationManager());
    //---
    
    if (ccbFileNode && ccbReader->getAnimationManager()->getAutoPlaySequenceId() != -1)
    {
        // Auto play animations
        ccbReader->getAnimationManager()->runAnimationsForSequenceIdTweenDuration(ccbReader->getAnimationManager()->getAutoPlaySequenceId(), 0);
    }
    
    if (ccbReader->isJSControlled() && pCCBReader->isJSControlled() && NULL != ccbReader->mOwner)
    {
        //set variables and callback to owner
        //set callback
        CCArray *ownerCallbackNames = ccbReader->getOwnerCallbackNames();
        CCArray *ownerCallbackNodes = ccbReader->getOwnerCallbackNodes();
        if (NULL != ownerCallbackNames && ownerCallbackNames->count() > 0 &&
            NULL != ownerCallbackNodes && ownerCallbackNodes->count() > 0)
        {
            assert(ownerCallbackNames->count() == ownerCallbackNodes->count());
            int nCount = ownerCallbackNames->count();
            for (int i = 0 ; i < nCount; i++) {
                pCCBReader->addOwnerCallbackName((dynamic_cast<CCString*>(ownerCallbackNames->objectAtIndex(i)))->getCString());
                pCCBReader->addOwnerCallbackNode(dynamic_cast<CCNode*>(ownerCallbackNames->objectAtIndex(i)) );
            }
        }
        //set variables
        CCArray *ownerOutletNames = ccbReader->getOwnerOutletNames();
        CCArray *ownerOutletNodes = ccbReader->getOwnerOutletNodes();
        if (NULL != ownerOutletNames && ownerOutletNames->count() > 0 &&
            NULL != ownerOutletNodes && ownerOutletNodes->count() > 0)
        {
            assert(ownerOutletNames->count() == ownerOutletNodes->count());
            int nCount = ownerOutletNames->count();
            for (int i = 0 ; i < nCount; i++) {
                pCCBReader->addOwnerOutletName((dynamic_cast<CCString*>(ownerOutletNames->objectAtIndex(i)))->getCString());
                pCCBReader->addOwnerOutletNode(dynamic_cast<CCNode*>(ownerOutletNodes->objectAtIndex(i)) );
            }
        }
    }
    return ccbFileNode;
}



void CCNodeLoader::onHandlePropTypePosition(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPosition, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_POSITION) == 0) {
        pNode->setPosition(pPosition);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPoint, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ANCHORPOINT) == 0) {
        pNode->setAnchorPoint(pPoint);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypePointLock(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPointLock, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        pNode->setContentSize(pSize);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloatXY(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pFloat, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SKEW) == 0) {
        pNode->setSkewX(pFloat[0]);
        pNode->setSkewY(pFloat[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}


void CCNodeLoader::onHandlePropTypeScaleLock(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        pNode->setScaleX(pScaleLock[0]);
        pNode->setScaleY(pScaleLock[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
//    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    // It may be a custom property, add it to custom property dictionary.
    m_pCustomProperties->setObject(CCBValue::create(pFloat), pPropertyName);
}


void CCNodeLoader::onHandlePropTypeDegrees(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pDegrees, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ROTATION) == 0) {
        pNode->setRotation(pDegrees);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATIONX) == 0) {
        pNode->setRotationX(pDegrees);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATIONY) == 0) {
        pNode->setRotationY(pDegrees);
    }
    else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pInteger, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TAG) == 0)
    {
        pNode->setTag(pInteger);
    }
    else if ( strcmp(pPropertyName, PROPERTY_DEPTH ) == 0 )
    {
        pNode->m_iDepth = pInteger;
    }
    else {
 //       ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
        // It may be a custom property, add it to custom property dictionary.
        m_pCustomProperties->setObject(CCBValue::create(pInteger), pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    
    if( strcmp(pPropertyName, PROPERTY_DEPTH ) == 0 )
    {
        pNode->m_iDepth = pIntegerLabeled;
    }
    else
    {
        ASSERT_FAIL_UNEXPECTED_PROPERTY( pPropertyName );
    }
}

void CCNodeLoader::onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pFloatVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_VISIBLE) == 0) {
        pNode->setVisible(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_IGNOREANCHORPOINTFORPOSITION) == 0) {
        pNode->ignoreAnchorPointForPosition(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_ENABLECHILDRENOPACITY) == 0) {
        //haru - enableChildrenOpacity 속성추가
        pNode->enableChildrenOpacity(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_IGNOREPARENTSOPACITY) == 0) {
        //haru - ignoreParentsOpacity 속성추가
        pNode->ignoreParentsOpacity(pCheck);
    } else {
        //ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
        // It may be a custom property, add it to custom property dictionary.
        m_pCustomProperties->setObject(CCBValue::create(pCheck), pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeAnimation(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCAnimation * pCCAnimation, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    //haru - childrenOpacity 속성추가
    if(strcmp(pPropertyName, PROPERTY_CHILDRENOPACITY) == 0) {
        pNode->setChildrenOpacity(pByte);
    } else {
         ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool * pFlip, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char* pFntFile, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pString, CCBReader * pCCBReader) {
//    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    // It may be a custom property, add it to custom property dictionary.
    m_pCustomProperties->setObject(CCBValue::create(pString), pPropertyName);
}

void CCNodeLoader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pText, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, const char* pPropertyName, BlockCCControlData * pBlockCCControlData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

NS_CC_EXT_END
