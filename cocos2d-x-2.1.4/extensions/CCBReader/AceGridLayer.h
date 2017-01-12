//
//  AceGridLayer.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#ifndef ScrollViewTest_AceGridLayer_h
#define ScrollViewTest_AceGridLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "CCBFileController.h"
#include "AceClippingScrollNode.h"


using namespace std;

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class AceGridLayer
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    //virtual void draw();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceGridLayer, create);
    
private:
    //NODE_FACTORY_DEC(GridLayer);
    //CHILDREN_HANDLER_DEC(GridLayer);
    
public:
    CC_SYNTHESIZE(int, m_row, Row);
    CC_SYNTHESIZE(int, m_col, Col);
    CC_SYNTHESIZE(CCSize, m_itemSize, ItemSize);
    CC_SYNTHESIZE(CCPoint, m_padding, Padding);
    CC_SYNTHESIZE(CCSize, m_gap, Gap);
    
    CC_SYNTHESIZE(bool, m_isAutoResize, IsAutoResize);
public:
    AceGridLayer();
    ~AceGridLayer();
    
    
    bool init();
    bool init(int row, int col, CCSize itemSize, CCPoint padding, CCSize gap);
    static AceGridLayer* layer(int row, int col, CCSize itemSize, CCPoint padding, CCSize gap);
    
    void addNodes(CCArray *pArray, bool bSort = false);
    
    CCSize calculateSize();
    void refresh();
    
    bool bMaxContentSizeW;
    float maxContentSizeW;
    bool bMaxContentSizeH;
    float maxContentSizeH;
    
    /*
        가로 방향으로 child 추가 가능하게 변수 추가
        2014.09.17 sj 추가
    */
    bool bAddWidth;
    
    
    bool bReverseRefresh;
    
public:
    bool m_bRefresh;
    AceClippingScrollNode* m_pClippingScrollNode;
    vector<ItemResource> m_lstData;
    vector<CCNode *> m_lstNode;
    void *m_pScene;
    void (*m_funUpdate)(void *thiz, CCNode* pNode, void* ptr, const int index);
    void AddCellNode(AceClippingScrollNode* pScrollNode, CCNode* (*funLoadAndAddCCBFile)(void *thiz, AceGridLayer* pGridLayer));
    
    CCRect m_rectClipping;
    int m_iCellCnt;
    float m_fScrollDelta;
    
    virtual void update(float delta);
    void Refresh();
    
    float m_fOldX;
    float m_fOldY;
};

NS_CC_EXT_END

#endif
