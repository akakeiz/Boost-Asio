// DaytimeServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

