#include"SimpleSocket.h"

using namespace std;

//Default constructor
HDE::SimpleSocket::SimpleSocket(int domain,int service,int protocol,int port,unsigned long interface){
	//Create a Socket
	sock = socket(domain,service,protocol);
	//Define address structure
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);
	test_connection(sock);
	//Establish conenction
	connection = connect_to_network(sock,address);
	test_connection(sock);
}

//Error check
void HDE::SimpleSocket::test_connection(int item){
	if(item<0){
		perror("Failed to connect..");
		exit(EXIT_FAILURE);
	}
	return ;
}

//Getter for different private variables
struct sockaddr_in HDE::SimpleSocket::get_address(){
	return address;
}

int HDE::SimpleSocket::get_sock(){
	return sock;
}

int HDE::SimpleSocket::get_connection(){
	return connection;
}
