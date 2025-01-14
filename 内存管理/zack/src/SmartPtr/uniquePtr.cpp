/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 18:25:31
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:28:20
 * @FilePath: /zack/src/SmartPtr/uniquePtr.cpp
 * @Description:
 */

/* 
 * ptr1 拥有 Test(100)，ptr2 拥有 Test(200)。
 * 通过 std::move 将 ptr1 的所有权转移到 ptr3，ptr1 变为空。
 * ptr2.reset(new Test(300)) 释放了原有的 Test(200)，并拥有新的 Test(300)。
 * 程序结束时，ptr3 和 ptr2 自动释放各自拥有的资源。 
*/

#include <iostream>
#include <memory>

#include "Test.hpp"

int main() {
    std::unique_ptr<Test> ptr1(new Test(1));
    ptr1->show();

    // 使用 make_unique
    std::unique_ptr<Test> ptr2 = std::make_unique<Test>(200);
    ptr2->show();

    // 使用 std::move 将 unique_ptr 转移所有权
    std::unique_ptr<Test> ptr3 = std::move(ptr1);
    if (!ptr1) {
        std::cout << "ptr1 is now nullptr after move." << std::endl;
    }
    ptr3->show();

    // 重置 unique_ptr
    ptr2.reset(new Test(300));
    ptr2->show();

    return 0;
}
