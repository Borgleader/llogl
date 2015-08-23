#pragma once

namespace llogl
{
    namespace v1
    {
        template <typename T>
        class noncopyable
        {
        protected:
            noncopyable() {};
            ~noncopyable() {};

        private:
            noncopyable(const noncopyable& other) {}
            noncopyable& operator=(const noncopyable& other) {}
        };
    }
    
    using namespace v1;
}
