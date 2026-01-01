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
#include<fstream>
#include<unordered_map>

namespace http{
	class tcpserver{
		public:
			tcpserver(std::string ip_address, int port);
			
			
		private:
			int m_sock;
			char m_buff[5024];
			std::unordered_map<std::string,std::string> m_paths={{"/","/index.html"},{"/index","/index.html"},{"/favicon.ico"," "},{"405","/405.html"},{"404","/404.html"},{"400","/400.html"}};
			struct sockaddr_in m_address;
			void assign(std::string address,int port);
			int create_sock();
			std::string m_msg;
			//std::string process(const std::string& msg);
			//std::string GET(const std::string& msg);
			void loop();
	};
}

#endif
