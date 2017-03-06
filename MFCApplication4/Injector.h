#pragma once

#include "MainFrame.h"
#include "EmployeeRepositoryFakeMemory.h"
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

	static Injector* getInstance();
	


};




