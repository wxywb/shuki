#pragma once
#include<ShukiShader.h>
#ifndef SHUKITECHNIQUE_H
#define SHUKITECHNIQUE_H
namespace shuki {

class Technique {

public:
    Technique(ShaderManger *shader_manager);

private:
    ShaderManger * shader_manager;
};
}

#endif