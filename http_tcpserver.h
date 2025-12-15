#pragma once
#ifndef HTTP_TCPSERVER_H
#define HTTP_TCPSERVER_H

#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

namespace http{
	class tcpserver{
		public:
			tcpserver(struct sockaddr_in );
			~tcpserver();
			
			
		private:
			int m_soc;
			struct sockaddr_in m_address;
			int create_sock();
			void close_sock();
	}
}
