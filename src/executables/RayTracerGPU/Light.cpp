#include "Light.h"

Light::Light(){
    m_Type = 0;
    m_Pos = glm::vec3(0.0f);
    m_Color = glm::vec3(0.0f);
}

Light::Light(int type, glm::vec3 pos, glm::vec3 color){
    m_Type = type;
    m_Pos = pos;
    m_Color = color;
}