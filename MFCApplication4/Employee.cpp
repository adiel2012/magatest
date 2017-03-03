#include "stdafx.h"
#include "Employee.h"


Employee::Employee()
{
	this->dateofbirth = GetCurrentTime();
}

Employee::Employee(std::string name, CTime  dateofbirth, float salary, std::string address, std::string phone, std::string ssn)
{
	this->name = name;
	this->dateofbirth = dateofbirth;
	this->salary = salary;
	this->address = address;
	this->phone = phone;
	this->ssn = ssn;
}


Employee::~Employee()
{
}



std::string Employee::getName()
{
	return name;
}

void Employee::setName(std::string name)
{
	this->name = name;
}

CTime  Employee::getDateofbirth()
{
	return this->dateofbirth;
}

void Employee::setDateofbirth(CTime  dateofbirth)
{
	this->dateofbirth = dateofbirth;
}

float Employee::getSalary()
{
	return this->salary;
}

void Employee::setSalary(float name)
{
	this->salary = salary;
}

std::string Employee::getAddress()
{
	return address;
}

void Employee::setAddress(std::string address)
{
	this->address = address;
}

std::string Employee::getPhone()
{
	return this->phone;
}

void Employee::setPhone(std::string phone)
{
	this->phone = phone;
}

std::string Employee::getSSN()
{
	return this->ssn;
}

void Employee::setSSN(std::string ssn)
{
	this->ssn = ssn;
}


