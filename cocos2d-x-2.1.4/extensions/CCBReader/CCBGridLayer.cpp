//
//  CCBGridLayer.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 18..
//
//

#include "CCBGridLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;


CCGridLayer::CCGridLayer()
{
    
}

CCGridLayer::~CCGridLayer()
{
    
}

bool CCGridLayer::init()
{
    return true;
}

void CCGridLayer::onEnter()
{
    //cocosBuilder에섯 셋팅한 값이 로더에서 셋팅된다음 onEnter()가 실행된다...
    //뭔가 셋팅값을 가지고 작업을할땐 생성자나 init()함수 말고 onEnter()함수에서 해야 할듯하다...
    CCLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~2");
    CCLog("m_fRow = %f", m_fRow);
    CCLog("m_fCol = %f", m_fCol);
    CCLog("m_fPadingLeft = %f", m_fPadingLeft);
    CCLog("m_fPadingTop = %f", m_fPadingTop);
    CCLog("m_fCellWidth = %f", m_fCellWidth);
    CCLog("m_fCellHight = %f", m_fCellHight);
    CCLog("m_fGapX = %f", m_fGapX);
    CCLog("m_fGapY = %f", m_fGapY);
    
    
}

void CCGridLayer::draw()
{
    
    //glEnable(GL_LINE_STRIP);
   
    if(m_fRow == 0) m_fRow = 99;
    if(m_fCol == 0) m_fCol = 99;
    
    //그리드 그리기
    for(int i=0; i<m_fRow; i++)
    {
        for(int j=0; j<m_fCol; j++)
        {
            
            ccDrawRect(ccp(m_fPadingLeft + (m_fCellWidth + m_fGapX) * j, this->getContentSize().height - m_fPadingTop - (m_fCellHight + m_fGapY) * i), ccp(m_fPadingLeft + m_fCellWidth + (m_fCellWidth + m_fGapX) * j, this->getContentSize().height - m_fPadingTop - m_fCellHight - (m_fCellHight + m_fGapY) * i));
        }
    }
   
}


