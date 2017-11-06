#include<ShukiModel.h>

namespace shuki
{

Model::Model(std::string & name_) 
{ 
    name = name_; 
}
    
void 
Model::Init() 
{
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(name.c_str(), aiProcess_Triangulate 
                                                          | aiProcess_GenSmoothNormals
                                                          | aiProcess_FlipUVs);
};

}