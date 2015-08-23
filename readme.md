1) Go ahead and clone the library:
2) Generate OpenGL headers for your platform using glLoadGen:
    lua LoadGen.lua core_4_3 -style=noload_cpp -spec=gl -version=4.4 -profile=core -stdext=gl_ubiquitous.txt -stdext=gl_core_post_3_3.txt
3) The library must be able to find "opengl.hpp" (and obviously you need to compile opengl.cpp)
4) Make pretty graphics!

Currently in flux. Don't expect documentation any time soon.
