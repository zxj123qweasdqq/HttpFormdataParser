#include"FileOperate.h"
#include "HttpFormdataParser.h"

using namespace protocol;

FileOperate::FileOperate()
{
    std::cout << "call Test Constructor fun" << std::endl;
    funcList.emplace("print", &FileOperate::print);
    funcList.emplace("fileUpload", &FileOperate::fileUpload);
}

FileOperate::~FileOperate()
{
    std::cout << "call Test Destructor fun" << std::endl;
}//
void FileOperate::print()
{
    std::cout << "call Test print fun" << std::endl;
}

void FileOperate::fileUpload()
{
    HttpFormdataParser parser;
    if (parser.parse(server_task->get_req()))
    {
        HttpFormdataCursor cursor(&parser);
        std::string name;
        std::string filename;
        std::string value;
        while (cursor.next(name))
        {
            if (cursor.is_file(name, filename))
            {
                if (filepath.back() != '/')
                    filepath.push_back('/');

                const void* data;
                size_t datasize;
                if (cursor.get_content(name, &data, &datasize))
                {
                    filepath += filename;
                    printf("received file \"%s\" with %zu bytes\n", filepath.c_str(), datasize);
                    WFFileIOTask* pwrite_task;
                    auto  callback = std::bind(&FileOperate::pwrite_callback, this, std::placeholders::_1);
                    pwrite_task = WFTaskFactory::create_pwrite_task(filepath, data, datasize, 0, callback);
                    pwrite_task->user_data = server_task->get_resp();
                    series_of(server_task)->push_back(pwrite_task);
                }
            }
            else if (cursor.get_string(name, value))
            {
                printf("maybe pair \"%s=%s\" \n", name.c_str(), value.c_str());
            }
        }
    }
    else
    {
        server_task->get_resp()->set_status_code("503");
        server_task->get_resp()->append_output_body("<html>503 Internal Server Error.</html>\r\n");
    }
}

void FileOperate::setServerInfo(WFHttpTask* servertask, const char* root)
{
    server_task = servertask;
    filepath = root;
}

void FileOperate::pwrite_callback(WFFileIOTask* task)
{
    long ret = task->get_retval();
    HttpResponse* resp = (HttpResponse*)task->user_data;

    if (task->get_state() != WFT_STATE_SUCCESS || ret < 0)
    {
        resp->set_status_code("503");
        resp->append_output_body("<html>503 Internal Server Error.</html>\r\n");
    }
    else
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout << "响应结束时间：" << dt << std::endl;
        resp->set_status_code("200");
        resp->append_output_body("<html>200 success.</html>\r\n");
    }
}
