#include<fstream>
#include<iostream>
#include<string>


#ifndef GENERAL_UTILS
#define GENERAL_UTILS




#define LOG(m) LOG_MESS(m)
#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))


void static 
LOG_MESS(char *message) {
	std::cout << message << std::endl;
}


bool 
static ReadFile(std::string filename,std::string&content ) {
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