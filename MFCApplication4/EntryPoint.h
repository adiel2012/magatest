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
		if (db.open("C:\\Users\\adiel\\Documents\\Adiel\\MagaAdiel\\MFCApp\\Debug\\goodsrv.cfg")) {

			IEmployeeRepositoryGOODs* miemployeerepo = ((IEmployeeRepositoryGOODs*)(Injector::getInstance()->getIEmployeeRepository()));
			miemployeerepo->setDb(&db);

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

