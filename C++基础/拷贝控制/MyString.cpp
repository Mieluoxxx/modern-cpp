#include "MyString.h"

// 构造函数，传入字符串
MyString::MyString(const char* str) {
    if (str != nullptr) {
        _data = new char[strlen(str) + 1];
        strcpy(_data, str);
    } else {
        _data = nullptr;
    }
}

// 拷贝构造函数
MyString::MyString(const MyString& str) {
    if (str._data != nullptr) {
        _data = new char[strlen(str._data) + 1];
        strcpy(_data, str._data);
    } else {
        _data = nullptr;
    }
}

// 拷贝赋值运算符
MyString& MyString::operator=(const MyString& str) {
    if (this != &str) {
        delete[] _data;
        if (str._data != nullptr) {
            _data = new char[strlen(str._data) + 1];
            strcpy(_data, str._data);
        } else {
            _data = nullptr;
        }
    }
    return *this;
}

// 移动构造函数
MyString::MyString(MyString&& str) {
    _data = str._data;
    str._data = nullptr;
}

// 移动赋值运算符
MyString& MyString::operator=(MyString&& str) {
    if (this != &str) {
        delete[] _data;
        _data = str._data;
        str._data = nullptr;
    }
    return *this;
}

// +运算符重载
MyString& MyString::operator+(const MyString& str) {
    char* new_data = new char[strlen(_data) + strlen(str._data) + 1];
    strcpy(new_data, _data);
    strcat(new_data, str._data);
    delete[] _data;
    _data = new_data;
    return *this;
}

// ==运算符重载
bool MyString::operator==(const MyString str) {
    if (_data == nullptr && str._data == nullptr) {
        return true;
    } else if (_data == nullptr || str._data == nullptr) {
        return false;
    } else {
        return strcmp(_data, str._data) == 0;
    }
}

// <<运算符重载
std::ostream& operator<<(std::ostream& out, const MyString& str) {
    if (str._data != nullptr) {
        out << str._data;
    } else {
        out << "nullptr";
    }
    return out;
}