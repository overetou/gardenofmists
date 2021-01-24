#include "gardenofmists.h"

static void load_css(t_master *m)
{
	GtkCssProvider *style_provider;
	FILE *global_settings;
	char c;

	assemble_paths(m->arg0, m->path_len, "variables" SLASH_S "settings.bin", &(m->realloc_string));
	global_settings = fopen(m->realloc_string, "rb");
	if (global_settings)
	{
		if (fread(&c, 1, 1, global_settings))//Taking darmode toogle state from settings file, and loading the corresponding css file.
		{
			m->dark_mode = c;
			assemble_paths(m->arg0, m->path_len, (c ? "variables" SLASH_S "darkstyle.css" : "variables" SLASH_S "lightstyle.css"), &(m->realloc_string));
			style_provider = gtk_css_provider_new();
			gtk_css_provider_load_from_path(style_provider, m->realloc_string, NULL);
		}
		else
		{
			display_error("Could not read color theme mode from the settings file.");
			exit(0);
		}
		fclose(global_settings);
		gtk_style_context_add_provider_for_screen(
			gdk_screen_get_default(),
			GTK_STYLE_PROVIDER(style_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		//free(style_provider);
	}
	else
		printf("Could not open %s.\n", m->realloc_string);//TODO make it visual
}