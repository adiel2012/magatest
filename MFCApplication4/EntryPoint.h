#pragma once
#include "Application.h"
class EntryPoint : public CWinApp
{
	BOOL InitInstance()
	{
		CWinApp::InitApplication();
		SetRegistryKey(_T("esta es mi llave"));
		main(this);
		return TRUE;
	}

	static void main(EntryPoint* gapp) {
		Application app;
		CDialog* dlg = app.run();
		gapp->m_pMainWnd = dlg;
		exit(0);
		//INT_PTR  nResponse = dlg->DoModal();

	}

public:
	EntryPoint();
	~EntryPoint();
};



EntryPoint  gapp;

