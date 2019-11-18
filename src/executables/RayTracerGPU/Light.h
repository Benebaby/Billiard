#pragma once
#include <Tools/Defs.h>

class Light
{
private:
    glm::vec3 m_Pos;
    float pad;
    glm::vec3 m_Color;
    int m_Type;

public:
    Light();
    Light(int type, glm::vec3 pos, glm::vec3 color);
};