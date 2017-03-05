#include "stdafx.h"
#include "my_root.h"


field_descriptor& my_root::describe_components()
{
	return FIELD(campo1);
}

REGISTER(my_root, // class name 
	object, // base class
	optimistic_repeatable_read_scheme // metaobject
	);
