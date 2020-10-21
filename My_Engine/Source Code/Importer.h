#pragma once
										
#include "Globals.h"
#include <string>
#include <vector>
#include <gl/GL.h>
#include <gl/GLU.h>

class aiScene;
class aiMesh;

class Mesh
{
public:
    Mesh();

    ~Mesh();

    bool LoadMesh(const std::string& Filename);

    void Render();

private:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry { //Each struct corresponds to one mesh structure in the aiScene object.
        MeshEntry();

        ~MeshEntry();

        bool Init(const std::vector<int>& Vertices,
            const std::vector<int>& Indices);

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

    std::vector<uint> m_Entries; //MeshEntries vector. 
    std::vector<uint> m_Textures; //Texturs vector. These textures can be shared between MeshEntries using the texture index.
};


