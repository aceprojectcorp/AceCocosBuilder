//
//  AceGridLayer.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#include "AceGridLayer.h"


USING_NS_CC_EXT;

AceGridLayer::AceGridLayer()
:   m_row(0),
    m_col(0),
    m_itemSize(CCSizeZero),
    m_padding(CCPointZero),
    m_gap(CCSizeZero),
    m_isAutoResize(false),
    bMaxContentSizeW(false),
    maxContentSizeW(0),
    bMaxContentSizeH(false),
    maxContentSizeH(0),
    bAddWidth(false),
    bReverseRefresh(false)
{
    m_fScrollDelta = 0.0f;
}
AceGridLayer::~AceGridLayer()
{
}

void AceGridLayer::onEnter()
{
    CCNode::onEnter();
    
    if(this->bMaxContentSizeW)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.width > maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
            
            this->setContentSize(mySize);
        }
    }
    
    if(this->bMaxContentSizeH)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.height > maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
            
            this->setContentSize(mySize);
        }
    }
    
    refresh();
    
    //this->schedule(schedule_selector(AceGridLayer::update));
    //this->unschedule(schedule_selector(AceGridLayer::update));
    /*
    //---test
    //--------------------------------------------
    CCArray* dataList;
    dataList = CCArray::create();
    dataList->retain();
    
    for(int i=0; i<m_nRow; i++)
    {
        for(int j=0; j<m_nCol; j++)
        {
            CCNodeLoaderLibrary* nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
            cocos2d::extension::CCBReader* reader = new cocos2d::extension::CCBReader(nodeLoaderLibrary);
            CCNode* node = reader->readNodeGraphFromFile(m_cellNodeName->getCString());
            reader->release();
            
            dataList->addObject(node);
        }
    }
    
    addNodes(dataList);
    //--------------------------------------------
    //---
     */
}

/*
NODE_FACTORY_DEF(GridLayer, gridLayer)
{
    float uiScale = AppContext::sharedContext()->getUIScale();
    
    int row = NodeFactoryUtils::getInt(xmlNode, "row", 0, pContext);
    int col = NodeFactoryUtils::getInt(xmlNode, "col", 0, pContext);
    
    float itemWidth = NodeFactoryUtils::getFloat(xmlNode, "itemWidth", 0, pContext) * uiScale;
    float itemHeight = NodeFactoryUtils::getFloat(xmlNode, "itemHeight", 0, pContext) * uiScale;
    
    float paddingLeft = NodeFactoryUtils::getFloat(xmlNode, "paddingLeft", 0, pContext) * uiScale;
    float paddingTop = NodeFactoryUtils::getFloat(xmlNode, "paddingTop", 0, pContext) * uiScale;
    
    float gapX = NodeFactoryUtils::getFloat(xmlNode, "gapX", 0, pContext) * uiScale;
    float gapY = NodeFactoryUtils::getFloat(xmlNode, "gapY", 0, pContext) * uiScale;
    
    GridLayer *pLayer = GridLayer::layer(row, col, CCSize(itemWidth, itemHeight), CCPoint(paddingLeft, paddingTop), CCSize(gapX, gapY));
    if(!pLayer) return NULL;
    
    bool autoResize = NodeFactoryUtils::getBool(xmlNode, "autoResize", false, pContext);
    pLayer->setIsAutoResize(autoResize);
    
    return pLayer;
}

CHILDREN_HANDLER_DEF(GridLayer, gridLayer)
{
    CCArray *pArray = NodeFactoryUtils::convertVectorToCCArray(children);
    if(!pArray) return;
    
    ((GridLayer*)pParent)->addNodes(pArray);
}
 */

bool AceGridLayer::init()
{
    if(!CCNode::init())
        return false;
    
    m_row = 1;
    m_col = 1;
    m_itemSize = CCSizeMake(1, 1);
    m_padding = CCPointMake(1, 1);
    m_gap = CCSizeMake(1, 1);
    
    m_isAutoResize = false;
    
    m_fOldX = -99999.9f;
    m_fOldY = -99999.9f;
    
    this->scheduleUpdate();
    
    return true;
}

bool AceGridLayer::init(int row, int col, CCSize itemSize, CCPoint padding, CCSize gap)
{
    m_row = row;
    m_col = col;
    m_itemSize = itemSize;
    m_padding = padding;
    m_gap = gap;
    
    m_isAutoResize = false;
    
    return true;
}

