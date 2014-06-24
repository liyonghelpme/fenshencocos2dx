/*
 * CCFontModify.h
 *
 *  Created on: 2014-3-5
 *      Author: Administrator
 */

#ifndef CCFONTMODIFY_H_
#define CCFONTMODIFY_H_
#include "cocos2d.h"
using namespace cocos2d;
class CCFontModify {
public:
	   //获取遮罩图
	  static CCSprite* createMaskedSprite(CCSprite* src, const char* maskFile); 

	  //给文字添加描边
	   static  CCLabelTTF* textAddOutline(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float lineWidth);

	    //添加阴影
	   static CCLabelTTF* textAddShadow(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float shadowSize,float shadowOpacity);

	    //既添加描边又添加阴影
	   static CCLabelTTF* textAddOutlineAndShadow(const char* string, const char* fontName, float fontSize,const ccColor3B &color3,float lineWidth,float shadowSize,float shadowOpacity);
};

#endif /* CCFONTMODIFY_H_ */
