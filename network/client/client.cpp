#define _WIN32_WINNT 0x0601
#include <string>
#include <thread>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Completion_Handler {
public :
	virtual int handler() = 0;
};
class Async_Operation {
public :
	Async_Operation(boost::asio::io_service& ios, Completion_Handler& handler) : ios_(ios), handler_(handler) {}
	virtual void execute() = 0;
private :
	Completion_Handler& handler_;
	boost::asio::io_service& ios_;
};

#pragma pack(1)

struct Header {
	unsigned long marker;
	unsigned long data_type;
	unsigned long data_size;
};
struct Data {
	unsigned long marker;
	unsigned long data_type;
	std::shared_ptr<unsigned char> buffer;
};
struct Packet {
	Header header;
	Data data;
	void encode() {
		header.marker = 0x01020304;
		data.marker = 0x04030201;
	}
	bool header_valid() const {
		unsigned long validation = 0x01020304;
		if (::memcmp(&header.marker, &validation, sizeof(unsigned long)) == 0) {
			return true;
		}
		return false;
	}
	bool data_valid() const {
		unsigned long validation = 0x04030201;
		if (::memcmp(&data.marker, &validation, sizeof(unsigned long)) == 0) {
			return true;
		}
		return false;
	}
};
struct Session {
	std::shared_ptr<boost::asio::ip::tcp::socket> socket;
	Packet packet;
};
class Client {
public :
	Client(boost::asio::io_service& ios) : ios_(ios) {
	}
	void connect(const std::string& raw_ip_address, const unsigned short& port_num) {
		// required element to connection request.
		// endpoint - server
		// socket - client, myself, must be alive for connect operation complete.
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
		std::shared_ptr<boost::asio::ip::tcp::socket> sock(std::make_shared<boost::asio::ip::tcp::socket>(ios_));
		session_ = std::make_shared<Session>();
		session_->socket = sock;

		std::cout << "try to connect " << ep.address().to_string() << ":" << ep.port() << std::endl;
		sock->async_connect(ep, 
			boost::bind(&Client::connect_handler, this, boost::placeholders::_1, session_));
	}
	void close() {

	}
	void send(const std::string& message) {
		send_header(message);
		send_data(message);
	}
protected :
	void send_header(const std::string& message) {

	}
	void send_data(const std::string& message) {

	}
	void receive_header(std::shared_ptr<Session>& session) {
		// asynchronously receive packet header.
		session->socket->async_receive(boost::asio::buffer((char*)&session->packet.header, sizeof(Header)),
			boost::bind(&Client::receive_header_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void receive_data(std::shared_ptr<Session>& session) {
		// prepare packet data buffer.
		session->packet.data.buffer = std::shared_ptr<unsigned char>(new unsigned char[session->packet.header.data_size], std::default_delete<unsigned char[]>());

		// asynchronously receive packet data.
		session->socket->async_receive(boost::asio::buffer((char*)session->packet.data.buffer.get(), sizeof(Header)),
			boost::bind(&Client::receive_header_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void connect_handler(const boost::system::error_code& e, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "CONNECT ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}
		boost::asio::ip::tcp::endpoint& remote = session->socket->remote_endpoint();
		boost::asio::ip::tcp::endpoint& local = session->socket->local_endpoint();
		std::cout << "successfully connected." << std::endl;
		std::cout << local.address().to_string() << ":" << local.port() << "----"
			<< remote.address().to_string() << ":" << remote.port() << std::endl;

		// start receiving packet.
		receive_header(session);
	}
	void receive_header_handler(const boost::system::error_code& e, std::size_t read_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "RECEIVE HEADER ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}
	}
	void receive_data_handler(const boost::system::error_code& e, std::size_t read_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "RECEIVE DATA ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}
	}
protected :
	boost::asio::io_service& ios_;
	std::shared_ptr<Session> session_;
};
int main(void) {

	boost::asio::io_service ios;

	std::thread t(boost::bind(&boost::asio::io_service::run, &ios));

	std::string server_ip_address("127.0.0.1");
	unsigned short server_port(33333);

	try {
		Client client(ios);

		client.connect(server_ip_address, server_port);

		{

			//std::cout << "successfully connected to " << s->socket->remote_endpoint().address().to_string() << ":" << s->socket->remote_endpoint().port() << std::endl;
			//std::cout << "my socket information : " << s->socket->local_endpoint().address().to_string() << ":" << s->socket->local_endpoint().port() << std::endl;


			std::string message;
			do {
				std::cout << "> ";
				std::getline(std::cin, message);

				client.send(message);

			} while (message != "quit");
		}

		client.close();
		t.join();
	}
	catch (boost::system::error_code& e) {
		std::cerr << "ERROR[" << e.value() << "] " << e.message() << std::endl;
		return e.value();
	}

	return 0;
}