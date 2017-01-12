#ifndef _CCB_CCNODELOADERLIBRARY_H_
#define _CCB_CCNODELOADERLIBRARY_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

class CCNodeLoader;

typedef std::map<std::string, CCNodeLoader *> CCNodeLoaderMap;
typedef std::pair<std::string, CCNodeLoader *> CCNodeLoaderMapEntry;

class CCNodeLoaderLibrary : public CCObject {
    private:
        CCNodeLoaderMap mCCNodeLoaders;

    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCNodeLoaderLibrary, library);

        CCNodeLoaderLibrary();
        virtual ~CCNodeLoaderLibrary();

        void registerDefaultCCNodeLoaders();
        void registerCCNodeLoader(const char * pClassName, CCNodeLoader * pCCNodeLoader);
        //void registerCCNodeLoader(CCString * pClassName, CCNodeLoader * pCCNodeLoader);
        void unregisterCCNodeLoader(const char * pClassName);
        //void unregisterCCNodeLoader(CCString * pClassName);
        CCNodeLoader * getCCNodeLoader(const char * pClassName);
        //CCNodeLoader * getCCNodeLoader(CCString * pClassName);
        void purge(bool pDelete);

    public:
        static CCNodeLoaderLibrary * sharedCCNodeLoaderLibrary();
        static void purgeSharedCCNodeLoaderLibrary();

        static CCNodeLoaderLibrary * newDefaultCCNodeLoaderLibrary();
    
        //haru - 하나의 ccb를 로딩할때 노드를 몇개나 생성하는지 체크하기 위함.    
        int nodeCount;
};

NS_CC_EXT_END

#endif
