#include"Router.h"
#include"FileOperate.h"
#include"ProcessPost.h"
#include"ReflectorFactory.h"
#include <string.h>

Router::~Router()
{
}
Router::Router()
{

}
Router::Router(const char* className, const char* method, WFHttpTask* server_task, const char* root)
{
    if (! strcmp(className,"FileOperate")) {
        auto  test=std::bind(&Router::CreateFileOperate, this);
        ReflectorFactory::getInstance().registClass("FileOperate", test);
        FileOperate* t = (FileOperate*)ReflectorFactory::getInstance().getClassByName("FileOperate");
        if (!t) {
            std::cout << "get instnce FileOperate err;" << std::endl;
            return;
        }
        void (FileOperate:: * ptr)() = t->funcList.at(method);
        t->setServerInfo(server_task, root);
        (t->*ptr)();
        delete t;
    }
    else if (!strcmp(className, "ProcessPost"))
    {
        auto  test = std::bind(&Router::CreateProcessPost, this);
        ReflectorFactory::getInstance().registClass("ProcessPost", test);
        ProcessPost* t = (ProcessPost*)ReflectorFactory::getInstance().getClassByName("ProcessPost");
        if (!t) {
            std::cout << "get instnce ProcessPost err;" << std::endl;
            return;
        }
        void (ProcessPost:: * ptr)() = t->funcList.at(method);
        t->setServerInfo(server_task);
        (t->*ptr)();
        delete t;
    }
    else if (className == "task")
    {
        std::cout << "task API exec" << std::endl;
    }
}

void* Router::CreateFileOperate()
{
	FileOperate* t = new FileOperate;
	return (t == NULL) ? NULL : t;
}

void Router::CreateTask()
{
}

void* Router::CreateProcessPost()
{
    ProcessPost* t = new ProcessPost;
    return (t == NULL) ? NULL : t;

}
