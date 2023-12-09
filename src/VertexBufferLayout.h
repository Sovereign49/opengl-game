#pragma once
#include <vector>

#include "Macros.h"

template<typename T>
struct identity {
    typedef T type;
};

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

    template<typename TL>
    void Push(unsigned int count, identity<TL>) {
        static_assert(false);
    }

    void Push(unsigned int count, identity<float>) {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void Push(unsigned int count, identity<unsigned int>) {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void Push(unsigned int count, identity<unsigned char>) {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += count* VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

public:
    VertexBufferLayout()
        : m_Stride(0) {}

    template<typename TL>
    void Push(unsigned int count) {
        Push(count, identity<TL>());

    }

    inline const std::vector<VertexBufferElement> GetElements() const& {
        return m_Elements;
    }
    inline unsigned int GetStride() const {
        return m_Stride;
    }
};
