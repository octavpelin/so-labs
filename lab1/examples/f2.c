#include <stdio.h>
#include "util.h"

void f2(void)
{
	printf("Current line %d in file %s\n",
		__LINE__, __FILE__);
}
