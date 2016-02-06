#pragma once

#include <exception>
#include <string>
#include <vector>

#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"
#include "util.hpp"

namespace llogl
{
    namespace v1
    {
        enum class shader_type: GLuint
        {
            vertex = gl::VERTEX_SHADER,
            geometry = gl::GEOMETRY_SHADER,
            fragment = gl::FRAGMENT_SHADER,
            compute = gl::COMPUTE_SHADER,
            tess_control = gl::TESS_CONTROL_SHADER,
            tess_evaluation = gl::TESS_EVALUATION_SHADER,
        };

        template <shader_type T>
        class shader: noncopyable<shader<T>>
        {
        public:
            shader(): id()
            {
            }

            shader(shader&& other): id(std::move(other.id))
            {
            }

            shader& operator=(shader&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            static GLuint create()
            {
                GLuint id = 0;
                id = gl::CreateShader(static_cast<GLuint>(T));
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteShader(id);
                id = 0;
            }

            static shader<T> create_from_file(std::string filepath)
            {
                return create_from_string(util::load_file_content<std::string>(filepath));
            }

            static shader<T> create_from_string(const std::string& shader_source, std::string* out_log = nullptr)
            {
                shader<T> shader;

                GLint shader_length = shader_source.length();
                auto shader_cstr = shader_source.c_str();

                gl::ShaderSource(shader.id.get(), 1, &shader_cstr, &shader_length);
                gl::CompileShader(shader.id.get());

                GLint compile_error = gl::GetError();
                GLint is_compiled = 0;
                gl::GetShaderiv(shader.id.get(), gl::COMPILE_STATUS, &is_compiled);

                struct shader_compilation_exception : public std::exception
                {
                    shader_compilation_exception(const std::string& error) : error(error) {}
                    const char* what() const override { return error.c_str(); }

                private:
                    std::string error;
                };

                GLint log_length = 0;
                gl::GetShaderiv(shader.id.get(), gl::INFO_LOG_LENGTH, &log_length);

                if (log_length > 1)
                {
                    std::string tmp_log;
                    std::string& log = out_log ? *out_log : tmp_log;
                    log.resize(log_length);

                    gl::GetShaderInfoLog(shader.id.get(), log_length, &log_length, &log[0]);
                }
                else if (out_log)
                {
                    out_log->clear();
                }

                if(is_compiled != gl::TRUE_)
                    throw shader_compilation_exception(std::to_string(compile_error));

                return shader;
            }

        private:
            glid<shader<T>> id;

            friend GLuint get_id<shader<T>>(const shader<T>& t);
        };

        typedef shader<shader_type::vertex> vertex_shader;
        typedef shader<shader_type::geometry> geometry_shader;
        typedef shader<shader_type::fragment> fragment_shader;
        typedef shader<shader_type::compute> compute_shader;
        typedef shader<shader_type::tess_control> tess_control_shader;
        typedef shader<shader_type::tess_evalutation> tess_evaluation_shader;
    }

    using namespace v1;
}
