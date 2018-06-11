//---------------------------------------------------------------------------
#ifndef _DEBUGPRINTF_H_
#define _DEBUGPRINTF_H_


//#include <tchar.h>
#include <stdio.h>
#include "LogFile.h"
//用于输出信息到编译器输出窗口的宏定义
//使用win API，DEBUG版本会执行，RELEASE版本则不会
//还可以使用DebugView，WinDbg等工具查看输出
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
