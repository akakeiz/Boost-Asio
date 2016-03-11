#include "stdafx.h"
#include "Client.h"

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace Sync {

using boost::asio::ip::tcp;

void
Client::Main( int argc, _TCHAR * argv[] )
{
	try
	{
		boost::asio::io_service io_service;

		tcp::resolver resolver( io_service );
		tcp::resolver::query query( "183.110.17.155", "9001" );
		tcp::resolver::iterator endpoint_iterator	= resolver.resolve( query );
		tcp::resolver::iterator end;

		tcp::socket socket( io_service );
		boost::system::error_code error	= boost::asio::error::host_not_found;

		while( error && endpoint_iterator != end )
		{
			socket.close();
			socket.connect( *endpoint_iterator++, error );		
		}

		if( error )
			throw boost::system::system_error( error );

		for( ;; )
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len	= socket.read_some( boost::asio::buffer(buf), error );

			if( error == boost::asio::error::eof )
				break;

			else if( error )
				throw boost::system::system_error( error );

			std::cout.write( buf.data(), len );
		}
	}
	catch ( std::exception e )
	{
		std::cerr << e.what() << std::endl;
	}
	
	return;
}




}