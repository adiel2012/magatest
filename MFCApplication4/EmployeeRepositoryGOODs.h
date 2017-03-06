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
	
	void initialize1()const{
		if (is_abstract_root()) {
			ref<CompanyExpress> root = this;
			CompanyExpress* ptr = NEW CompanyExpress(get_database());
			modify(root)->become(ptr);
		}
		object::default_mop = &optimistic_scheme;
	}
	ref<B_tree> employees;

	CompanyExpress(database const* db)
		: object(self_class){
		employees = B_tree::create(NULL);
		employees->attach_to_storage(db, 0);
	}
	~CompanyExpress(void){}
	METACLASS_DECLARATIONS(CompanyExpress, object);
};




class EmployeeRepositoryGOODs : public IEmployeeRepository
{
private:
	ref<CompanyExpress> company;
	ref<EmployeeGOODS> findEmployeeGOODS(std::string ssn);
public:


	void setDb(database* adb){
		adb->get_root(company);
		company->initialize1();
	}

	static void add_each(ref<set_member> mbr, void const*  stdvector_ptr);

	EmployeeRepositoryGOODs();
	~EmployeeRepositoryGOODs();

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

	wstring_t name;// [20];
	nat8  dateofbirth;
	double salary = 0;
	wstring_t address;// [200];
	wstring_t phone;// [10];
	wstring_t ssn;// [10];


	EmployeeGOODS();
	EmployeeGOODS(char name[20], CTime  dateofbirth, float salary, char address[200], char phone[10], char ssn[10]);
	EmployeeGOODS(Employee emp);
	Employee ToEmployee();
	~EmployeeGOODS();
	

	void setName(wstring_t name);
	
    METACLASS_DECLARATIONS(EmployeeGOODS, object);
};



#endif
