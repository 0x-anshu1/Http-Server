#pragma once
#define PROCESS_H
#include<string>
#include<cstring>
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<utility>

struct http_tokens{
	std::string method;
	std::string path;
	std::string version;
};
std::pair<int,std::string> process(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
std::string GET(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
std::string errormsg(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
http_tokens parser(const std::string&msg);
