#include <iostream>
#include <memory>

namespace __std
{
    template<typename T>
    class exceptional_shared_ptr
    {
        std::shared_ptr<T> __ptr;
    public:
        exceptional_shared_ptr() :
                __ptr(nullptr)
        {}

        exceptional_shared_ptr(exceptional_shared_ptr const &ptr) :
                __ptr(ptr)
        {}

        exceptional_shared_ptr &operator=(exceptional_shared_ptr const &ptr)
        {
            exceptional_shared_ptr::__ptr = ptr;
            return *this;
        }

        exceptional_shared_ptr(exceptional_shared_ptr &&ptr) noexcept :
                __ptr(ptr.get())
        {}

        exceptional_shared_ptr &operator=(exceptional_shared_ptr &&ptr) noexcept
        {
            exceptional_shared_ptr::__ptr = ptr;
            return *this;
        }

        explicit exceptional_shared_ptr(std::shared_ptr<T> const &ptr) :
                __ptr(ptr)
        {}

        exceptional_shared_ptr &operator=(std::shared_ptr<T> const &ptr)
        {
            exceptional_shared_ptr::__ptr = ptr;
            return *this;
        }

        exceptional_shared_ptr(std::shared_ptr<T> &&ptr) noexcept :
                __ptr(std::move(ptr))
        {}

        exceptional_shared_ptr &operator=(std::shared_ptr<T> &&ptr) noexcept
        {
            exceptional_shared_ptr::__ptr = ptr;
            return *this;
        }

        T *get() const noexcept
        { return __ptr.get(); }

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
    __std::exceptional_shared_ptr<int> intPtr(std::make_shared<int>(12));

    __std::exceptional_shared_ptr<foo> exceptional;
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

    __std::exceptional_shared_ptr<int> intPtr2 = std::make_shared<int>(12); // compile-error
    __std::exceptional_shared_ptr<foo> fooPtr = std::make_shared<foo>();// compile-error
    return 0;
}