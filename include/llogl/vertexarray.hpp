#pragma once

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"

namespace llogl
{
    namespace v1
    {
        class vertex_array: noncopyable<vertex_array>
        {
        public:
            vertex_array(): id()
            {
            }

            vertex_array(vertex_array&& other): id(std::move(other.id))
            {
            }

            vertex_array& operator=(vertex_array&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            void bind()
            {
                gl::BindVertexArray(id.get());
            }

            void unbind()
            {
                gl::BindVertexArray(0);
            }

            static GLuint create()
            {
                GLuint id;
                gl::GenVertexArrays(1, &id);
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteVertexArrays(1, &id);
                id = 0;
            }

        private:
            glid<vertex_array> id;

            friend GLuint get_id<vertex_array>(const vertex_array& t);
        };        
    }

    using namespace v1;
}
