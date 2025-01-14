/***
 * @Author: Morgan Woods weiyiding0@gmail.com
 * @Date: 2025-01-14 19:03:51
 * @LastEditors: Morgan Woods weiyiding0@gmail.com
 * @LastEditTime: 2025-01-14 19:04:17
 * @FilePath: /zack/src/SmartPtr/lambdaDeleter.cpp
 * @Description:
 */

#include <cstdio>
#include <iostream>
#include <memory>

int main() {
    {
        auto fileDeleter = [](FILE* fp) {
            if (fp) {
                std::cout << "Closing file via lambda." << std::endl;
                fclose(fp);
            }
        };

        std::unique_ptr<FILE, decltype(fileDeleter)> filePtr(
            fopen("test.txt", "w"), fileDeleter);
        if (filePtr) {
            std::cout << "File opened successfully." << std::endl;
            fprintf(filePtr.get(), "Hello, Lambda!\n");
        }
    }  // 自动关闭文件

    std::cout << "File closed." << std::endl;
    return 0;
}
