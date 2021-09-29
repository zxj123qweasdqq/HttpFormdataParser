#ifndef __FILEOPERATE_H
#define __FILEOPERATE_H

#include <iostream>
#include <unordered_map>
#include "workflow/WFTaskFactory.h"
#include "workflow/HttpMessage.h"
#include "workflow/WFHttpServer.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"
#include "workflow/WFFacilities.h"
#include "workflow/HttpUtil.h"



class FileOperate {
public:
	~FileOperate();
	 FileOperate();
	 void print();
	 void fileUpload();
	 void setServerInfo(WFHttpTask* servertask, const char* root);
	 void pwrite_callback(WFFileIOTask* task);
public:
	 std::unordered_map<std::string, void (FileOperate::*)()>funcList;
	 std::string filepath;
	 WFHttpTask* server_task;
};

#endif