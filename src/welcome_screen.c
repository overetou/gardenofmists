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

void	choose_dir_button_exec(GtkButton *button)
{
	GtkFileChooserNative	*native_chooser;

	native_chooser = gtk_file_chooser_native_new("Select Directory", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "Confirm", "Cancel");
	if (gtk_native_dialog_run(GTK_NATIVE_DIALOG(native_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		//TODO check the os and if windows, replace the / by \.
		m.proj_dir.s = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native_chooser));
		m.proj_dir.len = strlen(m.proj_dir.s);
		gtk_widget_set_tooltip_text(GTK_WIDGET(button), m.proj_dir.s);
	}
	g_object_unref(native_chooser);
}

//This function will read the project path from the global variable m.
void	open_new_project()
{
	t_const_str	text_sections_path	= {"text_sections", 13};
	t_const_str	meta_path 			= {"meta", 4};
	t_const_str	settings_path		= {"meta" SLASH_S "settings.bin", 17};
	t_const_str proj_list_path		= {"variables" SLASH_S "projects_list.txt", 27};
	FILE		*meta_settings;
	FILE		*global_projects_list;

	if (MKDIR(m.proj_dir.s)
		|| MKDIR(project_path(&text_sections_path))
		|| MKDIR(project_path(&meta_path))
		|| !(meta_settings = fopen(project_path(&settings_path), "wb")))
			display_notif("Failed to create new proj directory structure. All of the folders that could be created were left as is.");
		else
		{
			fwrite("\0", 1, 1, meta_settings);
			fclose(meta_settings);
			program_path(&proj_list_path);
			global_projects_list = fopen(m.realloc_string, "a");
			if (global_projects_list)
			{
				fwrite(m.proj_dir.s, 1, m.proj_dir.len, global_projects_list);
				fwrite("\n", 1, 1, global_projects_list);
				fclose(global_projects_list);
			}
			else
				display_notif("Failed to update the global project list for the welcome screen. You will have to open it manually next time.");
			//open_project(m, 1);TODO: enable this line.
		}
}

void	create_new_proj(GtkWidget *button)
{
	int		entry_len;

	(void)button;
	entry_len = strlen(gtk_entry_get_text(GTK_ENTRY(WELC_SCREEN.proj_name_entry)));
	if (m.proj_dir.len && entry_len)
	{
		//Resolving the project path. The + 2 stands for the 2 slashes, before and after the  final folder name.
		m.proj_dir.s = realloc(m.proj_dir.s, m.proj_dir.len + entry_len + 3);
		m.proj_dir.s[m.proj_dir.len] = SLASH_C;
		memcopy(m.proj_dir.s + m.proj_dir.len + 1, gtk_entry_get_text(GTK_ENTRY(WELC_SCREEN.proj_name_entry)), entry_len);
		m.proj_dir.len += 2 + entry_len;
		m.proj_dir.s[m.proj_dir.len - 1] = SLASH_C;
		m.proj_dir.s[m.proj_dir.len] = '\0';
		open_new_project();
	}
	else
		display_notif("Please fill all of the required fields before attempting to create a new project.\n(Note that the \"Directory\" button allows you to choose where your project will be stored.\nYou will be able to see the path you selected by hovering upon the \"Directory\" button.)");
}

void open_request(GtkButton *unused)
{
	GtkFileChooserNative *chooser;

	(void)unused;
	chooser = gtk_file_chooser_native_new("Select Project", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "Confirm", "Cancel");
	if (gtk_native_dialog_run(GTK_NATIVE_DIALOG(chooser)) == GTK_RESPONSE_ACCEPT)
	{
		m.proj_dir.s = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
		m.proj_dir.len = strlen(m.proj_dir.s);
		printf("Project path to open: %s\n", m.proj_dir.s);
		//open_project(m, 0);
	}
	g_object_unref(chooser);
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
	g_signal_connect(gtk_builder_get_object(m.builder, "choose_dir_button"), "clicked", G_CALLBACK(choose_dir_button_exec), NULL);
	g_signal_connect(gtk_builder_get_object(m.builder, "confirm_button"), "clicked", G_CALLBACK(create_new_proj), NULL);
	g_signal_connect(gtk_builder_get_object(m.builder, "open_button"), "clicked", G_CALLBACK(open_request), NULL);
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