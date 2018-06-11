//---------------------------------------------------------------------------
#ifndef _DEBUGPRINTF_H_
#define _DEBUGPRINTF_H_


//#include <tchar.h>
#include <stdio.h>
#include "LogFile.h"
//���������Ϣ��������������ڵĺ궨��
//ʹ��win API��DEBUG�汾��ִ�У�RELEASE�汾�򲻻�
//������ʹ��DebugView��WinDbg�ȹ��߲鿴���
#define _DEBUG
#ifdef _DEBUG

#define DP(fmt,...) {printf(fmt,##__VA_ARGS__);}


#endif

#ifndef _DEBUG

#define DP(fmt,...)


#endif


#ifdef _DEBUG
#define LOG(format,...) {char mybuf[1024]; sprintf(mybuf,format,##__VA_ARGS__); g_log.Log(mybuf);}
#else
#define LOG(format,... )
#endif


#endif
