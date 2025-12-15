#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#include"http_tcpserver.h"

using namespace std;
using namespace http;

int tcpserver::create_sock(){
	m_soc = socket(AF_INET,SOCK_STREAM,0);
	if(soc<0){
		perror("SOCKET");
		return 1;
	}
	return 0;
}
void tcpserver::close_sock(){
	close(m_soc);
}
