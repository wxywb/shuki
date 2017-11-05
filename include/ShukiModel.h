#include<assimp\Importer.hpp>
#include<assimp\postprocess.h>
#include<ShukiTexture.h>
#include<Shuki.h>


#ifndef SHUKI_MODEL
#define SHUKI_MODEL

namespace shuki 
{
	

class _ModelChunk
{
  public:

    void load();
  
  private:
    std::string model_file;
    float * vertices_data;
    
  };

class Model {
  public:
    Model(std::string & name_);
    void Init();

  private:
    GLuint VB;
    GLuint IB;
    std::shared_ptr<_ModelChunk> _modeldata;
    std::string name;
  };

}

#endif // !SHUKI_MODEL