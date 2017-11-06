#include<ShukiModel.h>
#include<general_utils.h>
namespace shuki
{

Model::Model(std::string & name_) 
{ 
    name = name_; 
   //m_vao = 0;
   // m_buffers = 0;
}
    
void 
Model::Init() 
{
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(name.c_str(), aiProcess_Triangulate 
                                                          | aiProcess_GenSmoothNormals
                                                          | aiProcess_FlipUVs);

    if (!pScene) {
        LOG("The object file doesn't exist");
        return;
    }

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_buffers), m_buffers);

    glBindVertexArray(0);

};




}