#pragma once

struct TcpServerImpl;
class TcpServer {
public :
	TcpServer();
	virtual ~TcpServer();

	void open(unsigned short port_num, int MAXCON = 0x7fffffff);

	void run();

private :
	TcpServerImpl* impl;
};