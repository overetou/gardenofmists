#include "gardenofmists.h"

static void run_exit_dialog(void)
{
	/* GtkDialog *popup;
	GtkWidget *text;//This is a GtkLabel
	int choice;

	popup = GTK_DIALOG(gtk_dialog_new());
	gtk_window_set_default_size(GTK_WINDOW(popup), 150, 130);
	text = gtk_label_new("Save before you quit?");
	gtk_widget_set_vexpand(text, TRUE);
	gtk_widget_set_hexpand(text, TRUE);
	gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(popup)), text);
	style_dialog_button(gtk_dialog_add_button(popup, "Yes", 1));
	style_dialog_button(gtk_dialog_add_button(popup, "No", 0));
	style_dialog_button(gtk_dialog_add_button(popup, "Cancel", 2));
	style_dialog(popup);
	choice = gtk_dialog_run(popup);
	gtk_widget_destroy(GTK_WIDGET(popup));
	if (choice < 2)
	{
		if (choice)
			m->win.save_work_func(&(ED_SCREEN));
		m->win.clean_before_quit_func(m);
		gtk_widget_destroy(GTK_WIDGET(m->win.gtk_obj));
		gtk_main_quit();
	} */
}

void quit_program(void)
{
	if (m.w.unsaved_work_remains_func())
		run_exit_dialog();
	else
	{
		m.w.clean_before_quit_func();
		gtk_widget_destroy(GTK_WIDGET(m.w.gobj));
		gtk_main_quit();
	}
}

void	do_nothing(void)
{
}

BOOL	return_false(void)
{
	return FALSE;
}

//This func is called when the user ask for program end. It lets us call what we need to make sure that the work is saved, ect...
gboolean handle_delete_event(GtkWidget *widget, GdkEvent *event, void *dummy)
{
	(void)dummy;
	(void)widget;
	(void)event;
	quit_program();
	return TRUE;
}

char on_window_keypress(GtkWidget *win, GdkEventKey *event)
{
	(void)win;
	(void)event;
	/* if (event->state & GDK_CONTROL_MASK)
	{
		switch (event->keyval)
		{
			case GDK_KEY_q:
				quit_program(m);
			break;
			case GDK_KEY_f:
				toggle_fullscreen(m);
			break;
			case GDK_KEY_s:
				m.w.save_work_func(&(ED_SCREEN));
			break;
			case GDK_KEY_h:
				show_shortcuts_and_creds(NULL);
			break;
		}
	} */
	return FALSE;
}