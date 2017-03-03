#pragma once

#include "MainFrame.h"
#include "IEmployeeRepositoryFakeMemory.h"
#include "EmployeeController.h"
#include "EmployeeADDForm.h"

class EmployeeController;

class Injector
{

private:
	
	static Injector* __instance;
	IEmployeeRepository* __IEmployeeRepository_instance;
	EmployeeADDForm* __IEmployeeADDForm;
	MainFrame* __IMainForm = nullptr;
	EmployeeController* __IEmployeeController;
	
public:
	Injector();
	~Injector();
	IEmployeeRepository* getIEmployeeRepository();
	EmployeeADDForm* getIEmployeeADDForm();
	MainFrame* getMAINForm();
	EmployeeController* getIEmployeeController();

	static Injector* Injector::getInstance()
	{
		// TODO: insert return statement here
		//static Injector instance;
		if (__instance == nullptr)
			__instance = new Injector();
		return __instance;
	}
	


};




