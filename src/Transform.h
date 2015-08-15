//
// Created by lejonmcgowan on 8/11/15.
//

#ifndef TESTPROJECT2_TRANSFORM_H
#define TESTPROJECT2_TRANSFORM_H


#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
private:
    glm::mat4 transform;
    bool

    glm::vec3 rotation;
    glm::vec3 position;
    glm::vec3 scale;
public:
    glm::mat4 getTransformMatrix(){ return };

    const glm::vec3 &getRotation() const
    {
        return rotation;
    }

    void setRotation(const glm::vec3 &rotation)
    {
        Transform::rotation = rotation;
    }

    const glm::vec3 &getPosition() const
    {
        return position;
    }

    void setPosition(const glm::vec3 &position)
    {
        Transform::position = position;
    }

    const glm::vec3 &getScale() const
    {
        return scale;
    }

    void setScale(const glm::vec3 &scale)
    {
        Transform::scale = scale;
    }


};


#endif //TESTPROJECT2_TRANSFORM_H
