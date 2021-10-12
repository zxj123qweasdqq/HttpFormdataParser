#ifndef __PROCESSPOST_H
#define __PROCESSPOST_H

#include <iostream>
#include <unordered_map>
#include "workflow/WFTaskFactory.h"
#include "workflow/HttpMessage.h"
#include "workflow/WFHttpServer.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"
#include "workflow/WFFacilities.h"
#include "workflow/HttpUtil.h"



class ProcessPost {
public:
	~ProcessPost();
	ProcessPost();
	void print();
	void arrayUpload();
	void setServerInfo(WFHttpTask* servertask);
	//void pwrite_callback(WFFileIOTask* task);
public:
	std::unordered_map<std::string, void (ProcessPost::*)()>funcList;
	std::string filepath;
	WFHttpTask* server_task;
};

#endif