//---------------------------------------------------------------------------




#include "myprocess.h"
#include "LogFile.h"
#include "debugout.h"

//---------------------------------------------------------------------------
#define WASH_TYPE 1


TestArray g_test_array;
ReagentArray g_reagent_array;
TestRowArray g_test_row_array;
ActionSequence g_action_sequence;
CupInfoArray g_cup_array;

void testinitial()
{
    //string abc="sdfdsf";
	{
	TestConfig tc={0, -2,0,20,0,0, 30,1 ,0,40,2,0,50,3,0,60, 1,2,3,4,5,0, 2, 1,2,3,4,1, 349,560};
	g_test_array.push(tc);
	}
	{
	TestConfig tc={1, -2,0,20,1,0, 30,2 ,0,40,3,0,50,-1,0,60, 1,2,3,4,5,1,2,2, 2,2,3, 2, 349,560};
	g_test_array.push(tc);
	}
	{
	TestConfig tc={2, -2,0,20,3,0, 30,1 ,0,40,-3,0,50,-3,0,60,1,2,3,4,5, 2,2,3, 3,2,4, 2, 349,560};
	g_test_array.push(tc);
	}
    {
    TestConfig tc={3, -2,0,20,3,0, 30,1 ,0,40,-3,0,50,-3,0,60,1,2,3,4,5, 2,2,3, 3,2,4, 2, 349,560};
    g_test_array.push(tc);
    }
    for(int i=0;i<80;i++)
    {
        Reagent_Info ri={i,i/40,i%40,3000,0,300};
        g_reagent_array.push(ri);
    }


//	{ TestRow tr={"1", 0,  0, 0, 1, 1,0,0,1,0, 0, 1, 0}; g_test_row_array.push(tr);}
//	{ TestRow tr={"2", 1,  0, 1, 0, 2,0,1,0,0, 1, 1, 2}; g_test_row_array.push(tr);}
//	{ TestRow tr={"3", 2,  0, 1, 0, 3,0,1,0,0, 1, 1, 2}; g_test_row_array.push(tr);}
//	{ TestRow tr={"4", 3,  0, 1, 0, 4,1,2,3,4, 1, 0, 3}; g_test_row_array.push(tr);}
//	{ TestRow tr={"5", 4,  0, 1, 0, 1,0,1,0,0, 1, 1, 0}; g_test_row_array.push(tr);}
//	{ TestRow tr={"6", 5,  0, 1, 0, 2,0,1,0,0, 1, 1, 2}; g_test_row_array.push(tr);}
//	{ TestRow tr={"7", 6,  0, 1, 0, 3,0,1,0,0, 1, 1, 2}; g_test_row_array.push(tr);}
//	{ TestRow tr={"8", 7,  0, 1, 0, 4,0,1,0,0, 1, 0, 4}; g_test_row_array.push(tr);}
//	{ TestRow tr={"9", 8,  0, 1, 0, 1,0,1,0,0, 1, 2, 0}; g_test_row_array.push(tr);}
//	{ TestRow tr={"10",9,  0, 1, 0, 2,0,1,0,0, 1, 1, 1}; g_test_row_array.push(tr);}
//	{ TestRow tr={"11",10, 0, 1, 0, 3,0,1,0,0, 1, 1, 1}; g_test_row_array.push(tr);}
//	{ TestRow tr={"12",11, 0, 1, 0, 4,0,1,0,0, 1, 0, 3}; g_test_row_array.push(tr);}

}
/*****************************************************************************
按照项目优先级--测试类型——测试优先级来排序



***************************************************************************/
bool comp(const TestRow &a,const TestRow &b)
{
	if (g_test_array.test_config_array[a.test_id].priority != g_test_array.test_config_array[b.test_id].priority)
		return  g_test_array.test_config_array[a.test_id].priority< g_test_array.test_config_array[b.test_id].priority;
	if (a.test_type!=b.test_type)
		return  a.test_type<b.test_type;
	if (a.priority!=b.priority)
		return  a.priority<b.priority  ;

	return false;
}


