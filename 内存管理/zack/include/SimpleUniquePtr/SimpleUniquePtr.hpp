/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 17:54:00
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 17:55:17
 * @FilePath: /zack/include/SimpleUniquePtr/SimpleUniquePtr.hpp
 * @Description:
 */

#ifndef SIMPLE_UNIQUE_PTR_HPP
#define SIMPLE_UNIQUE_PTR_HPP

template <typename T>
class SimpleUniquePtr {
   private:
    T* ptr;

   public:
    SimpleUniquePtr() : ptr(nullptr) {}
    SimpleUniquePtr(T* p) : ptr(p) {}

    ~SimpleUniquePtr() { delete ptr; }

    // 禁止拷贝构造和拷贝赋值
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;

    // 支持移动构造和移动赋值，以转移所有权
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;       // 释放当前对象管理的资源
            ptr = other.ptr;  // 转移所有权
            other.ptr = nullptr;
        }
        return *this;
    }

    // 重载解引用运算符
    T& operator*() const { return *ptr; }

    // 重载箭头运算符
    T* operator->() const { return ptr; }

    // 获取裸指针
    T* get() const { return ptr; }

    // 释放所有权，返回裸指针为nullptr
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置，释放当前管理的资源，并指向新的资源
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

#endif  // SIMPLE_UNIQUE_PTR_HPP