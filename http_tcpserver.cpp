#include<iostream>
#include<string>

#include"http_tcpserver.h"

using namespace std;
using namespace http;

tcpserver::tcpserver(std::string ip_address, int port){
	if(create_sock()==1){
		cerr<<"Error: Create Socket"<<endl;
		exit(EXIT_FAILURE);
	}

	assign(ip_address,port);
	if(bind(m_sock,(struct sockaddr*)&m_address,sizeof(m_address))<0){
			cerr<<"Error: Bind Unsuccessful"<<endl;
			perror("Bind");
			exit(EXIT_FAILURE);
	}

	if(listen(m_sock,5)<0){
		perror("listen");
		cerr<<"Error: Listen Unsuccessful"<<endl;
		exit(EXIT_FAILURE);
	}

	while(true){
		loop();
	}

}
tcpserver::~tcpserver(){
	close(m_sock);
	//close(m_lsock);
}

void tcpserver::assign(std::string address,int port){
	m_address.sin_family = AF_INET;
	m_address.sin_port = htons(port);
	if(inet_pton(AF_INET,address.c_str(),&m_address.sin_addr)!=1){
		perror("inet_pton");
		cerr<<"Error: Inet_pton Unsuccessful"<<endl;
		exit(EXIT_FAILURE);
	}
}

int tcpserver::create_sock(){
	m_sock = socket(AF_INET,SOCK_STREAM,0);
	if(m_sock<0){
		return 1;
	}
	return 0;
}

void tcpserver::loop(){
	int lsock = accept(m_sock,NULL,NULL);
	if(lsock<0){
		perror("accept");
		cerr<<"Error: Accept Problem."<<endl;
		exit(EXIT_FAILURE);
	}

	ssize_t i = recv(lsock,m_buff,sizeof(m_buff),0);
	if(i<=0){
		perror("recv");
		cerr<<"Error: Recv Problem"<<endl;
		exit(EXIT_FAILURE);
	}

	m_msg = process(m_buff);
	i = send(lsock,m_msg.c_str(),m_msg.size(),0);
	if(i<=0){
		perror("send");
		cerr<<"Error: Send Problem"<<endl;
		exit(EXIT_FAILURE);
	}

	close(lsock);
}
