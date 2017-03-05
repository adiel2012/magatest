#include "stdafx.h"
#include "IEmployeeRepositoryGOODs.h"
#include "commons.h"

field_descriptor& CompanyExpress::describe_components()
{
	return FIELD(employees);
}



REGISTER(CompanyExpress, // class name 
	object, // base class
	pessimistic_exclusive_scheme // metaobject
);

ref<EmployeeGOODS> IEmployeeRepositoryGOODs::findEmployeeGOODS(std::string ssn)
{

	//	task::initialize(task::normal_stack);

	ref<set_member> mbr = company->employees->find(ssn.c_str());
	if (!mbr.is_nil()) {
		return mbr->obj;
	}
	else {
		return NULL;
	}
}



IEmployeeRepositoryGOODs::IEmployeeRepositoryGOODs()
{
	//company->SetEmployees = B_tree::create(NULL);
}


IEmployeeRepositoryGOODs::~IEmployeeRepositoryGOODs()
{
}

int IEmployeeRepositoryGOODs::add(Employee& employee)
{
	if (!this->findEmployeeGOODS(employee.getSSN()).is_nil())
		return -1;

	EmployeeGOODS e(employee);
	const char* key = e.ssn.getChars();
	modify(company->employees)->insert(key, &e);
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
		modify(company->employees)->remove(res);
	}
	return 0;
}

int IEmployeeRepositoryGOODs::getbySSN(std::string ssn, Employee& employeefill)
{
	
	ref<set_member> mbr = company->employees->find(ssn.c_str());
	ref<EmployeeGOODS> cc = mbr;
	

	if (!mbr.is_nil()) {
		employeefill.setSSN(std::string(cc->ssn.getChars()));
		employeefill.setAddress(std::string(cc->address.getChars()));
		employeefill.setPhone(std::string(cc->phone.getChars()));
		employeefill.setName(std::string(cc->name.getChars()));
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
	company->employees->iterate(IEmployeeRepositoryGOODs::add_each, &res);
	return res;
}

void IEmployeeRepositoryGOODs::add_each(ref<set_member> mbr, void const * stdvector_ptr)
{
	std::vector<Employee>* buffer = (std::vector<Employee>*) stdvector_ptr;
	ref<EmployeeGOODS> p = mbr->obj;
	Employee b;
	b.setAddress(std::string(p->address.getChars()));
	b.setName(std::string(p->name.getChars()));
	b.setPhone(std::string(p->phone.getChars()));
	b.setName(std::string(p->ssn.getChars()));
	b.setSalary(p->salary);
	b.setSSN(std::string(p->ssn.getChars()));
	CTime time(p->dateofbirth);
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
	this->name= name;
	//  strcpy(this->name, name);
	this->dateofbirth = (long)(dateofbirth.GetTime());;
	this->salary = salary;
	this->address= address;
	//strcpy(this->address, address);
	this->phone= phone;
	//strcpy(this->phone, phone);
	this->ssn= ssn;
	//strcpy(this->ssn, ssn);
}

EmployeeGOODS::EmployeeGOODS(Employee emp) : object(self_class)
{
	this->name = emp.getName().c_str();
	this->dateofbirth = (long)(emp.getDateofbirth().GetTime());
	this->salary = emp.getSalary();
	this->address, emp.getAddress().c_str();
	this->phone, emp.getPhone().c_str();
	this->ssn, emp.getSSN().c_str();
}

Employee EmployeeGOODS::ToEmployee()
{
	return Employee(std::string(name.getChars()), dateofbirth, salary, std::string(address.getChars()), std::string(phone.getChars()), std::string(ssn.getChars()));
}

EmployeeGOODS::~EmployeeGOODS()
{
}

field_descriptor & EmployeeGOODS::describe_components()
{
	return FIELD(name), FIELD(dateofbirth), FIELD(salary), FIELD(address), FIELD(phone), FIELD(ssn);
	// name  dateofbirth salary, address, phone, ssn
}

REGISTER(EmployeeGOODS, object, pessimistic_repeatable_read_scheme);

//REGISTER(CompanyExpress, object, pessimistic_exclusive_scheme);