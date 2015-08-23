#pragma once

#include <type_traits>

#include "buffer.hpp"
#include "glid.hpp"
#include "noncopyable.hpp"
#include "opengl.hpp"

namespace llogl
{
    namespace v1
    {
        enum class texture_wrap
        {
            clamp_to_edge = gl::CLAMP_TO_EDGE,
            clamp_to_border = gl::CLAMP_TO_BORDER,
            mirrored_repeat = gl::MIRRORED_REPEAT,
            repeat = gl::REPEAT,
            mirror_clamp_to_edgee = gl::MIRROR_CLAMP_TO_EDGE,
        };

        enum class texture_filter
        {
            nearest = gl::NEAREST,
            linear = gl::LINEAR,
            nearest_mipmap_nearest = gl::NEAREST_MIPMAP_NEAREST,
            linear_mipmap_nearest = gl::LINEAR_MIPMAP_NEAREST,
            nearest_mipmap_linear = gl::NEAREST_MIPMAP_LINEAR,
            linear_mipmap_linear = gl::LINEAR_MIPMAP_LINEAR,
        };

        enum class texture_target
        {
            texture_1d = gl::TEXTURE_1D,
            texture_2d = gl::TEXTURE_2D,
            texture_3d = gl::TEXTURE_3D,
            texture_1d_array = gl::TEXTURE_1D_ARRAY,
            texture_2d_array = gl::TEXTURE_2D_ARRAY,
            texture_rectangle = gl::TEXTURE_RECTANGLE,
            texture_cube_map = gl::TEXTURE_CUBE_MAP,
            texture_cube_map_array = gl::TEXTURE_CUBE_MAP_ARRAY,
            texture_buffer = gl::TEXTURE_BUFFER,
            texture_2d_multisample = gl::TEXTURE_2D_MULTISAMPLE,
            texture_2d_multisample_array = gl::TEXTURE_2D_MULTISAMPLE_ARRAY,
        };

        template <texture_target Target>
        class texture: noncopyable<texture<Target>>
        {
        public:
            texture(): id()
            {
            }

            texture(texture&& other): id(std::move(other.id))
            {
            }

            texture<Target>& operator=(texture<Target>&& other)
            {
                id = std::move(other.id);
                return *this;
            }

            void bind()
            {
                gl::BindTexture(static_cast<GLenum>(Target), id.get());
            }

            void unbind()
            {
                gl::BindTexture(static_cast<GLenum>(Target), 0);
            }

            void parameteri(GLenum param, GLint value)
            {
                gl::TexParameteri(static_cast<GLenum>(Target), param, value);
            }

            template <buffer_type U, typename = typename std::enable_if<Target == texture_target::texture_buffer>::type>
            void tex_buffer(GLenum internal_format, const buffer<U>& buffer)
            {
                bind();
                gl::TexBuffer(static_cast<GLenum>(texture_target::texture_buffer), internal_format, get_id(buffer));
                unbind();
            }

            static GLuint create()
            {
                GLuint id;
                gl::GenTextures(1, &id);
                return id;
            }

            static void destroy(GLuint& id)
            {
                gl::DeleteTextures(1, &id);
                id = 0;
            }

        private:
            glid<texture<Target>> id;

            friend GLuint get_id<texture<Target>>(const texture<Target>& t);
        };

        typedef texture<texture_target::texture_1d> texture_1d;
        typedef texture<texture_target::texture_2d> texture_2d;
        typedef texture<texture_target::texture_3d> texture_3d;
        typedef texture<texture_target::texture_buffer> texture_buffer;
    }

    using namespace v1;
}
