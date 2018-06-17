//---------------------------------------------------------------------------




#include "interface.h"
#include "process.h"
#include "dbinterface.h"
#include "mainwindow.h"
//---------------------------------------------------------------------------



void Interface::initTestArray()
{



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
