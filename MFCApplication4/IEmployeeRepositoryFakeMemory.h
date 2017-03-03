#pragma once
#include "IEmployeeRepository.h"
class IEmployeeRepositoryFakeMemory : public IEmployeeRepository
{
private:
	std::vector<Employee> __list;
public:
	IEmployeeRepositoryFakeMemory();
	~IEmployeeRepositoryFakeMemory();

	virtual int add(Employee& employee);
	virtual int remove(Employee& employee);
	virtual int remove(std::string ssn);
	virtual int getbySSN(std::string ssn, Employee& employeefill);
	virtual std::vector<Employee> getAll() ;
	virtual int update(std::string oldSSN, Employee& employeedata);
};

