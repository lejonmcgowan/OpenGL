//
// Created by lejonmcgowan on 8/11/15.
//

#ifndef TESTPROJECT2_TRANSFORM_H
#define TESTPROJECT2_TRANSFORM_H

#define GLM_FORCE_RADIANS

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
class Transform
{
protected:
    glm::mat4 transform;

    glm::vec3 rotation;
    glm::vec3 translation;
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);

    bool updateTransform;
public:
    const glm::mat4& getTransformMatrix()
    {
        if(updateTransform)
        {
            transform = glm::mat4();
            transform *= glm::translate(glm::mat4(),translation);
            transform *= glm::toMat4(glm::quat(rotation));
            transform *= glm::scale(glm::mat4(),scale);

            updateTransform = false;
        }
        return transform;
    };

    const glm::vec3& getRotation() const
    {

        return rotation;
    }

    void rotateTo(glm::vec3& rotation)
    {
        updateTransform = true;
        this->rotation = rotation;
    }

    const glm::vec3& getTranslation() const
    {
        return translation;
    }

    void translateTo(glm::vec3& translation)
    {
        updateTransform = true;
        this->translation = translation;
    }

    const glm::vec3& getScale() const
    {
        return scale;
    }

    void scaleTo(glm::vec3& scale)
    {
        updateTransform = true;
        this->scale = scale;
    }

    void scaleBy(float factor)
    {
        updateTransform = true;
        this->scale *= factor;
    }

    void scaleBy(glm::vec3& factor)
    {
        updateTransform = true;
        this->scale += factor;
    }

    void scaleIncreaseBy(float factor)
    {
        updateTransform = true;
        scale.x += factor;
        scale.y += factor;
        scale.z += factor;
    }

    void scaleIncreaseBy(glm::vec3& factor)
    {
        updateTransform = true;
        scale.x += factor.x;
        scale.y += factor.y;
        scale.z += factor.z;
    }

    void translateBy(glm::vec3 factor)
    {
        updateTransform = true;
        this->translation += factor;
    }

    void rotateBy(glm::vec3 factor)
    {
        updateTransform = true;
        rotation.x += factor.x;
        rotation.y += factor.y;
        rotation.z += factor.z;
    }

    void reset()
    {
        updateTransform = true;
        scale = glm::vec3(1.0f,1.0f,1.0f);
        translation = glm::vec3();
        rotation = glm::vec3();
    }
};


#endif //TESTPROJECT2_TRANSFORM_H
