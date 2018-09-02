#include<assimp\Importer.hpp>
#include<assimp\postprocess.h>
#include<assimp\scene.h>
#include<ShukiTexture.h>
#include<Shuki.h>
#include<ogl_basic.h>
#include<ShukiMath.h>


#ifndef SHUKI_MODEL
#define SHUKI_MODEL

namespace shuki 
{
	
#define POSITION_LOCATION 0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION 2
#define TANGENT_LOCATION 3
#define INVALID_MATERIAL 0xFFFFFFFF

struct Mesh {

    Mesh()
    {
        NumIndices = 0;
        BaseVertex = 0;
        BaseIndex = 0;
        MaterialIndex = INVALID_MATERIAL;
    }

    unsigned int NumIndices;
    unsigned int BaseVertex;
    unsigned int BaseIndex;
    unsigned int MaterialIndex;
};

class _ModelChunk
{
  public:

    void load();
  
  private:
    std::string model_file;
    float * vertices_data;
    
  };


#define BUFFER_INDEX        0
#define BUFFER_POS          1
#define BUFFER_NORMAL       2
#define BUFFER_TEXCORD      3
#define BUFFER_WVP_mat      4
#define BUFFER_TANGENT      5

class Model {
  public:
    Model(std::string & name_);

    void Init();

    bool InitfromScene(const aiScene * pScene);

    void InitMesh(const aiMesh * pMesh,
        std::vector<Vector3f> &positions,
        std::vector<Vector3f> &normals,
        std::vector<Vector2f> &texd_uvs,
        std::vector<unsigned int> &indices,
        std::vector<Vector3f> &tangents);

    bool InitMaterials(const aiScene * pScene, const std::string & Filename);

    void Render();

    void RenderwithoutTexture();
   


  private:
    GLuint m_vao;
    GLuint m_buffers[6];
    std::shared_ptr<_ModelChunk> _modeldata;
    std::string filename;

    std::vector<Mesh> m_meshes;
    std::vector<Texture*> m_diffuse_textures;
    std::vector<Texture*> m_normal_textures;
 //   std::vector<Texture >

  };

}

#endif // !SHUKI_MODEL