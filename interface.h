//---------------------------------------------------------------------------

#ifndef interfaceH
#define interfaceH
//---------------------------------------------------------------------------
#define TEST_STEP_SUCCESS 0 //测试步骤成功
#define TEST_TIME_OUT 9 //测试超时
#define NOT_ENOUGH_REAGENT 10      //试剂不够

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
开始测试：所有登记的测试push到testrowarray中，然后设置command=1
其他动作，构造actionlist，然后设置command=2；




******************************************************************/
#endif
