#include<iostream>
#include<string>
#include<sstream>
#include<cstring>

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
	}

	ssize_t i = recv(lsock,m_buff,sizeof(m_buff),0);
	if(i<0){
		perror("recv");
		cerr<<"Error: Recv Problem"<<endl;
	}
	m_buff[i]='\0';
	
	std::string msg=process(m_buff);
	if(msg == "."){
		close(lsock);
		return;
	}
	if(msg == "I"){
		std::cerr<<"Bad request received."<<std::endl;
		m_msg="HTTP/1.1 400 Bad Request\r\ncontent-Type: text/html\r\ncontent-Length: 58\r\n\r\n<h1>400 Bad Reqest</h1><p>your request is invalid.</p>";
		i=send(lsock,m_msg.c_str(),m_msg.size(),0);
		if(i<=0){
			std::cerr<<"Error: Send Problem."<<std::endl;
		}
		
	}
	
	m_msg="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
	size_t size = msg.size();
	msg = "\r\n\r\n"+msg;
	msg = std::to_string(size)+msg;
	m_msg+=msg;
	i = send(lsock,m_msg.c_str(),m_msg.size(),0);
	if(i<=0){
		perror("send");
		cerr<<"Error: Send Problem"<<endl;
	}


	memset(m_buff,0,sizeof(m_buff));
	close(lsock);
}


std::string tcpserver::process(const std::string &msg){
	std::string method="",path="";
	int i=0;
	while(msg[i]!=' '){
		method+=msg[i];
		++i;
	}
	if(method!="GET"){
		cerr<<"Error:  Method is not GET."<<endl;
	}

	i+=1;
	while(msg[i]!=' '){
		path+=msg[i];
		++i;
	}
	if(path == "/favicon.ico"){
		return ".";
	}
	if(m_paths.find(path) == m_paths.end()){
		std::cerr<<"Invalid path: "<<path<<std::endl;
		return "I";
	}
	return GET(path);
}

std::string tcpserver::GET(const std::string &msg){
	std::string file = "path_file";
	if(msg=="/")file+="/index.html";
	else file+=m_paths[msg];
	ifstream in(file);
	std::stringstream s;
	s<<in.rdbuf();
	std::string re = s.str();
	in.close();
	return re;
}
