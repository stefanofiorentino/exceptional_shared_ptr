#include <iostream>
#include <memory>

namespace __std
{
    template<typename T>
    class shared_ptr
    {
        std::shared_ptr<T> __ptr;
    public:
        shared_ptr() :
                __ptr(nullptr)
        {}

        shared_ptr(shared_ptr const &ptr) :
                __ptr(ptr)
        {}

        shared_ptr &operator=(shared_ptr const &ptr)
        {
            shared_ptr::__ptr = ptr;
            return *this;
        }

        shared_ptr(shared_ptr &&ptr) noexcept :
                __ptr(ptr)
        {}

        shared_ptr &operator=(shared_ptr &&ptr) noexcept
        {
            shared_ptr::__ptr = ptr;
            return *this;
        }

        explicit shared_ptr(std::shared_ptr<T> const &ptr) :
                __ptr(ptr)
        {}

        shared_ptr &operator=(std::shared_ptr<T> const &ptr)
        {
            shared_ptr::__ptr = ptr;
            return *this;
        }

        explicit shared_ptr(std::shared_ptr<T> &&ptr) noexcept :
                __ptr(std::move(ptr))
        {}

        shared_ptr &operator=(std::shared_ptr<T> &&ptr) noexcept
        {
            shared_ptr::__ptr = ptr;
            return *this;
        }

        T *operator->() const
        {
            std::weak_ptr<T> __weak_ptr(__ptr);
            if (auto p = __weak_ptr.lock())
            {
                return __ptr.get();
            }
            else
            {
                std::string s = "NullPointerException: ";
                s += __PRETTY_FUNCTION__;
                throw std::runtime_error(s);
            }
        }
    };
}

class foo
{
public:
    void bar()
    {
        std::puts(__PRETTY_FUNCTION__);
    }
};

int main()
{
    __std::shared_ptr<int> intPtr(std::make_shared<int>(12));


    __std::shared_ptr<int> intPtr1(std::make_shared<int>(12));


    __std::shared_ptr<foo> exceptional;
    try
    {
        exceptional->bar();
    }
    catch (std::runtime_error const &err)
    {
        std::puts(err.what());
    }
    catch (...)
    {
        std::puts("Exception caught");
    }

//    __std::shared_ptr<int> intPtr2 = std::make_shared<int>(12); // compile-error
//    __std::shared_ptr<foo> fooPtr = std::make_shared<foo>();// compile-error
    return 0;
}