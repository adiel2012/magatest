#pragma once

#include "inc/goods.h"
#include "inc/dbscls.h"

USE_GOODS_NAMESPACE

class my_root : public object {
public:
	nat4 campo1;

    METACLASS_DECLARATIONS(my_root, object);

	my_root() : object(self_class)
	{
		campo1 = 9;
		//...
	}
	void initialize() const {
		if (is_abstract_root()) {
			ref<my_root> root = this;
			modify(root)->become(new my_root);
		}
	}
};


