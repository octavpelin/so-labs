#include <stdio.h>

#define show_var(a) printf("Variable %s has value %d\n", #a, a)

int main(void)
{
	int teh_var = 42;
	show_var(teh_var);
	return 0;
}
