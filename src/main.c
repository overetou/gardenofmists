#include "gardenofmists.h"

void	init_master(t_master *m, const char *path)
{
	m->realloc_string = NULL;
	m->arg0->len = path_len(path);
	m->arg0->s = path;
}

int main(int argc, char **argv)
{
	t_master m;

	(void)m;
	handle_git_error(git_libgit2_init());
	critical_test(gtk_init_check(&argc, &argv), "Could not initialize the gtk library.");
	init_master(&m, argv[0]);
	handle_git_error(git_libgit2_shutdown());
	return 0;
}
