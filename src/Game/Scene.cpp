#include "Scene.h"
#include <AssetManager.h>

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

		float vertices[] = {
			// x, y, r, g, b

			// I (left side)
			-0.9,  0.5, 1,0,0,
			-0.8,  0.5, 1,0,0,
			-0.8, -0.5, 1,0,0,
			-0.9, -0.5, 1,0,0,

			// Q (square)
			-0.6,  0.5, 0,1,0,
			-0.4,  0.5, 0,1,0,
			-0.4, -0.5, 0,1,0,
			-0.6, -0.5, 0,1,0,

			// Q tail
			-0.45, -0.5, 0,1,0,
			-0.35, -0.7, 0,1,0,
			-0.4, -0.5, 0,1,0,

			// B vertical
			-0.2,  0.5, 0,0,1,
			-0.1,  0.5, 0,0,1,
			-0.1, -0.5, 0,0,1,
			-0.2, -0.5, 0,0,1,

			// B top box
			-0.1,  0.5, 0,0,1,
			 0.05, 0.5, 0,0,1,
			 0.05, 0.1, 0,0,1,
			-0.1,  0.1, 0,0,1,

			// B bottom box
			-0.1,  0.0, 0,0,1,
			0.05, 0.0, 0,0,1,
			0.05, -0.5, 0,0,1,
			-0.1, -0.5, 0,0,1,

			// A left side
			 0.1, -0.5, 1,1,0,
			 0.2,  0.5, 1,1,0,
			 0.3, -0.5, 1,1,0,

			// L
			 0.6,  0.5, 1,0,1,
			 0.7,  0.5, 1,0,1,
			 0.7, -0.5, 1,0,1,
			 0.6, -0.5, 1,0,1,

			 0.6, -0.5, 1,0,1,
			 0.9, -0.5, 1,0,1,
			 0.9, -0.4, 1,0,1,
			 0.6, -0.4, 1,0,1,
		};

		int indices[] = {
			// I
			0,2,1, 0,3,2,

			// Q square
			4,6,5, 4,7,6,

			// Q tail
			8,9,10,

			// B vertical
			11,13,12, 11,14,13,

			// B top box
			15,17,16, 15,18,17,

			// B bottom box
			19,21,20, 19,22,21,

			// A (triangle)
			23,25,24,

			// L vertical
			26,28,27, 26,29,28,

			// L bottom
			30,32,31, 30,33,32
		};

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */

		//intializing the data and sending to the GPU memory
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Now we gonna create the VOA which tells the OGL how to understand that data
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		//postion attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
		glEnableVertexAttribArray(1);

		//ok we finally gonna try to render stuff using indices to make triangles
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

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
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);



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
