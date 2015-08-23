#pragma once

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"

namespace llogl
{
    namespace v1
    {
        enum class buffer_type: GLuint
        {
            array_buffer = gl::ARRAY_BUFFER,
            atomic_count_buffer = gl::ATOMIC_COUNTER_BUFFER,
            copy_read_buffer = gl::COPY_READ_BUFFER,
            copy_write_buffer = gl::COPY_WRITE_BUFFER,
            element_array_buffer = gl::ELEMENT_ARRAY_BUFFER,
            pixel_pack_buffer = gl::PIXEL_PACK_BUFFER,
            texture_buffer = gl::TEXTURE_BUFFER,
            transform_feedback_buffer = gl::TRANSFORM_FEEDBACK_BUFFER,
            uniform_buffer = gl::UNIFORM_BUFFER
        };

        template <buffer_type T>
        class buffer: noncopyable<buffer<T>>
        {
        public:
            buffer(): id()
            {
            }

            buffer(buffer&& other): id(std::move(other.id))
            {
            }

            buffer<T>& operator=(buffer<T>&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            void bind()
            {
                gl::BindBuffer(static_cast<GLuint>(T), id.get());
            }

            void unbind()
            {
                gl::BindBuffer(static_cast<GLuint>(T), 0);
            }

            void bind_buffer_base(GLuint index)
            {
                gl::BindBufferBase(static_cast<GLuint>(T), index, id.get());
            }

            static GLuint create()
            {
                GLuint id;
                gl::GenBuffers(1, &id);
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteBuffers(1, &id);
                id = 0;
            }

        private:
            glid<buffer<T>> id;

            friend GLuint get_id<buffer<T>>(const buffer<T>& t);
        };
    }

    using namespace v1;
}
