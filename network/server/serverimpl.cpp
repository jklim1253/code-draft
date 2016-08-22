#define _WIN32_WINNT 0x0601
#include "server.h"
#include <boost/asio.hpp>
using namespace boost::asio;

struct service { io_service ios; };
struct TcpServerImpl {
	io_service& ios;
	ip::tcp::acceptor acceptor;
	TcpServerImpl(io_service& _ios) : ios(_ios), acceptor(_ios) {}
};
TcpServer::TcpServer()
	: impl(new TcpServerImpl(service().ios)) {

}
TcpServer::~TcpServer() {
	if (impl) {
		delete impl;
		impl = nullptr;
	}
}
void TcpServer::open(unsigned short port_num, int MAXCON) {
	ip::tcp::endpoint ep(ip::tcp::v4(), port_num);
	impl->acceptor.open(ep.protocol());
	impl->acceptor.bind(ep);

	impl->acceptor.listen(MAXCON);

	// requirement for async_accept operation.
	// socket : keep alive for async_accept operation complete.
	// handler : after async_accept operation done, something to execute.
	std::shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(impl->ios));
	typedef void(*handler)(const boost::system::error_code& e);
	handler accept_handler;
	impl->acceptor.async_accept(*socket, accept_handler);
}
void TcpServer::run() {
	impl->ios.run();
}

void TcpServer::send()
{
}
