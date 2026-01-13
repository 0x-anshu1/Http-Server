# HTTP-Server: Static file server

## A functioning http-server built in c++ and linux sockets, process GET request to server static file.

This is a project that was built in order to understand HTTP protocol and working of an HTTP-server. This project is built without any use of external HTTP-libraries or framework and only linux sockets(sys/socket.h,unistd.h etc..) are used.
Features:
* HTTP request parsing
* Static file serving
* error handling for 400,404,405,500
* File serving: >first packet conatins HTTP header.
                >following packets stream raw file bytes.
* Hash table based routing for O(1) look up
* Binary file support

![alt text](image.png)

# How to install and run this project
## Requirements: Linux or wsl, g++ with c++17 support

1. Clone this project
2. open the project directory in a terminal
3. compile using:
```bash
g++ main.cpp http_tcpserver.cpp http_process.cc -o main
```
4. start the server using:
```bash
./main
```
note: The server will work on http://127.0.0.1:8000/ on the same machine.

# Example test requests
1. ```bash 
    http://127.0.0.1:8000/ 
```
This goes to index page.