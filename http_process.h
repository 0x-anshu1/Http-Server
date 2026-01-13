#pragma once
#define PROCESS_H
#include<string>
#include<cstring>
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<utility>

struct http_return{
    int status_code;
    std::string file_size;
    std::string file_path;
};
struct http_tokens{
	std::string method;
	std::string path;
	std::string version;
};
http_return process(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
std::string GET(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
std::string errormsg(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
http_tokens parser(const std::string&msg);
