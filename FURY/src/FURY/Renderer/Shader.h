#pragma once

#include <string>

namespace FURY
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader();

		virtual void Bind() const;
		virtual void Unbind() const;

		//static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		uint32_t m_RendererID;
	};
}