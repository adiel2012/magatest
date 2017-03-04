#pragma once

#include<Windows.h>
#include <iostream>
//using namespace std;
#include<tchar.h>

#include <string>
#include <sstream>


#include <cctype>

class Utils{
public:
	static wchar_t * convertToLPCWSTR(const char * charArray) {
		wchar_t * wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

	static bool is_valid_char(char c, std::string::size_type pos)
	{
		const char dash = '-';

		if (pos == 3 || pos == 6) // positions where dash is expected
			return c == dash;

		else // positions where a digit is expected
			return std::isdigit(c);
	}

	static bool is_phone_number(const std::string& candidate)
	{
		const std::string::size_type EXPECTED_SIZE = 3 + 1 + 3 + 1 + 4;

		if (candidate.size() != EXPECTED_SIZE) return false;

		for (std::size_t i = 0; i < EXPECTED_SIZE; ++i) // for each position in the string
			if (!is_valid_char(candidate[i], i)) return false;

		return true;
	}

	static void Message1(std::string tittle, std::string content, CWnd* wind) {
		std::string post = "Are you sure you want to delete the employee with SSN: ";
		//post = post + ssn;

		int msgboxID = wind->MessageBox(Utils::convertToLPCWSTR(content.c_str()), Utils::convertToLPCWSTR(tittle.c_str()),
			 MB_OK);
	}

	static  std::string Floattostring(float t) {
		std::ostringstream os;
		os << t;
		return os.str();
	}

	static std::string floatTostring(float number) {
		std::ostringstream buff;
		buff << number;
		return buff.str();
	}

	static std::string wstringTostring(std::wstring ws) {
		std::string s(ws.begin(), ws.end());
		return s;
	}


	static bool isFloat(std::string myString) {
		std::istringstream iss(myString);
		float f;
		iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
							  // Check the entire string was consumed and if either failbit or badbit is set
		return iss.eof() && !iss.fail();
	}

	static std::string CStringtostring(CString& cad) {
	
		std::string ssn = CT2A(cad.GetString());
		ssn = ssn.substr(0, cad.GetLength());
		return ssn;
	}


};