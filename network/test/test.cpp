#include <iostream>
#include <memory>

struct Receiver {
	virtual void prepare_header_buffer() = 0;
	virtual void prepare_data_buffer() = 0;
	virtual void process_header() = 0;
	virtual void process_data() = 0;
};
struct WebReceiver : public Receiver {
	void prepare_header_buffer() {
	}
};
struct Sender {
};
struct WebSender : public Sender {
};
struct SessionBase {
	int a;

	SessionBase() :a(0) {}

	virtual void foo() = 0;
	void setA(int _a) {
		a = _a;
	}

	std::shared_ptr<Receiver> receiver;
	std::shared_ptr<Sender> sender;
};

struct WebSession : public SessionBase {

	virtual void foo() {
		std::cout << a << "WebSession::foo called." << std::endl;
	}
};

struct SessionCreator {
	virtual std::shared_ptr<SessionBase> create() = 0;
};
struct WebSessionCreator : public SessionCreator {
	virtual std::shared_ptr<SessionBase> create() {
		return std::make_shared<WebSession>();
	}
};


struct Server {
	void setSessionCreator(std::shared_ptr<SessionCreator> creator) {
		_creator = creator;
	}
	void useSession() {
		std::shared_ptr<SessionBase> session = _creator->create();
		session->foo();
	}
	std::shared_ptr<SessionCreator> _creator;
};

int main() {

	Server webserver;
	webserver.setSessionCreator(std::make_shared<WebSessionCreator>());

	webserver.useSession();

	return 0;
}
