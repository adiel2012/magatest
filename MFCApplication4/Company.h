#include "Employee.h"

#pragma once
class Company : public object
{
public:

	ref<B_tree> employees;

	ref<Employee> find_employee_by_ssn(const char* ssn) const;
	void print_employees(CListBox*) const;
	ref<Employee> add_employee( char* name,  char* dob,  char* ssn, double salary,  char* address,  char* phone) const;
    BOOL rem_employee(const char* ssn) const;
	void initialize() const; 

  
    Company(database const* db);

	~Company(void);

    METACLASS_DECLARATIONS(Company, object);
};

