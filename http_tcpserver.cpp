#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<utility>

#include"http_tcpserver.h"
#include"http_process.h"

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
	}

	while(true){
		loop();
	}

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
	}

	ssize_t i = recv(lsock,m_buff,sizeof(m_buff),0);
	if(i<0){
		perror("recv");
		cerr<<"Error: Recv Problem"<<endl;
	}
	m_buff[i]='\0';
	//std::cout<<m_buff<<std::endl;	
	std::pair<int,std::string> msg=process(m_buff,m_paths);
	if(msg.second== "."){
		close(lsock);
		return;
	}
	
	switch(msg.first){
		case 400:
			m_msg="HTTP/1.1 400 BAD REQUEST\r\nContent-Type: text/html\r\nContent-Length: ";
			break;
		case 404:
			m_msg="HTTP/1.1 404 NOT FOUND\r\nContent-Type: text/html\r\nContent-Length: ";
			break;
		case 405:
			m_msg="HTTP/1.1 405 METHOD NOT ALLOWED\r\nContent-Type: text/html\r\nContent-Length: ";
			break;
		case 500:
			m_msg="HTTP/1.1 500 INTERNAL SERVER ERROR\r\nContent-Type: text/html\r\nContent-Length: ";
			break;
		default:
			m_msg="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
			break;
	}
	size_t size = msg.second.size();
	msg.second = "\r\n\r\n"+msg.second;
	msg.second = std::to_string(size)+msg.second;
	m_msg+=msg.second;
	i = send(lsock,m_msg.c_str(),m_msg.size(),0);
	if(i<=0){
		perror("send");
		cerr<<"Error: Send Problem"<<endl;
	}


	memset(m_buff,0,sizeof(m_buff));
	close(lsock);
}
