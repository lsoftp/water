//---------------------------------------------------------------------------

#ifndef __process_H
#define __process_H


//#include "string.h"
//#include <QString>
using namespace std;
#include <vector>
#include <list>
#include <algorithm>
#include <string>

#define TEST_NUMBER 512
#define REAGENT_NUMBER 512
#define CUP_NUMBER  44
#define GET_SAMPLE_TIME 10   //ȡ������Ӧ���ʱ�䣬����Ҫ��10s ����ɣ�����ͨѶ����
#define GET_REAGENT_TIME  10   // ȡ�Լ�����Ӧ�� �������� ��ϴ��
#define GET_SYSTEM_WATER 10    // ��ϵͳˮ����
#define GET_DILUTE_SAMPLE_TIME 10    // ��ϡ����Ʒ

#define  READ_RESULT_TIME 10    //��ȡ���
#define  WASH_ALL_CUP_TIME 100 //��ϴ���б���
//---------------------------------------------------------------------------
#define WORD_COPY(d,i,v) {d[i]=(0xff00&v)>>8; d[i+1]=(0x00ff&v);}
#define DWORD_COPY(d,i,v) {d[i]=(0xff000000&v)>>24; d[i+1]=(0x00ff0000&v)>>16;d[i+2]=(0x0000ff00&v)>>8; d[i+3]=v&0xff;}

#define TO_WORD(d,i,v)  {v= ((0x0000|d[i])<<8)|d[i+1];}
#define TO_DWORD(d,i,v) {v= (0x00000000|d[i])<<8; v=(v|d[i+1])<<8;v= (v|d[i+2])<<8;v=v|d[i+3];}


//������Ŀ����
struct TestConfig{
	int test_id;

	int reagent0;
	int sample_type0;
	int time0;
	int reagent1;
	int sample_type1;
	int time1;
	int reagent2;
	int sample_type2;
	int time2;
	int reagent3;  //if -1 no reagent
	int sample_type3;
	int time3;
	int reagent4;
	int sample_type4;
	int time4;
	int v0,v1,v2,v3,v4;
	int priority;    //0 is highest

	int repalcereagentid;

	int method;//1 one point 2 two points 3 dynamic
	// two points
	int readstep;//0 ,1,2,3,4
	// 3 dynamic
	int readinterval;// read inteval after all reagents added
	int readtimes;//

	int wavenum;//��ȡ������Ŀ
	int wl0;//������
	int wl1;//������
    int isreplace; // TRUE SAMPLE BLANK IS CHECKED

};



struct TestRow{
    string test_row_id;
	//int sample_no;

	unsigned short position;
	int sample_type;     //�������� 1���������� 0  ȱʡΪ0

	int sample_cup_type; //����������
	int priority; //smaller is highest  ���� 1 �Ӽ� 0
	int test_type;  // �հ�1 ���� 2���ʿ� 3  ���� 04
	//TDateTime reg_time;
	int isdilute;//�Ƿ����ϡ��
	int dilutevolume;//ϡ��ȡ����
	int dilutetimes;//ϡ�ͱ���
	int dilutetime;//ϡ��ʱ��
	int dilute_reagent; //ϡ���Լ�id

	int  test_id;  //���Է���id
	int isreplace;//�Ƿ����
	int status;// 0 �ɹ���1 ��ʱ��2 �Լ�����
	//int test_no;  //ȷ������id

};
struct Reagent_pos{

	unsigned short circle; //��Ȧ0����Ȧ0
	unsigned short pos;
};

struct Reagent_Info{
	int reagent_id;
	Reagent_pos r_pos;
	double  left_volume;
	char   bottletype; //�Լ�ƿ����
	unsigned short height;//
	double getSetVolume(){
		//for test   to be modified
		left_volume=height;
		return left_volume;
	}

};
typedef vector<Reagent_Info>  ReagentInfoArray;

class TestArray{
public:
	TestConfig test_config_array[TEST_NUMBER];
	void push(TestConfig tc){
		test_config_array[tc.test_id]=tc;
	}
};

