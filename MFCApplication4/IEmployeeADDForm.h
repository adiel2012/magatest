#pragma once
#include "Employee.h"
class IEmployeeADDForm
{
protected:
	int(*employee_add_request)(Employee employee, std::string ssn_old);
public:
	IEmployeeADDForm();
	~IEmployeeADDForm();
	virtual void clean() = 0;
	virtual void fill(Employee employee, std::string ssn) = 0;
	virtual void display()=0;
	virtual void hide() = 0;
	virtual void initialize_labels(std::string tittle, std::string btn_label) = 0;

	void setEmployee_add_request(int(*aEmployee_add_request)(Employee employee, std::string ssn_old)) {
		this->employee_add_request = aEmployee_add_request;
	}


};

