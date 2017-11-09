/* -*- mode: c++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
#include<Shuki.h>
#include<ogl_basic.h>
#include"general_utils.h"

#ifndef SHADER_HPP
#define SHADER_HPP

namespace shuki {

static GLchar ErrorLog[1024] = { 0 };


class Shader {
  public:
    Shader() {}	
  
    bool initialize_shaders();
  
    GLenum 					mshader_type;
    GLuint 					mshader;
    ::std::string 		    filename;
};

class ShaderManger {
  public:
  
    ShaderManger() {}

    void init_program();

    ShaderManger &setVSFile(std::string vsfilename_);

    ShaderManger &setFSFile(std::string fsfilename_);

    ShaderManger &setDir(std::string dir_name_);
    
	~ShaderManger() {};
    
    ShaderManger &initialize();
    
    void attach_shaders();
    
    void use();

    GLuint getprogram();

  private:

    std::string 					dir;
    const char * 					vsfilename;
    const char * 					fsfilename;
    std::vector<Shader> 			mshaders;
    GLuint 							mshaderprogram;
};

}

#endif