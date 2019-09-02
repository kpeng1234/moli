#include "stdafx.h"
#include "localTS.h"
#include "CTSPlugInterFace.h"

#include <iostream>



//MFC û��ȫ�ֶ���
//std::shared_ptr<spdlog::logger> logger = spdlog::get("maitianPT");
localTS::localTS()
{
	initTSDLL();
	logger = spdlog::get(LOG_MODEL_STR);
	logger->debug("Hello World");
}


localTS::~localTS()
{
	//releaseLogModel();

}

BOOL localTS::registerTS()
{
	CString strFilePath;
	WCHAR strBuff[256];
	GetCurrentDirectory(256, strBuff);
	strFilePath.Format(TEXT("%s\\lib\\TSPlug.dll"), strBuff);

	AfxMessageBox(strFilePath);




	LRESULT(CALLBACK* lpDllEntryPoint)();
	HINSTANCE hLib = LoadLibrary(strFilePath);
	if (hLib < (HINSTANCE)HINSTANCE_ERROR)
	{
		return FALSE;
	}
	(FARPROC&)lpDllEntryPoint = GetProcAddress(hLib, "DllRegisterServer");
	BOOL bRet = FALSE;
	if (lpDllEntryPoint != NULL)
	{
		HRESULT hr = (*lpDllEntryPoint)();
		bRet = SUCCEEDED(hr);
		if (FAILED(hr))
		{
			AfxMessageBox(TEXT("ע��ʧ��"));
		}
		else
		{
			AfxMessageBox(TEXT("ע��ɹ�"));
		}
	}
	FreeLibrary(hLib);
	return bRet;
}

void localTS::initTSDLL()
{
	int ret = 0;
	CLSID clsid;
	CoInitialize(NULL);
	HRESULT hr = CLSIDFromProgID(OLESTR("ts.tssoft"), &clsid);//���á�������.��������ȡCLSID��&���ǰ�ָ���������Ҳ���Ǵ�ַ�� 
	ret = ts.CreateDispatch(clsid);//��ע����л�ȡ��dll·����������͵��óɹ��ˡ� 
	if (ret == FALSE)
	{
		registerTS();
	}
}

void localTS::intLogModel()
{
	//spdlog::drop_all();
	auto console = spdlog::daily_logger_mt(LOG_MODEL_STR, "./daily_log.txt", 00, 00);
	console->flush_on(spdlog::level::level_enum::trace);
	//spdlog::register_logger(console);
}

void localTS::releaseLogModel()
{
	spdlog::drop_all();
}

void localTS::getGameInformatio()
{
	int ret = 0;
#if 1
	int hwnd = ts.FindWindow(TEXT("�۷�ħ��"), TEXT(""));
	logger->warn("hwnd res == {0}", hwnd);
	ret = ts.BindWindow(hwnd, TEXT("gdi"), TEXT("windows"), TEXT("windows"), 101);
	if (ret == FALSE)
	{
		AfxMessageBox(TEXT("BindWindow ʧ��"));
		return;
	}
	else if (ret == TRUE)
	{

		//AfxMessageBox(TEXT("BindWindow �ɹ�"));

	}


	VARIANT x1, y1, x2, y2;
	ret = ts.GetWindowRect(hwnd, &x1, &y1, &x2, &y2);
	logger->warn("GetWindowRect x1 = {0},y1 = {1},x2 = {2},y2 = {3}", x1.intVal,y1.intVal,x2.intVal,y2.intVal);

	ret = ts.GetClientRect(hwnd, &x1, &y1, &x2, &y2);
	logger->warn("GetClientRect x1 = {0},y1 = {1},x2 = {2},y2 = {3}", x1.intVal, y1.intVal, x2.intVal, y2.intVal);
#endif
	ret = ts.SetPath(TEXT("C:\\Users\\LX\\Desktop\\demo\\"));
	logger->warn("ts.SetPath ret == {0}", ret);
	CString path = ts.GetPath();
	AfxMessageBox(path);
	CString char_path = TEXT("moli_type.txt");
	ret = ts.SetDict(0, char_path);
	logger->warn("ts.SetDic ret == {0}", ret);
	test(hwnd);
	CString str = ts.Ocr(x1.intVal, y1.intVal, x2.intVal, y2.intVal, TEXT("000000-FFFFFF"), 1.0);
		//help.messagebox(s)
	AfxMessageBox(str);

}


void localTS::test(int hwnd)
{
	//logger->debug("hwnd == %s",hwnd);
	int ret = ts.SendString(hwnd, TEXT("/1"));
	int res = ts.KeyPressChar(TEXT("enter"));
	ts.KeyUpChar(TEXT("enter"));

	logger->warn("SendString res == {0}", res);


	if (ret == FALSE)
	{
		AfxMessageBox(TEXT("��������ʧ��"));
	}
	else if (ret == TRUE)
	{

		AfxMessageBox(TEXT("�������ݳɹ�"));
	}
	else
	{
		AfxMessageBox(TEXT("����������������"));
	}
	logger->flush();
}