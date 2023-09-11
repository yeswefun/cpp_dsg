#include <iostream>

using namespace std;

class Computer {
public:
    void run();
};

//方案整合商 & 操作系统, 多 对 多
//多维变化用桥接
class HpWin7 : public Computer {};
class HpWin8 : public Computer {};
class HpWin10 : public Computer {};

/*
一维扩展看继承
多维变化用桥接
*/
int main() {
    return 0;
}