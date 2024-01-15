#include "FURYpch.h"
#include "Buffer.h"

#include "Renderer.h"

//TODO: Switch between renderer API's #if HZ_PLATFORM_WINDOWS etc.
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace FURY
{
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FURY_ASSERT(false, "Renderer API::None is currently not supported!")	break;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);							break;
		default:																							break;
		}

		FURY_ASSERT(false, "Unknown Renderer API!")
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FURY_ASSERT(false, "Renderer API::None is currently not supported!")
				break;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;
		default:
			break;
		}

		FURY_ASSERT(false, "Unknown Renderer API!")
		return nullptr;
	}
}