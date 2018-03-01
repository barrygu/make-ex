//#include <stdio.h>
#include <iostream>
#include "print.h"

//static char modName[64] = {0};
int pr_str_ln(const char *str)
{
	std::cout << str << std::endl;
	return 0;
}
int pr_str(const char *str)
{
	std::cout << str;
	return 0;
}
