#include "stdafx.h"
#include "EmployeeController.h"




EmployeeController::EmployeeController()
{

	repo = Injector::getInstance()->getIEmployeeRepository();
	mainform = Injector::getInstance()->getMAINForm();
	add_form = Injector::getInstance()->getIEmployeeADDForm();


	mainform->setEmployee_add_request(EmployeeController::employee_add_requested);
	mainform->setEmployee_delete_request(EmployeeController::employee_delete_requested);
	mainform->setEmployee_edit_request(EmployeeController::employee_edit_requested);
	mainform->setEmployee_request(EmployeeController::employees_requested);

	add_form->setEmployee_add_request(EmployeeController::do_add_persistence);
	
}


EmployeeController::~EmployeeController()
{

}

void EmployeeController::show_add_form()
{
	add_form->display();
}

void EmployeeController::run()
{	
	mainform->display();
}

int EmployeeController::employee_add_requested(bool add)
{
	EmployeeController* employee_controller = Injector::getInstance()->getIEmployeeController();
	employee_controller->add_form->clean();
	employee_controller->add_form->fill(Employee(), "");
	//employee_controller->add_form->initialize_labels("Adding Employees", "Add");
	employee_controller->show_add_form();
	return 0;
}

int EmployeeController::employee_delete_requested(std::string id)
{	
	return Injector::getInstance()->getIEmployeeController()->repo->remove(id);
}


int EmployeeController::employee_edit_requested(std::string id)
{
	EmployeeController* employee_controller = Injector::getInstance()->getIEmployeeController();
	Employee empt;
	int res = employee_controller->repo->getbySSN(id,empt);
	if (res != 0)
		return res;
	employee_controller->add_form->fill(empt,id);
	//employee_controller->add_form->initialize_labels("Editing Employee", "Edit");
	employee_controller->show_add_form();

	return 0;
}


std::vector<Employee> EmployeeController::employees_requested()
{
	return  Injector::getInstance()->getIEmployeeController()->repo->getAll(); 
}


int EmployeeController::validate(Employee e)
{
	int lenSSN = e.getSSN().length();
	if (lenSSN != 10)
		return 5;
	int lenName = e.getName().length();
	if (lenName == 0)
		return 6;
	std::string phone = e.getPhone();
	int lenphone = e.getPhone().length();
	if (lenphone != 10)
		return 7;

	if (!Utils::is_phone_number(e.getPhone()))
		return 8;

	if (!Utils::is_chain_of_digits(e.getSSN()))
		return 9;
	
	

	return 0;
}


int EmployeeController::do_add_persistence(Employee employee, std::string ssn_old)
{
	Employee emp1;
	Employee emp2;
	int res1 = Injector::getInstance()->getIEmployeeController()->repo->getbySSN(ssn_old,emp1);
	int res2 = Injector::getInstance()->getIEmployeeController()->repo->getbySSN(employee.getSSN(),emp2);
	
	int valid = EmployeeController::validate(employee);
	
	int res = valid;
	if (res == 0){
		if (ssn_old == "") {
			//add
			if (res2 == 0) {
				res = 4;
			}
			else
				res = Injector::getInstance()->getIEmployeeController()->repo->add(employee);
			if (res == 0) {
				Utils::Message1("Employee registered correctly", "Correct", Injector::getInstance()->getMAINForm()->dialog);
			}
			else {
				Utils::Message1("Employee NOT registered correctly, REVIEW THE DATA ENTRY", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);
			}
		}
		else {
			// edit
			if (res1 != 0) {
				res = 2;
			}
			else
			if (ssn_old != employee.getSSN() && res2 == 0) {
				res = 3;
			}
			else
				res = Injector::getInstance()->getIEmployeeController()->repo->update(ssn_old, employee);
			Injector::getInstance()->getIEmployeeController()->add_form->hide();
			if (res == 0) {
				Utils::Message1("Employee edited correctly", "Correct", Injector::getInstance()->getMAINForm()->dialog);
			}
			else {
				Utils::Message1("Employee NOT edited correctly, REVIEW THE DATA ENTRY", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);
			}
		}
	}
	if (res == 0) {
		std::vector<Employee> list = Injector::getInstance()->getIEmployeeController()->repo->getAll();
		Injector::getInstance()->getIEmployeeController()->mainform->fill(list);
		Injector::getInstance()->getIEmployeeController()->add_form->clean();

	}

	switch (res) 
	{
	case 1: { Utils::Message1("Employee NOT edited correctly, REVIEW THE DATA ENTRY", "Incorrect", Injector::getInstance()->getMAINForm()->dialog); break; }
	case 2: { Utils::Message1("Employee do NOT EXIST", "Incorrect", Injector::getInstance()->getMAINForm()->dialog); break; }
	case 3: { Utils::Message1("YOUR TRYING TO REGISTER AN EXISTING SSN, REVIEW THE DATA ENTRY", "Incorrect", Injector::getInstance()->getMAINForm()->dialog); break; }
	case 4: { Utils::Message1("Employee NOT added correctly, REVIEW THE SSN", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);  break; }
	case 5: { Utils::Message1("Error in SSN Length", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);  break; }
	case 6: { Utils::Message1("Name required", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);  break; }
	case 7: { Utils::Message1("Review Phone Length", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);  break; }
	case 8: { Utils::Message1("Not a Valid Phone Number", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);  break; }
	case 9: { Utils::Message1("SSN must be a chain of digits", "Incorrect", Injector::getInstance()->getMAINForm()->dialog);  break; }
	default:
		break;
	}
	return res;
}


