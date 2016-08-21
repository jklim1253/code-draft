#define _WIN32_WINNT 0x0601
#include <list>
#include <thread>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#pragma pack(1)

using namespace boost::asio;

struct Header {
	unsigned long marker;
	unsigned long data_type;
	unsigned long data_size;
};
struct Data {
	//unsigned long marker;
	//unsigned long data_type;
	std::shared_ptr<unsigned char> buffer;
};
struct Packet {
	Header header;
	Data data;
	void encode() {
		header.marker = 0x01020304;
		//data.marker = 0x04030201;
	}
	bool is_valid() const {
		return header_valid();
	}
private :
	bool header_valid() const {
		unsigned long validation = 0x01020304;
		if (::memcmp(&header.marker, &validation, sizeof(unsigned long)) == 0) {
			return true;
		}
		return false;
	}
};
struct Session {
	std::shared_ptr<ip::tcp::socket> socket;
	Packet packet;
};
class Server {
public :
	Server(io_service& ios) : ios_(ios), acceptor_(ios), BACKLOG(5) {
	}
	void open(const unsigned short& port_num) {
		// requirement of server open
		// endpoint - host, all-ip, specific-port
		// socket 
		// acceptor
		ip::tcp::endpoint ep(ip::tcp::v4(), port_num);
		acceptor_.open(ep.protocol());
		acceptor_.bind(ep);

		acceptor_.listen(BACKLOG);

		std::cout << acceptor_.local_endpoint().address().to_string() << ":" << acceptor_.local_endpoint().port() << " listening..." << std::endl;

		accept();
	}
	void run() {
		ios_.run();
	}
	void close() {

	}
private :
	void accept() {
		std::shared_ptr<Session> session(std::make_shared<Session>());
		std::shared_ptr<ip::tcp::socket> socket(std::make_shared<ip::tcp::socket>(ios_));
		session->socket = socket;

		acceptor_.async_accept(*socket,
			boost::bind(&Server::accept_handler, this, boost::placeholders::_1, session));
	}
	void receive(std::shared_ptr<Session>& session) {
		ip::tcp::socket& socket = *(session->socket);

		// asynchronously receive header.
		socket.async_receive(buffer((char*)&session->packet.header, sizeof(Packet)),
			boost::bind(&Server::receive_header_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void send(std::shared_ptr<Session>& session) {

	}
	void accept_handler(const boost::system::error_code& e, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "ACCEPT ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}

		const ip::tcp::endpoint& remote = session->socket->remote_endpoint();
		std::cout << remote.address().to_string() << ":" << remote.port() << " connected." << std::endl;

		sessionlist.push_back(session);

		receive(session);

		accept();
	}
	void receive_header_handler(const boost::system::error_code& e, std::size_t read_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "RECEIVE HEADER ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}
		// check marker of header.
		if (!session->packet.is_valid()) {
			std::cerr << "INVALID MARKER" << std::endl;
			return;
		}
		// check data type. (not yet)
		// prepare buffer.
		session->packet.data.buffer = std::shared_ptr<unsigned char>(new unsigned char[session->packet.header.data_size], std::default_delete<unsigned char[]>());

		// asynchronously receive data
		session->socket->async_receive(boost::asio::buffer((char*)session->packet.data.buffer.get(), session->packet.header.data_size),
			boost::bind(&Server::receive_data_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void receive_data_handler(const boost::system::error_code& e, std::size_t read_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "RECEIVE DATA ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}

		// notify.
		const ip::tcp::endpoint& remote = session->socket->remote_endpoint();
		std::string msg(session->packet.data.buffer.get(), session->packet.data.buffer.get() + session->packet.header.data_size);
		std::cout << remote.address().to_string() << ":" << remote.port() << " > " << msg << std::endl;

		receive(session);
	}

private :
	boost::asio::io_service& ios_;
	boost::asio::ip::tcp::acceptor acceptor_;
	int BACKLOG;
	std::list<std::shared_ptr<Session>> sessionlist;
};
int main(void) {
	boost::asio::io_service ios;

	Server server(ios);

	unsigned short port_num(33333);

	server.open(port_num);

	server.run();

	return 0;
}