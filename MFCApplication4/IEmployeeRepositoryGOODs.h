#pragma once


#ifndef __IEmployeeRepository
#define __IEmployeeRepository
 // !__IEmployeeRepository


#include "IEmployeeRepository.h"

#include "inc/goods.h"
#include "inc/dbscls.h"

USE_GOODS_NAMESPACE


class EmployeeGOODS;
class IEmployeeRepositoryGOODs: public IEmployeeRepository
{
private:
	database db;
	ref<B_tree>  employees;
    //task::initialize(task::normal_stack);
	ref<EmployeeGOODS> findEmployeeGOODS(std::string ssn);
public:

	static void add_each(ref<set_member> mbr, void const*  stdvector_ptr);
	
	IEmployeeRepositoryGOODs();
	~IEmployeeRepositoryGOODs();

	virtual int add(Employee& employee) ;
	virtual int remove(Employee& employee) ;
	virtual int remove(std::string ssn);
	virtual int getbySSN(std::string ssn, Employee& employeefill);
	virtual std::vector<Employee> getAll();
	virtual int update(std::string oldSSN, Employee& employeedata);
};



class EmployeeGOODS: public object
{
public:
	//[[FieldDescription("Name")]]
	char name[20];

	//	[[FieldDescription("Date of Birth")]]
	CTime  dateofbirth;

	//	[[FieldDescription("Annual Salary")]]
	float salary = 0;

	//	[[FieldDescription("Personal Address")]]
	char address[200];

	//[[FieldDescription("Private Phone of ten digit")]]
	//[[Field(ft_string, 10)]]
	char phone[10];

	//[[FieldDescription("Social Security Number of ten digits")]]
	//[[Field(ft_string,10)]]
	char ssn[10];

public:

	EmployeeGOODS();
	EmployeeGOODS(char name[20], CTime  dateofbirth, float salary, char address[200], char phone[10], char ssn[10]);
	EmployeeGOODS(Employee emp);

	Employee ToEmployee();

	~EmployeeGOODS();

	//field_descriptor& describe_components();

	METACLASS_DECLARATIONS(EmployeeGOODS, object);

};


#endif
