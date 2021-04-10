#include "gardenofmists.h"

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
	if (event->state & GDK_CONTROL_MASK)
	{
		switch (event->keyval)
		{
			case GDK_KEY_q:
				quit_program();
			break;
			case GDK_KEY_f:
				toggle_fullscreen();
			break;
			case GDK_KEY_s:
				m.w.save_work_func();
			break;
			case GDK_KEY_h:
				show_shortcuts_and_creds(NULL, NULL);
			break;
		}
	}
	return FALSE;
}