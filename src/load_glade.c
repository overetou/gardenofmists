#include "gardenofmists.h"

void load_builder(void)
{
	t_const_str	ui_path_end = {"variables" SLASH_S "visuals.ui", 20};

	proj_path(&ui_path_end);
	m.builder = gtk_builder_new_from_file(m.realloc_string);
	critical_test(m.builder != NULL,
		"visuals.ui could not be opened.");
}

void window_step(void)
{
	//gtk obj init
	m.w.gobj = gtk_builder_get_object(m.builder, "master_window");
	g_signal_connect(m.w.gobj, "delete-event", G_CALLBACK(handle_delete_event), NULL);
	//fullscreen management
	m.w.fullscreen = TRUE;
	gtk_window_fullscreen(GTK_WINDOW(win->gtk_obj));//Comment and put the 1 above to 0 to launch in windowed mode.
	//keys interception
	gtk_widget_add_events(GTK_WIDGET(win->gtk_obj), GDK_KEY_PRESS_MASK);//TODO: check if this line is useful
	m->win.handler_id = g_signal_connect(win->gtk_obj, "key_press_event", G_CALLBACK(on_window_keypress), m);
	//exit management funcs
	win->save_work_func = do_nothing;
	win->unsaved_work_remains_func = return_false;
	win->clean_before_quit_func = free_welcome_screen;
	//creds toggle
	win->can_show_creds = 1;
}