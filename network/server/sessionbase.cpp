#include "sessionbase.h"

ip::tcp::endpoint SessionBase::local() const {
	return _socket->local_endpoint();
}
ip::tcp::endpoint SessionBase::remote() const {
	return _socket->remote_endpoint();
}
std::shared_ptr<SessionBase::socketType>& SessionBase::socket() {
	return _socket;
}