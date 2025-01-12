/*** 
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-08 18:09:18
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-08 19:53:11
 * @FilePath: /zack/include/MemoryPool/MemoryPool.hpp
 * @Description: 符合RAII原则的内存池
 */
#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <iostream>
#include <stack>

// 线程安全（加锁）问题
// 上层加锁：本案例选择这种
// 内存池加锁：会有开销

class MemoryPool {
   public:
    MemoryPool(size_t objSize, size_t totalNum);
    ~MemoryPool();
   void* allocate();
   void* deallocate(void *ptr);
   int left();

   private:
    size_t objSize;
    size_t totalSize;
    char* pool;
    std::stack<void*> freeList;
};

#endif  // MEMORYPOOL_H
