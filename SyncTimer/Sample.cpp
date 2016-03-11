// Sample.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t( io, boost::posix_time::seconds(5) );

	std::cout << "Start wating.." << std::endl;

	t.wait();

	std::cout << "Hello, World" << std::endl;

	return 0;
}

