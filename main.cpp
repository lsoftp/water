#include "mainwindow.h"
#include <QApplication>
#include "dbinterface.h"

#include "process.h"
#include "clientsockt.h"
#include "handlethread.h"
#include "debugout.h"
#include "LogFile.h"
#include "sampleregister.h"

void testinit()

{
    //String mypath="c:\\temp\\test.log";
    //String mylog=  mypath+Now().FormatString("yyyy-mm-dd hh-nn-ss")+".log";
    //g_log.SetFileName(mylog);
    //LogFile log1(mypath);
   //	g_log.Log("hahah");
    char buf[512];
    testinitial();
    DP("rows %d",g_test_row_array.test_array.size());
    g_test_row_array.rearrange();
     DP("****************rows %d",g_test_row_array.test_array.size());
         vector<TestRow>::iterator iter;
    for (iter=g_test_row_array.test_array.begin();iter!=g_test_row_array.test_array.end();iter++)
    {
        DP("***%d*****%d******** %d",(*iter).test_id,(*iter).test_type,(*iter).priority);
    }
    g_action_sequence.makelist();
    DP("size %d",g_action_sequence.action_list.size());
    list<ActionRow> &a=g_action_sequence.action_list;
    list<ActionRow>::iterator li;
    for(li=a.begin();li!=a.end();li++)
    {
        ActionRow ar= *li;
        DP("test_id %d   s %d e %d",g_test_row_array.test_array[li->ptestrow].test_id, li->start_time,li->end_time);
        sprintf(buf,"test sn  %d testid %d st %d et %d ,artype %d", li->ptestrow,g_test_row_array.test_array[li->ptestrow].test_id, li->start_time,li->end_time,li->a.type);
        g_log.Log(buf);
    }
    CCliSocket::makeupWSA();
    g_tcp_client.init();
    g_tcp_client.Connect("127.0.0.1",40000);
    g_tcp_client.setNonBlock();


}
DBInterface db;
DBInterface dbhandle;
    MainWindow *g_w;
int main(int argc, char *argv[])
{
    db.open();
    dbhandle.open1();
    QApplication a(argc, argv);
    g_w=new MainWindow ;
    printf("thisis a test");

    g_w->sr->setbutton();
    g_w->sr->initstate();
    g_w->show();
    //testinit();
    g_handler.start();
    fflush(stdout);
    return a.exec();
}
