//
// Created by magnus on 3/27/20.
//

#ifndef CPP_ENGINE_OBJECTS_H
#define CPP_ENGINE_OBJECTS_H

#include <vector>

class Objects {
public:

    typedef struct {
        float x, y, z;
    } Vertex;

    Objects();

    void generateCube();

    std::vector<Vertex> vertices;
    std::vector<int> indices;


    void cubeIndices();
};


Objects::Objects(){

}

void Objects::generateCube() {
    int j = 0;
    float width = 0;
    vertices.emplace_back();
    vertices[j].x = 0.5f;
    vertices[j].y = 0.5f;
    vertices[j].z = width;
    j++;
    vertices.emplace_back();
    vertices[j].x = 0.5f;
    vertices[j].y = -0.5f;
    vertices[j].z = width;
    j++;
    vertices.emplace_back();
    vertices[j].x = -0.5f;
    vertices[j].y = -0.5f;
    vertices[j].z = width;
    j++;
    vertices.emplace_back();
    vertices[j].x = -0.5f;
    vertices[j].y = 0.5f;
    vertices[j].z = width;

    width = -0.5f;
    j++;
    vertices.emplace_back();
    vertices[j].x = 0.5f;
    vertices[j].y = 0.5f;
    vertices[j].z = width;
    j++;
    vertices.emplace_back();
    vertices[j].x = 0.5f;
    vertices[j].y = -0.5f;
    vertices[j].z = width;
    j++;
    vertices.emplace_back();
    vertices[j].x = -0.5f;
    vertices[j].y = -0.5f;
    vertices[j].z = width;
    j++;
    vertices.emplace_back();
    vertices[j].x = -0.5f;
    vertices[j].y = 0.5f;
    vertices[j].z = width;


}

void Objects::cubeIndices(){

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

}



#endif //CPP_ENGINE_OBJECTS_H
