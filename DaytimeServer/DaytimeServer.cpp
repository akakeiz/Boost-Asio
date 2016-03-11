// DaytimeServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "Sync/Server.h"
#include "ASync/Server.h"
#include "ASyncUdp/Server.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Sync::Server::Main();
	Async::Server::Main();

	return 0;
}

