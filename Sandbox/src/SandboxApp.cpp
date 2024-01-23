#include <Fury.h>

#include <Platform/OpenGL/OpenGLShader.h>
#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public FURY::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f, 1.5), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(FURY::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		FURY::Ref<FURY::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(FURY::VertexBuffer::Create(vertices, sizeof(vertices)));
		FURY::BufferLayout layout = {
			{ FURY::ShaderDataType::Float3, "a_Position" },
			{ FURY::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		unsigned int indices[3] = { 0, 1, 2 };
		FURY::Ref<FURY::IndexBuffer> indexBuffer;
		indexBuffer.reset(FURY::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(FURY::VertexArray::Create());


		float squareVertices[5 * 4] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		FURY::Ref<FURY::VertexBuffer> squareVB;
		squareVB.reset(FURY::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ FURY::ShaderDataType::Float3, "a_Position" },
			{ FURY::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		FURY::Ref<FURY::IndexBuffer> squareIB;
		squareIB.reset(FURY::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

#pragma region ShaderGLSL
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;	
				v_Color = a_Color;
				gl_Position = uViewProjection * uTransform * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrcSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1);
			}
		)";

		std::string textureVertexSrcSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;	
				gl_Position = uViewProjection * uTransform * vec4(a_Position, 1.0);
			}
		)";
		std::string textureFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

#pragma endregion

		m_TextureShader.reset(FURY::Shader::Create(textureVertexSrcSquare , textureFragmentSrc));
		m_FlatColorShader.reset(FURY::Shader::Create(vertexSrc, fragmentSrcSquare));

		m_Texture = FURY::Texture2D::Create("assets/textures/NightSky.png");

		std::dynamic_pointer_cast<FURY::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<FURY::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(FURY::Timestep ts) override
	{
		//Camera movement
		if (FURY::Input::IsKeyPressed(FURY_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (FURY::Input::IsKeyPressed(FURY_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (FURY::Input::IsKeyPressed(FURY_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (FURY::Input::IsKeyPressed(FURY_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		//Camera rotation
		if (FURY::Input::IsKeyPressed(FURY_KEY_A))
			m_CameraRotation -= m_CameraSensibility * ts;
		else if (FURY::Input::IsKeyPressed(FURY_KEY_D))
			m_CameraRotation += m_CameraSensibility * ts;
		//Square movement JKLI
		if (FURY::Input::IsKeyPressed(FURY_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (FURY::Input::IsKeyPressed(FURY_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		if (FURY::Input::IsKeyPressed(FURY_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (FURY::Input::IsKeyPressed(FURY_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		FURY::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		FURY::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		FURY::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<FURY::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<FURY::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("uColor", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				transform = glm::translate(transform, m_SquarePosition);
				FURY::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		FURY::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//FURY::Renderer::Submit(m_Shader, m_VertexArray);

		FURY::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(FURY::Event& event) override
	{
	}

private:
	FURY::Ref<FURY::Shader> m_TextureShader;
	FURY::Ref<FURY::VertexArray> m_VertexArray;
	FURY::Ref<FURY::Shader> m_FlatColorShader;
	FURY::Ref<FURY::VertexArray> m_SquareVA;

	FURY::Ref<FURY::Texture2D> m_Texture;

	FURY::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 0.3f;
	float m_CameraSensibility = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 0.3f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public FURY::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

FURY::Application* FURY::CreateApplication()
{
	return new Sandbox();
}