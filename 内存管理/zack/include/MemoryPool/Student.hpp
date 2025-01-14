/*** 
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 16:56:55
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 17:54:58
 * @FilePath: /zack/include/Student.h
 * @Description: 
 */
#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

class Student {
   public:
    Student() : name("Jerry"), age(10) {};
    Student(std::string name, int age) : name(name), age(age) {};
    ~Student() = default;

    std::string get_name() const { return name; }
    int get_age() const { return age; }

    std::string name;
    int age;
};

#endif  // STUDENT_HPP