server

010. port number
050. acceptor.listen

090. prepare session(need to manage).
099. prepare socket(need to manage).
100. acceptor.async_accept

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

Session
	- socket
	- mutable_buffer
	- const_buffer
	- time record of read
	- time record of write
	- validate header
	- process data buffer
	- local endpoint
	- remote endpoint