class ReagentArray{
public:
	ReagentInfoArray  reagent_info_array[REAGENT_NUMBER];
	void push(Reagent_Info ri){
		reagent_info_array[ri.reagent_id].push_back(ri);
	}

	// return 0 failed ,1 success rp hold the pos
	int getPos(Reagent_pos &rp,unsigned int reag_id,int v)
	{
		if(reag_id>= REAGENT_NUMBER){
			return 0;
		}
		ReagentInfoArray ra= reagent_info_array[reag_id];
		vector<Reagent_Info>::iterator  iri;
		for (iri=ra.begin(); iri != ra.end(); iri++) {
			if(iri->left_volume>=v){
				rp=iri->r_pos;
				return 1;
			}
		}
		return 0;
	}
};

struct CupInfo{
	int cup_pos;
	char is_in_use;
	char status;
};

struct TwoCup{
	int j,j1;
};
class CupInfoArray{
public:
	CupInfo cv[CUP_NUMBER];
	void clear(int i){
		cv[i].is_in_use=0;
		cv[i].status=0;
	}
	void clearall(){
		for(int i=0; i<CUP_NUMBER;i++)
			clear(i);
	}
	int getFreecup()
	{
		for(int i=0; i<CUP_NUMBER;i++)
			if(!cv[i].is_in_use)
			{
				cv[i].is_in_use=1;
				return i;
			}
		// full return -1
		return -1;
	}
	bool getFree2cup(TwoCup & atc)
	{
		int j,j1;
		j=getFreecup();
		if (j==-1)
		{
			return false;

		}
		else
		{
			cv[j].is_in_use=1;
			j1=getFreecup();
			if(j1==-1)
			{
				return false;
			}
			else
			{
				cv[j1].is_in_use=1;
				atc.j=j;
				atc.j1=j1;
				return true;
			}
		}
	}
};


//�Ǽǵ�������Ŀ�ʿأ����� ���棬���ȷ������ݿ����棬Ȼ������ʼ����
bool comp(const TestRow &a,const TestRow &b);
class TestRowArray{
public:
	vector<TestRow> test_array;

	void rearrange(){ // ���չ������� ���Ȱ���Ŀ���ȼ���Ȼ���ղ������ȼ� ��test_type
		sort(test_array.begin(),test_array.end(),comp);
	}
	void push(TestRow tr){
		test_array.push_back(tr);
	}


};

struct Action{
	unsigned short type;// 0  ����Ʒ����Ӧ�� 1 ���Լ�����Ӧ��  2 ��ȡ���
	//0
	union{
		//0 ����Ʒ����Ӧ��
		struct {
			unsigned short sample_pos;
			unsigned short cup_pos;
			int sample_volume;
			char sample_type;
			char wash_type;
			char sam_cup_type;
		}get_sample;
		// 1 ���Լ�����Ӧ��
		struct {
			int reagent_id;
			Reagent_pos r_pos;
			unsigned short cup_pos;
			int sample_volume;
			char sample_type;
			char wash_type;
		}get_reagent;
		//2 ��ȡ���
		struct{
			unsigned short cup_pos;
			int wavenum;
			int  wavelength0;
			int  wavelength1;
		}get_result;
		 //3 ��ϴ��Ӧ��
		struct{
			unsigned char cup_pos0;       //start
			unsigned char cup_pos1;              //end
		}wash_cup;
		 //4 ��ϴ���з�Ӧ��
		//5 ��λ
		//6 ��ע
		//7��Ӧ���հ�
		//8 ͨ�ż��
		//9��Ӧ��עˮ
		//10��������ϴ
		//11������
		//12�Լ��������
		struct {
			unsigned short  startpos;
			unsigned short   endpos;
		}reagent_check;
		//13 ��ϵͳˮ
		struct{
			int v;
			unsigned char cup_pos;
		}system_water;
		//14 ��ϡ�ͺ���Ʒ
		struct{
			unsigned cup0;  //from
			unsigned cup1; //to
			int v;
			}get_dilute_sample;


	}params;



};

struct ActionRow{
	Action a;
	int step;
	int ptestrow;
	int start_time;
	int end_time;
	int span_to_next; //seconds
	int span_to_prev;
	int if_send;
	operator <(const ActionRow &a){ return start_time<a.start_time;}
	int  toStream(unsigned char * dest);
	ActionRow(){if_send=1;};
};

