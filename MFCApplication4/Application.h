#pragma once
#include "EmployeeController.h"

//
//class CMainFrameT : public CFrameWnd
//{
//private:
//	
//public:
//	static wchar_t * convertToLPCWSTR(const char * charArray) {
//		wchar_t * wString = new wchar_t[4096];
//		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
//		return wString;
//	}
//	CMainFrameT()
//	{
//		CFrameWnd::Create(NULL, convertToLPCWSTR("Windows Application Tester"));
//	}
//};


class Application
{
private:
	
public:
	Application();
	~Application();
	//static EmployeeController* employee_controller;
	CDialog* run();
};
