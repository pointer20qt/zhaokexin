#include "c.h"
#include <iostream>

c::c()
{
	std::cout << "������" << std::endl;
}

void run()
{
	std::cout << __FUNCTIONW__ << std::endl;
}
c::~c()
{
	std::cout << "������" << std::endl;
}