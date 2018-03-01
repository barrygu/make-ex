#include <stdio.h>
#include "conv.h"
#include "print.h"

//static char modName[64] = {0};
int pr_num(int num)
{
	char buff[20];
	n2s(buff, num);
  	pr_str(buff);
	return 0;
}
