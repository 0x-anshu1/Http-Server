#include"http_process.h"
#include<unordered_map>
#include<utility>

http_return process(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	http_tokens req = parser(msg);
	
	if(req.version!="HTTP/1.1" && req.version!="HTTP/1.0") return {400,errormsg("400",mp),"/error/400.html"};
	if(req.method!="GET") return {405,errormsg("405",mp),"/error/405.html"};
	if(req.path == "/favicon.ico"){
		return {0,"."};
	}
	if(mp.find(req.path)==mp.end()){
		std::cerr<<"Invalid Path"<<std::endl;
		return {404,errormsg("404",mp),"/error/404.hml"};
	}
	return {200,GET(req.path,mp),mp[req.path]};
}

std::string GET(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	std::string file="path_file";
	if(msg=="/") file+="/index.html";
	else file+=mp[msg];
	
	std::ifstream in(file,std::ios::binary);
    std::streamsize i;
    if(in){
        in.seekg(0,std::ios::end);
        i=in.tellg();
    }
    /*
	//std::stringstream s;
	//s<<in.rdbuf();

	std::string r = s.str();*/
	in.close();
	return std::to_string(i);
}

std::string errormsg(const std::string&msg,std::unordered_map<std::string,std::string>&mp){
	std::string file="path_file/error";
	if(msg=="405") file+=mp[msg];
	else if(msg=="404") file+=mp[msg];
	else if(msg=="400") file+=mp[msg];
	std::ifstream in(file,std::ios::binary);
	if(in.is_open()){
        /*
		std::stringstream s;
		s<<in.rdbuf();
		std::string r = s.str();*/

        //std::cout<<"true"<<std::endl;
        in.seekg(0,std::ios::end);
        std::string r=std::to_string(in.tellg());
		in.close();
		return r;
	}
	return "<!DOCTYPE html>\n<html>\n<head>\n<title>Error 500</title>\n</head>\n<body>\n<h1>Error 500</h1>\n<p>Missing file.</p>\n</body></html>";
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
