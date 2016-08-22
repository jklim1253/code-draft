#include <iostream>
#include <memory>

struct SessionBase {
	int a;

	SessionBase() :a(0) {}

	virtual void foo() = 0;
	void setA(int _a) {
		a = _a;
	}
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