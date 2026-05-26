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

		cubeTransform.rotate(glm::vec3(
			glm::radians(30.0f),
			glm::radians(40.0),
			0.0
		));

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


	/*
    * ************
    * Place your code here!
    * ************
    */
	m_shader->use();
	glBindVertexArray(vaoID);
	m_shader->setUniform("transformMatrix", cubeTransform.getMatrix(), false);
	glDrawElements(GL_TRIANGLES, sizeof(cubeInd) / sizeof(int), GL_UNSIGNED_INT, 0);



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
