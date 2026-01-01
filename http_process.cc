#include"http_process.h"
#include<unordered_map>

std::string process(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	http_tokens req = parser(msg);
	
	if(req.version!="HTTP/1.1" && req.version!="HTTP/1.0") return errormsg("400",mp);
	if(req.method!="GET") return errormsg("405",mp);
	if(req.path == "/favicon.ico"){
		return ".";
	}
	if(mp.find(req.path)==mp.end()){
		std::cerr<<"Invalid Path"<<std::endl;
		return errormsg("404",mp);
	}
	return GET(req.path,mp);
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

std::string errormsg(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	std::string file="path_file/error";
	if(msg=="405") file+="/405.html";
	else if(msg=="404") file+="/404.html";
	else if(msg=="400") file+="/400.html";

	std::fstream in(file);
	std::stringstream s;
	s<<in.rdbuf();

	std::string r = s.str();
	in.close();
	return r;
}

http_tokens parser(const std::string&msg){
	http_tokens req;
	std::stringstream ss(msg);
	std::string l1;
	std::string ch;

	if(std::getline(ss,l1)){
		std::stringstream sps(l1);

		sps>>req.method;
		sps>>req.path;
		sps>>req.version;
		sps>>ch;
	}
	if(!ch.empty() || req.method.empty() || req.path.empty() || req.version.empty()){
		req.version="400";
		std::cout<<"Error: 400"<<std::endl;
	}
	
	return req;
}
