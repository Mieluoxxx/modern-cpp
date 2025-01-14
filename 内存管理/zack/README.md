## 引言
C++ 引入智能指针的主要目的是为了自动化内存管理，减少手动 `new` 和 `delete` 带来的复杂性和错误。智能指针通过 `RAII`（资源获取即初始化）机制，在对象生命周期结束时自动释放资源，从而有效防止内存泄漏和资源管理错误。

### 原生指针
原生指针是 C++ 最基本的指针类型，允许程序员直接管理内存。然而，原生指针存在以下问题：
- **内存泄漏**：未释放动态分配的内存。
- **悬挂指针**：指针指向已释放或未初始化的内存。
- **双重释放**：多次释放同一内存区域。

### 智能指针的优势
智能指针通过封装原生指针，自动管理内存，解决上述问题。主要优势包括：
- **自动销毁**：在智能指针生命周期结束时自动释放资源。
- **引用计数**：共享智能指针能够跟踪引用数量，确保资源在最后一个引用结束时释放。
- **避免内存泄漏**：通过 RAII 机制自动管理资源生命周期。
- **类型安全**：提供更严格的类型检查，减少错误。

## std::unique_ptr
`std::unique_ptr` 是一种独占所有权的智能指针，任何时刻只能有一个 `unique_ptr` 实例拥有对某个对象的所有权。不能被拷贝，只能被移动。

主要特性：
- **独占所有权**：确保资源在一个所有者下。
- **轻量级**：没有引用计数，开销小。
- **自动释放**：在指针销毁时自动释放资源。

`unique_ptr` 提供多种构造函数和赋值操作，以支持不同的使用场景。
- **默认构造函数**：创建一个空的 `unique_ptr`。
- **指针构造函数**：接受一个裸指针，拥有其所有权。
- **移动构造函数**：将一个 `unique_ptr` 的所有权转移到另一个 `unique_ptr`。
- **移动赋值操作符**：将一个 `unique_ptr` 的所有权转移到另一个 `unique_ptr`。


## std::shared_ptr
`std::shared_ptr` 是一种共享所有权的智能指针，允许多个 `shared_ptr` 实例共享对同一个对象的所有权。通过引用计数机制，管理资源的生命周期。

主要特性：
- **共享所有权**：多个 `shared_ptr` 可以指向同一个对象。
- **引用计数**：跟踪有多少 `shared_ptr` 实例指向同一对象。
- **自动释放**：当引用计数为0时，自动释放资源。

### 引用计数与控制块
`shared_ptr` 背后依赖一个**控制块**（`Control Block`），用于存储引用计数和指向实际对象的指针。控制块的主要内容包括：
- **强引用计数**（use_count）：表示有多少个 `shared_ptr` 指向对象。
- **弱引用计数**（weak_count）：表示有多少个 `weak_ptr` 指向对象（不增加强引用计数）。

`shared_ptr` 提供多种构造函数和赋值操作，以支持不同的使用场景。
- **默认构造函数**：创建一个空的 `shared_ptr`。
- **指针构造函数**：接受一个裸指针，拥有其所有权。
- **拷贝构造函数**：增加引用计数，共享对象所有权。
- **移动构造函数**：转移所有权，源 `shared_ptr` 变为空。
- **拷贝赋值操作符**：释放当前资源，增加引用计数，指向新对象。
- **移动赋值操作符**：释放当前资源，转移所有权，源 `shared_ptr` 变为空。


## std::weak_ptr
`std::weak_ptr` 是一种不拥有对象所有权的智能指针，用于观察但不影响对象的生命周期。主要用于解决 `shared_ptr` 之间的循环引用问题。

主要特性：
- **非拥有所有权**：不增加引用计数。
- **可从 `shared_ptr` 生成**：通过 `std::weak_ptr` 可以访问 `shared_ptr` 管理的对象。
- **避免循环引用**：适用于双向关联或观察者模式。

## 避免循环引用
在存在双向关联（如父子关系）时，使用多个 `shared_ptr` 可能导致循环引用，导致内存泄漏。此时，可以使用 `weak_ptr` 来打破循环。

**场景：双向关联导致循环引用**
```cpp
#include <iostream>
#include <memory>

class B; // 前向声明

class A {
public:
    std::shared_ptr<B> ptrB;

    A() { std::cout << "A Constructor" << std::endl; }
    ~A() { std::cout << "A Destructor" << std::endl; }
};

class B {
public:
    std::shared_ptr<A> ptrA;

    B() { std::cout << "B Constructor" << std::endl; }
    ~B() { std::cout << "B Destructor" << std::endl; }
};

int main() {
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->ptrB = b;
        b->ptrA = a;
    }
    std::cout << "Exiting main..." << std::endl;
    return 0;
}
```

输出：
```
A Constructor
B Constructor
Exiting main...
A Destructor
B Destructor
```

## 解决方案：使用 `weak_ptr`
```cpp
#include <iostream>
#include <memory>

#include "Test.hpp"

class B;  // 前向声明

class A {
   public:
    std::shared_ptr<B> ptrB;

    A() { std::cout << "A Constructor" << std::endl; }
    ~A() { std::cout << "A Destructor" << std::endl; }
};

class B {
   public:
    std::weak_ptr<A> ptrA;  // 使用 weak_ptr

    B() { std::cout << "B Constructor" << std::endl; }
    ~B() { std::cout << "B Destructor" << std::endl; }
};

int main() {
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->ptrB = b;
        b->ptrA = a;
    }
    std::cout << "Exiting main..." << std::endl;
    return 0;
}
```

输出：
```
A Constructor
B Constructor
A Destructor
B Destructor
Exiting main...
```

`weak_ptr` 不能直接访问对象，需要通过 `lock()` 方法转换为 `shared_ptr`，并检查对象是否仍然存在。

## 自定义删除器
有时，默认的 `delete` 操作不适用于所有资源管理场景。
此时，可以使用自定义删除器来指定资源释放的方式。
例如，管理文件句柄、网络资源或自定义清理逻辑。

使用 `std::unique_ptr` 搭配 `lambda` 删除器管理 `FILE*`。
提供了更灵活和简洁的删除器实现。

## 最佳实践与常见陷阱

### 1. 选择合适的智能指针
`std::unique_ptr`：
用于明确的**独占所有权**场景。
适用于资源的**单一管理者**或需要**所有权转移**的情况。
更**轻量**，**性能更优**。
`std::shared_ptr`：
用于**共享所有权**的场景。
需要**多个指针共同管理同一资源**时使用。
**引用计数带来一定的性能开销**。
`std::weak_ptr`：
用于**观察不拥有资源**的场景。
适用于需要**避免循环引用**或**只需临时访问资源**的情况。

### 2. 避免循环引用
在使用 `shared_ptr` 时，特别是在对象间存在双向引用时，容易导致循环引用，内存泄漏。
使用 `weak_ptr` 打破循环引用。

### 3. 使用 `make_shared` 与 `make_unique`
优先使用 `make_shared` 和 `make_unique` 来创建智能指针，避免直接使用 `new`，提高效率和异常安全性。
```cpp
auto sp = std::make_shared<Test>(100);
auto up = std::make_unique<Test>(200);
```

### 4. 不要混用原生指针与智能指针
避免在智能指针管理的对象上同时使用原生指针进行管理，防止重复释放或不安全访问。

### 5. 理解智能指针的所有权语义
深入理解不同智能指针的所有权规则，避免误用导致资源管理错误。