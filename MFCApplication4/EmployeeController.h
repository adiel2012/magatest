#pragma once
#include "IEmployeeRepository.h"
#include "Injector.h"
#include "EmployeeADDForm.h"

class EmployeeController
{
private:

	IEmployeeRepository* repo =nullptr;
	IMainForm* mainform = nullptr;
	IEmployeeADDForm* add_form = nullptr;
	static int validate(Employee e);

public:
	EmployeeController();
	~EmployeeController();

	void show_add_form();
	void run();
	static int employee_add_requested(bool add);
	static int employee_delete_requested(std::string id);
	static int employee_edit_requested(std::string id);
	static std::vector<Employee> employees_requested();
	static int do_add_persistence(Employee employee, std::string ssn_old);

};

