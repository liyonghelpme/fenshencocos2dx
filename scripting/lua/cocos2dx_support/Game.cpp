#include "Game.h"

using namespace cocos2d;
USING_NS_CC_EXT;

extern "C"
{
	//初始化socket
	void NetInitRaw(std::string ip,unsigned int port,std::string domain,int funcID)
	{
		CCLOG("NetInitRaw:ip:%s port %d funcID:%d",ip.c_str(),port,funcID);
		SocketListener *mSocketListener = new SocketListener;
		mSocketListener->setFuncID(funcID);
		SocketManager::getInstance()->init(ip.c_str(),port,domain.c_str(),mSocketListener);
	}

	//socket重连
	void NetReconnectRaw()
	{
		CCLOG("tolua_Cocos2d_NetReconnectRaw00");
		SocketManager::getInstance()->reconnect();
	}

	void NetReqRaw(const char* value)
	{
		//CCLOG("length=%d  %s",strlen(value),value);
		SocketManager::addMessageToSendQueue(value);
	}

	void NetHttpInitRaw(int funcID)
	{
		CCLOG("NetHttpInitRaw:ip: funcID:%d",funcID);
		CCHttpClient::getInstance()->setLuaFuncID(funcID);
	}

	void NetHttpReqRaw(string url,string data,string type,string tag)
	{
		CCHttpRequest* request = new CCHttpRequest();
		request->setUrl(url.c_str());
		request->setTag(tag.c_str());
		if(type=="post"){
			request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
			request->setRequestData(data.c_str(),data.length());
		}else{
			request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
		}
		CCHttpClient::getInstance()->send(request);
	}

	void cclogRaw(string msg)
	{
		if(!msg.empty()){
			CCLOG(msg.c_str());
		}
	}

}

