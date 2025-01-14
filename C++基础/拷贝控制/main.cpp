/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-13 21:25:55
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-13 21:26:04
 * @FilePath: /拷贝控制/main.cpp
 * @Description:
 */
#include <iostream>

#include "MyString.h"

int main() {
    MyString s1("hello");
    MyString s2(s1);
    MyString s3 = s1;
    MyString s4 = "world";
    MyString s5 = s4 + s1;
    MyString s6 = s4 + "world";
    return 0;
}