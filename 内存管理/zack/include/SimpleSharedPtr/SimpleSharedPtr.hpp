#ifndef SIMPLE_SHARED_PTR_HPP
#define SIMPLE_SHARED_PTR_HPP

#include <iostream>

// 控制块结构
struct ControlBlock {
    int ref_count;

    ControlBlock() : ref_count(1) {}
};

// 简化版的 shared_ptr 实现
template <typename T>
class SimpleSharedPtr {
   private:
    T* ptr;                 // 指向管理的对象
    ControlBlock* control;  // 指向控制块

    // 释放当前资源
    void release() {
        if (control) {
            control->ref_count--;
            std::cout << "Decremented ref_count to " << control->ref_count
                      << std::endl;
            if (control->ref_count == 0) {
                delete ptr;
                delete control;
                std::cout << "Resource and ControlBlock destroyed."
                          << std::endl;
            }
        }
        ptr = nullptr;
        control = nullptr;
    }

   public:
    // 默认构造函数
    SimpleSharedPtr() : ptr(nullptr), control(nullptr) {
        std::cout << "Default constructed SimpleSharedPtr (nullptr)."
                  << std::endl;
    }

    // 参数化构造函数
    explicit SimpleSharedPtr(T* p) : ptr(p) {
        if (p) {
            control = new ControlBlock();
            std::cout << "Constructed SimpleSharedPtr, ref_count = "
                      << control->ref_count << std::endl;
        } else {
            control = nullptr;
        }
    }

    // 拷贝构造函数
    SimpleSharedPtr(const SimpleSharedPtr& other)
        : ptr(other.ptr), control(other.control) {
        if (control) {
            control->ref_count++;
            std::cout << "Copied SimpleSharedPtr, ref_count = "
                      << control->ref_count << std::endl;
        }
    }

    // 拷贝赋值操作符
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->ref_count++;
                std::cout << "Assigned SimpleSharedPtr, ref_count = "
                          << control->ref_count << std::endl;
            }
        }
        return *this;
    }

    // 移动构造函数
    SimpleSharedPtr(SimpleSharedPtr&& other) noexcept
        : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
        std::cout << "Moved SimpleSharedPtr." << std::endl;
    }

    // 移动赋值操作符
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
            std::cout << "Move-assigned SimpleSharedPtr." << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~SimpleSharedPtr() { release(); }

    // 解引用操作符
    T& operator*() const { return *ptr; }

    // 箭头操作符
    T* operator->() const { return ptr; }

    // 获取引用计数
    int use_count() const { return control ? control->ref_count : 0; }

    // 获取裸指针
    T* get() const { return ptr; }

    // 重置指针
    void reset(T* p = nullptr) {
        release();
        ptr = p;
        if (p) {
            control = new ControlBlock();
            std::cout << "Reset SimpleSharedPtr, ref_count = "
                      << control->ref_count << std::endl;
        } else {
            control = nullptr;
        }
    }
};
#endif  // SIMPLE_SHARED_PTR_HPP