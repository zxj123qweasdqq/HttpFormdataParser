#ifndef __REFLECTORFACTORY_
#define __REFLECTORFACTORY_

#include <iostream>
#include<string>
#include<map>
#include <functional>

//#using std namespce;

//定义函数指针
//typedef void* (*create_fun)(void);
#define FUNC std::function<void*(void)>
class ReflectorFactory {
public:
    ~ReflectorFactory() {};
    void* getClassByName(std::string name) {
        std::map<std::string, FUNC>::iterator it = class_map.find(name);
        if (it == class_map.end()) { return NULL; }
        FUNC fun = it->second;
        if (!fun) { return NULL; }

        return fun();
    }

    void registClass(std::string name, FUNC&& generator) {
        class_map[name] = generator;
    }
    static ReflectorFactory& getInstance() {
        static ReflectorFactory fac;
        return fac;
    }

private:
    ReflectorFactory() {}; 
    std::map<std::string, FUNC> class_map;
};

#endif

//#define REGISTER(CLASS_NAME) \
//RegisterAction g_register_action_##CLASS_NAME(#CLASS_NAME, []()\
//{\
//    return new CLASS_NAME(); \
//});