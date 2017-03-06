#pragma once
#include "Application.h"
#include "EmployeeRepositoryGOODs.h"
#include "my_root.h"

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

			EmployeeRepositoryGOODs* miemployeerepo = ((EmployeeRepositoryGOODs*)(Injector::getInstance()->getIEmployeeRepository()));
			miemployeerepo->setDb(&db);

			Application app;
			
			CDialog* dlg = app.run();
			gapp->m_pMainWnd = dlg;

			db.close();
		}
		else
		{
			
			Utils::Message1("Can not connect to Server", "Error", nullptr);
		}


		exit(0);
		////INT_PTR  nResponse = dlg->DoModal();


		/*task::initialize(task::huge_stack);
		database db;

		if (db.open("C:\\Users\\adiel\\Documents\\Adiel\\MagaAdiel\\MFCApp\\Debug\\goodsrv.cfg")) {
			ref<my_root> root;
			db.get_root(root);
			root->initialize();
			db.close();
		}*/


		//Employee    e1("Juan", GetCurrentTime(), 1.0f, "mia addfdghh", "ffffff", "2222222222");
		//Employee e2("Adiel", GetCurrentTime(), 1.0f, "mia add", "dffsdsdf", "1111111111");
		//EmployeeGOODS egood1(e1);


	}

public:
	EntryPoint();
	~EntryPoint();
};



EntryPoint  gapp;

