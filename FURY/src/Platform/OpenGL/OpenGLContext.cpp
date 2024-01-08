#include "FURYpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace FURY
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		FURY_CORE_ASSERT(windowHandle, "Window handle is null!")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FURY_CORE_ASSERT(status, "Failed to initialize Glad!");

		FURY_CORE_INFO("--OpenGL Info--");
		FURY_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		FURY_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		FURY_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}