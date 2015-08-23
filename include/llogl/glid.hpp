#pragma once

#include "noncopyable.hpp"
#include "opengl.hpp"

namespace llogl
{
    namespace v1
    {
        template <typename T>
        class glid: noncopyable<glid<T>>
        {
        public:
            glid(): id(T::create())
            {
            }

            glid(glid<T>&& other): id(other.id)
            {
                other.id = 0;
            }

            ~glid()
            {
                T::destroy(id);
            }

            glid<T>& operator=(glid<T>&& other)
            {
                T::destroy(id);
                id = other.id;
                other.id = 0;
                return *this;
            }

            GLuint get() const
            {
                return id;
            }

        private:
            GLuint id;
        };

        template <typename T>
        GLuint get_id(const T& t)
        {
            return t.id.get();
        }
    }

    using namespace v1;
}
