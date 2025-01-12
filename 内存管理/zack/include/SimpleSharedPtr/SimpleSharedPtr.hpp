/***
 * @Author: error: error: git config user.name & please set dead value or
 * install git && error: git config user.email & please set dead value or
 * install git & please set dead value or install git
 * @Date: 2025-01-08 21:13:44
 * @LastEditors: error: error: git config user.name & please set dead value or
 * install git && error: git config user.email & please set dead value or
 * install git & please set dead value or install git
 * @LastEditTime: 2025-01-08 21:16:00
 * @FilePath: /zack/include/SimpleSharedPtr/SimpleSharedPtr.hpp
 * @Description:
 */
#ifndef SIMPLESHARED_PTR_HPP
#define SIMPLESHARED_PTR_HPP

struct ControlBlock {
    int ref_count;
    ControlBlock() : ref_count(1) {}
};

template <typename T>
class SimpleSharedPtr {
   private:
    T *ptr;
    ControlBlock *control;
    void release() {
        if (control) {
            --control->ref_count;
            if (count->ref_count == 0) {
                delete ptr;
                ptr = nullptr;
                delete control;
                control = nullptr;
            }
        }
    }

   public:
    // 隐式转换: SimpleSharedPtr p = new Student();
    // 显示构造: SimpleSharedPtr p(new Student());
    explicit SimpleSharedPtr(T *p) : ptr(p) {
        if (p)
            control = new ControlBlock();
        else
            control = nullptr;
    }

    ~SimpleSharedPtr() {
        if (ptr) {
            release();
        }
    }

    // 拷贝构造 SimpleSharedPtr s1(s2);
    SimpleSharedPtr(const SimpleSharedPtr<T> &s)
        : ptr(s.ptr), control(s.control) {
        if (control) {
            ++control->ref_count;
        }
    }

    // 赋值操作 SimpleSharedPtr s1 = s2;
    SimpleSharedPtr<T> &operator=(const SimpleSharedPtr<T> &s) {
        if (this != &s) {   // 防止自赋值
            realase();
            ptr = s.ptr;
            control = s.control;
            if (control) {
                ++control->ref_count;
            }
        }
        return *this; // 返回引用
    }
};

#endif  // SIMPLESHARED_PTR_HPP
