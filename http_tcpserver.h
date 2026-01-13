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
            std::unordered_map<int,std::string> m_response={{400,"HTTP/1.1 400 BAD REQUEST\r\nContent-Type: text/html\r\nContent-Length: "},{404,"HTTP/1.1 404 NOT FOUND\r\nContent-Type: text/html\r\nContent-Length: "},{405,"HTTP/1.1 405 METHOD NOT ALLOWED\r\nContent-Type: text/html\r\nContent-Length: "},{200,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: "}};
            struct sockaddr_in m_address;
			void assign(std::string address,int port);
			int create_sock();
			std::string m_msg;
			void fsend(const std::string& msg,int lsock);
			//std::string GET(const std::string& msg);
			void loop();
	};
}

#endif
