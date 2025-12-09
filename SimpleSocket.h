#pragma once
#define SimpleSocket_h

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

namespace HDE{
    class SimpleSocket{
        public:
        SimpleSocket(int domain,int service,int protocol,int port,unsigned long interface);
	virtual int connect_to_network(int sock,struct sockaddr_in address) = 0;
	void test_connection(int item);
	struct sockaddr_in get_address();
	int get_sock();
	int get_connection();

	private:
	struct sockaddr_in address;
	int sock;
	int connection;
    };
}