AceGridLayer* AceGridLayer::layer(int row, int col, CCSize itemSize, CCPoint padding, CCSize gap)
{
    AceGridLayer *pLayer = new AceGridLayer();
    if(pLayer && pLayer->init(row, col, itemSize, padding, gap)) {
        pLayer->autorelease();
        return pLayer;
    }
    
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void AceGridLayer::addNodes(CCArray *pArray, bool bSort)
{
    if(!pArray) return;
    
    CCObject *pObject;
    
    // 새로운 노드 추가
    CCARRAY_FOREACH(pArray, pObject) {
        CCNode *pNode = static_cast<CCNode*>(pObject);
        if(!pNode) continue;
        
        pNode->setAnchorPoint(ccp(0.5, 0.5));
        addChild(pNode);
    }
    
    if(bSort) sortAllChildren();
    
//    int a = this->getChildrenCount() / getRow();
//    int b = this->getChildrenCount() % getRow();
//    int resultCol = a + (b > 0 ? 1 : 0);
//    this->setCol(resultCol);
    
    refresh();
}

CCSize AceGridLayer::calculateSize()
{
    CCSize size = getContentSize();
    
    int count = this->getChildrenCount();
    
    //노창록
    if ( m_lstData.size() > 0 )
        count = (int)m_lstData.size();
    
    if(m_isAutoResize && m_col && m_row) {
        
        int r = count / m_col;
        if(bAddWidth)
        {
            r = count / m_row;
            if(count % m_row) r++;
            
            size.width = m_padding.x * 2 + m_itemSize.width * r + m_gap.width * (r ? r - 1 : 0);
            size.height = m_padding.y * 2 + m_itemSize.height * m_row + m_gap.height * (m_row ? m_row - 1 : 0);
        }
        else
        {
            if(count % m_col) r++;
            
            size.width = m_padding.x * 2 + m_itemSize.width * m_col + m_gap.width * (m_col ? m_col - 1 : 0);
            size.height = m_padding.y * 2 + m_itemSize.height * r + m_gap.height * (r ? r - 1 : 0);
        }
        
//        size.width = m_padding.x * 2 + m_itemSize.width * m_col + m_gap.width * (m_col ? m_col - 1 : 0);
//        size.height = m_padding.y * 2 + m_itemSize.height * r + m_gap.height * (r ? r - 1 : 0);
    }
    
    return size;
}

//---수정
void AceGridLayer::refresh()
{
    int dataCnt = (int)m_lstData.size();
    
    if(m_isAutoResize) {
        CCSize size = calculateSize();
        
        //CCLog("size.width = %f", size.width);
        //CCLog("size.height = %f", size.height);
        
        setContentSize(size);
    }
    
    /*
    if(bMaxContentSizeW || bMaxContentSizeH)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.width >= maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
            this->setContentSize(mySize);
        }
        if(mySize.height >= maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
            this->setContentSize(mySize);
        }
    }
     */
    
    if(bMaxContentSizeW)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.width >= maxContentSizeW)
        {
            mySize.width = maxContentSizeW;
            this->setContentSize(mySize);
        }
    }
    
    if(bMaxContentSizeH)
    {
        CCSize mySize = this->getContentSize();
        if(mySize.height >= maxContentSizeH)
        {
            mySize.height = maxContentSizeH;
            this->setContentSize(mySize);
        }
    }
    
    int tmpRow = 0;
    int tmpCol = 0;
    CCObject *pObject;
    
    float height = getContentSize().height;
    
    //CCLog("position.x = %f", getPosition().x);
    //CCLog("position.y = %f", getPosition().y);
    
    //CCLog("height = %f", height);
    
    /*
    if(bMaxContentSizeW)
    {
        float totalW;
        float itemW;
        int itemCnt;
        int gapCnt;
        float gapW;
        float tmpW;
        
        CCSize mySize = this->getContentSize();
        
        if(mySize.width >= maxContentSizeW)
        {
            totalW = maxContentSizeW;
        }
        else
        {
            totalW = mySize.width;
        }
        itemCnt = this->m_col;
        
        if(itemCnt > 1)
        {
            gapCnt = itemCnt - 1;
            itemW = this->m_itemSize.width;
            tmpW = totalW - (itemW * this->m_col);
            gapW = tmpW / gapCnt;
            
            int tmpCol = 0;
            int tmpRow = 0;
            for(int i=0; i<(int)getChildren()->count(); i++)
            {
                CCNode* pNode = (CCNode*)getChildren()->objectAtIndex(i);
                if(pNode)
                {
                    CCPoint tmpPos = pNode->getPosition();
                    tmpPos.x = itemW * tmpCol + gapW * tmpCol + (m_itemSize.width * 0.5);
                    tmpPos.y = height - m_padding.y - tmpRow * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                    
                    pNode->setPosition(tmpPos);
                    
                    tmpCol++;
                    if(tmpCol >= this->m_col)
                    {
                        tmpCol = 0;
                        tmpRow++;
                    }
                }
            }
        }
    }
     */
    if(bMaxContentSizeW || bMaxContentSizeH)
    {
        CCARRAY_FOREACH(getChildren(), pObject) {
            CCSize mySize = this->getContentSize();
            float startX = 0;
            float startY = 0;
            float newGapX = 0;
            if(m_col - 1 == 0)
            {
                newGapX = 0;
            }
            else
            {
                float tmpMyWidth = this->getContentSize().width;
                if(tmpMyWidth > maxContentSizeW)
                {
                    tmpMyWidth = maxContentSizeW;
                }
                newGapX = (tmpMyWidth - (m_col*m_itemSize.width)) / (m_col-1);
            }
            
            float newGapY = 0;
            if(m_row - 1 == 0)
            {
                newGapY = 0;
            }
            else
            {
                float tmpMyHeight = this->getContentSize().height;
                if(tmpMyHeight > maxContentSizeH)
                {
                    tmpMyHeight = maxContentSizeH;
                }
                newGapY = (tmpMyHeight - (m_row*m_itemSize.height)) / (m_row-1);
            }
            
            if(bMaxContentSizeW)
            {
                startX = (m_itemSize.width + newGapX) * tmpCol;
            }
            else
            {
                startX = m_padding.x + (m_itemSize.width + m_gap.width) * tmpCol;
            }
            
            if(bMaxContentSizeH)
            {
                startY = mySize.height - ((m_itemSize.height + newGapY)*tmpRow);
            }
            else
            {
                startY = mySize.height - m_padding.y - ((m_itemSize.height + m_gap.height)*tmpRow);
            }
            
            startX += m_itemSize.width*0.5f;
            startY -= m_itemSize.height*0.5f;
            
            CCNode *pNode = static_cast<CCNode*>(pObject);
            if(pNode)
            {
                pNode->setPosition(ccp(startX, startY));
            }
            
            if(bAddWidth) // 가로 방향으로 추가
            {
                tmpRow++;
                if(tmpRow >= m_row) {
                    tmpRow = 0;
                    tmpCol++;
                }
            }
            else // 세로 방향으로 추가
            {
                tmpCol++;
                if(tmpCol >= m_col) {
                    tmpCol = 0;
                    tmpRow++;
                }
            }
        }
    }
    else
    {
        if ( dataCnt > 0 )
        {
            int nodeCnt = (int)m_lstNode.size();
            if(bAddWidth)
            {
                for ( int i = 0 ; i < nodeCnt ; i ++ )
                {
                    CCNode * pNode = m_lstNode[i];
                    int d = pNode->m_iDepth;
                    
                    float x = m_padding.x + d * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                    float y = height - m_padding.y - 0 * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                    
                    pNode->setPosition(ccp(x, y));
                 
                }
            }
            else
            {
                for ( int i = 0 ; i < nodeCnt ; i ++ )
                {
                    CCNode * pNode = m_lstNode[i];
                    int d = pNode->m_iDepth;
                    
                    float x = m_padding.x + 0 * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                    float y = height - m_padding.y - d * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                    
                    pNode->setPosition(ccp(x, y));
                    
                    //CCLog(" -- %d -- ", i );
                }
            }

        }
        else if (bReverseRefresh)
        {
            // 자식 노드들 위치 조정
            CCARRAY_FOREACH_REVERSE(getChildren(), pObject)
            {
                CCNode *pNode = static_cast<CCNode*>(pObject);
                if(!pNode) continue;
                
                
                float x = m_padding.x + tmpCol * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                float y = height - m_padding.y - tmpRow * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                
                
                pNode->setPosition(ccp(x, y));
                
                //CCLog("x = %f", x);
                //CCLog("y = %f", y);
                
                
                if(bAddWidth) // 가로 방향으로 추가
                {
                    tmpRow++;
                    if(tmpRow >= m_row) {
                        tmpRow = 0;
                        tmpCol++;
                    }
                }
                else // 세로 방향으로 추가
                {
                    tmpCol++;
                    if(tmpCol >= m_col) {
                        tmpCol = 0;
                        tmpRow++;
                    }
                }
            }
        }
        else
        {
            // 자식 노드들 위치 조정
            CCARRAY_FOREACH(getChildren(), pObject)
            {
                CCNode *pNode = static_cast<CCNode*>(pObject);
                if(!pNode) continue;
                
                
                float x = m_padding.x + tmpCol * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                float y = height - m_padding.y - tmpRow * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                
                
                pNode->setPosition(ccp(x, y));
                
                //CCLog("x = %f", x);
                //CCLog("y = %f", y);
                
                
                if(bAddWidth) // 가로 방향으로 추가
                {
                    tmpRow++;
                    if(tmpRow >= m_row) {
                        tmpRow = 0;
                        tmpCol++;
                    }
                }
                else // 세로 방향으로 추가
                {
                    tmpCol++;
                    if(tmpCol >= m_col) {
                        tmpCol = 0;
                        tmpRow++;
                    }
                }
            }
        }
    }
    
    if ( dataCnt > 0 )
    {
        CCSize parSize = m_pClippingScrollNode->getContentSize();
        CCPoint parPos = m_pClippingScrollNode->getPosition();
        CCPoint parAnchorPos = m_pClippingScrollNode->getAnchorPoint();
        
        parPos.x += parAnchorPos.x * -parSize.width - (m_itemSize.width * 0.5f) + m_fScrollDelta;
        parPos.y += parAnchorPos.y * -parSize.height - (m_itemSize.height * 0.5f) + m_fScrollDelta;
        
        //int d = m_iCellCnt - 1;
        //float x = m_padding.x + d * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
        //float y = m_padding.y + d * (m_itemSize.height + m_gap.height) + (m_itemSize.height * 0.5);
        
        //parSize.width = x;
        //parSize.height = y;
        
        float x = (m_itemSize.width);
        float y = (m_itemSize.height);
        parSize.width += x;
        parSize.height += y;
        
        CCPoint objPoint = getParent()->convertToWorldSpace(parPos);
        
//        CCLog("%f %f---", parSize.width, parSize.height);
//        CCLog("%f %f---", parPos.x, parPos.y);
//        CCLog("%f %f---", parAnchorPos.x, parAnchorPos.y);
//        CCLog("%f %f---", objPoint.x, objPoint.y);

        m_rectClipping.origin = objPoint;
        m_rectClipping.size = parSize;
        
        Refresh();
    }
}
void AceGridLayer::AddCellNode(AceClippingScrollNode* pScrollNode, CCNode* (*funLoadAndAddCCBFile)(void *thiz, AceGridLayer* pGridLayer))
{
    m_pClippingScrollNode = pScrollNode;
    CCSize mySize = m_pClippingScrollNode->getContentSize();
    int dataCnt = (int)m_lstData.size();
    if (bAddWidth)
    {
        float w = mySize.width - m_padding.x;
        
        float oneW = m_itemSize.width + m_gap.width;
        
        int nodeCnt = (int)(w / oneW + 0.5f) + 2;
        
        if ( dataCnt < nodeCnt )
            nodeCnt = dataCnt;
        
        for ( int i = 0 ; i < nodeCnt ; i ++ )
        {
            CCNode *pCellNode = funLoadAndAddCCBFile(m_pScene, this);
            pCellNode->m_iDepth = i;
            m_lstNode.push_back(pCellNode);
        }
        m_iCellCnt = nodeCnt;
    }
    else
    {
        float h = mySize.height - m_padding.y;
        
        float oneH = m_itemSize.height + m_gap.height;
        
        int nodeCnt = (int)(h / oneH) + 2;
        
        if ( dataCnt < nodeCnt )
            nodeCnt = dataCnt;
        
        for ( int i = 0 ; i < nodeCnt ; i ++ )
        {
            CCNode *pCellNode = funLoadAndAddCCBFile(m_pScene, this);
            pCellNode->m_iDepth = i;
            m_lstNode.push_back(pCellNode);
        }
        m_iCellCnt = nodeCnt;
    }

}
/*
void AceGridLayer::AddCCBFile(AceClippingScrollNode* pScrollNode, const string& ccbiPath, CCNode* pTargetNode, AceGridLayer* pAddTargetGrid)
{
    m_pClippingScrollNode = pScrollNode;
        
    
    CCSize mySize = m_pClippingScrollNode->getContentSize();
    
    if (bAddWidth)
    {
        float w = mySize.width - m_padding.x;
        
        float oneW = m_itemSize.width + m_gap.width;
        
        int nodeCnt = (int)(w / oneW) + 1;
        for ( int i = 0 ; i < nodeCnt ; i ++ )
        {
            CCNode* pSlotNode = CCBFileController::GetInstance()->loadAndAddCCBFile( ccbiPath, pTargetNode, pAddTargetGrid );
            pSlotNode->m_iDepth = i;
            m_lstNode.push_back(pSlotNode);
        }
        m_iCellCnt = nodeCnt;
    }
    else
    {
        float h = mySize.height - m_padding.y;
        
        float oneH = m_itemSize.height + m_gap.height;
        
        int nodeCnt = (int)(h / oneH) + 1;
        for ( int i = 0 ; i < nodeCnt ; i ++ )
        {
            CCNode* pSlotNode = CCBFileController::GetInstance()->loadAndAddCCBFile( ccbiPath, pTargetNode, pAddTargetGrid );
            pSlotNode->m_iDepth = i;
            m_lstNode.push_back(pSlotNode);
        }
        m_iCellCnt = nodeCnt;
    }
    
    
}
 */
