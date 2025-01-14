/*** 
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 18:23:48
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 18:23:52
 * @FilePath: /zack/include/Test.hpp
 * @Description: 
 */
#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

// 测试类
class Test {
   public:
    Test(int val) : value(val) {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test() { std::cout << "Test Destructor: " << value << std::endl; }
    void show() const { std::cout << "Value: " << value << std::endl; }

   private:
    int value;
};

#endif // TEST_HPP