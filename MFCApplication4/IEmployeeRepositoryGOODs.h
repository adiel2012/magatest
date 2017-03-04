#pragma once


#ifndef __IEmployeeRepository
#define __IEmployeeRepository
// !__IEmployeeRepository


#include "IEmployeeRepository.h"

#include "inc/goods.h"
#include "inc/dbscls.h"

USE_GOODS_NAMESPACE




class EmployeeGOODS;


class CompanyExpress : public object{

public:
	database* db;
	void initialize1(database* db)const{
		if (is_abstract_root()) {
			ref<CompanyExpress> root = this;
			CompanyExpress* ptr = NEW CompanyExpress();
			ptr->db = db;
			modify(root)->become(ptr);
		}
		object::default_mop = &optimistic_scheme;
	}
	ref<B_tree> employees;
	/*void SetEmployees(ref<B_tree> a){
		employees = a;
	}*/
	CompanyExpress() : object(self_class){
		employees = B_tree::create(NULL);
	}
	~CompanyExpress(){}


	



	METACLASS_DECLARATIONS(CompanyExpress, object);

};




class IEmployeeRepositoryGOODs : public IEmployeeRepository
{
private:

	//ref<B_tree>  employees;
	ref<CompanyExpress> company;

	ref<EmployeeGOODS> findEmployeeGOODS(std::string ssn);
	database* db;
public:


	void setDb(database* adb){
		this->db = adb;
		db->get_root(company);
		company->initialize1(adb);
		//this->company->initialize(adb);

	}
	//task::initialize(task::normal_stack);

	static void add_each(ref<set_member> mbr, void const*  stdvector_ptr);

	IEmployeeRepositoryGOODs();
	~IEmployeeRepositoryGOODs();

	virtual int add(Employee& employee);
	virtual int remove(Employee& employee);
	virtual int remove(std::string ssn);
	virtual int getbySSN(std::string ssn, Employee& employeefill);
	virtual std::vector<Employee> getAll();
	virtual int update(std::string oldSSN, Employee& employeedata);
};



class EmployeeGOODS : public object
{
public:
	//[[FieldDescription("Name")]]
	wstring_t name;// [20];

	//	[[FieldDescription("Date of Birth")]]
	real8  dateofbirth;

	//	[[FieldDescription("Annual Salary")]]
	real4 salary = 0;

	//	[[FieldDescription("Personal Address")]]
	wstring_t address;// [200];

	//[[FieldDescription("Private Phone of ten digit")]]
	//[[Field(ft_string, 10)]]
	wstring_t phone;// [10];

	//[[FieldDescription("Social Security Number of ten digits")]]
	//[[Field(ft_string,10)]]
	wstring_t ssn;// [10];

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
