#include<fstream>
#include<iostream>
#include<string>


#ifndef GENERAL_UTILS
#define GENERAL_UTILS

void static LOG_MESS(char *message) {
	std::cout << message << std::endl;
}
#define LOG(m) LOG_MESS(m)

bool static ReadFile(std::string filename,std::string&content ) {
using namespace std;
	std::ifstream in(filename);
	std::string buffer;
	if (!in.is_open()) {
		LOG("file doesn' exist");
		return false;
	}
	while(!in.eof()){
		getline(in, buffer);
		content += buffer;
		content += '\n';
	}
	return true;

}

#endif