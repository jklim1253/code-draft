#define _WIN32_WINNT 0x0601
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server.h"
#include "sessionbase.h"
using namespace boost::asio;

void error_msg(const std::string& type, const boost::system::error_code& e) {
	std::cerr << type << " error[" << e.value() << "] " << e.message() << std::endl;
}
struct service { io_service ios; };
struct TcpServerImpl {
	typedef std::shared_ptr<SessionBase> SessionType;
	typedef SessionBase::socketType socketType;
	typedef std::list<SessionType> SessionContainer;

	io_service& ios;
	ip::tcp::acceptor acceptor;
	int backlog;
	unsigned short port_num;
	SessionContainer sessionlist;
	std::shared_ptr<SessionCreator> creator;

	TcpServerImpl(io_service& _ios) : ios(_ios), acceptor(_ios) {}

	void prepare_acceptor() {
		ip::tcp::endpoint ep(ip::tcp::v4(), port_num);
		acceptor.open(ep.protocol());
		acceptor.bind(ep);
	}

	SessionType prepare_session() {
		SessionType session = creator->create();
		sessionlist.push_back(session);
		session->socket() = std::make_shared<socketType>(ios);

		return session;
	}
	void operation_accept() {
		SessionType session = prepare_session();

		acceptor.async_accept((*session->socket()),
			boost::bind(&TcpServerImpl::handler_accept, this, boost::placeholders::_1, session));
	}
	void handler_accept(const boost::system::error_code& e, SessionType& session) {
		if (e.value() != 0) {
			error_msg("accept", e);
			return;
		}
		operation_accept();

		operation_recv(session);

		operation_send(session);
	}
	void operation_recv(SessionType& session) {
		operation_recv_header(session);
	}
	void operation_recv_header(SessionType& session) {
		session->prepare_header_buffer();

		session->socket()->async_receive(buffer(session->header()),
			boost::bind(&TcpServerImpl::handler_recv_header, this, boost::placeholders::_1,
				boost::placeholders::_2, session));
	}
	void handler_recv_header(const boost::system::error_code& e, std::size_t read_size, SessionType& session) {
		if (e.value() != 0) {
			error_msg("recv header", e);
			return;
		}

		if (!session->validate_header()) {
			error_msg("invalid header", boost::system::error_code());
			return;
		}

		operation_recv_data(session);
	}
	void operation_recv_data(SessionType& session) {
		session->prepare_data_buffer();

		session->socket()->async_receive(buffer(session->data()),
			boost::bind(&TcpServerImpl::handler_recv_data, this, boost::placeholders::_1,
				boost::placeholders::_2, session));
	}
	void handler_recv_data(const boost::system::error_code& e, std::size_t read_size, SessionType& session) {
		if (e.value() != 0) {
			error_msg("recv data", e);
			return;
		}

		operation_recv(session);

		session->process_received_data();
	}
	void operation_send(SessionType& session) {
		// check whether there is something to send or not.
		session->process_send_data();

		session->prepare_send_buffer();

		session->socket()->async_send(buffer(session->out_packet()),
			boost::bind(&TcpServerImpl::handler_send, this, boost::placeholders::_1,
				boost::placeholders::_2, session));
	}
	void handler_send(const boost::system::error_code& e, std::size_t send_size, SessionType& session) {
		if (e.value() != 0) {
			error_msg("send", e);
			return;
		}

		session->notify_sent_result();
	}
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
void TcpServer::setSessionCreator(std::shared_ptr<SessionCreator> creator) {
	impl->creator = creator;
}
void TcpServer::open(unsigned short port_num, int MAXCON) {
	impl->port_num = port_num;
	impl->backlog = MAXCON;

	impl->prepare_acceptor();

	impl->acceptor.listen(MAXCON);

	impl->operation_accept();
}
void TcpServer::run() {
	impl->ios.run();
}

