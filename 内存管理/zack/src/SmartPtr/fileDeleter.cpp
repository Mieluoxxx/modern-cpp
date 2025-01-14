/*** 
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 18:58:55
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 19:02:41
 * @FilePath: /zack/src/SmartPtr/filedeleter.cpp
 * @Description: 
 */

/*
 * 自定义删除器 FileDeleter 用于在 shared_ptr 被销毁时关闭文件。
 * 使用 filePtr.get() 获取原生 FILE* 指针进行文件操作。
 *离开作用域时，自动调用 FileDeleter 关闭文件。
 */

#include <cstdio>
#include <iostream>
#include <memory>

struct FileDeleter {
    void operator()(FILE* fp) const {
        if (fp) {
            std::cout << "Closing file" << std::endl;
            fclose(fp);
        }
    }
};

int main() {
    {
        std::shared_ptr<FILE> filePtr(fopen("example.txt", "w"), FileDeleter());
        if (filePtr) {
            std::cout << "File opened successfully." << std::endl;
            // 使用 filePtr 进行文件操作
            fprintf(filePtr.get(), "Hello, World!\n");
        }
    } // 自动关闭文件

    std::cout << "Existing main..." << std::endl;
    return 0;
}