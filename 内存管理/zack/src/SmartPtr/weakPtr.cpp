/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 18:47:30
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:51:09
 * @FilePath: /zack/src/SmartPtr/weakPtr.cpp
 * @Description:
 */

/**
 * 解析：
 * B 使用 weak_ptr 指向 A，不增加引用计数。
 * a 和 b 离开作用域，引用计数降为0，资源被正确释放。
 * 防止了循环引用，避免了内存泄漏。
 */

#include <iostream>
#include <memory>

class B;  // 前向声明

class A {
   public:
    std::shared_ptr<B> ptrB;

    A() { std::cout << "A Constructor" << std::endl; }
    ~A() { std::cout << "A Destructor" << std::endl; }
};

class B {
   public:
    std::weak_ptr<A> ptrA;  // 使用 weak_ptr

    B() { std::cout << "B Constructor" << std::endl; }
    ~B() { std::cout << "B Destructor" << std::endl; }
};

int main() {
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->ptrB = b;
        b->ptrA = a;
    }
    std::cout << "Exiting main..." << std::endl;
    return 0;
}