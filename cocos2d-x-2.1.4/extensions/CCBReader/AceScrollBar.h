//
//  AceScrollBar.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 2..
//
//

#ifndef ScrollViewTest_AceScrollBar_h
#define ScrollViewTest_AceScrollBar_h

#include "cocos2d.h"


using namespace cocos2d;

class AceScrollBar : public CCNode//, public CCRGBAProtocol
{
public:
    bool init(float fSize, int mode);
    static AceScrollBar* node(float fSize, int mode);
    
    void setColor(const ccColor3B& color) {}
    const ccColor3B& getColor(void) {return ccWHITE;}
    
    GLubyte getOpacity(void) {return 255;}
    void setOpacity(GLubyte opacity);
    
    void setOpacityModifyRGB(bool bValue);
    bool isOpacityModifyRGB(void) {return false;}
    
    void show();
    void hide();
};

#endif
