/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-13 20:58:54
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-13 20:59:00
 * @FilePath: /拷贝控制/MyString.h
 * @Description:
 */
#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <iostream>

class MyString {
   public:
    MyString() : _data(nullptr) {}
    MyString(const char* str);

    MyString(const MyString& str);
    MyString& operator=(const MyString& str);

    MyString(MyString&& str);
    MyString& operator=(MyString&& str);

    MyString& operator+(const MyString& str);
    bool operator==(const MyString str);
    friend std::ostream& operator<<(std::ostream& out, const MyString& str);

   private:
    char* _data;
};

#endif  // !MYSTRING_H