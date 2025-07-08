#pragma once 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

struct Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw, pitch;
    float speed;
    float sensativity;

    Camera();
    glm::mat4 getViewerMatrix() const;
    void processInput(GLFWwindow* window, float deltaTime);
    void processMouse(float xoffset, float yoffset);
    void updateCameraVectors();
    
};
