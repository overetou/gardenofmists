#include "gardenofmists.h"

//The result must be true else the given message is displayed and the program ends.
void critical_test(char bool_val, const char *msg)
{
	if (bool_val)
		return ;
	puts("\nError:");
	puts(msg);
	exit(0);
}
