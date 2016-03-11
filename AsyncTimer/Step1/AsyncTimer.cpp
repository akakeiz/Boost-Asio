#include "stdafx.h"
#include "AsyncTimer.h"

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Step1 {

void print( const boost::system::error_code & error )
{
	std::cout << "Hello, World!" << std::endl;
}


void
AsyncTimer::Main()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t( io, boost::posix_time::seconds(5) );

	t.async_wait( print );
	io.run();	
}


}