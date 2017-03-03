#pragma once
#include "Employee.h"
#include "annotations.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
//using namespace std;

class IEmployeeRepository
{
public:
	IEmployeeRepository();
	~IEmployeeRepository();
	virtual int add(Employee& employee)=0;
	virtual int remove(Employee& employee) = 0;
	virtual int remove(std::string ssn) = 0;
	virtual int getbySSN(std::string ssn, Employee& employeefill) = 0;
	virtual std::vector<Employee> getAll() = 0;
	virtual int update(std::string oldSSN, Employee& employeedata) = 0;
};

