
#ifndef DYNOBJ_H_
#define DYNOBJ_H_

#include <string>
#include <map>

typedef void* (*Constructor)();


class CObjFactory {
public:
    static void registerClass(const std::string& className, Constructor constructor) {
        constructors()[className] = constructor;
    }

    static void* createObject(const std::string& className) {
        Constructor constructor = nullptr;
        if (constructors().find(className) != constructors().end()) {
            // first -> key
            // second -> value
            constructor = constructors().find(className)->second;
        }
        if (constructor == nullptr) {
            return nullptr;
        }
        //只能调用无参构造
        return (*constructor)();
    }
private:
    /*
        key: string, 动态创建的类名
        value: 函数指针

        //TODO: 为什么下面不能使用 const std::string& 呢?
    */
    inline static std::map<const std::string, Constructor>& constructors() {
        static std::map<const std::string, Constructor> instance;
        return instance;
    }
};


/*
class ImplOneHelper {
public:
    ImplOneHelper() {
        CObjFactory::registerClass("ImplOne", ImplOneHelper::createObjFunc);
    }

    static void* createObjFunc() {
        return new ImplOne;
    }
};
*/
#define REG_CLASS(class_name) class class_name##Helper { \
public: \
    class_name##Helper() { \
        CObjFactory::registerClass(#class_name, class_name##Helper::createObjFunc); \
    } \
    static void* createObjFunc() { \
        return new class_name; \
    } \
}; \
class_name##Helper class_name##_dummy
// class_name##Helper class_name##helper

#endif // DYNOBJ_H_
