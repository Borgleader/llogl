#pragma once

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"

namespace llogl
{
    namespace v1
    {
        class framebuffer: noncopyable<framebuffer>
        {
        public:
            framebuffer(): id()
            {
            }

            framebuffer(framebuffer<T>&& other): id(std::move(other.id))
            {
            }

            framebuffer& operator=(framebuffer&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            void bind()
            {
                // target: Specifies the target to which the framebuffer object is bound.
                //     The symbolic constant must be GL_FRAMEBUFFER.
                gl::BindFramebuffer(gl::FRAMEBUFFER, id.get());
            }

            void unbind()
            {
                // target: Specifies the target to which the framebuffer object is bound.
                //     The symbolic constant must be GL_FRAMEBUFFER.
                gl::BindFramebuffer(gl::FRAMEBUFFER, 0);
            }

            static GLuint create()
            {
                GLuint id;
                gl::GenFramebuffers(1, &id);
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteFramebuffers(1, &id);
                id = 0;
            }

        private:
            glid<framebuffer> id;

            friend GLuint getId<framebuffer>(const framebuffer& t);
        };
    }

    using namespace v1;
}
