#pragma once

#include "VertexArray/VertexArray.h"
#include "IndexBuffer/IndexBuffer.h"
#include "Shader/Shader.h"

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void BatchDraw(float* vertices, unsigned int indices, glm::mat4 mvp );
    void Clear();
};
