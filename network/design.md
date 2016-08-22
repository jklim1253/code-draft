server procedure

010. prepare acceptor
	- 011. endpoint
		- 012. port number
		- 013. protocol type(tcp, udp, icmp)
	- 015. backlog
050. acceptor.listen

	- 090. prepare session(need to manage).
	- 099. prepare socket(need to manage).
100. acceptor.async_accept(operation accept)

	- 110. prepare mutable_buffer(header buffer) - at Session
	- 120. socket.async_receive(header receive)
		- 121. validate header. - at Session
		- 122. prepare mutable_buffer(data buffer) - at Session
		- 123. socket.async_receive(data receive)
			- 125. socket.async_receive
			- 126. process data buffer - at Session

	- 139. prepare data to send. - at Session
	- 140. prepare const_buffer(header, data) - at Session
	- 150. socket.async_send
400. socket.shutdown
410. socket.close

Requirement
Server
	- boost::asio::io_service(noncopyable)
	- boost::asio::ip::tcp::acceptor
	- port number(configurable)
	- backlog(configurable, optional)

Session
	- socket
	- mutable_buffer
	- const_buffer
	- last record of read
	- last record of write
	- local endpoint
	- remote endpoint
	- prepare header buffer.
	- validate header
	- prepare data buffer.
	- process received data.
	- process send data.
	- prepare send buffer.
