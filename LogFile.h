//---------------------------------------------------------------------------
#ifndef LogFileH
#define LogFileH
//---------------------------------------------------------------------------

//�ɰ��������ɶ����־�� ���ɷ�������Ƶ�������ļ���

//����������ù�ҵ�ֳ�24X7ֵ�صĳ����¼������Ϣ�� ������;
//һ����һ��ȫ����־���� ���ٽ��ų���Զ��̰߳�ȫʹ�á�
//��������
//class LogFile;//�û�������־�ļ���
//class LogFileEx;//����־�ļ����Զ����ɹ��� , �ɷ�������Ƶ�������ļ���, ��ָ����־��ŵ�Ŀ¼
//LogFile gLog("My.Log");
//gLog.Log("test", 4);//��¼��־
//gLog.Log("ϵͳ����");
//LogFileEx gLog(".", LogFileEx :: YEAR);//һ������һ����־�ļ�
//LogFileEx gLog(".//Log", LogFileEx :: MONTH);//һ������һ����־�ļ�
//LogFileEx gLog(".//Log", LogFileEx :: DAY);//һ������һ����־�ļ�
//ע����־����Ŀ¼����ʧ�ܻ��Զ��˳��� ��ע��Ŀ¼�ĺϷ��ԣ� �ļ�����Ƶ�ʿ��������
//24Сʱ���еĳ������ÿ������һ����־�ļ��� �������ݹ���


#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
//#include <tchar.h>
#include <QString>
#include <QDateTime>
using namespace std;

class LogFile
{
public:
    LogFile(QString szFileName = "Log.log"); //�趨��־�ļ���
	virtual ~LogFile();

    const QString GetFileName() {
		return _szFileName;
	}

    void SetFileName(const QString szName); //�޸��ļ����� ͬʱ�ر���һ����־�ļ�

	bool IsOpen() {
		return _hFile != INVALID_HANDLE_VALUE;
	}

	void Close();

    void Log(const QString szText){
        Log(szText.data(), szText.length() );
	}

protected:
	CRITICAL_SECTION _csLock;
    QString _szFileName;
	HANDLE _hFile;

	bool OpenFile(); //���ļ��� ָ�뵽�ļ�β
	DWORD Write(LPCVOID lpBuffer, DWORD dwLength);

	void Log(LPCVOID lpBuffer, DWORD dwLength); //׷����־����

	virtual void WriteLog( LPCVOID lpBuffer, DWORD dwLength); //д��־, ������չ�޸�
	void Lock()  {
		::EnterCriticalSection(&_csLock);
	}

	void Unlock() {
		::LeaveCriticalSection(&_csLock);
	}

private://���κ���
	LogFile(const LogFile&);
	LogFile&operator = (const LogFile&);
};



extern LogFile g_log;
#endif


