#pragma once
#include "annotations.h"


class Employee
{
private:
	//[[FieldDescription("Name")]]
	std::string name;

//	[[FieldDescription("Date of Birth")]]
	CTime  dateofbirth;

//	[[FieldDescription("Annual Salary")]]
	float salary=0;

//	[[FieldDescription("Personal Address")]]
	std::string address;

	//[[FieldDescription("Private Phone of ten digit")]]
	//[[Field(ft_string, 10)]]
	std::string phone;

	//[[FieldDescription("Social Security Number of ten digits")]]
	//[[Field(ft_string,10)]]
	std::string ssn;

public:
	
	Employee();
	Employee(std::string name, CTime  dateofbirth, float salary, std::string address, std::string phone, std::string ssn);

	~Employee();

	std::string getName();
	void setName(std::string name);

	CTime  getDateofbirth();
	void setDateofbirth(CTime  dateofbirth);

	float getSalary();
	void setSalary(float salary);

	std::string getAddress();
	void setAddress(std::string address);

	std::string getPhone();
	void setPhone(std::string phone);

	std::string getSSN();
	void setSSN(std::string ssn);

};

