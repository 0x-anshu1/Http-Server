#pragma once
#ifndef HTTP_TCPSERVER_H
#define HTTP_TCPSERVER_H

#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>
#include<string>
#include<cstdlib>

namespace http{
	class tcpserver{
		public:
			tcpserver(std::string ip_address, int port);
			~tcpserver();
			
			
		private:
			int m_sock;
			char m_buff[5024];
			struct sockaddr_in m_address;
			void assign(std::string address,int port);
			int create_sock();
			std::string m_msg;
			std::string process(char& msg);
	};
}