void ActionSequence::clearAll()
{
	this->action_list.clear();
}
void  ActionSequence::addsample(ActionRow &ar, int &lt,int pos, int v,int cuppos,int step,int i)
{
	TestRow tr=g_test_row_array.test_array[i];
   ar.a.type=0;
   ar.a.params.get_sample.sample_pos= pos;

   ar.a.params.get_sample.cup_pos=cuppos;

   ar.a.params.get_sample.sample_volume=v;
   ar.a.params.get_sample.sample_type=tr.sample_type;
   ar.a.params.get_sample.wash_type=WASH_TYPE;
   ar.start_time=lt;
   ar.end_time=lt+GET_SAMPLE_TIME;
   ar.step=step;
   ar.ptestrow=i;
   lt=ar.end_time;
   LOG("add sample testsn %s step %x testid %d st %d et %d  acttype %d pos %d v %d cuppos %d", tr.test_row_id.data(),step,tr.test_id,ar.start_time,ar.end_time,ar.a.type,pos,v,cuppos);
}
void ActionSequence::addreagent(ActionRow &ar, int &lt,int rid, int v,int cuppos,int step,int i)
{
	TestRow tr=g_test_row_array.test_array[i];
		ar.a.type=1;

		ar.a.params.get_reagent.reagent_id=rid;
		ar.a.params.get_reagent.cup_pos =cuppos;
		ar.a.params.get_reagent.sample_volume=v;
		ar.a.params.get_reagent.sample_type=0;
		ar.a.params.get_reagent.wash_type=WASH_TYPE;
		ar.start_time=lt;
        ar.end_time=lt+GET_REAGENT_TIME;
		ar.step=step;
		ar.ptestrow=i;
		lt=ar.end_time;
		//arv.push_back(ar);
		LOG("add reagent testsn %s step %x testid %d st %d et %d  acttype %d rid %d v %d cuppos %d", tr.test_row_id.data(),step,tr.test_id,ar.start_time,ar.end_time,ar.a.type,rid,v,cuppos);
}
void ActionSequence::readresult(ActionRow &ar, int &lt,int num, int w0, int w1,int cuppos,int step,int i)
{
	TestRow tr=g_test_row_array.test_array[i];
	   ar.a.type=2;
   ar.a.params.get_result.cup_pos=cuppos;
   ar.a.params.get_result.wavenum= num;
   ar.a.params.get_result.wavelength0=w0;
   ar.a.params.get_result.wavelength1= w1;
   ar.start_time=lt;
   ar.end_time=ar.start_time+READ_RESULT_TIME;
   ar.step=step;
   ar.ptestrow=i;
   lt=ar.end_time;
   LOG("readresult testsn %s step %x testid %d st %d et %d  acttype %d num %d w0 %d  w1 %d cuppos %d", tr.test_row_id.data(),step,tr.test_id,ar.start_time,ar.end_time,ar.a.type,num,w0,w1,cuppos);
}
void ActionSequence::adddiutesample(ActionRow &ar, int &lt, int v, int cuppos0,int cuppos,int step,int i)
{
	TestRow tr=g_test_row_array.test_array[i];
   ar.a.type=14;
   ar.a.params.get_dilute_sample.cup0= cuppos0;

   ar.a.params.get_dilute_sample.cup1=cuppos;

   ar.a.params.get_dilute_sample.v=v;

   ar.start_time=lt;
   ar.end_time=lt+GET_DILUTE_SAMPLE_TIME;
   ar.step=step;
   ar.ptestrow=i;
   lt=ar.end_time;
	LOG("add  dilute sample testsn %s step %x testid %d st %d et %d  acttype %d fromcuppos %d v %d cuppos %d", tr.test_row_id.data(),step,tr.test_id,ar.start_time,ar.end_time,ar.a.type,cuppos0,v,cuppos);
}
void ActionSequence::addsystemwater(ActionRow &ar, int &lt, int v, int cuppos,int step,int i)
{
	TestRow tr=g_test_row_array.test_array[i];
   ar.a.type=13;
   ar.a.params.system_water.v= v;

   ar.a.params.system_water.cup_pos=cuppos;


   ar.start_time=lt;
   ar.end_time=lt+GET_SYSTEM_WATER;
   ar.step=step;
   ar.ptestrow=i;
   lt=ar.end_time;
   LOG("system water testsn %s step %x testid %d st %d et %d  acttype %d  v %d cuppos %d", tr.test_row_id.data(),step,tr.test_id,ar.start_time,ar.end_time,ar.a.type,v,cuppos);
}
void ActionSequence::insertTestRow(int i)
{
	vector<ActionRow> arv;
   //	if(tr.pre_dilute)
   int lasttime=0;
   ActionRow ar;
   TestRow tr=g_test_row_array.test_array[i];
   int tid=tr.test_id;
   int j;
   bool isa=false;// if cup free
   TwoCup atc;
   if(gi::get_is_dilute(i))
   {
		if(g_cup_array.getFree2cup(atc))
		{
			isa=true;
		}
   }
   else
   {
		j=g_cup_array.getFreecup();
		if(j!=-1)
		{
			isa=true;
		}
   }
   //int j=g_cup_array.getFreecup();
   if(!isa) // no free cup
   {
	   ar.a.type=4;
	   ar.start_time=0;
       ar.end_time= WASH_ALL_CUP_TIME;
       lasttime=WASH_ALL_CUP_TIME;
       ar.ptestrow=i;
	   arv.push_back(ar);
	   this->from_time=getendtime();    // insert from endtime
	   //insert last row  to clear all cups
	   g_cup_array.clearall() ;
	   if(gi::get_is_dilute(i))
		{
			if(g_cup_array.getFree2cup(atc))
			{
				isa=true;
			}
		}
		else
		{
				j=g_cup_array.getFreecup();
				if(j!=-1)
				{
					isa=true;
				}
		}

   }
   if(gi::get_is_dilute(i))
   {
		j=atc.j1;
		this->addsample(ar,lasttime,gi::get_sample_pos(i),gi::get_dilute_v(i),atc.j,0x1000,i);

		arv.push_back(ar);
		this->addreagent(ar,lasttime,gi::get_dilute_rid(i),(gi::get_dilutetimes(i)-1)*gi::get_dilute_v(i),atc.j,0x1001,i);
		arv.push_back(ar);
		lasttime+=gi::get_dilutetime(i);
		for(int k=0;k<5;k++)
		{
			int tempid=  gi::get_rid(i,tid,k);
			if(tempid!=-3)
			{
				if(tempid==-2)
				{
					this->adddiutesample(ar, lasttime, gi::get_reagentv(tid,k), atc.j,j,k, i);
							arv.push_back(ar);
				}
				else if(tempid==-1)
				{
					this->addsystemwater(ar,lasttime,gi::get_reagentv(tid,k),j,k,i);
							arv.push_back(ar);
				}
				else
				{
					this->addreagent(ar,lasttime,tempid,gi::get_reagentv(tid,k),j,k,i);
							arv.push_back(ar);
				}
				lasttime+=gi::get_reagentt(tid,k);
				if((gi::get_method(tid)== 2)&&(gi::get_readstep(tid)==k))
				{
					//two point
					this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,0x0200,i);
							arv.push_back(ar);
				}
			}
		}
		if(gi::get_method(tid)==1)
		{
				this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,0x0100,i);
						arv.push_back(ar);
		}
		if(gi::get_method(tid)==2)
		{
				this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,0x0201,i);
						arv.push_back(ar);
		}
		if(gi::get_method(tid)==3)
		{
			int readinterval=gi::get_readinterval(tid);
			int rr,readtimes=gi::get_readtimes(tid);
			for(rr=0;rr<readtimes;rr++)
			{   int ttt=0x0300|rr;
				this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,ttt,i);
						arv.push_back(ar);
				lasttime+=readinterval;
			}
		}
   }
   else
   {
		for(int k=0;k<5;k++)
		{
			int tempid=  gi::get_rid(i,tid,k);
			if(tempid!=-3)
			{
				if(tempid==-2)   // sample
				{
					addsample(ar,lasttime,gi::get_sample_pos(i),gi::get_reagentv(tid,k),j,k,i);
							arv.push_back(ar);
				}
				else if(tempid==-1)
				{
					this->addsystemwater(ar,lasttime,gi::get_reagentv(tid,k),j,k,i);
							arv.push_back(ar);
				}
				else
				{
					this->addreagent(ar,lasttime,tempid,gi::get_reagentv(tid,k),j,k,i);
							arv.push_back(ar);
				}
				lasttime+=gi::get_reagentt(tid,k);
				if((gi::get_method(tid)== 2)&&(gi::get_readstep(tid)==k))
				{
					//two point
					this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,0x0200,i);
							arv.push_back(ar);
				}
			}
		}
		if(gi::get_method(tid)==1)
		{
				this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,0x0100,i);
						arv.push_back(ar);
		}
		if(gi::get_method(tid)==2)
		{
				this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,0x0201,i);
						arv.push_back(ar);
		}
		if(gi::get_method(tid)==3)
		{
			int readinterval=gi::get_readinterval(tid);
			int rr,readtimes=gi::get_readtimes(tid);
			for(rr=0;rr<readtimes;rr++)
			{
				int ttt=0x0300|rr;
				this->readresult(ar,lasttime,gi::get_wnum(tid),gi::get_w0(tid),gi::get_w1(tid),j,ttt,i);
						arv.push_back(ar);
				lasttime+=readinterval;
			}
		}
   }


	insertOneRow(arv);
}
void ActionSequence::makelist() // 通过调用insertTestRow 生成动作序列
{
    this->action_list.clear();//clear when start make
	from_time=0;
	endtime=0;
	static int oldtid=-1;
	for(unsigned int i=0;i<g_test_row_array.test_array.size();i++)
	{
		if(g_test_row_array.test_array[i].test_id!=oldtid)
		{
			oldtid= g_test_row_array.test_array[i].test_id;
			from_time=getendtime();
			endtime=from_time;
		}
		this->insertTestRow(i);
    }
}

