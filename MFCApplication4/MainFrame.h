#pragma once
#include "commons.h"
#include "IMainForm.h"
#include "resource.h"






class MainFrameDialog;
class MainFrame: public  IMainForm {

private:	
protected:	
	void request_fill();
public:
	MainFrameDialog* dialog = nullptr;
	friend class MainFrameDialog;
	MainFrame(CWnd* pParent = nullptr);
	~MainFrame();
	virtual void execute_add_employee();
	virtual void display();
	virtual void hide();
	void fill(std::vector<Employee> employees);
	static void AddData(CListCtrl &ctrl, int row, int col, const char *str);
};

class MainFrameDialog: public CDialog {
private:
	CButton btn_add;
	CButton btn_delete;
	CButton btn_edit;
	CListCtrl grid;
	void init();
	MainFrame* parent;

protected:
	//CMainFrameMFC *Frame = nullptr;
	virtual void DoDataExchange(CDataExchange* pDX);
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog();

public:
	friend class MainFrame;
	MainFrameDialog(CWnd* pParent);
	~MainFrameDialog();


	afx_msg void add_click();
	afx_msg void delete_click();
	afx_msg void edit_click();
	
	DECLARE_MESSAGE_MAP()

};
