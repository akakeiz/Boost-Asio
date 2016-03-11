#include "stdafx.h"
#include "AsyncTimer.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Step4 {

class AsyncTimer::Printer
{
public:
	Printer( boost::asio::io_service& io )
	: strand_( io ),
	  timer1_( io, boost::posix_time::seconds(1) ),
	  timer2_( io, boost::posix_time::seconds(1) ),
	  count_(0)
	{
		timer1_.async_wait( boost::bind( &Printer::print1, this) );
		timer2_.async_wait( boost::bind( &Printer::print2, this) );
	}

	~Printer()
	{
		std::cout << "Final count is " << count_ << std::endl;
	}
			
	void print1()
	{
		if( count_ < 10 )
		{
			std::cout << "Timer 1: " << count_ << std::endl;
			++( count_ );

			timer1_.expires_at( timer1_.expires_at() + boost::posix_time::seconds(1) );
			timer1_.async_wait( boost::bind( &Printer::print1, this ) );
		}
	}

	void print2()
	{
		if( count_ < 10 )
		{
			std::cout << "Timer 2: " << count_ << std::endl;
			++( count_ );

			timer2_.expires_at( timer2_.expires_at() + boost::posix_time::seconds(1) );
			timer2_.async_wait( boost::bind( &Printer::print2, this ) );
		}
	}

private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	int count_;
};


void
AsyncTimer::Main()
{
	boost::asio::io_service io;
	Printer p( io );
	
	boost::thread t( boost::bind( &boost::asio::io_service::run, &io ) );
	
	io.run();
	t.join();
}


}