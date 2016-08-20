#define _WIN32_WINNT 0x0601
#include <string>
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

struct Session {
	std::shared_ptr<boost::asio::ip::tcp::socket> socket;
};
class Client {
public :
	Client(boost::asio::io_service& ios) : ios_(ios) {
	}
	template<typename completionHandler>
	void connect(const std::string& raw_ip_address, const unsigned short& port_num, completionHandler& handler) {
		// required element to connection request.
		// endpoint - server
		// socket - client, myself, must be alive for connect operation complete.
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
		std::shared_ptr<boost::asio::ip::tcp::socket> sock(std::make_shared<boost::asio::ip::tcp::socket>(ios_));
		session_ = std::make_shared<Session>();
		session_->socket = sock;

		std::cout << "try to connect " << ep.address().to_string() << ":" << ep.port() << std::endl;
		sock->async_connect(ep, boost::bind<void>(handler, boost::placeholders::_1, session_));
	}
	void close() {

	}
	void send(const std::string& message) {
		send_header(message);
		send_data(message);
	}
	void receive() {
		receive_header();
		receive_data();
	}
protected :
	void send_header(const std::string& message) {

	}
	void send_data(const std::string& message) {

	}
	void receive_header() {

	}
	void receive_data() {

	}
protected :
	boost::asio::io_service& ios_;
	std::shared_ptr<Session> session_;
};
int main(void) {

	boost::asio::io_service ios;


	std::string server_ip_address("127.0.0.1");
	unsigned short server_port(33333);

	try {
		Client client(ios);

		client.connect(server_ip_address, server_port, [&](boost::system::error_code e, std::shared_ptr<Session>& s) { 
			if (e.value() != 0) {
				throw e;
			}
			std::cout << "successfully connected to " << s->socket->remote_endpoint().address().to_string() << ":" << s->socket->remote_endpoint().port() << std::endl;

			client.receive(); 

			std::string message;
			do {
				std::cout << "> ";
				std::getline(std::cin, message);

				client.send(message);

			} while (message != "quit");
		});

		client.close();
		ios.run();
	}
	catch (boost::system::error_code& e) {
		std::cerr << "ERROR[" << e.value() << "] " << e.message() << std::endl;
		return e.value();
	}

	return 0;
}