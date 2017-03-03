#include "stdafx.h"
#include "IEmployeeRepositoryGOODs.h"


ref<EmployeeGOODS> IEmployeeRepositoryGOODs::findEmployeeGOODS(std::string ssn)
{
	ref<set_member> mbr = employees->find(ssn.c_str());
	if (!mbr.is_nil()) {
		return mbr->obj;
	}
	else {
		return NULL;
	}
}



IEmployeeRepositoryGOODs::IEmployeeRepositoryGOODs()
{
	this->employees = B_tree::create(NULL);
}


IEmployeeRepositoryGOODs::~IEmployeeRepositoryGOODs()
{
}

int IEmployeeRepositoryGOODs::add(Employee& employee)
{
	if (!this->findEmployeeGOODS(employee.getSSN()).is_nil())
		return -1;

	EmployeeGOODS e(employee);
	modify(employees)->insert(&(e.ssn[0]),&e);
	return 0;
}

int IEmployeeRepositoryGOODs::remove(Employee& employee)
{
	return this->remove(employee.getSSN());
}

int IEmployeeRepositoryGOODs::remove(std::string ssn)
{
	ref<EmployeeGOODS> s = this->findEmployeeGOODS(ssn.c_str());
	if (s == NULL) {
		return -1;
	}
	else {
		ref<set_member> res = s;
		modify(employees)->remove(res);
	}
	return 0;
}

int IEmployeeRepositoryGOODs::getbySSN(std::string ssn, Employee& employeefill)
{

	
	ref<set_member> mbr = employees->find(ssn.c_str());
	ref<EmployeeGOODS> cc = mbr;
	

	if (!mbr.is_nil()) {
		employeefill.setSSN(std::string(cc->ssn));
		employeefill.setAddress(std::string(cc->address));
		employeefill.setPhone(std::string(cc->phone));
		employeefill.setName(std::string(cc->name));
		employeefill.setDateofbirth(cc->dateofbirth);
		employeefill.setSalary(cc->salary);
	}
	else {
		return NULL;
	}
	return -1;  // std::unique_ptr<Employee>(new Employee());
}

std::vector<Employee> IEmployeeRepositoryGOODs::getAll()
{
	std::vector<Employee> res;
	employees->iterate(IEmployeeRepositoryGOODs::add_each, &res);
	return res;
}

void IEmployeeRepositoryGOODs::add_each(ref<set_member> mbr, void const * stdvector_ptr)
{
	std::vector<Employee>* buffer = (std::vector<Employee>*) stdvector_ptr;
	ref<EmployeeGOODS> p = mbr->obj;
	Employee b;
	buffer->push_back(b);
}



int IEmployeeRepositoryGOODs::update(std::string oldSSN, Employee& employeedata)
{
	ref<EmployeeGOODS> res1 = this->findEmployeeGOODS(oldSSN);
	ref<EmployeeGOODS> res2 = this->findEmployeeGOODS(employeedata.getSSN());
	if (res1.is_nil()) {
		return 4; // element not present
	}
	else {
		if (!res2.is_nil() && oldSSN != employeedata.getSSN()) {
			return 5; // the ssn wil be repeated
		}
	}

	this->remove(oldSSN);
	this->add(employeedata);
	return 0;
}

EmployeeGOODS::EmployeeGOODS() : object(self_class)
{
}

EmployeeGOODS::EmployeeGOODS(char name[20], CTime dateofbirth, float salary, char address[200], char phone[10], char ssn[10]) : object(self_class)
{
	strcpy(this->name, name);
	this->dateofbirth = dateofbirth;
	this->salary = salary;
	strcpy(this->address, address);
	strcpy(this->phone, phone);
	strcpy(this->ssn, ssn);
}

EmployeeGOODS::EmployeeGOODS(Employee emp) : object(self_class)
{
	strcpy(this->name, emp.getName().c_str());
	this->dateofbirth = emp.getDateofbirth();
	this->salary = emp.getSalary();
	strcpy(this->address, emp.getAddress().c_str());
	strcpy(this->phone, emp.getPhone().c_str());
	strcpy(this->ssn, emp.getSSN().c_str());
}

Employee EmployeeGOODS::ToEmployee()
{
	return Employee(std::string(name), dateofbirth, salary, std::string(address), std::string(phone), std::string(ssn));
}

EmployeeGOODS::~EmployeeGOODS()
{
}

field_descriptor & EmployeeGOODS::describe_components()
{
	return FIELD(ssn),  FIELD(address),
		FIELD(phone), FIELD(ssn);
}

REGISTER(EmployeeGOODS, object, pessimistic_repeatable_read_scheme);

