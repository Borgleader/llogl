#pragma once

#include <exception>
#include <fstream>
#include <math.h>
#include <string>

namespace llogl
{
    namespace util
    {
        namespace v1
        {
            static const float kPI = 3.14159265358979323846f;

            template <typename Container>
            Container load_file_content(std::string filename)
            {
                struct file_not_found_exception : public std::exception
                {
                };

                std::ifstream file(filename, std::ios::binary);
                if(!file)
                {
                    throw file_not_found_exception();
                }

                std::istreambuf_iterator<char> beg(file), end;
                return Container(beg, end);
            }

            template<typename Container>
            size_t size_in_bytes(const Container& c)
            {
                return c.size() * sizeof(Container::value_type);
            }

            inline float degToRad(float deg_angle)
            {
                return deg_angle * (2.0f * kPI) / 360.0f;
            }

            inline float radToDeg(float rad_angle)
            {
                return rad_angle * 360.0f / (2.0f * kPI);
            }

            template<typename T, typename U>
            size_t offset_of(U T::* member)
            {
                return static_cast<size_t>(reinterpret_cast<const volatile char&>(member));
            }
        }

        using namespace v1;
    }
}
