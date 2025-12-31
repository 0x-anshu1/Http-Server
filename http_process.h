#pragma once
#define PROCESS_H
#include<string>
#include<cstring>
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<sstream>

std::string process(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
std::string GET(const std::string&msg,std::unordered_map<std::string,std::string>&mp);
