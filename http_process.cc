#include"http_process.h"
#include<unordered_map>

std::string process(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	std::string method,path;
	int i=0;
	while(msg[i]!=' '){
		method+=msg[i];
		++i;
	}
	if(method!="GET"){
		std::cerr<<"Method is not get."<<std::endl;
	}
	i+=1;
	while(msg[i]!=' '){
		path+=msg[i];
		++i;
	}
	if(path == "/favicon.ico"){
		return ".";
	}
	if(mp.find(path)==mp.end()){
		std::cerr<<"Invalid Path"<<std::endl;
		return "404";
	}
	return GET(path,mp);
}

std::string GET(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	std::string file="path_file";
	if(msg=="/") file+="/index.html";
	else file+=mp[msg];
	
	std::ifstream in(file);
	std::stringstream s;
	s<<in.rdbuf();

	std::string r = s.str();
	in.close();
	return r;
}

