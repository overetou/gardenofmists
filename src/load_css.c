#include "gardenofmists.h"

void	load_css(void)
{
	GtkCssProvider	*style_provider;
	FILE			*global_settings;
	t_const_str		path_end;
	char			*s;

	proj_path(init_const_str("variables" SLASH_S "settings.bin", &path_end));
	global_settings = fopen(m.realloc_string, "rb");
	if (global_settings)
	{
		if (fread(&(m.dark_mode), 1, 1, global_settings))//Taking darkmode toogle state from settings file, and loading the corresponding css file.
		{
			proj_path(init_const_str((m.dark_mode ? "variables" SLASH_S "darkstyle.css" : "variables" SLASH_S "lightstyle.css"), &path_end));
			style_provider = gtk_css_provider_new();
			gtk_css_provider_load_from_path(style_provider, m.realloc_string, NULL);
		}
		else
		{
			display_error("Could not read color theme mode from the settings file.");
			exit(0);
		}
		fclose(global_settings);
		gtk_style_context_add_provider_for_screen
		(
			gdk_screen_get_default(),
			GTK_STYLE_PROVIDER(style_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
		);
		g_object_unref(style_provider);
	}
	else
	{
		s = malloc(17 + strlen(m.realloc_string));
		sprintf(s, "Could not open %s.", m.realloc_string);
		display_error(s);
	}
}

void	set_norm_for_sol_back(GtkWidget *w)
{
	GtkStyleContext *style;

	style = gtk_widget_get_style_context(w);
	gtk_style_context_add_class(style, "solid_background");
	gtk_style_context_add_class(style, "normal_foreground");
}

void	style_dialog(GtkDialog *popup)
{
	gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_CENTER_ALWAYS);
	set_norm_for_sol_back(GTK_WIDGET(popup));
}

void	style_dialog_button(GtkWidget *button)
{
	GtkStyleContext *context;

	context = gtk_widget_get_style_context(button);
	gtk_style_context_add_class(context, "popover_background");
	gtk_style_context_add_class(context, "no_border");
	gtk_style_context_add_class(context, "band_button");
}