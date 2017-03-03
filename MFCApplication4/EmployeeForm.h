#pragma once

#include "Company.h"
#include "afxwin.h"

// EmployeeForm dialog

class EmployeeForm : public CDialogEx
{
	DECLARE_DYNAMIC(EmployeeForm)

public:
	EmployeeForm(CWnd* pParent = NULL);   // standard constructor
	virtual ~EmployeeForm();

// Dialog Data
	enum { IDD = IDD_DIALOGEmployee };
	// get the employee just added to the DB
	ref<Employee> GetEmployee();
	// initialize the data
	void SetEmployees(ref<Company>, BOOL);
	// pass the Employee its been edited
	void SetEmployee(ref<Employee>);

	BOOL EmployeeExists(char* ssn);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	// variable to hold the employee to be edited
	ref<Employee> employee;
	// pointer to the employee list to search by SSN
	ref<Company> root;
	// flag to determine if I'm editing
	BOOL new_employee;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit edtName;
	CEdit edtSSN;
	CEdit edtSalary;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CEdit edtDoB;
	CEdit edtAddress;
	CEdit edtPhone;
};
