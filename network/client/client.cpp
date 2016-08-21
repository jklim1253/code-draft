#define _WIN32_WINNT 0x0601
#include <string>
#include <thread>
#include <iostream>
#include <queue>
#include <list>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

class Completion_Handler {
public :
	virtual int handler() = 0;
};
class Async_Operation {
public :
	Async_Operation(io_service& ios, Completion_Handler& handler) : ios_(ios), handler_(handler) {}
	virtual void execute() = 0;
private :
	Completion_Handler& handler_;
	io_service& ios_;
};

#pragma pack(1)

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
	//bool data_valid() const {
	//	unsigned long validation = 0x04030201;
	//	if (::memcmp(&data.marker, &validation, sizeof(unsigned long)) == 0) {
	//		return true;
	//	}
	//	return false;
	//}
};
struct Session {
	std::shared_ptr<ip::tcp::socket> socket;
	Packet packet;
	Packet packet_for_sending;
};
class Client {
public :
	Client(io_service& ios) : ios_(ios) {
	}
	void connect(const std::string& remote_ip_address, const unsigned short& remote_port_num) {
		// requirement for connection operation.
		// io_service : member variable.
		// server endpoint : for local socket to connect
		// local socket : having server endpoint, must be alive for connect operation have completed. saved in Session.
		ip::tcp::endpoint server_ep(ip::address::from_string(remote_ip_address), remote_port_num);
		std::shared_ptr<ip::tcp::socket> socket(std::make_shared<ip::tcp::socket>(ios_));

		session_ = std::make_shared<Session>();
		session_->socket = socket;

		std::cout << "try to connect " << server_ep.address().to_string() << ":" << server_ep.port() << std::endl;

		// request connect operation asynchronously.
		socket->async_connect(server_ep, 
			boost::bind(&Client::connect_handler, this, boost::placeholders::_1, session_));
	}
	void close() {
		session_->socket->shutdown(ip::tcp::socket::shutdown_both);
		session_->socket->close();
	}
	// enqueue message in messageQueue
	void send(const std::string& message) {
		// make packet from message.
		Packet packet;
		packet.encode();
		packet.header.data_size = message.length();
		packet.data.buffer = std::shared_ptr<unsigned char>(new unsigned char[message.length()], std::default_delete<unsigned char[]>());
		::memcpy(packet.data.buffer.get(), message.c_str(), message.length());

		// enqueue message in messageQueue.
		messageQueue.push(packet);

		send_internal(session_);
	}
protected :
	void send_internal(std::shared_ptr<Session>& session) {
		if (messageQueue.empty()) { return; }

		session->packet_for_sending = messageQueue.front();

		send_header(session);
	}
	void send_header(std::shared_ptr<Session>& session) {
		session->socket->async_send(buffer(&session->packet_for_sending.header, sizeof(Header)),
			boost::bind(&Client::send_header_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void send_data(std::shared_ptr<Session>& session) {
		session->socket->async_send(buffer(session->packet_for_sending.data.buffer.get(), session->packet_for_sending.header.data_size),
			boost::bind(&Client::send_data_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void receive_internal(std::shared_ptr<Session>& session) {
		receive_header(session);
	}
	void receive_header(std::shared_ptr<Session>& session) {
		// asynchronously receive packet header.
		session->socket->async_receive(buffer((char*)&session->packet.header, sizeof(Header)),
			boost::bind(&Client::receive_header_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	void receive_data(std::shared_ptr<Session>& session) {
		// prepare packet data buffer.
		session->packet.data.buffer = std::shared_ptr<unsigned char>(new unsigned char[session->packet.header.data_size], std::default_delete<unsigned char[]>());

		// asynchronously receive packet data.
		session->socket->async_receive(buffer((char*)session->packet.data.buffer.get(), session->packet.header.data_size),
			boost::bind(&Client::receive_data_handler, this, boost::placeholders::_1, boost::placeholders::_2, session));
	}
	// completion handler for connect request.
	// 1. check whether error occur or not.
	// 2. notify result of connect request.
	// 3. start next operation : receive & send
	void connect_handler(const boost::system::error_code& e, std::shared_ptr<Session>& session) {
		// check whether error occur or not.
		if (e.value() != 0) {
			std::cerr << "CONNECT ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}

		// notify result of connect request
		const ip::tcp::endpoint& remote = session->socket->remote_endpoint();
		const ip::tcp::endpoint& local = session->socket->local_endpoint();
		std::cout << "successfully connected." << std::endl;
		std::cout << "local[" << local.address().to_string() << ":" << local.port() << "]----"
			<< "remote[" << remote.address().to_string() << ":" << remote.port() << "]" << std::endl;

		// start next operation : receive & send.
		receive_internal(session);

		send_internal(session);
	}
	void receive_header_handler(const boost::system::error_code& e, std::size_t read_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "RECEIVE HEADER ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}
		
		// notify
		std::cout << read_size << "bytes header received." << std::endl;

		// receive data
		receive_data(session);
	}
	void receive_data_handler(const boost::system::error_code& e, std::size_t read_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "RECEIVE DATA ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}

		// notify
		const ip::tcp::endpoint& remote = session->socket->remote_endpoint();
		std::cout << read_size << "bytes data received." << std::endl;
		std::string msg(session->packet.data.buffer.get(), session->packet.data.buffer.get() + session->packet.header.data_size);
		std::cout << remote.address().to_string() << ":" << remote.port() << "> " << msg << std::endl;

		// receive another packet.
		receive_internal(session);
	}
	void send_header_handler(const boost::system::error_code& e, std::size_t send_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "SEND HEADER ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}

		// notify
		std::cout << "HEADER SENT" << std::endl;
		
		// send data
		send_data(session);
	}
	void send_data_handler(const boost::system::error_code& e, std::size_t send_size, std::shared_ptr<Session>& session) {
		if (e.value() != 0) {
			std::cerr << "SEND DATA ERROR[" << e.value() << "] " << e.message() << std::endl;
			return;
		}

		// notify
		std::cout << "DATA SENT" << std::endl;

		// dequeue message.
		messageQueue.pop();

		// send another message.
		send_internal(session);
	}
protected :
	io_service& ios_;
	std::shared_ptr<Session> session_;
	std::queue<Packet> messageQueue;
};
int main(void) {

	io_service ios;

	std::string server_ip_address("127.0.0.1");
	unsigned short server_port(33333);

	Client client(ios);

	client.connect(server_ip_address, server_port);

	std::thread t([&]() {
		std::string message;
		do {
			std::cout << "> ";
			std::getline(std::cin, message);

			client.send(message);

		} while (message != "quit");

		client.close();
	});

	ios.run();

	t.join();

	return 0;
}