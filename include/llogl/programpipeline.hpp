#pragma once

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"
#include "shaderprogram.hpp"

namespace llogl
{
    namespace v1
    {
        enum class program_stages
        {
            vertex = gl::VERTEX_SHADER_BIT,
            tess_control = gl::TESS_CONTROL_SHADER_BIT, 
            tess_evaluation = gl::TESS_EVALUATION_SHADER_BIT,
            geometry = gl::GEOMETRY_SHADER_BIT, 
            fragment = gl::FRAGMENT_SHADER_BIT,
            all = gl::ALL_SHADER_BITS,
        };

        class program_pipeline: noncopyable<program_pipeline>
        {
        public:
            program_pipeline(): id()
            {
            }

            program_pipeline(program_pipeline&& other): id(std::move(other.id))
            {
            }

            program_pipeline& operator=(program_pipeline&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            void bind()
            {
                gl::BindProgramPipeline(id.get());
            }

            void unbind()
            {
                gl::BindProgramPipeline(0);
            }

            void use_program_stages(program_stages stage, const shader_program& program)
            {
                gl::UseProgramStages(id.get(), static_cast<GLbitfield>(stage), get_id(program));
            }

            void unuse_program_stages(program_stages stage)
            {
                gl::UseProgramStages(id.get(), static_cast<GLbitfield>(stage), 0);
            }

            static GLuint create()
            {
                GLuint id = 0;
                gl::GenProgramPipelines(1, &id);
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteProgramPipelines(1, &id);
                id = 0;
            }

        private:
            glid<program_pipeline> id;

            friend GLuint get_id<program_pipeline>(const program_pipeline& t);
        };
    }
    
    using namespace v1;
}
