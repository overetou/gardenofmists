#include "gardenofmists.h"

void	init_master(t_master *m, char *path)
{
	m->realloc_string = NULL;
	init_str_with_len(path, strlen(path), &(m->proj_path));
}

static void  free_master(t_master *m)
{
	free(m->realloc_string);
	free(m->proj_path.s);
}

int main(int argc, char **argv)
{
	t_master m;

	handle_git_error(git_libgit2_init());
	critical_test(gtk_init_check(&argc, &argv),
	"Could not initialize the gtk library.");
	init_master(&m, get_proj_path());
	//display_notif("salut les gars", &m);
	free_master(&m);
	handle_git_error(git_libgit2_shutdown());
	return 0;
}
