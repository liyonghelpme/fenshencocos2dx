#include "ImageAsyncLoader.h"
#include "cocos2d.h"
#include "LuaCocos2d.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"
#include "CCLuaEngine.h"
#include "script_support/CCScriptSupport.h"


extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}

using namespace cocos2d;
USING_NS_CC_EXT;

ImageAsyncLoader::ImageAsyncLoader()
{
}

ImageAsyncLoader::~ImageAsyncLoader()
{
}

ImageAsyncLoader* ImageAsyncLoader::create(const char * path,LUA_FUNCTION callbackFuncID)
{
    ImageAsyncLoader* pRet = new ImageAsyncLoader();
    if (pRet && pRet->init(path,callbackFuncID))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void ImageAsyncLoader::onLoadFinishCallback(CCObject *texture)
{
	CCLuaEngine* pEngine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
			
	CCLuaStack* luaStack= pEngine->getLuaStack();	
	luaStack->pushString(this->path);	
	luaStack->pushCCObject(texture,"CCTexture2D");
	luaStack->executeFunctionByHandler(callbackFuncID, 2);
	luaStack->removeScriptHandler(this->callbackFuncID);
}

bool ImageAsyncLoader::init(const char * path,LUA_FUNCTION callbackFuncID)
{
	CCAssert(path != NULL, "ImageAsyncLoader: path MUST not be NULL");  
	CCAssert(callbackFuncID != -1, "ImageAsyncLoader: callbackFuncID MUST not be -1");  

	this->callbackFuncID = callbackFuncID;
	this->path = path;
	return true;
}

void ImageAsyncLoader::load()
{
	CCTextureCache::sharedTextureCache()->addImageAsync(this->path,this,callfuncO_selector(ImageAsyncLoader::onLoadFinishCallback));
}




