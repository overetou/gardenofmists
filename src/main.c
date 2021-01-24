#include "gardenofmists.h"

void	init_master(t_master *m, const char *path)
{
	m->realloc_string = NULL;
	init_str_with_len(path, path_len(path), &(m->arg0));
}

int main(int argc, char **argv)
{
	t_master m;

	handle_git_error(git_libgit2_init());
	critical_test(gtk_init_check(&argc, &argv), "Could not initialize the gtk library.");
	//We need to get put the installation folder in a string and read it.
	init_master(&m, argv[0]);
	display_notif("salut les gars", &m);
	free(m.realloc_string);
	handle_git_error(git_libgit2_shutdown());
	return 0;
}
