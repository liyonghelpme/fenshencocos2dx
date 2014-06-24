#ifndef  _IMAGE_ASYNC_LOADER_H_
#define  _IMAGE_ASYNC_LOADER_H_

#include "cocos2d.h"
#include "LuaCocos2d.h"
#include "cocos-ext.h"
#include "CCLuaValue.h"

using namespace cocos2d;
USING_NS_CC_EXT;

class ImageAsyncLoader : public CCObject{
private:
	LUA_FUNCTION callbackFuncID;
	const char * path;

public:
	bool init(const char * path,LUA_FUNCTION callbackFuncID);
	static ImageAsyncLoader* create(const char * path,LUA_FUNCTION callbackFuncID);
	void onLoadFinishCallback(CCObject *target);
	void load();

	ImageAsyncLoader();
	~ImageAsyncLoader();
};

#endif