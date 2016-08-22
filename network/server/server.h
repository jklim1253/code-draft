#pragma once

struct SessionCreator;
struct TcpServerImpl;
class TcpServer {
public :
	TcpServer();
	virtual ~TcpServer();

	void setSessionCreator(std::shared_ptr<SessionCreator> creator);

	void open(unsigned short port_num, int MAXCON = 0x7fffffff);

	void run();

private :
	TcpServerImpl* impl;
};