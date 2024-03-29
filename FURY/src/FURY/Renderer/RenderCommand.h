#pragma once

#include "RendererAPI.h"

namespace FURY
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RenderAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RenderAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RenderAPI;

	};
}