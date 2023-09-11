#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t mutex;

class Singleton {
private:
    Singleton() {
        cout << "构造一个 Singleton 对象: " << this << endl;
    }
public:
    static Singleton* getInstance() {
/*
		if (instance == nullptr) {
			usleep(100000);
			instance = new Singleton;
		}
*/
/*
        if (instance == nullptr) {
			if (instance == nullptr) {
				usleep(100000);
            	instance = new Singleton;
			}
        }
*/
        if (instance == nullptr) {
			usleep(100000);
			pthread_mutex_lock(&mutex);
			if (instance == nullptr) {
				usleep(100000);
            	instance = new Singleton;
			}
			pthread_mutex_unlock(&mutex);
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
        cout << arg  << " *************** " << Singleton::getInstance() << endl;
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
	pthread_mutex_init(&mutex, NULL);

	pthread_t tids[NUM];
	
	for (int i = 0; i < NUM; i++) {
		pthread_create(&tids[i], NULL, thread_task, new int(i));
	}

	void *status = nullptr;
	for (int i = 0; i < NUM; i++) {
		pthread_join(tids[i], &status);
		cout << "status: " << *(int*)status << endl;
		delete (int*)status;
	}

	pthread_mutex_destroy(&mutex);
    return 0;
}
