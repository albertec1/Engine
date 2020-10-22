#pragma once
										
#include "Globals.h"
#include <string>
#include <vector>

class aiScene;
class aiMesh;

class Importer
{
public:
    Importer();

    ~Importer();

    bool LoadScene(const std::string& filename, std::vector<uint> mesh_array);
    
private:
    bool InitMaterials(const aiScene* pScene, const std::string& Filename); //for textures; not using this yet
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    std::vector<uint> m_Entries; //MeshEntries vector. 
    std::vector<uint> m_Textures; //Texturs vector. These textures can be shared between MeshEntries using the texture index.
};

struct MeshEntry { //Each struct corresponds to one mesh structure in the aiScene object.

    uint id_index = 0; // index in VRAM
    uint num_index = 0;
    uint* index = nullptr;

    uint id_vertex = 0; // unique vertex in VRAM
    uint num_vertex = 0;
    float* vertex = nullptr;

    unsigned int MaterialIndex; //For now, a material is simply a texture and since mesh entries can share materials, 
                                //we have a separate vector for them (m_Textures).
                                //MeshEntry::MaterialIndex points into one of the textures in m_Textures.
};