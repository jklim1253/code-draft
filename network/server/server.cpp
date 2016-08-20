#define _WIN32_WINNT 0x0601
#include <list>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Server {
public :
	Server(boost::asio::io_service& ios) : ios_(ios), acceptor_(ios), BACKLOG(5) {
		ios_.run();
	}
	void open(const unsigned short& port_num) {
		// requirement of server open
		// endpoint - host, all-ip, specific-port
		// socket 
		// acceptor
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4(), port_num);
		std::shared_ptr<boost::asio::ip::tcp::socket> socket(std::make_shared<boost::asio::ip::tcp::socket>(ios_));

		acceptor_.bind(ep);

		acceptor_.listen(BACKLOG);

		acceptor_.async_accept(*socket, boost::bind(&Server::accept_handler, this, boost::placeholders::_1));

	}
	void close() {

	}
	void accept_handler(boost::system::error_code e) {

	}

private :
	boost::asio::io_service& ios_;
	boost::asio::ip::tcp::acceptor acceptor_;
	int BACKLOG;
	std::list<std::shared_ptr<boost::asio::ip::tcp::socket>> socketlist;
};
int main(void) {
	boost::asio::io_service ios;

	Server server(ios);

	unsigned short port_num(33333);

	server.open(port_num);

	return 0;
}