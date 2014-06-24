#include "StrokeLabelTTF.h"
using namespace cocos2d;


StrokeLabelTTF::StrokeLabelTTF()
	:m_colStroke(ccc3(0,0,0))
	,m_fStrokeSize(0)
	,m_sprite(NULL)
	,m_label(NULL)
    ,anchorPoint(0.5,0.5)
{}
StrokeLabelTTF::~StrokeLabelTTF()
{
	CC_SAFE_RELEASE_NULL(m_label);
}

StrokeLabelTTF * StrokeLabelTTF::create()
{
   StrokeLabelTTF *pRet = new StrokeLabelTTF();
    
    if(pRet && pRet->initWithString("",NULL,0.0,1,ccc3(0,0,0),kCCTextAlignmentCenter,kCCVerticalTextAlignmentTop,CCSizeZero))
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool StrokeLabelTTF::initWithString(const char *string, const char *fontName, float fontSize, float strokeSize,const cocos2d::ccColor3B& colStroke, CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment,const CCSize& dimensions)
{
	m_fStrokeSize = strokeSize;
	m_colStroke = colStroke;
	m_label = CCLabelTTF::create(string, fontName, fontSize, dimensions,hAlignment,vAlignment);
	m_label->retain();
	if (m_fStrokeSize != 0)
	{
		updateStroke();
	}
	return true;
}
StrokeLabelTTF* StrokeLabelTTF::create(const char *string, const char *fontName, float fontSize, float fStrokeSize,const cocos2d::ccColor3B& colStroke ,CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
	StrokeLabelTTF *pRet = new StrokeLabelTTF();
	if(pRet && pRet->initWithString(string, fontName, fontSize, fStrokeSize, colStroke, hAlignment, vAlignment,CCSizeZero))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

StrokeLabelTTF * StrokeLabelTTF::create(const char *string, const char *fontName, float fontSize)
{
    StrokeLabelTTF *pRet = new StrokeLabelTTF();
    
    if(pRet && pRet->initWithString(string,fontName,fontSize,0,ccc3(0,0,0),kCCTextAlignmentCenter,kCCVerticalTextAlignmentTop,CCSizeZero))
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}

StrokeLabelTTF * StrokeLabelTTF::create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment)
{
    StrokeLabelTTF *pRet = new StrokeLabelTTF();
    
    if(pRet && pRet->initWithString(string,fontName,fontSize,0,ccc3(0,0,0),hAlignment,kCCVerticalTextAlignmentTop,dimensions))
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}

StrokeLabelTTF * StrokeLabelTTF::create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment)
{
    StrokeLabelTTF *pRet = new StrokeLabelTTF();
    
    if(pRet && pRet->initWithString(string,fontName,fontSize,0,ccc3(0,0,0),hAlignment,vAlignment,dimensions))
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}

const char* StrokeLabelTTF::getString(void)
{
    return m_label->getString();
}

void StrokeLabelTTF::updateStroke()
{
	if (m_sprite)
	{
		removeChild(m_sprite, true);
	}

	CCSize textureSize = m_label->getContentSize();
	textureSize.width += 2 * m_fStrokeSize;
	textureSize.height += 2 * m_fStrokeSize;
	//call to clear error
	glGetError();
	CCRenderTexture *rt = CCRenderTexture::create(textureSize.width, textureSize.height);
	if(!rt)
	{
		CCLOG("create render texture failed !!!!");
		addChild(m_label);
		return;
	}

	ccColor3B col = m_label->getColor();
	m_label->setColor(m_colStroke);

	ccBlendFunc originalBlend = m_label->getBlendFunc();
	ccBlendFunc func = { GL_SRC_ALPHA, GL_ONE};
	m_label->setBlendFunc(func);

	m_label->setAnchorPoint(ccp(0.5f,0.5f));

	rt->begin();
	for(int i = 0; i < 360; i += 15)
	{
		float r = CC_DEGREES_TO_RADIANS(i);
		m_label->setPosition(ccp(
			textureSize.width * 0.5f + sin(r) * m_fStrokeSize,
			textureSize.height * 0.5f + cos(r) * m_fStrokeSize));
		m_label->visit();
	}

	m_label->setColor(col);
	m_label->setBlendFunc(originalBlend);
	m_label->setPosition(ccp(textureSize.width * 0.5f, textureSize.height * 0.5f));
	m_label->visit();
	rt->end();

	CCTexture2D *texture = rt->getSprite()->getTexture();
	texture->setAliasTexParameters();
	m_sprite = CCSprite::createWithTexture(rt->getSprite()->getTexture());
	setContentSize(m_sprite->getContentSize());
	m_sprite->setAnchorPoint(this->anchorPoint);//------------
	m_sprite->setPosition(ccp(0, 0));
	((CCSprite *)m_sprite)->setFlipY(true);
	addChild(m_sprite);
}
void StrokeLabelTTF::setString(const char *label)
{
	if (m_label)
	{
		if(0!=strcmp(label, m_label->getString()))
		{
			m_label->setString(label);
			if(strlen(label)!=0)
			{
				updateStroke();
			}
		}
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setString m_label=NULL");
	}
}
void StrokeLabelTTF::setColor(const ccColor3B& color3)
{
	if (m_label)
	{
		ccColor3B col = m_label->getColor();
		if(color3.r!=col.r || color3.g!=col.g || color3.b!=col.b)
		{
			m_label->setColor(color3);
			updateStroke();
		}
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
	}
}

void StrokeLabelTTF::setAnchorPoint(const cocos2d::CCPoint &anchorPoint1)
{

    this->anchorPoint=anchorPoint1;
    updateStroke();
}

CCTextAlignment StrokeLabelTTF::getHorizontalAlignment()
{
	return m_label->getHorizontalAlignment();
}

void StrokeLabelTTF::setHorizontalAlignment(CCTextAlignment alignment)
{
	m_label->setHorizontalAlignment(alignment);
	this->updateStroke();
}

CCVerticalTextAlignment StrokeLabelTTF::getVerticalAlignment()
{
	return m_label->getVerticalAlignment();
}

void StrokeLabelTTF::setVerticalAlignment(CCVerticalTextAlignment verticalAlignment)
{
	m_label->setVerticalAlignment(verticalAlignment);
	this->updateStroke();
}

CCSize StrokeLabelTTF::getDimensions()
{
	return m_label->getDimensions();
}

void StrokeLabelTTF::setDimensions(const CCSize &dim)
{
	m_label->setDimensions(dim);
	this->updateStroke();
}

float StrokeLabelTTF::getFontSize()
{
	return m_label->getFontSize();
}

void StrokeLabelTTF::setFontSize(float fontSize)
{
	m_label->setFontSize(fontSize);
	this->updateStroke();
}

const char* StrokeLabelTTF::getFontName()
{
	return m_label->getFontName();
}

void StrokeLabelTTF::setFontName(const char *fontName)
{
	m_label->setFontName(fontName);
	this->updateStroke();
}

