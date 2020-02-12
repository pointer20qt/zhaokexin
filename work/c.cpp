#include "c.h"
#include <iostream>

c::c()
{
	std::cout << "构造了" << std::endl;
}

void run()
{
	std::cout << __FUNCTIONW__ << std::endl;
}
c::~c()
{
	std::cout << "析构了" << std::endl;
}