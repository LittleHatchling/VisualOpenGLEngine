#include "Scene.h"
#include <AssetManager.h>
#include "Cube.h"
#include "Framework/SceneElements/Transform.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();



		/*
		 * ************
		 * Place your code here!
		 * ************
		 */

		//intializing the data and sending to the GPU memory
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), cubeVert, GL_STATIC_DRAW);

		// Now we gonna create the VOA which tells the OGL how to understand that data
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		//postion attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		//ok we finally gonna try to render stuff using indices to make triangles, basically just making it ready in memory
		//uses indices data, sends it to gpu
		//index buffer, stores which vertices form triangles
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_GREATER);
		glClearDepth(0.0);

		float s = 0.5f;

		// Torso (root)
		torso.scale(glm::vec3(s, s * 1.5f, s * 0.5f));

		// Head
		head.translate(glm::vec3(0.0f, 1.2f * s, 0.0f));
		head.scale(glm::vec3(s * 0.5f));

		// Arms
		leftArm.translate(glm::vec3(-0.8f * s, 0.2f * s, 0.0f));
		rightArm.translate(glm::vec3(0.8f * s, 0.2f * s, 0.0f));

		leftArm.scale(glm::vec3(s * 0.4f, s, s * 0.4f));
		rightArm.scale(glm::vec3(s * 0.4f, s, s * 0.4f));

		// Legs
		leftLeg.translate(glm::vec3(-0.3f * s, -1.5f * s, 0.0f));
		rightLeg.translate(glm::vec3(0.3f * s, -1.5f * s, 0.0f));

		leftLeg.scale(glm::vec3(s * 0.4f, s * 1.2f, s * 0.4f));
		rightLeg.scale(glm::vec3(s * 0.4f, s * 1.2f, s * 0.4f));



        std::cout << "Scene initialization done\n";
        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}

void Scene::render(float dt)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->use();
	glBindVertexArray(vaoID);

	// -----------------------
	// DRAW ROBOT
	// -----------------------

	m_shader->setUniform("transformMatrix", torso.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	m_shader->setUniform("transformMatrix", head.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	m_shader->setUniform("transformMatrix", leftArm.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	m_shader->setUniform("transformMatrix", rightArm.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	m_shader->setUniform("transformMatrix", leftLeg.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	m_shader->setUniform("transformMatrix", rightLeg.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




}

void Scene::update(float dt)
{

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
