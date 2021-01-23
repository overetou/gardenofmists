#include "gardenofmists.h"

int main(void)
{
	t_master m;

	(void)m;
	handle_git_error(git_libgit2_init());
	handle_git_error(git_libgit2_shutdown());
	return 0;
}
