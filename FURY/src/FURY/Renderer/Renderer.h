#pragma once

namespace FURY
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1//TODO: , DirectX = 2, Vulkan = 3, Metal = 4
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};
}