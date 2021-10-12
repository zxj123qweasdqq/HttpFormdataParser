#ifndef __ROUTER_H
#define __ROUTER_H
#include <functional>
#include "workflow/WFTaskFactory.h"
#include "workflow/HttpMessage.h"
#include "workflow/WFHttpServer.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"
#include "workflow/WFFacilities.h"
#include "workflow/HttpUtil.h"

class Router {
public:
	~Router();
	Router();
	Router(const char* className, const char* method, WFHttpTask* server_task, const char* root);
	void* CreateFileOperate();
	void CreateTask();
	void* CreateProcessPost();
public:
	std::function<void* (void)> Functional;
};

#endif