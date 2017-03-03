#pragma once
class IEmployeeController
{
public:
	IEmployeeController();
	~IEmployeeController();


	virtual void run()=0;
	virtual void employee_add_requested()=0;
};

