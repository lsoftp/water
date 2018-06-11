//---------------------------------------------------------------------------

#ifndef handlethreadH
#define handlethreadH
//---------------------------------------------------------------------------
#include <QThread>
#include "clientsockt.h"
#include "myprocess.h"
//---------------------------------------------------------------------------
class HandleThread : public QThread
{
protected:

public:
	static int command;     //0 for accept command 1 test suite 2 handle actionlist

private:
	static unsigned char  sn;
	static unsigned char  currentCmd;
	static unsigned char started;
	static RecvBuf recvbuf;
	static int settime;
	static list<ActionRow>::iterator li;
	static unsigned char getSn();
	void HandleActionList();
	static int toOriginalMsg(unsigned char * composed,int comlen, unsigned char * original, int *origlen);
	static int toComposedMsg(unsigned char * original,int origlen, unsigned char * composed, int* comlen);
	static int addCheckCode(unsigned char * original, int len);
	static int getMsgFromBuf( int & state);
	static void handleMsg(const RecvStream &r);
	static int checkCode(unsigned char * original, int len);
	void  run();
};
//---------------------------------------------------------------------------

extern HandleThread  g_handler;
#endif
