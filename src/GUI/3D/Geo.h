#ifndef _OBJLOAD_H_
#define _OBJLOAD_H_

#include "array.h"

typedef struct{
    float x,y,z;
}Vec3D;

typedef struct{
    float u,v;
}Vec2D;

typedef struct{
    unsigned int IdVertex, IdNormal, IdTexCoord;
}Point;

typedef struct{
    Array points;
    unsigned int IdMaterial;
}Face;

typedef struct{
    Array vertices;
    Array normals;
    Array texCoords;
    Array faces;
    Array materials;
    GLuint vboVertices;
    GLuint vboNormals;
    GLuint vboTexCoords;
    GLuint *vboIndices;
    Array numIndices;
}Geo;

typedef struct{
    float r,g,b,a;
}RGBA;

typedef struct{
    char *name;
    char *texture;
    unsigned int texID;
    RGBA amb;
    RGBA dif;
    RGBA spe;
    int bright;
    int illum;
}Material;

// Esta funcion ha de ser llamada una vez el contexto de OpenGL este inicializado
Geo    GeoLoad(const char *filename);
void   GeoScale(Geo &geo, float s);
void   GeoClear(Geo &geo);
void   GeoDraw(const Geo &geo);
void   GeoCreateVBO(Geo &geo);

Array MtlLoad(const char *filename);
Array GetFace(char *line);

Material MatCreate(const char *name);
int      MatGetID(const Array &materials, char *name);
void     MatApply(const Material &mat);

void PrintMaterials(const Array &materials);

unsigned int LoadTexture(const char* filename);
void LoadTextures(Array &materials);
/*
class Geo {
public:
    Geo(const char *filename);
    ~Geo();
    
    void Scale(float s);
    void Draw();
    
private:
    int GetMatID(Array materiales, const char *name);
};
*/

#endif
