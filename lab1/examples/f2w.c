#include <stdio.h>
#include "funs.h"

void f2(void)
{
	printf("Current line %d in file %s\n",
		__LINE__, __FILE__);
}