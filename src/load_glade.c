#include "gardenofmists.h"

void load_builder(void)
{
	t_const_str	ui_path_end = {"variables" SLASH_S "visuals.ui", 20};

	proj_path(&ui_path_end);
	m.builder = gtk_builder_new_from_file(m.realloc_string);
	critical_test(m.builder != NULL,
		"visuals.ui could not be opened.");
}

void load_window(void)
{
	//gtk obj init
	m.w.gobj = gtk_builder_get_object(m.builder, "master_window");
	g_signal_connect(m.w.gobj, "delete-event", G_CALLBACK(handle_delete_event), NULL);
	//fullscreen management
	m.w.fullscreen = FALSE;
	//gtk_window_fullscreen(GTK_WINDOW(m.w.gobj));
	//keys interception
	gtk_widget_add_events(GTK_WIDGET(m.w.gobj), GDK_KEY_PRESS_MASK);//TODO: check if this line is useful
	m.w.handler_id = g_signal_connect(m.w.gobj, "key_press_event", G_CALLBACK(on_window_keypress), NULL);
	//exit management funcs
	m.w.save_work_func = do_nothing;
	m.w.unsaved_work_remains_func = return_false;
	m.w.clean_before_quit_func = free_welcome_screen;
	//creds toggle
	m.w.can_show_creds = TRUE;
}