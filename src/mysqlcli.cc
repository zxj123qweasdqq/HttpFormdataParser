#include"mysqlcli.h"
#include "WFMySQLConnection.h"

Mysqlcli::~Mysqlcli()
{
}

Mysqlcli::Mysqlcli()
{
	WFMySQLConnection conn(1);
    conn.init("mysql://root:Wpy522167321@127.0.0.1/test_db");
    //����
   // const char* query = "INSERT INTO testalter_tb1 (c,i) VALUES ('k',3); ";
   //��ѯ
    //const char* query = "select * from testalter_tb1 where c='e'; ";
    //���� 
   //  const char* query = "UPDATE testalter_tb1 SET i = 100 where c = 'e';";
    //ɾ��
    const char* query = "delete from testalter_tb1 where c = 'e';";


    WFMySQLTask* t1 = conn.create_query_task(query, task_callback);
    t1->start();
}
