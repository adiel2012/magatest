#include "stdafx.h"
#include "EmployeeADDForm.h"




Employee_Dialog::~Employee_Dialog()
{
}

void Employee_Dialog::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);

	//edt_ssn = (CEdit*)GetDlgItem(EDT_SSN);
	//edt_salary = (CEdit*)GetDlgItem(EDT_SALARY);
	//edt_name = (CEdit*)GetDlgItem(EDT_NAME);
	//edt_address = (CEdit*)GetDlgItem(EDT_ADDRESS);
	//edt_phone = (CEdit*)GetDlgItem(EDT_PHONE);
	//edt_date_birth = (CEdit*)GetDlgItem(EDT_DATE_BIRTH);

	DDX_Control(pDX, EDT_SSN, edt_ssn);
	DDX_Control(pDX, EDT_SALARY, edt_salary);
	DDX_Control(pDX, EDT_NAME, edt_name);
	DDX_Control(pDX, EDT_ADDRESS, edt_address);
	DDX_Control(pDX, EDT_PHONE, edt_phone);
	DDX_Control(pDX, EDT_DATE_BIRTH, edt_date_birth);
	DDX_Control(pDX, ID_INFORM_CLICK, btn_OK);
	

	//DDX_Control(pDX, IDC_LIST1, grid);
}

BOOL Employee_Dialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	init();
	/*pButtonimp = (CButton *)GetDlgItem(IDOK);
	pButtonquit = (CButton *)GetDlgItem(IDCANCEL);*/

	return true;
}

void Employee_Dialog::init()
{
	edt_address.SetWindowText(Utils::convertToLPCWSTR(this->parent->employee_toedit.getAddress().c_str()));
	//edt_date_birth.SetWindowText(Utils::convertToLPCWSTR(this->parent->employee_toedit.getDateofbirth().c_str()));
	CTime timee = this->parent->employee_toedit.getDateofbirth();
	
	edt_date_birth.SetTime(&timee);
	//edt_date_birth.gettim

	edt_name.SetWindowText(Utils::convertToLPCWSTR(this->parent->employee_toedit.getName().c_str()));
	edt_phone.SetWindowText(Utils::convertToLPCWSTR(this->parent->employee_toedit.getPhone().c_str()));
	edt_salary.SetWindowText(Utils::convertToLPCWSTR(Utils::floatTostring(this->parent->employee_toedit.getSalary()).c_str()));
	edt_ssn.SetWindowText(Utils::convertToLPCWSTR(this->parent->employee_toedit.getSSN().c_str()));

	//this ->parent->initialize_labels("AAAAAAAAAA", "Edit");
	
	std::string tittle = "";
	std::string btn_label = "";

	if (parent->ssn_toedit=="") {
		tittle = "Add Employee";
		btn_label = "Add";
	}
	else {
		tittle = "Edit Employee";
		btn_label = "Edit";
	}

	SetWindowText(Utils::convertToLPCWSTR(tittle.c_str()));
	btn_OK.SetWindowText(Utils::convertToLPCWSTR(btn_label.c_str()));

	//

	/*this->btn_add = (CButton*)GetDlgItem(ID_APP_Add);
	this->grid = (CListCtrl*)GetDlgItem(IDC_LIST1);*/
}

EmployeeADDForm::EmployeeADDForm(CWnd* pParent): IEmployeeADDForm()
{
	dialog = new Employee_Dialog(pParent);
	dialog->parent = this;
}


EmployeeADDForm::~EmployeeADDForm()
{
	delete dialog;
}

void EmployeeADDForm::clean()
{
	this->ssn_toedit = "";
	this->dialog->clean();
}

void EmployeeADDForm::fill(Employee employee, std::string ssn)
{
	this->ssn_toedit = ssn;
	this->employee_toedit = employee;
	
	/*this->dialog->edt_address.SetWindowText(Utils::convertToLPCWSTR(employee.getAddress().c_str()));
	this->dialog->edt_date_birth.SetWindowText(Utils::convertToLPCWSTR(employee.getDateofbirth().c_str()));
	this->dialog->edt_name.SetWindowText(Utils::convertToLPCWSTR(employee.getName().c_str()));
	this->dialog->edt_phone.SetWindowText(Utils::convertToLPCWSTR(employee.getPhone().c_str()));
	this->dialog->edt_salary.SetWindowText(Utils::convertToLPCWSTR(Utils::floatTostring(employee.getSalary()).c_str()));
	this->dialog->edt_ssn.SetWindowText(Utils::convertToLPCWSTR(employee.getSSN().c_str()));
	*/
	int g = 0;
}

//void EmployeeADD::fill(Employee employee)
//{
//}
static bool createdEmployeeADDForm = false;
void EmployeeADDForm::display()
{
	/*if(!createdEmployeeADDForm)
	BOOL res = this->dialog->Create(IDD_DIALOG1, NULL);	
	this->dialog->ShowWindow(SW_NORMAL);*/


	

	this->dialog->DoModal();

	createdEmployeeADDForm=true;
	//if (this->employee_add_request != nullptr) {

	//	CString ssn;
	//	edt_ssn->GetWindowText(ssn);
	//	CString name;
	//	edt_ssn->GetWindowText(name);
	//	CString salary;
	//	edt_ssn->GetWindowText(salary);
	//	CString phone;
	//	edt_ssn->GetWindowText(phone);
	//	CString date;
	//	edt_ssn->GetWindowText(date);
	//	CString address;
	//	edt_ssn->GetWindowText(address);

	//	this->employee_add_request(Employee());
	//}
}

void EmployeeADDForm::hide()
{
	this->dialog->EndDialog(0);
}

void EmployeeADDForm::initialize_labels(std::string tittle, std::string btn_label)
{
	/*this->dialog->SetWindowText(Utils::convertToLPCWSTR(tittle.c_str()));
	this->dialog->btn_OK.SetWindowText(Utils::convertToLPCWSTR(btn_label.c_str()));*/
}

#include "commons.h"
void Employee_Dialog::inform_click()
{
	if (parent->employee_add_request!=nullptr) {

			CString ssn;
			edt_ssn.GetWindowText(ssn);
			CString name;
			edt_name.GetWindowText(name);
			CString salary;
			edt_salary.GetWindowText(salary);
			CString phone;
			edt_phone.GetWindowText(phone);
			CTime date;
			edt_date_birth.GetTime(date);
			CString address;
			edt_address.GetWindowText(address);
			//  Employee(string name, string dateofbirth, float salary, string address,  string phone,  string ssn);

			/*CTimeSpan dateadd();
			dateadd.*/
			
			float fsalary = atof( Utils::CStringtostring(salary).c_str());
		    parent->employee_add_request(Employee(Utils::CStringtostring(name), date, fsalary, Utils::CStringtostring(address), Utils::CStringtostring(phone), Utils::CStringtostring(ssn)),parent->ssn_toedit);
	}
	
}

void Employee_Dialog::clean()
{
	//this->edt_address.settezt
	this->parent->fill(Employee(),"");

}


BEGIN_MESSAGE_MAP(Employee_Dialog, CDialog)
	ON_COMMAND(ID_INFORM_CLICK, inform_click)

END_MESSAGE_MAP()