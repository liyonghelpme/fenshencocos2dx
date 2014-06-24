/*
 * CCFontModify.cpp
 *
 *  Created on: 2014-3-5
 *      Author: Administrator
 */

#include "CCFontModify.h"



CCSprite*  CCFontModify::createMaskedSprite(CCSprite* src, const char* maskFile) 
{ 
    CCSprite * mask = CCSprite::create(maskFile); 
     
    assert(src); 
    assert(mask); 
 
    CCSize srcContent = src->getContentSize(); 
    CCSize maskContent = mask->getContentSize(); 
 
    CCRenderTexture * rt = CCRenderTexture::create(srcContent.width, srcContent.height, kTexture2DPixelFormat_RGBA8888); 
     
    float ratiow = srcContent.width / maskContent.width; 
    float ratioh = srcContent.height / maskContent.height; 
    mask->setScaleX(ratiow); 
    mask->setScaleY(ratioh); 
 
    mask->setPosition(ccp(srcContent.width / 2, srcContent.height / 2)); 
    src->setPosition(ccp(srcContent.width / 2, srcContent.height / 2)); 
 
    ccBlendFunc blendFunc2 = { GL_ONE, GL_ZERO }; 
    mask->setBlendFunc(blendFunc2); 
    ccBlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO }; 
    src->setBlendFunc(blendFunc3); 
 
    rt->begin(); 
    mask->visit(); 
    src->visit(); 
    rt->end(); 
 
    CCSprite * retval = CCSprite::createWithTexture(rt->getSprite()->getTexture()); 
    retval->setFlipY(true); 
    return retval; 
} 
/*
    制作文字描边效果是很简单的，我们写好一段文字之后，也就是创建出一个CCLabelTTF，称之为正文CCLabelTTF。然后再创建出4个CCLabelTTF，颜色为黑色，大小同正文CCLabelTTF相同，
    称之为描边CCLabelTTF。说到这大家可能已经明白了，没错，就是把4个描边CCLabelTTF放于正文CCLabelTTF的下面，分别于左右上下与正文CCLabelTTF错开，这样描边效果就实现啦。。

    *string     文本
    *fontName   文本字体类型
    *fontSize   文本大小
    *color3     文本颜色
    *lineWidth  所描边的宽度
 */
CCLabelTTF* CCFontModify::textAddOutline(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float lineWidth)
{
    //描边CCLabelTTF 左
    CCLabelTTF* left = CCLabelTTF::create(string, fontName, fontSize);
    left->setColor(ccBLACK);

    //描边CCLabelTTF 右
    CCLabelTTF* right = CCLabelTTF::create(string, fontName, fontSize);
    right->setColor(ccBLACK);
    right->setPosition(ccp(left->getContentSize().width*0.5+lineWidth*2,left->getContentSize().height*0.5));
    left->addChild(right);

    //描边CCLabelTTF 上
    CCLabelTTF* up = CCLabelTTF::create(string, fontName, fontSize);
    up->setColor(ccBLACK);
    up->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5+lineWidth));
    left->addChild(up);

    //描边CCLabelTTF 下
    CCLabelTTF* down = CCLabelTTF::create(string, fontName, fontSize);
    down->setColor(ccBLACK);
    down->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5-lineWidth));
    left->addChild(down);

    //正文CCLabelTTF
    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize);
    center->setColor(color3);
    center->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5));
    left->addChild(center);

    return left;
}


/*
    给文字添加阴影，一看就懂的。。。
    *string         文本
    *fontName       文本字体类型
    *fontSize       文本大小
    *color3         文本颜色
    *shadowSize     阴影大小
    *shadowOpacity  阴影透明度

 */
CCLabelTTF* CCFontModify::textAddShadow(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float shadowSize,float shadowOpacity)
{
    CCLabelTTF* shadow = CCLabelTTF::create(string, fontName, fontSize);
    shadow->setColor(ccBLACK);
    shadow->setOpacity(shadowOpacity);

    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize);
    center->setColor(color3);
    center->setPosition(ccp(shadow->getContentSize().width*0.5-shadowSize, shadow->getContentSize().height*0.5+shadowSize));
    shadow->addChild(center);

    return shadow;
}


//既添加描边又添加阴影
CCLabelTTF* CCFontModify::textAddOutlineAndShadow(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float lineWidth,float shadowSize,float shadowOpacity)
{
    CCLabelTTF* shadow = CCLabelTTF::create(string, fontName, fontSize);
    shadow->setColor(ccBLACK);
    shadow->setOpacity(shadowOpacity);

    CCLabelTTF* left = CCLabelTTF::create(string, fontName, fontSize);
    left->setColor(ccBLACK);
    left->setPosition(ccp(shadow->getContentSize().width*0.5-shadowSize, shadow->getContentSize().height*0.5+shadowSize));
    shadow->addChild(left);

    CCLabelTTF* right = CCLabelTTF::create(string, fontName, fontSize);
    right->setColor(ccBLACK);
    right->setPosition(ccp(left->getContentSize().width*0.5+lineWidth*2,left->getContentSize().height*0.5));
    left->addChild(right);

    CCLabelTTF* up = CCLabelTTF::create(string, fontName, fontSize);
    up->setColor(ccBLACK);
    up->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5+lineWidth));
    left->addChild(up);

    CCLabelTTF* down = CCLabelTTF::create(string, fontName, fontSize);
    down->setColor(ccBLACK);
    down->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5-lineWidth));
    left->addChild(down);

    CCLabelTTF* center = CCLabelTTF::create(string, fontName, fontSize);
    center->setColor(color3);
    center->setPosition(ccp(left->getContentSize().width*0.5+lineWidth, left->getContentSize().height*0.5));
    left->addChild(center);

    return shadow;
}
