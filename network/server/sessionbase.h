#pragma once
#define _WIN32_WINNT 0x0601
#include <boost/asio.hpp>
using namespace boost::asio;

class SessionBase {
public :
	typedef ip::tcp::socket socketType;
protected :
	std::shared_ptr<socketType> _socket;
	mutable_buffer _in_packet;
	const_buffer _out_packet;
	time_t _last_read_time;
	time_t _last_write_time;
public :
	// receive part.
	virtual void prepare_header_buffer() = 0;
	virtual bool validate_header() = 0;
	virtual void prepare_data_buffer() = 0;
	virtual void process_received_data() = 0;
	// send part.
	virtual void process_send_data() = 0;
	virtual void prepare_send_buffer() = 0;
	virtual void notify_sent_result() = 0;
	// utility.
	inline ip::tcp::endpoint local() const;
	inline ip::tcp::endpoint remote() const;
	std::shared_ptr<socketType>& socket();
	// buffer relative
	// receive buffer
	virtual mutable_buffer& header() = 0;
	virtual mutable_buffer& data() = 0;
	// send buffer
	virtual const_buffer& out_packet() = 0;
};

struct SessionCreator {
	virtual std::shared_ptr<SessionBase> create() = 0;
};

template<typename Derived>
struct SessionCreatorTemplate : public SessionCreator {
	virtual std::shared_ptr<SessionBase> create() {
		return std::make_shared<Derived>();
	}
};