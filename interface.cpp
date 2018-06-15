//---------------------------------------------------------------------------




#include "interface.h"
#include "process.h"
#include "dbinterface.h"
#include "mainwindow.h"
//---------------------------------------------------------------------------



void Interface::initTestArray()
{
    unsigned short position;
    int sample_type;     //过量采样 1，正常采样 0  缺省为0

    int sample_cup_type; //采样杯类型
    int priority; //smaller is highest  常规 1 加急 0
    int test_type;  // 空白1 定标 2，质控 3  常规 04
    //TDateTime reg_time;
    int isdilute;//是否机器稀释
    int dilutevolume;//稀释取样量
    int dilutetimes;//稀释倍数
    int dilutetime;//稀释时间
    int dilute_reagent; //稀释试剂id

    int  test_id;  //测试方法id
    int isreplace;//是否替代
    int status;// 0 成功，1 超时，2 试剂不够


}
static int  getdilutereagentid()
{
    return 0;
}

void Interface::initTestrowArray()
{
    QSqlQueryModel sqm;
    db.getalltest(sqm,::g_current_index);
    TestRow tr;
    g_test_row_array.test_array.clear();
    for(int i=0;i<sqm.rowCount();i++)
    {
        tr.test_row_id=sqm.record(i).value("testsn").toString().toStdString();
        tr.position=sqm.record(i).value("Pos").toInt();
        tr.sample_type=0;
        tr.sample_cup_type=sqm.record(i).value("Samplecuptype").toInt();
        tr.priority=sqm.record(i).value("Isurgent").toInt();
        tr.test_type=sqm.record(i).value("Testtype").toInt();
        tr.isdilute=sqm.record(i).value("IsDilute").toInt();
        tr.dilutevolume=sqm.record(i).value("DiluteVolume").toInt();
        tr.dilutetime=sqm.record(i).value("Dilutetime").toInt();
        tr.dilute_reagent=getdilutereagentid();
        tr.test_id=sqm.record(i).value("TestID").toInt();
        tr.isreplace=sqm.record(i).value("Isreplace").toInt();
        tr.status=-1;//初始状态
        g_test_row_array.push(tr);
    }

}
void Interface::initReagentArray()
{

}
void Interface::updateReagent(unsigned char circle, unsigned char pos, int v)
{

}
/*************************************************************
pos : test cup pos
status  step of cup
**************************************************************/

void Interface::updateCup(unsigned char pos, unsigned char status)
{

}
/*************************************************************
test_no : in database identify a test
nums,r1,r2 test result for this test_no test
**************************************************************/
void Interface::pushTestResult(int test_no, char nums,float r1,float r2)
{

}
void Interface::pushTestStatus(int test_num, int step, int status)
{

   //g_test_row_array.test_array[test_num].status=status;
   //int test_no= g_test_row_array.test_array[test_num].test_no;

   // to do ,update database test_no info

}
