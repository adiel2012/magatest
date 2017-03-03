#include "stdafx.h"
#include "Company.h"

static void output_employee(ref<set_member> mbr, void const* listbox)
{
	CListBox* lb = (CListBox*)listbox;
    ref<Employee> e = mbr->obj;
    e->print(lb);
}

Company::Company(database const* db) : object(self_class) 
{
    employees = B_tree::create(NULL);
	employees->attach_to_storage(db, 0); 
}

ref<Employee> Company::find_employee_by_ssn(const char* ssn) const
{
    ref<set_member> mbr = employees->find(ssn);
    if (!mbr.is_nil()) { 
        return mbr->obj;
    } else { 
        return NULL;
    }
}

ref<Employee> Company::add_employee( char* name,  char* dob,  char* ssn, double salary,  char* address,  char* phone) const
{
	ref<Employee> e = find_employee_by_ssn(ssn);
    if (e == NULL) { 
        ref<Employee> e = Employee::create(name, dob, ssn, salary, address, phone);
        modify(employees)->insert(e->employees);
        modify(e)->cluster_with(employees);
		return e;
    } 
	return NULL;
}

BOOL Company::rem_employee(const char* ssn) const
{
    ref<Employee> e = find_employee_by_ssn(ssn);
    if (e == NULL) { 
        return false;
    } else { 
        modify(employees)->remove(e->employees);
    }           
	return true;
}

void Company::print_employees(CListBox* listbox) const
{
    employees->iterate(output_employee,listbox);
}

void Company::initialize() const 
{ 
    if (is_abstract_root()) { 
        ref<Company> root = this;
        modify(root)->become(NEW Company(get_database()));
    } 
    object::default_mop = &optimistic_scheme;
}

Company::~Company(void)
{
}

field_descriptor& Company::describe_components()
{
    return FIELD(employees);
}

REGISTER(Company, // class name 
        object,    // base class
        pessimistic_exclusive_scheme // metaobject
);
