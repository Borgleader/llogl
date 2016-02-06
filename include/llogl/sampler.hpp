#pragma once

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"

namespace llogl
{
    namespace v1
    {
        class sampler : noncopyable<sampler>
        {
        public:
            sampler() : id()
            {
            }

            sampler(sampler&& other) : id(std::move(other.id))
            {
            }

            sampler& operator=(sampler&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            void bind(GLuint unit)
            {
                gl::BindSampler(unit, id.get());
            }


            void unbind(GLuint unit)
            {
                gl::BindSampler(unit, 0);
            }

            static GLuint create()
            {
                GLuint id = 0;
                gl::GenSamplers(1, &id);
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteSamplers(1, &id);
                id = 0;
            }

        private:
            glid<sampler> id;

            friend GLuint get_id<sampler>(const sampler& t);
        };
    }

    using namespace v1;
}
