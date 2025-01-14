#include <iostream>

#include "SimpleUniquePtr/SimpleUniquePtr.hpp"
#include "Test.hpp"

int main() {
    // 创建一个 SimpleUniquePtr
    SimpleUniquePtr<Test> ptr1(new Test(1));
    ptr1->show();
    (*ptr1).show();

    // 移动所有权到 ptr2
    SimpleUniquePtr<Test> ptr2 = std::move(ptr1);
    if (ptr1.get() == nullptr) {
        std::cout << "ptr1 is now nullptr after move." << std::endl;
    }
    ptr2->show();

    // 释放所有权
    Test* rawPtr = ptr2.release();
    if (ptr2.get() == nullptr) {
        std::cout << "ptr2 is now nullptr after release." << std::endl;
    }
    rawPtr->show();
    delete rawPtr;  // 手动删除

    // 使用 reset
    ptr2.reset(new Test(2));
    ptr2->show();

    ptr2.reset();  // 自动删除
    if (ptr2.get() == nullptr) {
        std::cout << "ptr2 is now nullptr after reset." << std::endl;
    }

    return 0;
}