#include "stdafx.h"
#include "Server.h"

#include <ctime>
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_array.hpp>
#include <boost/asio.hpp>

namespace AsyncUdp {

using boost::asio::ip::udp;

std::string make_daytime_string()
{
	using namespace std;
	time_t now	= time(0);
	return ctime( & now );
}


class Server::Udp_Server
{
public:
	Udp_Server( boost::asio::io_service & io_service )
	: socket_( io_service, udp::endpoint( udp::v4(), 9001 ) )
	{
		start_receive();
	}

private:
	void start_receive()
	{
		socket_.async_receive_from( 
			boost::asio::buffer( recv_buffer_ ), remote_endpoint_,
			boost::bind( & Udp_Server::handle_receive, this,
				boost::asio::placeholders::error, 
				boost::asio::placeholders::bytes_transferred )
			);
	}

	void handle_receive( const boost::system::error_code & error, std::size_t recv_bytes )
	{
		if( !error || error == boost::asio::error::message_size )
		{
			boost::shared_ptr<std::string> message( new std::string(make_daytime_string()) );

			socket_.async_send_to( boost::asio::buffer( *message ), remote_endpoint_,
				boost::bind( & Udp_Server::handle_send, this ) );

			start_receive();
		}
	}

	void handle_send()
	{
	}

	udp::socket		socket_;
	udp::endpoint	remote_endpoint_;
	boost::array<char, 1>	recv_buffer_;
};


void
Server::Main()
{
	try
	{
		boost::asio::io_service	io_service;
		Udp_Server server( io_service );
		io_service.run();
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << std::endl;
	}
}


}