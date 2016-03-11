#include "stdafx.h"
#include "Server.h"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

namespace Sync {

using boost::asio::ip::tcp;

std::string
Make_daytime_string()
{
	std::time_t	now	= std::time( 0 );
	return std::ctime( &now );
}


void
Server::Main()
{
	try
	{
		boost::asio::io_service io_service;

		tcp::acceptor acceptor( io_service, tcp::endpoint(tcp::v4(), 9001) );

		for( ;; )
		{
			tcp::socket socket( io_service );
			acceptor.accept( socket );

			std::string message = Make_daytime_string();

			boost::system::error_code ignored_error;
			boost::asio::write( socket, boost::asio::buffer( message ), boost::asio::transfer_all(), ignored_error );
		}
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << std::endl;
	}
}




}