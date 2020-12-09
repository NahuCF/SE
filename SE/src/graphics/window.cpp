#include <iostream>
#include <time.h>

#include "window.h"
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace se {namespace graphics {

	Window::Window(const char* title, unsigned int width, unsigned int height)
	{
		m_Title = title;
		m_Height = height;
		m_Width = width;
		if(!Init())
			glfwTerminate();
	};
	
	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init()
	{
		m_LastTime = time(NULL);
		if (!glfwInit())
		{
			std::cout << "Failed to load GLFW :c" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if(!m_Window)
		{
			glfwTerminate();
			std::cout << "Fail to create GLFW wondow :c" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		if (glewInit() != GLEW_OK)
			std::cout << "Error to initializate GLEW :c" << std::endl;
		return true;
	}

	void Window::Update() 
	{
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
		FPS();
	}

	bool Window::Closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::FPS()
	{
		m_FPS++;
		m_CurrentTime = time(NULL);
		if(m_CurrentTime - m_LastTime > 1)
		{
			m_LastTime = m_CurrentTime;
			std::cout << "FPS: " << m_FPS << std::endl;
			m_FPS = 0;
		}
	}

	void Window::Vsync(const char *state)
	{
		if(state == "Enable")
		{
			glfwSwapInterval(1);
		}
		else if (state == "Disable")
		{
			glfwSwapInterval(0);
		}
	}

}}