/*** 
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-13 20:03:30
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:09:42
 * @FilePath: /zack/src/MemoryPool/MemoryPool.cpp
 * @Description: 
 */
#include <iostream>
#include "MemoryPool/MemoryPool.hpp"

MemoryPool::MemoryPool(size_t objSize, size_t totalSize)
    : objSize(objSize), totalSize(totalSize) {
    pool = (char*)malloc(objSize * totalSize);
    if (!pool) {
        throw std::bad_alloc();
    }

    // 初始化freeList
    for (size_t i = 0; i < totalSize; i++) {
        freeList.push(pool + i * objSize);
    }
}

MemoryPool::~MemoryPool() {
    std::cout << "MemoryPool::~MemoryPool()" << std::endl;
    free(pool);
}

// 用户层面malloc，从池子里分配内存
void* MemoryPool::allocate() {
    if (freeList.empty()) throw std::bad_alloc();  // 进攻式编程
    // 如果return nullptr; 则是一种防御式编程
    void* p = freeList.top();
    freeList.pop();
    return p;
}

// 用户层面free，将内存归还给池子
void* MemoryPool::deallocate(void* ptr) {
    freeList.push(ptr);

    return nullptr;
}

// 池子里的剩余大小
int MemoryPool::left() { return freeList.size(); }
