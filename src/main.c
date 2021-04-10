#include "gardenofmists.h"

t_master m;

void	init_master(char *path)
{
	m.realloc_string = NULL;
	init_str_with_len(path, strlen(path), &(m.proj_path));
	load_css();
	load_builder();
}

static void  free_master()
{
	free(m.realloc_string);
	free(m.proj_path.s);
	g_object_unref(m.builder);
}

int main(int argc, char **argv)
{
	handle_git_error(git_libgit2_init());
	critical_test(gtk_init_check(&argc, &argv),
	"Could not initialize the gtk library.");
	init_master(get_proj_path());
	free_master();
	handle_git_error(git_libgit2_shutdown());
	return 0;
}
