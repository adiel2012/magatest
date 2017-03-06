#include "stdafx.h"
#include "IMainForm.h"


IMainForm::IMainForm()
{
}


IMainForm::~IMainForm()
{
}

void IMainForm::setEmployee_request(std::vector<Employee>(* aEmployee_request)())
{
	this->Employees_request = aEmployee_request;
}

void IMainForm::setEmployee_add_request(handle_add a)
{
	this->request_add = a;
}

void IMainForm::setEmployee_delete_request(handle_delete a)
{
	this->request_delete = a;
}

void IMainForm::setEmployee_edit_request(handle_edit a)
{
	this->request_edit = a;
}
