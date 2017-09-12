#pragma once

#include <exception>
#include <string>
#include <vector>

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"
#include "shader.hpp"

namespace llogl
{
    namespace v1
    {
        class shader_program: noncopyable<shader_program>
        {
        public:
            shader_program(bool is_separable = false): id()
            {
                if (is_separable)
                    gl::ProgramParameteri(id.get(), gl::PROGRAM_SEPARABLE, gl::TRUE_);
            }

            shader_program(shader_program&& other): id(std::move(other.id))
            {
            }

            shader_program& operator=(shader_program&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            template<shader_type T>
            void attach_shader(const shader<T>& shader)
            {
                gl::AttachShader(id.get(), get_id(shader));
            }

            template<shader_type T>
            void detach_shader(const shader<T>& shader)
            {
                gl::DetachShader(id.get(), get_id(shader));
            }

            void bind_attribute(GLuint attrib_index, std::string attribute)
            {
                gl::BindAttribLocation(id.get(), attrib_index, attribute.c_str());
            }

            void link(std::string* out_log = nullptr)
            {
                gl::LinkProgram(id.get());

                GLint link_error = gl::GetError();

                GLint is_linked = 0;
                gl::GetProgramiv(id.get(), gl::LINK_STATUS, &is_linked);

                struct shader_compilation_exception : public std::exception
                {
                    shader_compilation_exception(const std::string& error) : error(error) {}
                    const char* what() const override { return error.c_str(); }

                private:
                    std::string error;
                };

                GLint log_length = 0;
                gl::GetProgramiv(id.get(), gl::INFO_LOG_LENGTH, &log_length);

                if (log_length > 1)
                {
                    std::string tmp_log;
                    std::string& log = out_log ? *out_log : tmp_log;
                    log.resize(log_length);

                    gl::GetProgramInfoLog(id.get(), log_length, &log_length, &log[0]);
                }
                else if (out_log)
                {
                    out_log->clear();
                }

                if(is_linked != gl::TRUE_)
                    throw shader_compilation_exception(std::to_string(link_error));
            }

            GLuint get_uniform_location(std::string name)
            {
                return gl::GetUniformLocation(id.get(), name.c_str());
            }

            GLint get_attrib_location(std::string name)
            {
                return gl::GetAttribLocation(id.get(), name.c_str());
            }

            void use()
            {
                gl::UseProgram(id.get());
            }

            void unuse()
            {
                gl::UseProgram(0);
            }

            static GLuint create()
            {
                GLuint id = 0;
                id = gl::CreateProgram();
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteProgram(id);
                id = 0;
            }

        private:
            glid<shader_program> id;

            friend GLuint get_id<shader_program>(const shader_program& t);
        };
    }

    using namespace v1;
}
