#include<ShukiModel.h>
#include<general_utils.h>
#include<ShukiMath.h>
#include<ogl_basic.h>
#include<string>

namespace shuki
{

Model::Model(std::string & name_) 
{ 
    filename = name_; 
}
    
void 
Model::Init() 
{
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate 
                                                          | aiProcess_GenSmoothNormals
                                                          | aiProcess_FlipUVs
                                                          | aiProcess_CalcTangentSpace);

    if (!pScene) {
        LOG("The object file doesn't exist");
        return;
    }
  
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_buffers), m_buffers);
    InitfromScene(pScene);
    glBindVertexArray(0);

};

bool
Model::InitfromScene(const aiScene* pScene) 
{
    using namespace std;
    
    m_meshes.resize(pScene->mNumMeshes);
    m_diffuse_textures.resize(pScene->mNumMaterials);
    m_normal_textures.resize(pScene->mNumMaterials);
    std::vector<Vector3f>   positions;
    std::vector<Vector3f>   normals;
    std::vector<Vector2f>   texd_uvs;
    std::vector<Vector3f>   tangents;
    std::vector<unsigned int> indices;

    unsigned int NumVertices = 0;
    unsigned int NumIndices = 0;

    for (unsigned int i = 0; i < pScene->mNumMeshes; i++) 
    {
        m_meshes[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
        m_meshes[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
        m_meshes[i].BaseVertex = NumVertices;
        m_meshes[i].BaseIndex = NumIndices;

        NumVertices += pScene->mMeshes[i]->mNumVertices;
        NumIndices += m_meshes[i].NumIndices;
    
    }

    positions.reserve(NumVertices);
    normals.reserve(NumVertices);
    texd_uvs.reserve(NumVertices);
    tangents.reserve(NumVertices);
    indices.reserve(NumIndices);

    for (unsigned int i = 0; i < m_meshes.size(); i++) 
    {
        const aiMesh* pmesh = pScene->mMeshes[i];
        InitMesh(pmesh, positions, normals, texd_uvs, indices, tangents);
    }


    if (pScene->mNumMaterials &&!InitMaterials(pScene, filename)) {
        return false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_POS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_TEXCORD]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texd_uvs[0]) * texd_uvs.size(), &texd_uvs[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_NORMAL]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[BUFFER_INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
   
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_TANGENT]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tangents[0]) * tangents.size(), &tangents[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TANGENT_LOCATION);
    glVertexAttribPointer(TANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    return GLCheckError();
}

void 
Model::InitMesh(const aiMesh * pMesh, 
                std::vector<Vector3f> &positions,
                std::vector<Vector3f> &normals, 
                std::vector<Vector2f> &texd_uvs,
                std::vector<unsigned int> &indices,
                std::vector<Vector3f> &tangents)
{

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    for (unsigned int i = 0; i < pMesh->mNumVertices; i++) {
        auto pPos           = &(pMesh->mVertices[i]);
        auto pNormal        = &(pMesh->mNormals[i]);
        auto pTexUV = pMesh->HasTextureCoords(0) ? &(pMesh->mTextureCoords[0][i]) : &Zero3D;
        auto pTangent       = &(pMesh->mTangents[i]);
        positions.push_back(Vector3f(pPos->x, pPos->y, pPos->z));
        normals.push_back(Vector3f(pNormal->x,pNormal->y,pNormal->z));
        texd_uvs.push_back(Vector2f(pTexUV->x, pTexUV->y));
        tangents.push_back(Vector3f(pTangent->x, pTangent->y, pTangent->z));
    }

    for (unsigned int i = 0; i < pMesh->mNumFaces; i ++) {
        const aiFace & face = pMesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

}


bool 
Model::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;


    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool Ret = true;

    // Initialize the materials
    for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        m_diffuse_textures[i] = NULL;
        m_normal_textures[i] = NULL;
        using namespace std;
        if (pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0) {
            aiString Path;
            if (pMaterial->GetTexture(aiTextureType_NORMALS, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string p(Path.data);

                if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }

                std::string FullPath = Dir + "/" + p;

                m_normal_textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!m_normal_textures[i]->Load()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_normal_textures[i];
                    m_normal_textures[i] = NULL;
              //      Ret = false;
                }
                else {
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }
            }
        }
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string p(Path.data);

                if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }

                std::string FullPath = Dir + "/" + p;

                m_diffuse_textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!m_diffuse_textures[i]->Load()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_diffuse_textures[i];
                    m_diffuse_textures[i] = NULL;
                    Ret = false;
                }
                else {
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }
            }
        }
    }

    return Ret;
}

void 
Model::Render() {
    glBindVertexArray(m_vao);
    for (unsigned int i = 0; i < m_meshes.size(); i++) {
        const unsigned int MaterialIndex = m_meshes[i].MaterialIndex;

        //_ASSERT(MaterialIndex < m_textures.size());
  


        if (m_diffuse_textures[MaterialIndex]) {
            m_diffuse_textures[MaterialIndex]->Bind(COLOR_TEXTURE_UNIT);
        }
        if (m_normal_textures[MaterialIndex]) {
            m_normal_textures[MaterialIndex]->Bind(NORMAL_TEXTURE_UNIT);
        }

        glDrawElementsBaseVertex(GL_TRIANGLES,
            m_meshes[i].NumIndices,
            GL_UNSIGNED_INT,
            (void*)(sizeof(unsigned int) * m_meshes[i].BaseIndex),
            m_meshes[i].BaseVertex);
    }

    // Make sure the VAO is not changed from the outside    
    glBindVertexArray(0);
}


//RenderwithoutTexuture is special for the purpose that render a
//plane for display the content of the previou shader's output.
void
Model::RenderwithoutTexture() {
    glBindVertexArray(m_vao);
    for (unsigned int i = 0; i < m_meshes.size(); i++) {
        glDrawElementsBaseVertex(GL_TRIANGLES,
            m_meshes[i].NumIndices,
            GL_UNSIGNED_INT,
            (void*)(sizeof(unsigned int) * m_meshes[i].BaseIndex),
            m_meshes[i].BaseVertex);
    }

    // Make sure the VAO is not changed from the outside    
    glBindVertexArray(0);
}
}