#include "FURYpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FURY
{
	RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI;
}