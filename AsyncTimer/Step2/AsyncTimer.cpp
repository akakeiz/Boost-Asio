#include "stdafx.h"
#include "AsyncTimer.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Step2 {

void print( const boost::system::error_code & error, boost::asio::deadline_timer * t, int * count )
{
	if( *count < 5 )
	{
		std::cout << * count << std::endl;
		++( *count );

		t->expires_at( t->expires_at() + boost::posix_time::seconds(1) );
		t->async_wait( boost::bind( print, boost::asio::placeholders::error, t, count ) );
	}
}


void
AsyncTimer::Main()
{
	boost::asio::io_service io;
	
	int count = 0;
	boost::asio::deadline_timer t( io, boost::posix_time::seconds(1) );
	t.async_wait( boost::bind( print, boost::asio::placeholders::error, &t, &count) );

	io.run();	
}


}