#include "stdafx.h"
#include "Injector.h"
#include "EmployeeRepositoryGOODs.h"
#include "EmployeeRepositoryPosgress.h"

//   la locura
Injector* Injector::__instance;

Injector::Injector()
{
}




Injector::~Injector()
{
	//instanceFlag = false;
	delete __IEmployeeRepository_instance;
	//delete __IEmployeeADDForm;
}

IEmployeeRepository* Injector::getIEmployeeRepository()
{
	//static EmployeeRepositoryGOODs instance;
	if (__IEmployeeRepository_instance == nullptr)
		__IEmployeeRepository_instance =  new EmployeeRepositoryGOODs();  //    new IEmployeeRepositoryFakeMemory();
	
	return __IEmployeeRepository_instance;
}

EmployeeADDForm * Injector::getIEmployeeADDForm()
{
	if (__IEmployeeADDForm == nullptr)
		__IEmployeeADDForm = new  EmployeeADDForm();
	return this->__IEmployeeADDForm;
}

MainFrame* Injector::getMAINForm()
{
	// TODO: insert return statement here
	//static MainFrame instance;
	if (__IMainForm == nullptr)
		__IMainForm = new MainFrame();

	return __IMainForm;
}

//IEmployeeController * Injector::getIEmployeeController()
//{
//	if (__IEmployeeController== nullptr)
//		__IEmployeeController = new EmployeeController();
//
//	return __IEmployeeController;
//	return nullptr;
//}
#include "EmployeeController.h"

EmployeeController* Injector::getIEmployeeController()
{
	// TODO: insert return statement here
	// static EmployeeController instance;
	if (__IEmployeeController == nullptr)
		__IEmployeeController = new EmployeeController();

	return __IEmployeeController;


	//return nullptr;
}

Injector* Injector::getInstance()

{
	// TODO: insert return statement here
	//static Injector instance;
	if (__instance == nullptr)
		__instance = new Injector();
	return __instance;
}

//EmployeeController & Injector::getEmployeeController()
//{
//	// TODO: insert return statement here
//	static EmployeeController instance;
//	return instance;
//}

//IEmployeeADDForm & Injector::getIEmployeeADDForm()
//{
//	return new IEmployeeADDForm();
//	// TODO: insert return statement here
//}
