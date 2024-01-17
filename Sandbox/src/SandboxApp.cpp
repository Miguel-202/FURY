#include <Fury.h>

#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>

class ExampleLayer : public FURY::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(FURY::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<FURY::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(FURY::VertexBuffer::Create(vertices, sizeof(vertices)));
		FURY::BufferLayout layout = {
			{ FURY::ShaderDataType::Float3, "a_Position" },
			{ FURY::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<FURY::IndexBuffer> indexBuffer;
		indexBuffer.reset(FURY::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(FURY::VertexArray::Create());


		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<FURY::VertexBuffer> squareVB;
		squareVB.reset(FURY::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ FURY::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<FURY::IndexBuffer> squareIB;
		squareIB.reset(FURY::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


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

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1);
			}
		)";



		std::string vertexSrcSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;	
				gl_Position = uViewProjection * uTransform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader.reset(new FURY::Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new FURY::Shader(vertexSrcSquare, fragmentSrcSquare));
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

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		FURY::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
		FURY::Renderer::Submit(m_Shader, m_VertexArray);

		FURY::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(FURY::Event& event) override
	{
	}

private:
	std::shared_ptr<FURY::Shader> m_Shader;
	std::shared_ptr<FURY::VertexArray> m_VertexArray;

	std::shared_ptr<FURY::Shader> m_BlueShader;
	std::shared_ptr<FURY::VertexArray> m_SquareVA;

	FURY::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 0.3f;
	float m_CameraSensibility = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 0.3f;
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