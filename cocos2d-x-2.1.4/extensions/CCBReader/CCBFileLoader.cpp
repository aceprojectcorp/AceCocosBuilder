#include "CCBFileLoader.h"



NS_CC_EXT_BEGIN

#define PROPERTY_CCBFILE "ccbFile"
#define PROPERTY_OPACITY "mm_opacity"

void CCBFileLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CCBFILE) == 0) {
        ((CCBFile*)pNode)->setCCBFileNode(pCCBFileNode);
    } else {
        CCNodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}

void CCBFileLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    CCBFile* tmpNode = (CCBFile*)pNode;
    
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        tmpNode->mm_opacity = pByte;
    }
}

NS_CC_EXT_END
