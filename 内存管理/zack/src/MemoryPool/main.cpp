/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-13 20:03:30
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:09:36
 * @FilePath: /zack/src/MemoryPool/main.cpp
 * @Description:
 */

#include <iostream>

#include "MemoryPool/MemoryPool.hpp"
#include "MemoryPool/Student.hpp"

int main() {
    try {
        // 创建一个内存池，最多存储3个Student对象
        MemoryPool pool(sizeof(Student), 3);
        void* mem1 = pool.allocate();
        void* mem2 = pool.allocate();
        void* mem3 = pool.allocate();

        // 将这片内存空间初始化为Student对象
        Student* obj1 = new (mem1) Student("Tom", 20);
        std::cout << obj1->get_age() << std::endl;

        auto obj2 = new (mem2) Student();
        std::cout << obj2->get_name() << std::endl;

        // std::cout << pool.left() << std::endl;
        auto obj3 = new (mem3) Student("Mickey", 15);
        std::cout << obj3->get_name() << std::endl;

        void* mem4 = pool.allocate();
        auto obj4 = new (mem4) Student();  // 这里会抛出异常，因为内存池已满

        obj1->~Student();
        obj2->~Student();
        obj3->~Student();

        pool.deallocate(mem1);
        pool.deallocate(mem2);
        pool.deallocate(mem3);

        obj4->~Student();
        pool.deallocate(mem4);
        // 这里会调用析构函数，释放内存池中的内存
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << '\n';
        return 1;
    }
    return 0;
}