int ActionSequence::getendtime()
{
		list<ActionRow>::iterator iter;
		if (this->action_list.size()==0) {
			return 0;

		}
		iter=action_list.end();
		--iter;
		return iter->end_time;
}

void ActionSequence::insertOneRow( vector<ActionRow> & av)
{
	vector<ActionRow>::iterator ai;
	int time=get_available_time(av);
	for(ai=av.begin();ai!=av.end();ai++)
	{
		ai->start_time=ai->start_time+time;
		ai->end_time=ai->end_time+time;
		this->action_list.push_back(*ai);
	}
	action_list.sort();
	endtime= getendtime();
}
int ActionSequence::get_available_time(vector<ActionRow> & av)
{
	int start,i;
	if(from_time>=endtime) return from_time;
	for(i=from_time;i<endtime;i=get_next_available(i))
	{
	  vector<ActionRow>::iterator ai;
	  list<ActionRow>::iterator lai;
	  bool b=true;
	  for(ai=av.begin();ai!=av.end();ai++)
	  {
			int s=ai->start_time+i;
			int e=ai->end_time+i;
			for(lai=action_list.begin();lai!=action_list.end();lai++)
			{
				 int s1=lai->start_time;
				 int e1=lai->end_time;
				 if((s>=s1 && s<e1)||(e>s1&&e<=e1)||(s<=s1&& e>e1))
				 {
					 b=false;
					 goto con;
				 }
			}

	  }
	  if(b){start=i; break;}
      con: ;
	}
	if(i==endtime) start=endtime;
    return start;



}

