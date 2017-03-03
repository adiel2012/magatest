// EmployeeForm.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication4.h"
#include "EmployeeForm.h"
#include "afxdialogex.h"

#include <string.h>


// EmployeeForm dialog

IMPLEMENT_DYNAMIC(EmployeeForm, CDialogEx)

EmployeeForm::EmployeeForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(EmployeeForm::IDD, pParent)
{
	
}

EmployeeForm::~EmployeeForm()
{
}


void EmployeeForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edtName);
	DDX_Control(pDX, IDC_EDIT2, edtSSN);
	DDX_Control(pDX, IDC_EDIT3, edtSalary);
	DDX_Control(pDX, IDC_EDIT4, edtDoB);
	DDX_Control(pDX, IDC_EDIT5, edtAddress);
	DDX_Control(pDX, IDC_EDIT6, edtPhone);
}

// get a reference to the employee added/edited
ref<Employee> EmployeeForm::GetEmployee()
{
	return this->employee;
}

// method used to pass a reference of the Company object in the main dialog. 
// The second parameter es to specify if I'm editing or adding a new employee
void EmployeeForm::SetEmployees(ref<Company> root, BOOL new_employee)
{
	this->root = root;
	this->new_employee = new_employee;
}

// Pass the employee to edit to the form
void EmployeeForm::SetEmployee(ref<Employee> employee)
{
	this->employee = employee;
}

// Search if the employee exists on the database (by SSN)
BOOL EmployeeForm::EmployeeExists(char* ssn)
{
	ref<set_member> mbr = this->root->find_employee_by_ssn(ssn);
	if (!mbr.is_nil()) { 
		return true;
	}
	return false;
}


BEGIN_MESSAGE_MAP(EmployeeForm, CDialogEx)
	ON_BN_CLICKED(IDOK, &EmployeeForm::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// EmployeeForm message handlers


void EmployeeForm::OnBnClickedOk()
{

	// name
	CString strLine;
	int len = edtName.LineLength(edtName.LineIndex(0));
	edtName.GetLine(0,strLine.GetBuffer(len), len);

	strLine.ReleaseBuffer(len);
	
	char* temp = new char[len+1];

	size_t   i;
	wchar_t*pWCBuffer = strLine.GetBuffer();
    wcstombs_s(&i, temp, (size_t)len+1, 
               pWCBuffer, (size_t)len+1 );

	// SSN
	len = edtSSN.LineLength(edtSSN.LineIndex(0));
	edtSSN.GetLine(0,strLine.GetBuffer(len), len);

	strLine.ReleaseBuffer(len);
	
	char* temp_ssn = new char[len+1];

	pWCBuffer = strLine.GetBuffer();

    wcstombs_s(&i, temp_ssn, (size_t)len+1, 
               pWCBuffer, (size_t)len+1 );


	// DoB
	len = edtDoB.LineLength(edtDoB.LineIndex(0));
	edtDoB.GetLine(0,strLine.GetBuffer(len), len);

	strLine.ReleaseBuffer(len);
	
	char* temp_dob = new char[len+1];

	pWCBuffer = strLine.GetBuffer();

	wcstombs_s(&i, temp_dob, (size_t)len+1, 
               pWCBuffer, (size_t)len+1 );

	// Address
	len = edtAddress.LineLength(edtAddress.LineIndex(0));
	edtAddress.GetLine(0,strLine.GetBuffer(len), len);

	strLine.ReleaseBuffer(len);
	
	char* temp_address = new char[len+1];

	pWCBuffer = strLine.GetBuffer();

	wcstombs_s(&i, temp_address, (size_t)len+1, 
               pWCBuffer, (size_t)len+1 );

	// Phone
	len = edtPhone.LineLength(edtPhone.LineIndex(0));
	edtPhone.GetLine(0,strLine.GetBuffer(len), len);

	strLine.ReleaseBuffer(len);
	
	char* temp_phone = new char[len+1];

	pWCBuffer = strLine.GetBuffer();

	wcstombs_s(&i, temp_phone, (size_t)len+1, 
               pWCBuffer, (size_t)len+1 );

	// Salary
	len = edtSalary.LineLength(edtSalary.LineIndex(0));
	edtSalary.GetLine(0,strLine.GetBuffer(len), len);

	strLine.ReleaseBuffer(len);
	double salary = _wtof(strLine);

	BOOL exists = (new_employee && EmployeeExists(temp_ssn)); // only check for SSN if I'm adding a new employee
	if (exists == true){
		MessageBoxA(0,"Employee already exists","Error",0);
	}
	else{
		// create the new Employee
		this->employee = this->root->add_employee(temp,temp_dob,temp_ssn, salary,temp_address,temp_phone);
		CDialogEx::OnOK();
	}
}


void EmployeeForm::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	// when showing the dialog, if I'm editing an employee, display its data
	if (!new_employee){
		// get the name
		wstring_t name = this->employee->GetName();
		edtName.SetWindowText(name);

		// get the SSN
		wstring_t ssn = this->employee->GetSSN();
		edtSSN.SetWindowText(ssn);

		// get the Date of Birth
		wstring_t dob = this->employee->GetDoB();
		edtDoB.SetWindowText(dob);

		// get the Address
		wstring_t address = this->employee->GetAddress();
		edtAddress.SetWindowText(address);

		// get the phone
		wstring_t phone = this->employee->GetPhone();
		edtPhone.SetWindowText(phone);

		// get the salary
		double salary = this->employee->GetSalary();

		// convert the salary to a char*
		char * buf = 0;
		  int decimal;
		  int sign;
		  int err;

		  buf = (char*) malloc(_CVTBUFSIZE);
		  _gcvt_s(buf, _CVTBUFSIZE, salary, 12 ); 
		LPTSTR text = A2BSTR(buf);
		edtSalary.SetWindowText(text);
	}
}
