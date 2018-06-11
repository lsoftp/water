//---------------------------------------------------------------------------

#ifndef interfaceH
#define interfaceH
//---------------------------------------------------------------------------
#define TEST_STEP_SUCCESS 0 //���Բ���ɹ�
#define TEST_TIME_OUT 9 //���Գ�ʱ
#define NOT_ENOUGH_REAGENT 10      //�Լ�����

class Interface{
public:
	static void initTestArray();
	static void initTestrowArray();
	static void initReagentArray();
	static void updateReagent(unsigned char circle, unsigned char pos, int h);
	static void updateCup(unsigned char pos, unsigned char status);
	static void pushTestResult(int test_no, char nums,float r1,float r2);
	static void pushTestStatus(int test_num, int step, int status); //update memory and database
};

/**************************************************************
��ʼ���ԣ����еǼǵĲ���push��testrowarray�У�Ȼ������command=1
��������������actionlist��Ȼ������command=2��




******************************************************************/
#endif
