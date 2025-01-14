/*** 
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 18:36:18
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:45:06
 * @FilePath: /zack/src/SmartPtr/sharedPtr.cpp
 * @Description: 
 */

/*
 * 创建 sp1，引用计数为1。
 * 拷贝构造 sp2，引用计数增加到2。
 * 拷贝赋值 sp3，引用计数增加到3。
 * sp2.reset(new Test(200))：
  - 原 Test(100) 的引用计数减少到2。
  - 分配新的 Test(200)，sp2 拥有它，引用计数为1。
 * 程序结束时：
 * sp1 和 sp3 释放 Test(100)，引用计数降到0，资源被销毁。
 * sp2 释放 Test(200)，引用计数为0，资源被销毁。
 */
#include <iostream>
#include <memory>

#include "Test.hpp"

int main() {
    // 创建一个 shared_ptr
    std::shared_ptr<Test> sp1(new Test(100));
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
    sp1->show();

    // 通过拷贝构造共享所有权
    std::shared_ptr<Test> sp2 = sp1;
    std::cout << "After sp2 = sp1:" << std::endl;
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;

    // 通过拷贝赋值共享所有权
    std::shared_ptr<Test> sp3;
    sp3 = sp2;
    std::cout << "After sp3 = sp2:" << std::endl;
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
    std::cout << "sp3 use_count: " << sp3.use_count() << std::endl;

    // 重置 shared_ptr
    sp2.reset(new Test(200));
    std::cout << "After sp2.reset(new Test(200)):" << std::endl;
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
    std::cout << "sp3 use_count: " << sp3.use_count() << std::endl;
    sp2->show();

    // 自动释放资源
    std::cout << "Exiting main..." << std::endl;
    return 0;
}