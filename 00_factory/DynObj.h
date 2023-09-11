
#ifndef DYNOBJ_H_
#define DYNOBJ_H_

#include <string>
#include <map>

typedef void* (*Constructor)();


class CObjFactory {
public:
    static void registerClass(std::string className, Constructor constructor) {
        constructors()[className] = constructor;
    }

    static void* createObject(const std::string& className) {
        Constructor constructor = nullptr;
        if (constructors().find(className) != constructors().end()) {
            // first -> key
            // seconde -> value
            constructor = constructors().find(className)->second;
        }
        if (constructor == nullptr) {
            return nullptr;
        }
        return (*constructor)();
    }
private:
    /*
        key: string, 动态创建的类名
        value: 
    */
    inline static std::map<std::string, Constructor>& constructors() {
        static std::map<std::string, Constructor> instance;
        return instance;
    }
};

#endif // DYNOBJ_H_
