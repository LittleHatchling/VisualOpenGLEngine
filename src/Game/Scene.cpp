#include "Scene.h"
#include <AssetManager.h>
#include "Cube.h"
#include "Framework/SceneElements/Transform.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Scene::Scene(OpenGLWindow * window)
    : m_window(window)
{
    assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
    try
    {
        // Shader
        m_assets.addShaderProgram(
            "shader",
            AssetManager::createShaderProgram(
                "assets/shaders/vertex.glsl",
                "assets/shaders/fragment.glsl"
            )
        );

        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        // -------------------------
        // GPU SETUP
        // -------------------------
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), cubeVert, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        // -------------------------
        // RENDER SETTINGS
        // -------------------------
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearDepth(1.0);

        // -------------------------
        // ROBOT BASE POSE
        // -------------------------
        float s = 0.5f;
        float zScale = 0.8f;

        torso.scale(glm::vec3(s, s * 1.5f, s * 0.5f));

        //head
        head.translate(glm::vec3(0.0f, 0.78f, 0.0f));
        head.scale(glm::vec3(0.7f));

        //left arm
        leftArm.translate(glm::vec3(-0.75f, 0.1f, 0.0f));
        leftArm.scale(glm::vec3(0.3f, 0.8f, zScale));

        //right arm
        rightArm.translate(glm::vec3(0.75f, 0.1f, 0.0f));
        rightArm.scale(glm::vec3(0.4f, 0.8f, zScale));

        //left leg
        leftLeg.translate(glm::vec3(-0.3f, -0.95f, 0.0f));
        leftLeg.scale(glm::vec3(0.4f, 0.9f, zScale));

        //right leg
        rightLeg.translate(glm::vec3(0.3f, -0.95f, 0.0f));
        rightLeg.scale(glm::vec3(0.4f, 0.9f, zScale));

        std::cout << "Scene initialization done\n";
        return true;
    }
    catch (std::exception& ex)
    {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()));
    }
}

void Scene::render(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->use();
    glBindVertexArray(vaoID);

    // -------------------------
    // PROJECTION MATRIX
    // -------------------------
    float fov = glm::radians(45.0f);
    float aspect = 16.0f / 9.0f;  // Adjust to your window size
    float near = 0.1f;
    float far = 100.0f;
    glm::mat4 projection = glm::perspective(fov, aspect, near, far);

    m_shader->setUniform("projectionMatrix", projection, false);

    // -------------------------
    // VIEW MATRIX (CAMERA)
    // -------------------------
    glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector     = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, upVector);

    m_shader->setUniform("viewMatrix", view, false);

    float swing = sin(time * 3.0f) * 0.5f;
    float legSwing = sin(time * 3.0f) * 0.6f;

    // -------------------------
    // ROOT
    // -------------------------
    Transform torsoRotation;
    torsoRotation.setRotation(glm::angleAxis(time, glm::vec3(0.0f, 1.0f, 0.0f)));

    glm::mat4 torsoM = torso.getMatrix() * torsoRotation.getMatrix();

    m_shader->setUniform("transformMatrix", torsoM, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // -------------------------
    // HEAD
    // -------------------------
    glm::mat4 headM = torsoM * head.getMatrix();
    m_shader->setUniform("transformMatrix", headM, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // -------------------------
    // LEFT ARM
    // -------------------------
    Transform leftArmAnim = leftArm;
    leftArmAnim.rotateAroundPoint(glm::vec3(0.0f, 0.4f, 0.0f),
        glm::angleAxis(swing, glm::vec3(1.0f, 0.0f, 0.0f)));

    glm::mat4 leftArmM = torsoM * leftArmAnim.getMatrix();
    m_shader->setUniform("transformMatrix", leftArmM, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // -------------------------
    // RIGHT ARM
    // -------------------------
    Transform rightArmAnim = rightArm;
    rightArmAnim.rotateAroundPoint(glm::vec3(0.0f, 0.4f, 0.0f),
        glm::angleAxis(-swing, glm::vec3(1.0f, 0.0f, 0.0f)));

    glm::mat4 rightArmM = torsoM * rightArmAnim.getMatrix();
    m_shader->setUniform("transformMatrix", rightArmM, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // -------------------------
    // LEGS
    // -------------------------
    Transform leftLegAnim = leftLeg;
    leftLegAnim.rotateAroundPoint(glm::vec3(0.0f, 0.45f, 0.0f),
        glm::angleAxis(-legSwing, glm::vec3(1.0f, 0.0f, 0.0f)));

    glm::mat4 leftLegM = torsoM * leftLegAnim.getMatrix();
    m_shader->setUniform("transformMatrix", leftLegM, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    Transform rightLegAnim = rightLeg;
    rightLegAnim.rotateAroundPoint(glm::vec3(0.0f, 0.45f, 0.0f),
        glm::angleAxis(legSwing, glm::vec3(1.0f, 0.0f, 0.0f)));

    glm::mat4 rightLegM = torsoM * rightLegAnim.getMatrix();
    m_shader->setUniform("transformMatrix", rightLegM, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Scene::update(float dt)
{
    time += dt;

    // IMPORTANT: removed torso.rotate()
    // because it causes long-term transform distortion in scene graphs
}

OpenGLWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}