//sorted TestRowArray -->  action sequence when start
class ActionSequence{
public:
	list<ActionRow> action_list;
	int starttime;
	int endtime;
	int from_time;
	void clearAll();
	void insertTestRow(int i);
	void insertOneRow( vector<ActionRow> & av);
	void makelist(); // ͨ������insertTestRow ���ɶ�������
	int getendtime();
	int get_next_available(int i);
	int get_available_time(vector<ActionRow> & av);//��ȡ�����ʱ��
	void  addsample(ActionRow &ar, int &lt,int pos, int v,int cuppos ,int step,int i);
	void addreagent(ActionRow &ar, int &lt,int rid, int v,int cuppos ,int step,int i);
	void readresult(ActionRow &ar, int &lt,int num, int w0, int w1,int cuppos,int step,int i);
	void adddiutesample(ActionRow &ar, int &lt, int v, int cuppos0,int cuppos,int step,int i);
	void addsystemwater(ActionRow &ar, int &lt, int v, int cuppos,int step,int i);
};


void testinitial();
extern TestArray g_test_array;
extern ReagentArray g_reagent_array;
extern TestRowArray g_test_row_array;
extern ActionSequence g_action_sequence;

class gi{
public:

	static int get_replaceid(int testid)
	{
		return g_test_array.test_config_array[testid].repalcereagentid;
	}

	static int get_reagentid(int testid,int step)
	{
		TestConfig &tc= g_test_array.test_config_array[testid];
		int rid;
		switch(step){
			case 0: rid= tc.reagent0; break;
			case 1: rid= tc.reagent1; break;
			case 2: rid= tc.reagent2; break;
			case 3: rid = tc.reagent3; break;
			case 4: rid= tc.reagent4; break;
		}
		return rid;
	}
	static int get_rid(int i,int testid,int step)
	{
		if(g_test_row_array.test_array[i].isreplace)
			if  (get_reagentid(testid,step)!=-2)
				return get_replaceid(testid);
			else return -2;
		else
			return get_reagentid(testid,step);
	}
	static int get_reagentv(int testid, int step) {
		TestConfig &tc = g_test_array.test_config_array[testid];
		int rid;
		switch (step) {
		case 0:
			rid = tc.v0;
			break;
		case 1:
			rid = tc.v1;
			break;
		case 2:
			rid = tc.v2;
			break;
		case 3:
			rid = tc.v3;
			break;
		case 4:
			rid = tc.v4;
			break;
		}
		return rid;
	}

	static int get_reagentt(int testid, int step) {
		TestConfig &tc = g_test_array.test_config_array[testid];
		int rid;
		switch (step) {
		case 0:
			rid = tc.time0;
			break;
		case 1:
			rid = tc.time1;
			break;
		case 2:
			rid = tc.time2;
			break;
		case 3:
			rid = tc.time3;
			break;
		case 4:
			rid = tc.time4;
			break;
		}
		return rid;
	}

	static int get_testid(int testrowsn) {
		return g_test_row_array.test_array[testrowsn].test_id;
	}
	static int get_is_replace(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].isreplace;
	}
	static int get_is_dilute(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].isdilute;
	}
	 static int get_sample_pos(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].position;
	}
	 static int get_dilute_v(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].dilutevolume;
	}
	static int get_dilute_rid(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].dilute_reagent;
	}
		 static int get_dilutetimes(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].dilutetimes;
	}
	static int get_dilutetime(int testrowsn)
	{
		return g_test_row_array.test_array[testrowsn].dilutetime;
	}

	static int get_method(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.method;
	}
		static int get_readstep(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.readstep;
	}
			static int get_wnum(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.wavenum;
	}
			static int get_w0(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.wl0;
	}
			static int get_w1(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.wl1;
	}
		static int get_readinterval(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.readinterval  ;
	}
		static int get_readtimes(int testid)
	{
		TestConfig &tc = g_test_array.test_config_array[testid];
		return tc.readtimes;
	}

};
#endif
