#pragma once

#include "../IndexBuffer/IndexBuffer.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../VertexBuffer/VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const IndexBuffer& ib);
    void Bind() const;
    void Unbind() const;
};
