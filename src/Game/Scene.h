#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "Transform.h"

class Scene
{
public:
	Scene(OpenGLWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
	OpenGLWindow* getWindow();

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);

private:
	OpenGLWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID, ibo;
	glm::vec2 cameraPos;
	float cameraSpeed = 0.01f;
	Transform cubeTransform;
	Transform torso;
	Transform head;
	Transform leftArm;
	Transform rightArm;
	Transform leftLeg;
	Transform rightLeg;
	float time = 0.0f;
	Transform baseLeftArm;
	Transform baseRightArm;
	Transform baseLeftLeg;
	Transform baseRightLeg;

	// Light source
	glm::vec3 lightColor;
	glm::vec3 lightPosition;

};