int ActionSequence::get_next_available(int i)
{
	  list<ActionRow>::iterator lai;
	  int j;

	  for(j=i+1;j<endtime;j++)
	  {
			bool b=true;
			for(lai=action_list.begin();lai!=action_list.end();lai++)
			{

				int s1=lai->start_time;
				int e1=lai->end_time;
				if ((j>=s1)&&(j<e1)) {
				   b=false;
				   j=e1-1;
				   break;
				}
			}
			if(b) return j;
	  }
	  return endtime;
}

int ActionRow::toStream(unsigned char * dest)
{
	int i=3,r=0;
	int v;
	dest[0]=a.type;
	switch(a.type){
	case 0:
		dest[1]=7;//length
		dest[i+0]=a.params.get_sample.sample_pos;
		dest[i+1]=a.params.get_sample.cup_pos;
		v = a.params.get_sample.sample_volume;
		WORD_COPY(dest,i+2,v);
		dest[i+4]=a.params.get_sample.sample_type;

		dest[i+5]=a.params.get_sample.sam_cup_type;
		dest[i+6]=a.params.get_sample.wash_type;
		r= 10;
		break;
	case 1:
		dest[1]=7;
		dest[i+0] = a.params.get_reagent.r_pos.circle;
		dest[i+1] = a.params.get_reagent.r_pos.pos;
		dest[i+2] = a.params.get_reagent.cup_pos;
		v=a.params.get_reagent.sample_volume;
		WORD_COPY(dest,i+3,v);
		dest[i+5]=a.params.get_reagent.sample_type;
		dest[i+6]=a.params.get_reagent.wash_type;
		r = 10;
		break;
	case 2:
		dest[1]=6;
		dest[i+0]=a.params.get_result.cup_pos;
		dest[i+1]=a.params.get_result.wavenum;
		//a.params.get_result.wavelength0;
		WORD_COPY(dest,i+2,a.params.get_result.wavelength0);
		WORD_COPY(dest,i+4,a.params.get_result.wavelength1);
		r = 9;
		break;
	case 13:
		dest[1]=3;
		v=a.params.system_water.v;
		WORD_COPY(dest,i,v);
		dest[i+2]=a.params.system_water.cup_pos;
		r=6;
		break;
	case 14:
		dest[1]=4;
		dest[i+0]=a.params.get_dilute_sample.cup0;
		dest[i+1]=a.params.get_dilute_sample.cup1;
		v=a.params.get_dilute_sample.v;
		WORD_COPY(dest ,i+2,v);
		r=7;
		break;
	default:
		dest[1]=0;
		r= 3;
		break;


	}
	return r;
}
