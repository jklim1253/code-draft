#pragma once

#include "sessionbase.h"

class TestSession : public SessionBase {
public :
	// receive part.
	virtual void prepare_header_buffer() { }
	virtual bool validate_header() { }
	virtual void prepare_data_buffer() {}
	virtual void process_received_data() {}
	// send part.
	virtual void process_send_data() {}
	virtual void prepare_send_buffer() {}
	virtual void notify_sent_result() {}
	// buffer relative
	// receive buffer
	virtual mutable_buffer& header() { return mutable_buffer(); }
	virtual mutable_buffer& data() { return mutable_buffer(); }
	// send buffer
	virtual const_buffer& out_packet() { return const_buffer(); }
};