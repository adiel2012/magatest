#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
//using namespace std;
#include "Employee.h"



typedef  int(*handle_add)(bool add);
typedef  int(*handle_delete)(std::string id);
typedef  int(*handle_edit)(std::string id);

class IMainForm
{
protected:
	
	// it is executed to when you need to request
	std::vector<Employee>(* Employees_request)()=nullptr;
	// it is executed when you need to add an employee
	

public:
	handle_add request_add = nullptr;
	handle_delete request_delete = nullptr;
	handle_edit request_edit = nullptr;	
	
	IMainForm();
	~IMainForm();
	void setEmployee_request(std::vector<Employee>(*aEmployee_request)());

	void setEmployee_add_request(handle_add a);
	void setEmployee_delete_request(handle_delete a);
	void setEmployee_edit_request(handle_edit a);

	virtual void execute_add_employee() = 0;
	virtual void display() = 0;
	virtual void fill(std::vector<Employee> employees)=0;
	virtual void hide() = 0;

	
};

