#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;


class Singleton {
private:
    Singleton() {
        cout << "构造一个 Singleton 对象: " << this << endl;
    }
public:
    // 懒汉式 - 问题
    static Singleton* getInstance() {
        if (instance == nullptr) {
			usleep(100000);
            instance = new Singleton;
        }
        return instance;
    }
private:
    static Singleton *instance;
};

Singleton* Singleton::instance = nullptr;

void* thread_task(void *args) {
	int arg = *(int*)args;
    for (int x = 0; x < 6; x++) {
        cout << Singleton::getInstance() << endl;
    }
	pthread_exit(args);
	return nullptr;
}

const int NUM = 10;

/*
在 C++ 中，构造函数是非线程安全的
# g++ Singleton2.cpp -lpthread && ./a.out
*/
int main() {
	pthread_t tids[NUM];
	
	for (int i = 0; i < NUM; i++) {
		pthread_create(&tids[i], NULL, thread_task, new int(i));
        //TODO: (void *)&i 这样传递是否会有问题
        // pthread_create(&tids[i], NULL, thread_task, (void *)&i); // 不需要 delete (int*)status;
	}

	void *status = nullptr;
	for (int i = 0; i < NUM; i++) {
		pthread_join(tids[i], &status);
		//cout << "status: " << *(int*)status << endl;
		delete (int*)status;
	}

    return 0;
}
