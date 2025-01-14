/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 18:52:56
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:53:00
 * @FilePath: /zack/src/SmartPtr/weak2shared.cpp
 * @Description:
 */

/*
 * wp.lock() 返回一个 shared_ptr，如果对象依然存在，则有效。
 * sp.reset() 释放资源后，wp.lock() 无法获取有效的 shared_ptr。
 */

#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;

    if (auto locked = wp.lock()) {  // 尝试获取 shared_ptr
        std::cout << "Value: " << *locked << std::endl;
    } else {
        std::cout << "Object no longer exists." << std::endl;
    }

    sp.reset();  // 释放资源

    if (auto locked = wp.lock()) {  // 再次尝试获取 shared_ptr
        std::cout << "Value: " << *locked << std::endl;
    } else {
        std::cout << "Object no longer exists." << std::endl;
    }

    return 0;
}