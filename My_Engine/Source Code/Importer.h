#pragma once
										
#include "Globals.h"
#include <string>
#include <vector>

class aiScene;
class aiMesh;

enum class BufferIndex
{
    VERTICES,
    NORMALS,
    TEX_COORDINATES
};

struct MeshEntry {

    uint num_indices = 0;
    uint* indices;
    //std::vector<uint> indices;

    uint num_vertices = 0;
    float* vertices ;
   //std::vector<float*> vertices;

    uint num_normals = 0;
    float* normals = nullptr;
    
    uint num_tex_coords = 0;
    float* texture_coords = nullptr;

    //vertex array object to hold all buffers
    uint VAO = 0;
    //buffers
    uint b_indices;
    uint b_vertices;
    uint b_normals;
    uint b_texture_coords;

    //unsigned int MaterialIndex;   //For now, a material is simply a texture and since mesh entries can share materials, 
                                    //we have a separate vector for them (m_Textures).
                                    //MeshEntry::MaterialIndex points into one of the textures in m_Textures.
};

class Importer
{
public:
    Importer();

    ~Importer();

    MeshEntry* ImportMesh(const aiScene* scene, int i);
    MeshEntry* LoadScene(const std::string& filename);


private:
    bool InitMaterials(const aiScene* pScene, const std::string& Filename); //for textures; not using this yet
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    std::vector<uint> m_Textures; //Texturs vector. These textures can be shared between MeshEntries using the texture index.
};