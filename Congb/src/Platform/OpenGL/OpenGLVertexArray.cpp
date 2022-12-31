#include "cbpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Congb {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Congb::ShaderDataType::Float:	   return GL_FLOAT;
			case Congb::ShaderDataType::Float2:	   return GL_FLOAT;
			case Congb::ShaderDataType::Float3:	   return GL_FLOAT;
			case Congb::ShaderDataType::Float4:	   return GL_FLOAT;
			case Congb::ShaderDataType::Mat3:	   return GL_FLOAT;
			case Congb::ShaderDataType::Mat4:	   return GL_FLOAT;
			case Congb::ShaderDataType::Int:	   return GL_INT;
			case Congb::ShaderDataType::Int2:	   return GL_INT;
			case Congb::ShaderDataType::Int3:	   return GL_INT;
			case Congb::ShaderDataType::Int4:	   return GL_INT;
			case Congb::ShaderDataType::Bool:	   return GL_BOOL;
		}

		CB_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		CB_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}