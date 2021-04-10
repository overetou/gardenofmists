#include "gardenofmists.h"

t_master m;

void	init_master(char *path)
{
	m.realloc_string = NULL;
	m.proj_dir.len = 0;
	init_str_with_len(path, strlen(path), &(m.program_path));
	load_css();
	load_builder();
	load_window();
	load_welcome_screen();
	gtk_container_add(GTK_CONTAINER(m.w.gobj), GTK_WIDGET(WELC_SCREEN.gobj));
}

static void  free_master()
{
	free(m.realloc_string);
	free(m.program_path.s);
	g_object_unref(m.builder);
	gtk_widget_destroy(GTK_WIDGET(m.w.gobj));
}

int main(int argc, char **argv)
{
	//libraries activation
	handle_git_error(git_libgit2_init());
	critical_test(gtk_init_check(&argc, &argv),
	"Could not initialize the gtk library.");
	//setting up the interface.
	init_master(get_proj_path());
	//actual display operation
	gtk_widget_show_all(GTK_WIDGET(m.w.gobj));
	//main loop
	gtk_main();
	//desinitialisation
	free_master();
	handle_git_error(git_libgit2_shutdown());
	return 0;
}
