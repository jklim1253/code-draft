#pragma once
#include <memory>

template<typename Header, typename Data>
struct PacketBase {
	Header header;
	Data data;
};
template<typename SocketType, typename Data>
class Session {
	std::shared_ptr<SocketType> _socket;
	std::shared_ptr<Data> _in_packet;
	std::shared_ptr<Data> _out_packet;
public :
	std::shared_ptr<SocketType>& socket(std::shared_ptr<SocketType>& sock) {
		_socket = sock;
	}
	std::shared_ptr<SocketType>& socket() {
		return _socket;
	}
	std::shared_ptr<Data>& in_packet(std::shared_ptr<Data>& packet) {
		_in_packet = packet;
	}
	std::shared_ptr<Data>& in_packet() {
		return _in_packet;
	}
	std::shared_ptr<Data>& out_packet(std::shared_ptr<Data>& packet) {
		_out_packet = packet;
	}
	std::shared_ptr<Data>& out_packet() {
		return _out_packet;
	}
private :
	
};