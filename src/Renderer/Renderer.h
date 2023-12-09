#pragma once

#include "../VertexArray/VertexArray.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../Shader/Shader.h"

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void Clear();
};
