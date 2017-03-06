#include "stdafx.h"
#include "EmployeeRepositoryFakeMemory.h"


EmployeeRepositoryFakeMemory::EmployeeRepositoryFakeMemory()
{
	
	add(Employee("Juan", GetCurrentTime(), 1.0f, "mia addfdghh", "ffffff", "2222222222"));
	add(Employee("Adiel", GetCurrentTime(),1.0f,"mia add","dffsdsdf","1111111111"));
}


EmployeeRepositoryFakeMemory::~EmployeeRepositoryFakeMemory()
{
}

int EmployeeRepositoryFakeMemory::add(Employee& employee)
{
	__list.push_back(employee);
	return 0;
}

int EmployeeRepositoryFakeMemory::remove(Employee& employee)
{
	return this->remove(employee.getSSN());
}

int EmployeeRepositoryFakeMemory::remove(std::string ssn)
{

	int position = -1;
	int index = 0;
	for (std::vector<Employee>::iterator it = this->__list.begin(); it != this->__list.end(); ++it) {
		if ((*it).getSSN() == ssn) {
			position = index;
		}
		index++;
	}
	if (position != -1) {
		this->__list.erase(this->__list.begin()+ position);
		return 0;
	}
	else {
		// code of error
		return 1;
	}	

	return 0;
}

int EmployeeRepositoryFakeMemory::getbySSN(std::string ssn, Employee& employeefill)
{

	int position = -1;
	int index = 0;
	for (std::vector<Employee>::iterator it = this->__list.begin(); it != this->__list.end(); ++it) {
		if ((*it).getSSN() == ssn) {
			position = index;
		}
		index++;
	}
	if (position != -1) {
		employeefill = this->__list[position];
		//return unique_ptr<Employee>(&this->__list[position]);
		return 0;
	}
	else {
		// code of error
		return -1;
	}

	return -1;
}

std::vector<Employee> EmployeeRepositoryFakeMemory::getAll()
{
	return std::vector<Employee>(this->__list);
}



int EmployeeRepositoryFakeMemory::update(std::string oldSSN, Employee& employeedata)
{
	if (this->remove(oldSSN) == -1)
		return -1;
	return this->add(employeedata);
}
