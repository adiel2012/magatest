#include "stdafx.h"

#include "EmployeeRepositoryPosgress.h"


EmployeeRepositoryPostgre::EmployeeRepositoryPostgre()
{
	
}


EmployeeRepositoryPostgre::~EmployeeRepositoryPostgre()
{
}

int EmployeeRepositoryPostgre::add(Employee& employee)
{
	return 0;
}

int EmployeeRepositoryPostgre::remove(Employee& employee)
{
	return 0;
}

int EmployeeRepositoryPostgre::remove(std::string ssn)
{
	return 0;
}

int EmployeeRepositoryPostgre::getbySSN(std::string ssn, Employee& employeefill)
{
	return 0;
}

std::vector<Employee> EmployeeRepositoryPostgre::getAll()
{
	return std::vector<Employee>();
}

int EmployeeRepositoryPostgre::update(std::string oldSSN, Employee& employeedata)
{
	return 0;
}
