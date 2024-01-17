#include "FURYpch.h"
#include "Shader.h"

#include "FURY/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace FURY
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FURY_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ::at Shader.cpp"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		FURY_CORE_ASSERT(false, "Unknown RendererAPI! ::at Shader.cpp");
		return nullptr;
	}
}
