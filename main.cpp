#include<iostream>

#include "http_tcpserver.h"

using namespace std;
using namespace http;

int main(){
	tcpserver server("127.0.0.1",8000);
	return 0;
}
