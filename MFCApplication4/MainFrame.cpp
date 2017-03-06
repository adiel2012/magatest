#include "stdafx.h"
#include "MainFrame.h"


//CMainFrameMFC::CMainFrameMFC()
//{
//	CFrameWnd::Create(NULL, Utils::convertToLPCWSTR("Windows Application Tester"));
//}
//
//
//CMainFrameMFC::~CMainFrameMFC()
//{
//}

void MainFrameDialog::init()
{
	//this->btn_add = (CButton*)GetDlgItem(ID_APP_Add);
	//this->grid = (CListCtrl*)GetDlgItem(IDC_LIST1);

	grid.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	grid.InsertColumn(0, _T("SSN"), LVCFMT_LEFT);
	grid.SetColumnWidth(0, 100);
	grid.InsertColumn(1, _T("Name"), LVCFMT_LEFT);
	grid.SetColumnWidth(1, 100);
	grid.InsertColumn(2, _T("Salary"), LVCFMT_LEFT);
	grid.SetColumnWidth(2, 100);
	grid.InsertColumn(3, _T("Address"), LVCFMT_LEFT);
	grid.SetColumnWidth(3, 100);
	grid.InsertColumn(4, _T("Date of Birth"), LVCFMT_LEFT);
	grid.SetColumnWidth(4, 100);
	grid.InsertColumn(5, _T("Phone"), LVCFMT_LEFT);
	grid.SetColumnWidth(5, 100);
}

void MainFrameDialog::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, grid);
	//btn_delete
}

BOOL MainFrameDialog::OnInitDialog()

{
	CDialog::OnInitDialog();
	init();
	parent->request_fill();



	return true;
}
MainFrameDialog::MainFrameDialog(CWnd * pParent) :CDialog(IDD_DIALOG_MAIN_FORM, pParent)
{
}
MainFrameDialog::~MainFrameDialog()
{
}
void MainFrame::request_fill()
{
	if (this->Employees_request != nullptr) {
		fill(this->Employees_request());
	}
}
MainFrame::MainFrame(CWnd* pParent) :IMainForm()
{

	this->dialog = new MainFrameDialog(pParent);
	this->dialog->parent = this;
	//Frame = new CMainFrameMFC();
	//CDialog::Create(NULL, Utils::convertToLPCWSTR("Windows Application Tester"));
	//CFrameWnd::LoadFrame(IDD_ABOUTBOX);

	//this->Dump(afxDump);
}

MainFrame::~MainFrame()
{
	//delete Frame;
}

void MainFrame::execute_add_employee()
{
}

void MainFrame::display()
{

	//m_pMainWnd = Frame;

	/*ShowWindow(SW_NORMAL);
	UpdateWindow();

	/DoModal();


	//this->Create(NULL, Utils::convertToLPCWSTR("siiii"));
	/*this->DoModal();

	if (this->request_add != nullptr) {
		this->request_add();

	}*/

	//this->
	/*BOOL res = this->dialog->Create(IDD_DIALOG_MAIN_FORM, NULL);
	this->dialog->ShowWindow(SW_NORMAL);*/
	this->dialog->DoModal();
}

void MainFrame::hide()
{
	this->dialog->ShowWindow(SW_HIDE);
}

void MainFrame::fill(std::vector<Employee> employees)
{
	int cant = employees.size();
	this->dialog->grid.DeleteAllItems();

	for (int i = 0; i < cant; i++)
	{
		Employee e = employees.at(i);
		char mybuff1[50];
		//sprintf(mybuff1, "%d", 28);

		AddData(this->dialog->grid, 0, 0, e.getSSN().c_str());
		AddData(this->dialog->grid, 0, 1, e.getName().c_str());
		/*sprintf_s(mybuff1, "%d", e.getSalary());
		AddData(this->dialog->grid, 0, 2, mybuff1);*/
		AddData(this->dialog->grid, 0, 2, Utils::floatTostring(e.getSalary()).c_str());
		AddData(this->dialog->grid, 0, 3, e.getAddress().c_str());
		AddData(this->dialog->grid, 0, 4, Utils::CStringtostring(e.getDateofbirth().Format(_T(" %m /%d/ %Y"))   ).c_str()      );
		AddData(this->dialog->grid, 0, 5, e.getPhone().c_str());

	}



}

#include "Injector.h"
void MainFrameDialog::add_click()
{
	IMainForm* ff = this->parent;
	if (ff->request_add != nullptr) {
		ff->request_add(true);
	}

	//Injector::
}

//#include <Windows.h>

void MainFrameDialog::delete_click()
{
	int cc = grid.GetSelectedCount();
	POSITION pos = grid.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE(_T("No items were selected!\n"));
	}
	else
	{
		while (pos)
		{
			int nItem = grid.GetNextSelectedItem(pos);
			CString s1 = grid.GetItemText(nItem, 0).Trim();

			std::string ssn = CT2A(s1.GetString());
			ssn = ssn.substr(0, 10);

			std::string post = "Are you sure you want to delete the employee with SSN: ";
			post = post + ssn;

			int msgboxID = MessageBox(Utils::convertToLPCWSTR(post.c_str()), _T("Warning"),
				MB_OKCANCEL | MB_OK);
			if (msgboxID == 1) {
				if (this->parent->request_delete != nullptr)
					this->parent->request_delete(ssn);
				TRACE(_T("Item %d was selected!\n"), nItem);
				// you could do your own processing on nItem here
			}
		}
		this->parent->request_fill();
	}
}

void MainFrameDialog::edit_click()

{


	int cc = grid.GetSelectedCount();
	POSITION pos = grid.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE(_T("No items were selected!\n"));
	}
	else
	{

		int nItem = grid.GetNextSelectedItem(pos);
		CString s1 = grid.GetItemText(nItem, 0).Trim();

		std::string ssn = CT2A(s1.GetString());
		ssn = ssn.substr(0, 10);
		int g = 0;
		IMainForm* ff = this->parent;
		if (ff->request_edit != nullptr) {
			ff->request_edit(ssn);
		}

	}


	
}

//CFrameWnd * MainFrame::getFrame()
//{
//	return this;
//}
BEGIN_MESSAGE_MAP(MainFrameDialog, CDialog)
	ON_COMMAND(ID_APP_Add, add_click)
	ON_COMMAND(ID_APP_DELETE, delete_click)
	ON_COMMAND(ID_APP_EDIT, edit_click)

END_MESSAGE_MAP()


//IMPLEMENT_DYNAMIC(MainFrame, CDialog)

//IMPLEMENT_DYNAMIC(MainFrame, CDialog)

//IMPLEMENT_DYNAMIC(MainFrame, CDialog)
//	ON_COMMAND(ID_APP_Add, add_click)
//	ON_COMMAND(ID_APP_DELETE, delete_click)
//	ON_COMMAND(ID_APP_EDIT, edit_click)
//
//END_IMPLEMENT_DYNAMIC()