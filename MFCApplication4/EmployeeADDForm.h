#pragma once
#include "IEmployeeADDForm.h"
#include "resource.h"
#include "commons.h"

class Employee_Dialog;
class EmployeeADDForm: public IEmployeeADDForm
{
private:
	Employee_Dialog* dialog; 
	friend class Employee_Dialog;
	// utilery
	std::string ssn_toedit = "";
	Employee employee_toedit;
protected:
	
public:
	EmployeeADDForm(CWnd* pParent = NULL);
	~EmployeeADDForm();

	virtual void clean() ;
	virtual void fill(Employee employee, std::string ssn);
	virtual void display() ;
	virtual void hide();
	virtual void initialize_labels(std::string tittle, std::string btn_label);
	
};



class Employee_Dialog : public CDialog {
private:
	CEdit edt_ssn;
	CEdit edt_salary;
	CEdit edt_name;
	CEdit edt_address;
	CEdit edt_phone;
	CDateTimeCtrl  edt_date_birth;
	EmployeeADDForm* parent;
	CButton btn_OK;
	friend class EmployeeADDForm;

public:
	Employee_Dialog(CWnd* pParent);
	~Employee_Dialog();

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	void init();

	afx_msg void inform_click();
	virtual void OnClose();
	void clean();
	DECLARE_MESSAGE_MAP()
};