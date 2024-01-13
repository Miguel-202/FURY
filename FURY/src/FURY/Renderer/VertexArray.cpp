#include "FURYpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace FURY
{
	VertexArray* FURY::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		FURY_ASSERT(false, "Renderer API::None is currently not supported!")	break;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();											break;
		default:																							break;
		}

		FURY_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}

}
