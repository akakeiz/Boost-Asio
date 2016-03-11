#include "stdafx.h"
#include "Server.h"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace Async {

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std;
	time_t now	= time(0);
	return ctime( &now );
}

class Server::Tcp_Connection
:	public boost::enable_shared_from_this<Server::Tcp_Connection>
{
public:
	typedef boost::shared_ptr<Tcp_Connection> pointer;

	static pointer Create( boost::asio::io_service & io_service )
	{
		return pointer( new Tcp_Connection( io_service ) );
	}

	tcp::socket & socket()
	{
		return socket_;	
	}

	void Start()
	{	
		message_	= make_daytime_string();

		boost::asio::async_write( socket_, 
								boost::asio::buffer(message_), 
								boost::bind( & Tcp_Connection::handle_write, 
											this->shared_from_this(), 
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred )
								);
	}

private:
	Tcp_Connection( boost::asio::io_service & io_service )
	:	socket_( io_service )
	{
	}

	void handle_write( const boost::system::error_code & e, size_t size )
	{
	}

	tcp::socket	socket_;
	std::string	message_;
};


class Server::Tcp_Server
{
public:
	Tcp_Server( boost::asio::io_service & io_service )
	: acceptor_( io_service, tcp::endpoint(tcp::v4(), 9001) )
	{
		start_accept();
	}

private:
	void start_accept()
	{
		Tcp_Connection::pointer	new_connection	= Tcp_Connection::Create( acceptor_.get_io_service() );

		acceptor_.async_accept( new_connection->socket(), 
								boost::bind( &Tcp_Server::handle_accept, this, new_connection, boost::asio::placeholders::error ) );
	}

	void handle_accept( Tcp_Connection::pointer new_connection, const boost::system::error_code & error )
	{
		if( !error )
		{
			new_connection->Start();
			start_accept();
		}
	}

	tcp::acceptor	acceptor_;
};

void 
Server::Main()
{
	try
	{
		boost::asio::io_service io_service;
		Tcp_Server server( io_service );
		io_service.run();
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << std::endl;
	}
}


}