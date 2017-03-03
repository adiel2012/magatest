#pragma once
#include "Application.h"
#include "IEmployeeRepositoryGOODs.h"
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

		database db;
		task::initialize(task::normal_stack);
		if (db.open("unidb.cfg")) {

			IEmployeeRepositoryGOODs* midb = ((IEmployeeRepositoryGOODs*)(Injector::getInstance()->getIEmployeeRepository()));
			midb->setDb(&db);

			Application app;
			CDialog* dlg = app.run();
			gapp->m_pMainWnd = dlg;

			db.close();

			exit(0);

		}
		//INT_PTR  nResponse = dlg->DoModal();

	}

public:
	EntryPoint();
	~EntryPoint();
};



EntryPoint  gapp;
