#include "gardenofmists.h"

void set_sub_menu_tooltips(t_welc_screen *welcome_screen, gboolean sign)
{
	GList *kids;

	kids = gtk_container_get_children(GTK_CONTAINER(welcome_screen->new_proj_box_space));
	gtk_widget_set_has_tooltip(GTK_WIDGET(kids->data), sign);
	gtk_widget_set_has_tooltip(GTK_WIDGET(kids->next->data), sign);
	gtk_widget_set_has_tooltip(GTK_WIDGET(kids->next->next->data), sign);
	g_list_free(kids);
}

void	hide_new_proj_box(GObject *unused, t_welc_screen *welcome_screen)
{
	(void)unused;
	if (gtk_widget_get_opacity(GTK_WIDGET(welcome_screen->new_proj_box_space)))
	{
		gtk_widget_set_opacity(GTK_WIDGET(welcome_screen->new_proj_box_space), 0);
		gtk_widget_set_sensitive(GTK_WIDGET(welcome_screen->new_proj_box_space), FALSE);
		set_sub_menu_tooltips(welcome_screen, FALSE);
	}
}

void	display_new_proj_box(GObject *unused, t_welc_screen *welcome_screen)
{
	(void)unused;
	if (gtk_widget_get_opacity(GTK_WIDGET(welcome_screen->new_proj_box_space)))
		return ;
	gtk_widget_set_opacity(GTK_WIDGET(welcome_screen->new_proj_box_space), 1);
	gtk_widget_set_sensitive(GTK_WIDGET(welcome_screen->new_proj_box_space), TRUE);
	set_sub_menu_tooltips(welcome_screen, TRUE);
}

void	load_welcome_screen(void)
{
	//Get subreferences of welcome screen
	WELC_SCREEN.gobj = gtk_builder_get_object(m.builder, "welcome_screen");
	WELC_SCREEN.new_proj_box_space = gtk_builder_get_object(m.builder, "new_proj_box_space");
	WELC_SCREEN.projs_display_box = gtk_builder_get_object(m.builder, "projs_display_box");
	WELC_SCREEN.proj_name_entry = gtk_builder_get_object(m.builder, "proj_name_entry");
	//Connect buttons
	g_signal_connect(gtk_builder_get_object(m.builder, "new_button"), "clicked", G_CALLBACK(display_new_proj_box), &(WELC_SCREEN));
	g_signal_connect(gtk_builder_get_object(m.builder, "cancel_button"), "clicked", G_CALLBACK(hide_new_proj_box), &(WELC_SCREEN));
	/* g_signal_connect(gtk_builder_get_object(m.builder, "open_button"), "clicked", G_CALLBACK(open_request), NULL);
	g_signal_connect(gtk_builder_get_object(m.builder, "choose_dir_button"), "clicked", G_CALLBACK(choose_dir_button_exec), NULL);
	g_signal_connect(gtk_builder_get_object(m.builder, "confirm_button"), "clicked", G_CALLBACK(create_new_proj), NULL);*/
	g_signal_connect(gtk_builder_get_object(m.builder, "creds_button"),
	"clicked", G_CALLBACK(show_shortcuts_and_creds), NULL);
	//set_sub_menu_tooltips(&(WELC_SCREEN), FALSE);
	WELC_SCREEN.proj_string_list = NULL;
	//fill_proj_display_box(m);
}

void	free_welcome_screen(void)
{
	/* if (WELC_SCREEN.proj_list_string)
	{
		free(WELC_SCREEN.proj_list_string);
		free(WELC_SCREEN.projects_paths_ends);
	} */
}