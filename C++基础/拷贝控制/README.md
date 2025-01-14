# 拷贝控制

**拷贝构造函数与拷贝赋值运算符**

## 拷贝构造函数

**定义**：用于创建一个新对象，并复制现有对象的成员。
**语法**：`ClassName(const className& other);`

使用引用类型是为了避免无限递归调用拷贝构造函数。
使用const是为了保证不会修改传入的对象。

## 拷贝赋值运算符
**定义**：用于将一个已有对象的值赋给另一个已有对象。
**语法**：`ClassName& operator=(const ClassName& other);`

`this`指针指向当前对象

# 移动语义
**移动语义**：允许资源的所有权从一个对象转移到另一个对象，避免不必要的拷贝，提高性能。

## 移动构造函数与移动赋值运算符
移动构造函数：`ClassName(ClassName && other) noexcept;`
移动赋值运算符：`ClassName& operator=(ClassName&& other) noexcept;`
