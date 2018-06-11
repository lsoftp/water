//---------------------------------------------------------------------------


#include "LogFile.h"

//---------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------
QString mydir="c:\\temp\\";
LogFile g_log(mydir  +QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss.log"));
LogFile::LogFile(const QString szFileName)//�趨��־�ļ���
{
	_hFile = INVALID_HANDLE_VALUE;
	::InitializeCriticalSection(&_csLock);
	SetFileName(szFileName);
}

//-----------------------------------------------------------------------------------------

LogFile::~LogFile()
{
	::DeleteCriticalSection(&_csLock);
	Close();
}

//-----------------------------------------------------------------------------------------

void LogFile::SetFileName(const QString szName)//�޸��ļ����� ͬʱ�ر���һ����־�ļ�
{
	Close();
	this->_szFileName = szName;
}

//-----------------------------------------------------------------------------------------

bool LogFile::OpenFile()//���ļ��� ָ�뵽�ļ�β
{
	if(IsOpen()) {
		return true;
	}

	if(_szFileName == "") {
		return false;
	}

	_hFile =  CreateFile(
        _szFileName.toStdWString().c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if(!IsOpen() && GetLastError() == 2)//�򿪲��ɹ��� ����Ϊ�ļ������ڣ� �����ļ�
		_hFile =  CreateFile(
        _szFileName.toStdWString().c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if(IsOpen())
		SetFilePointer(_hFile, 0, NULL, FILE_END);

	return IsOpen();
}

//-----------------------------------------------------------------------------------------

DWORD LogFile::Write(LPCVOID lpBuffer, DWORD dwLength)
{
	DWORD dwWriteLength = 0;
	if(IsOpen())
		WriteFile(_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);
	return dwWriteLength;
}
//-----------------------------------------------------------------------------------------

void LogFile::WriteLog( LPCVOID lpBuffer, DWORD dwLength)//д��־, ������չ�޸�
{
	char temp[21] = {0};
	DWORD dwWriteLength;
	if(IsOpen())
	{
		time_t now1;
		time(&now1);
		struct tm timeInfo;
        localtime_s( &timeInfo,&now1); //ת����tm�ṹ
		strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", &timeInfo);
        //WriteFile(_hFile, "\xd\xa#-----------------------------", 32, &dwWriteLength, NULL);
		WriteFile(_hFile, temp, 19, &dwWriteLength, NULL);
        WriteFile(_hFile, ":  ", 3, &dwWriteLength, NULL);
		WriteFile(_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);
		WriteFile(_hFile, "\xd\xa", 2, &dwWriteLength, NULL);

		FlushFileBuffers(_hFile);
	}
}

//-----------------------------------------------------------------------------------------

void LogFile::Close()
{
	if(IsOpen())
	{
		CloseHandle(_hFile);
		_hFile = INVALID_HANDLE_VALUE;
	}
}

//-----------------------------------------------------------------------------------------

void LogFile::Log(LPCVOID lpBuffer, DWORD dwLength)//׷����־����
{
	assert(lpBuffer);
    __try
	{
		Lock();
		if(!OpenFile())
			return;
		WriteLog(lpBuffer, dwLength);
	}
    __catch(int e)
    {

    }


	{
		Unlock();
	}
}

//LogFileEx**********************************************************************************

/*
LogFileEx::LogFileEx(const char *szPath, LOG_TYPE iType)
{
	memset(_szPath, 0, sizeof(_szPath));
	SetPath(szPath);
	_iType = iType;
	memset(_szLastDate, 0, sizeof(_szLastDate));
}

//---------------------------------------------------------------------------------

LogFileEx::~LogFileEx()
{

}

//---------------------------------------------------------------------------------


void LogFileEx::Log(LPCVOID lpBuffer, DWORD dwLength)
{
	assert(lpBuffer);;
	static const char format[3][10] = {"%Y", "%Y-%m", "%Y%m%d"};

	__try
	{
		Lock();

		char temp[20] = {0};
		time_t now = time(NULL);
		tm timeInfo;
		localtime_s(&timeInfo, &now); //ת��tm�ṹ
		strftime(temp, sizeof(temp), format[_iType], &timeInfo);
		if(strcmp(_szLastDate, temp) != 0)//�����ļ���
		{
			int len = sizeof(_szFileName);
			strcpy_s(_szFileName, len, _szPath); len -= strlen(_szPath);
			strcat_s(_szFileName, len, "//"); len -= 2;
			strcat_s(_szFileName, len, temp); len -= sizeof(temp);
			strcat_s(_szFileName, len, ".log"); len -= 4;

			strcpy_s(_szLastDate, sizeof(_szLastDate), temp);
			Close();
		}
		if(!OpenFile())
			return;

		WriteLog(lpBuffer, dwLength);
	}
	__finally
	{
		Unlock();
	}
}

//---------------------------------------------------------------------------------
void LogFileEx::SetPath(const char *szPath)
{
	assert(szPath);
	WIN32_FIND_DATA wfd;
	char temp[MAX_PATH + 1] = {0};
	if(FindFirstFile(szPath, &wfd) == INVALID_HANDLE_VALUE && CreateDirectory(szPath, NULL) == 0)
	{
		strcpy_s(temp, sizeof(temp), szPath);
		strcat_s(temp, sizeof(temp), " Create Fail. Exit Now! Error ID :");
		_ltoa_s(GetLastError(), temp + strlen(temp), 20, 10);
		MessageBox(NULL, temp, "Class LogFileEx", MB_OK);
		exit(1);
	}
	else
	{
		GetFullPathName(szPath, MAX_PATH, temp, NULL);
		strcpy_s(_szPath, sizeof(_szPath), temp);
	}
}
*/
