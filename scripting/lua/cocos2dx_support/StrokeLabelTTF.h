#ifndef __STROKELABELTTF_H__
#define __STROKELABELTTF_H__

#include "cocos2d.h"
#include "LuaCocos2d.h"
using namespace cocos2d;
class StrokeLabelTTF : public cocos2d::CCNode
{
public:
	StrokeLabelTTF();
	~StrokeLabelTTF();

public:
	static StrokeLabelTTF* create(const char *string, const char *fontName, float fontSize, float strokeSize,const cocos2d::ccColor3B&      colStroke = cocos2d::ccc3(0, 0, 0), cocos2d::CCTextAlignment hAlignment=cocos2d::kCCTextAlignmentCenter, cocos2d::CCVerticalTextAlignment vAlignment=cocos2d::kCCVerticalTextAlignmentTop);
	bool initWithString(const char *label, const char *fontName, float fontSize, float fStrokeSize, const cocos2d::ccColor3B&      colStroke, cocos2d::CCTextAlignment hAlignment, cocos2d::CCVerticalTextAlignment vAlignment,const CCSize& dimensions);
    
    static StrokeLabelTTF * create(const char *string, const char *fontName, float fontSize);
	static StrokeLabelTTF * create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment);
	static StrokeLabelTTF * create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment);
public:
	void setColor(const cocos2d::ccColor3B& color3);
	void setString(const char *label);
	void setStrokeColor(cocos2d::ccColor3B col){ m_colStroke = col; updateStroke(); }
	void setStrokeSize(float StrokeSize){ m_fStrokeSize = StrokeSize; updateStroke();}
    void setAnchorPoint(const cocos2d::CCPoint &anchorPoint);
	const char* getString(void);

	CCTextAlignment getHorizontalAlignment();
    void setHorizontalAlignment(CCTextAlignment alignment);
    
    CCVerticalTextAlignment getVerticalAlignment();
    void setVerticalAlignment(CCVerticalTextAlignment verticalAlignment);
    
    CCSize getDimensions();
    void setDimensions(const CCSize &dim);
    
    float getFontSize();
    void setFontSize(float fontSize);
    
    const char* getFontName();
    void setFontName(const char *fontName);

	static StrokeLabelTTF * create();

protected:
	void updateStroke();

private:
	float                   m_fStrokeSize;
	cocos2d::ccColor3B      m_colStroke;
	cocos2d::CCSprite*      m_sprite;
	cocos2d::CCLabelTTF*    m_label;
    CCPoint anchorPoint;
};


#endif //__CCLABEL_H__