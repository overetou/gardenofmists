#include "gardenofmists.h"

void load_builder(void)
{
	t_const_str	ui_path_end = {"variables" SLASH_S "visuals.ui", 20};

	proj_path(&ui_path_end);
	m.builder = gtk_builder_new_from_file(m.realloc_string);
	critical_test(m.builder != NULL,
		"visuals.ui could not be opened.");
}