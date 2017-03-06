#pragma once
#include "Application.h"
#include "IEmployeeRepositoryGOODs.h"
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

			IEmployeeRepositoryGOODs* miemployeerepo = ((IEmployeeRepositoryGOODs*)(Injector::getInstance()->getIEmployeeRepository()));
			miemployeerepo->setDb(&db);

			Application app;

			/*std::vector<Employee> v = miemployeerepo->getAll();
			int cant = v.size();
			//miemployeerepo->add(Employee("Juan", GetCurrentTime(), 1.0f, "mia addfdghh", "ffffff", "1222222222"));
			//miemployeerepo->remove("1222222222");
			Employee e;
			//int res = miemployeerepo->getbySSN("2222222222", e);
			int res = miemployeerepo->update("4444444444", Employee("CACA3", GetCurrentTime(), 1.0f, "mia addfdghh", "ffffff", "5555555555"));
			v = miemployeerepo->getAll();
			cant = v.size();*/


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

