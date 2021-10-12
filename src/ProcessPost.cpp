#include"ProcessPost.h"
#include "HttpFormdataParser.h"

using namespace protocol;

ProcessPost::~ProcessPost()
{
}

ProcessPost::ProcessPost()
{
    funcList.emplace("print", &ProcessPost::print);
    funcList.emplace("arrayUpload", &ProcessPost::arrayUpload);
}

void ProcessPost::print()
{
}
void ProcessPost::arrayUpload()
{

    protocol::HttpRequest* req = server_task->get_req();
    protocol::HttpResponse* resp = server_task->get_resp();
    long seq = server_task->get_task_seq();
    protocol::HttpHeaderCursor cursor(req);
    std::string name;
    std::string value;
    char buf[31457280];
    int len;
    resp->append_output_body_nocopy("<html>", 6);
    len = snprintf(buf, 31457280, "<p>%s %s %s</p>", req->get_method(),
        req->get_request_uri(), req->get_http_version());
    resp->append_output_body(buf, len);

    while (cursor.next(name, value))
    {
        len = snprintf(buf, 8192, "<p>%s: %s</p>", name.c_str(), value.c_str());
        resp->append_output_body(buf, len);
    }

    resp->append_output_body_nocopy("</html>", 7);

    /* Set status line if you like. */
    resp->set_http_version("HTTP/1.1");
    resp->set_status_code("200");
    resp->set_reason_phrase("OK");

    resp->add_header_pair("Content-Type", "text/html");
    resp->add_header_pair("Server", "Sogou WFHttpServer");
    if (seq == 9) /* no more than 10 requests on the same connection. */
        resp->add_header_pair("Connection", "close");
}

void ProcessPost::setServerInfo(WFHttpTask* servertask)
{
    server_task = servertask;
}
