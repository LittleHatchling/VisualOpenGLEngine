#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraController
{
public:
    CameraController();
    ~CameraController();

    // Toggle FPV mode
    void toggleFPV();
    bool isFPVEnabled() const { return m_fpvEnabled; }

    // Update camera based on input
    void update(float dt);

    // Input handling
    void onKey(int key, bool pressed);
    void onMouseMove(double xpos, double ypos);

    // Get camera matrices
    glm::mat4 getViewMatrix() const;

    // Configuration
    void setSpeed(float speed) { m_speed = speed; }
    void setSensitivity(float sens) { m_mouseSensitivity = sens; }
    void toggleMouseLook() { m_mouseLookEnabled = !m_mouseLookEnabled; }
    bool isMouseLookEnabled() const { return m_mouseLookEnabled; }
    void setWindowDimensions(int width, int height) 
    { 
        m_windowWidth = width; 
        m_windowHeight = height; 
    }
    void setGLFWWindow(void* window) { m_glfwWindow = window; }

private:
    bool m_fpvEnabled = false;

    // Camera position and orientation
    glm::vec3 m_position;
    float m_yaw = 0.0f;      // Rotation around Y-axis
    float m_pitch = 0.0f;    // Rotation around X-axis

    // Movement
    float m_speed = 5.0f;
    bool m_moveForward = false;
    bool m_moveBackward = false;
    bool m_moveLeft = false;
    bool m_moveRight = false;
    bool m_moveUp = false;
    bool m_moveDown = false;

    // Mouse
    float m_mouseSensitivity = 0.1f;
    double m_lastMouseX = 0.0;
    double m_lastMouseY = 0.0;
    bool m_firstMouse = true;
    bool m_mouseLookEnabled = true;
    int m_windowWidth = 800;
    int m_windowHeight = 600;
    void* m_glfwWindow = nullptr;

    // Helper to get forward direction
    glm::vec3 getForwardDirection() const;
    glm::vec3 getRightDirection() const;
};
