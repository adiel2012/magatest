#pragma once

#include <iostream>
#include <vector>
#include <string>
//using namespace std;

class Entity {

};

enum FieldType { ft_integer = 0, ft_float = 1, ft_string };
class Field {
private:
	FieldType ft;
	int length=-1;
public:

	Field(FieldType ft, int length=-1) {
		this->ft = ft;
		this->length = length;
	}
};

class FieldDescription {
private:
	std::string description;
public:
	FieldDescription(std::string description) {
		this->description = description;
	}

};