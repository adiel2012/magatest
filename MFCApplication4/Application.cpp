#include "stdafx.h"
#include "Application.h"


//EmployeeController* Application::employee_controller;

Application::Application()
{
	//this->employee_controller = Injector::getInstance()->getIEmployeeController(); // new EmployeeController();
}


Application::~Application()
{
	//delete this->employee_controller;
}

CDialog* Application::run()
{
/*
	CMainFrameT *Frame = new CMainFrameT();
	//m_pMainWnd = Frame;

	Frame->ShowWindow(SW_NORMAL);
	Frame->UpdateWindow();

	return Frame;*/

	//this->employee_controller->run();// Injector::getInstance()->getMAINForm();
	////return (CDialog*)Injector::getInstance()->getIEmployeeADDForm();  
	//return   Injector::getInstance()->getMAINForm();

	CDialog* res = Injector::getInstance()->getMAINForm()->dialog;

	Injector::getInstance()->getIEmployeeController()->run();
	
	return   res;
	
	
	//return Injector::getInstance()->getIEmployeeADDForm();

}