#include "stdafx.h"
#include "IEmployeeADDForm.h"


IEmployeeADDForm::IEmployeeADDForm()
{
}


IEmployeeADDForm::~IEmployeeADDForm()
{
}

void IEmployeeADDForm::setEmployee_add_request(int(* aEmployee_add_request)(Employee employee, std::string ssn_old))
{
	this->employee_add_request = aEmployee_add_request;
}
