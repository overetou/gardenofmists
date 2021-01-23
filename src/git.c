#include "gardenofmists.h"

void	handle_git_error(const int error_code)
{
	if (error_code < 0)
	{
		const git_error *e = git_error_last();
		printf("Error %d/%d: %s\n", error_code, e->klass, e->message);
		exit(error_code);
	}
}