void AceGridLayer::Refresh()
{
    if ( m_bRefresh == true )
    {
        m_bRefresh = false;
        int nodeCnt = (int)m_lstNode.size();
        for ( int i = 0 ; i < nodeCnt ; i ++ )
        {
            CCNode * pNode = m_lstNode[i];
            int d = pNode->m_iDepth;
            m_funUpdate(m_pScene, pNode, &m_lstData[d], m_lstData[d].index);
            
        }
    }
}
void AceGridLayer::update(float delta)
{
    int cnt = (int)m_lstData.size();
    if ( cnt > 0 )
    {
        Refresh();
        int nodeCnt = (int)m_lstNode.size();
        if (bAddWidth)
        {
            float nowX = getPositionX();
            if ( m_fOldX == nowX )
            {
                //CCLog("---return ----");
                return;
            }
            
            m_fOldX = nowX;
            
            float c_X = m_rectClipping.origin.x - m_itemSize.width - m_fScrollDelta;
            float c_W = c_X + (m_iCellCnt * (m_itemSize.width + m_gap.width));

            int move_able_last_Index = cnt - m_iCellCnt;
            float height = getContentSize().height;
            
            for ( int i = 0 ; i < nodeCnt ; i ++ )
            {
                CCNode * pNode = m_lstNode[i];
                CCPoint p = pNode->getPosition();
                CCPoint objPoint = convertToWorldSpace( p );
                if ( objPoint.x < c_X )
                {
                    if ( pNode->m_iDepth < move_able_last_Index )
                    {
                        pNode->m_iDepth += m_iCellCnt;
                        int d = pNode->m_iDepth;
                        //CCLog(" out up (%d) (%.2f : %.2f)------", d, objPoint.x, c_X);
                        int index  = m_lstData[d].index;
                        m_funUpdate(m_pScene, pNode, &m_lstData[d], index);
                        float x = m_padding.x + d * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                        float y = height - m_padding.y - 0 * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                        
                        pNode->setPosition(ccp(x, y));
                    }
                    
                }
                else if ( objPoint.x > c_W )
                {
                    if ( pNode->m_iDepth > m_iCellCnt - 1 )
                    {
                        pNode->m_iDepth -= m_iCellCnt;
                        int d = pNode->m_iDepth;
                        
                        int index  = m_lstData[d].index;
                        //CCLog(" out dn (%d) %d ------", d, index);
                        m_funUpdate(m_pScene, pNode, &m_lstData[d], index);
                        float x = m_padding.x + d * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                        float y = height - m_padding.y - 0 * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                        
                        pNode->setPosition(ccp(x, y));
                    }
                }
            }
        }
        else
        {
            float nowY = getPositionY();
            if ( m_fOldY == nowY )
            {
                //CCLog("---return ----");
                return;
            }
            
            
            //float m_Old = m_fOldY;
            m_fOldY = nowY;
            
            float c_Y = m_rectClipping.origin.y;
            float c_H = c_Y + m_rectClipping.size.height;
            c_Y = c_H - (m_iCellCnt * (m_itemSize.height + m_gap.height));
            int move_able_last_Index = cnt - m_iCellCnt;
            float height = getContentSize().height;
            
            //printf("--- %f %f %d %d --- \n", m_Old, nowY , nodeCnt, m_iCellCnt);
            
            for ( int i = 0 ; i < nodeCnt ; i ++ )
            {
                CCNode * pNode = m_lstNode[i];
                CCPoint p = pNode->getPosition();
                CCPoint objPoint = convertToWorldSpace( p );
                if ( objPoint.y > c_H )
                {
                    while ( objPoint.y > c_H )
                    {
                        if ( pNode->m_iDepth < move_able_last_Index )
                        {
                            pNode->m_iDepth += m_iCellCnt;
                            
                            int d = pNode->m_iDepth;
                            
                            int index  = m_lstData[d].index;
                            m_funUpdate(m_pScene, pNode, &m_lstData[d], index);
                            float x = m_padding.x + 0 * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                            float y = height - m_padding.y - d * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                            
                            pNode->setPosition(ccp(x, y));
                            
                            p = pNode->getPosition();
                            objPoint = convertToWorldSpace( p );
                            
                            
                            //CCLog(" out up (%d->%d)--(%.2f -> %.2f)--%.2f",i, d , objPoint.y, convertToWorldSpace( p ).y , c_H);
                            
                            //m_fOldY = -999.9f;
                        }
                        else
                        {
                            break;
                        }
                    
                    }
                    
                }
                else if ( objPoint.y < c_Y )
                {
                    while ( objPoint.y < c_Y )
                    {
                        if ( pNode->m_iDepth > m_iCellCnt - 1 )
                        {
                            pNode->m_iDepth -= m_iCellCnt;
                            
                            
                            int d = pNode->m_iDepth;
                            
                            int index  = m_lstData[d].index;
                            
                            m_funUpdate(m_pScene, pNode, &m_lstData[d], index);
                            float x = m_padding.x + 0 * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
                            float y = height - m_padding.y - d * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
                            
                            pNode->setPosition(ccp(x, y));
                            
                            p = pNode->getPosition();
                            objPoint = convertToWorldSpace( p );
                            
                            //m_fOldY = -999.9f;
                            //CCLog(" out dn (%d->%d)--(%.2f -> %.2f)--%.2f", i, d , objPoint.y, convertToWorldSpace( p ).y , c_Y);
                        }
                        else
                        {
                            break;
                        }
                        
                    }
                }
            }
        }
        
    }
}
/* //원본
void AceGridLayer::refresh()
{
    if(m_isAutoResize) {
        CCSize size = calculateSize();
        
        //CCLog("size.width = %f", size.width);
        //CCLog("size.height = %f", size.height);
        
        setContentSize(size);
    }
    
    int row = 0;
    int col = 0;
    CCObject *pObject;
    
    float height = getContentSize().height;
    
    //CCLog("position.x = %f", getPosition().x);
    //CCLog("position.y = %f", getPosition().y);
    
    //CCLog("height = %f", height);
    
    // 자식 노드들 위치 조정
    CCARRAY_FOREACH(getChildren(), pObject) {
        CCNode *pNode = static_cast<CCNode*>(pObject);
        if(!pNode) continue;
        
        
        float x = m_padding.x + col * (m_itemSize.width + m_gap.width) + (m_itemSize.width * 0.5);
        float y = height - m_padding.y - row * (m_itemSize.height + m_gap.height) - (m_itemSize.height * 0.5);
        
        
        pNode->setPosition(ccp(x, y));
        
        //CCLog("x = %f", x);
        //CCLog("y = %f", y);
        
        col++;
        if(col >= m_col) {
            col = 0;
            row++;
        }
    }
}
*/







