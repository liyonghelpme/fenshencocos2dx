#ifndef  _GAME_H_
#define  _GAME_H_

#include "LuaCocos2d.h"
#include "cocos-ext.h"

#include "SocketListener.h"
#include "SocketManager.h"
#include "pay.h"
#include "utils.h"
#include "EncryptTxtReader.h"
#include "UmengLog.h"



extern "C"
{
	void NetInitRaw(std::string ip,unsigned int port,std::string domain,LUA_FUNCTION funcID);
	void NetReconnectRaw();
	void NetReqRaw(const char* value);
	void NetHttpInitRaw(LUA_FUNCTION funcID);
	void NetHttpReqRaw(string url,string data,string type,string tag);
	void cclogRaw(string msg);
	extern void startPay(const char* orderUrl);
	extern CCString* readEncryptTxt(const char* filePath);
	extern char * readEncryptStr(const char* filePath);
	extern int UmengLogEvent(int tag,const char* logEvent,cocos2d::CCDictionary* kv);
	extern void startShare(const char* jniJson);
}
#endif	