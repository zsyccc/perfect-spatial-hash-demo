// Include GLFW
#include <iostream>
#include <GLFW/glfw3.h>
// The "extern" keyword here is to access the variable "window"
// declared in tutorialXXX.cpp. This is a hack to keep the
// tutorials simple. Please avoid this.
extern GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() { return ViewMatrix; }
glm::mat4 getProjectionMatrix() { return ProjectionMatrix; }

glm::vec3 initialEye(0.0f, 0.0f, 5.0f);
glm::vec3 initialUp(0.0f, 1.0f, 0.0f);

glm::vec3 eyevec = initialEye;
glm::vec3 upvec = initialUp;

// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f;  // 3 units / second
float mouseSpeed = 0.005f;

void left(float degree) {
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), degree, upvec);
    glm::vec4 v = rot * glm::vec4(eyevec, 10.f);
    eyevec = glm::vec3(v.x, v.y, v.z);
}

void up(float degree) {
    glm::vec3 axis = glm::cross(eyevec, upvec);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), degree, axis);
    glm::vec4 e = rot * glm::vec4(eyevec, 1.0f);
    glm::vec4 u = rot * glm::vec4(upvec, 1.0f);
    eyevec = glm::vec3(e.x, e.y, e.z);
    upvec = glm::vec3(u.x, u.y, u.z);
}

void zoom(float dist) {
    float distance = glm::sqrt(eyevec.x * eyevec.x + eyevec.y * eyevec.y +
                               eyevec.z * eyevec.z);
    if ((distance + dist) / distance > 0) distance += dist;
    glm::vec3 direction = glm::normalize(eyevec);
    eyevec = direction * distance;
}

void computeMatricesFromInputs() {
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    float degree = deltaTime * speed;

    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        zoom(-degree * 0.5);
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        zoom(degree * 0.5);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        up(degree);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        up(-degree);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        left(-degree);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        left(degree);
    }

    float FoV = initialFoV;  // - 5 * glfwGetMouseWheel(); // Now GLFW 3
                             // requires setting up a callback for this. It's a
                             // bit too complicated for this beginner's
                             // tutorial, so it's disabled instead.

    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1
    // unit <-> 100 units
    ProjectionMatrix =
        glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix

    ViewMatrix =
        glm::lookAt(eyevec,                  // Camera is here
                    vec3(0.0f, 0.0f, 0.0f),  // and looks here : at the same
                                             // position, plus "direction"
                    upvec  // Head is up (set to 0,-1,0 to look upside-down)
        );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}