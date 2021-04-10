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

//TODO: This system doest not take account of the actions of the desktop.
void toggle_fullscreen(void)
{
	if (m.w.fullscreen)
		gtk_window_unfullscreen(GTK_WINDOW(m.w.gobj));
	else
		gtk_window_fullscreen(GTK_WINDOW(m.w.gobj));
	m.w.fullscreen = !(m.w.fullscreen);
}

//TODO make that window independant, not a popup, so that the execution of the application is unaltered.
void show_shortcuts_and_creds(GtkButton *clicked, void *dummy)
{
	FILE			*license;
	char			license_text[34667 + 1];//This is the exact len of the license file (+ the NULL terminating byte).
	GtkAboutDialog	*popup;
	const gchar 	*authors[] = {"Oscar Veretout", NULL};
	GList			*kids;
	t_const_str		license_path = {"COPYING", 7};

	(void)clicked;
	(void)dummy;
	if (m.w.can_show_creds == TRUE)
	{
		m.w.can_show_creds = FALSE;
		program_path(&license_path);
		license = fopen(m.realloc_string, "r");
		if (license == NULL)
		{
			display_notif("Failed to open the license file.");
			return;
		}
		if (fread(license_text, 1, 34667, license) == 34667)
		{
			license_text[34667] = '\0';
			popup = GTK_ABOUT_DIALOG(gtk_about_dialog_new());
			gtk_about_dialog_set_authors(popup, authors);
			gtk_about_dialog_set_version(popup, "Version: 0.1");
			gtk_about_dialog_set_comments(popup, "Help\tCtrl+H\nQuit\tCtrl+Q\nFullscreen\tCtrl-F\n\nWhile editing:\nleft panel (controls)\tCtrl+l\nright panel (time traveler)\tCtrl+t\n\nAll dates are noted: day/month/year.");
			gtk_about_dialog_set_logo_icon_name(popup, NULL);
			gtk_about_dialog_set_license(popup, license_text);
			gtk_about_dialog_set_wrap_license(popup, TRUE);
			style_dialog(GTK_DIALOG(popup));
			int	indexes[] = {0, 1, 0};
			kids = dive_through_children(3, indexes, GTK_CONTAINER(popup));
			style_dialog_button(GTK_WIDGET(kids->data));
			style_dialog_button(GTK_WIDGET(kids->next->data));
			style_dialog_button(GTK_WIDGET(kids->next->next->data));
			g_list_free(kids);
			gtk_dialog_run(GTK_DIALOG(popup));
			gtk_widget_destroy(GTK_WIDGET(popup));
			m.w.can_show_creds = TRUE;
		}
		else
			display_error("Could not read the correct amount of bytes from the license file.");
		fclose(license);
	}
}

void	do_nothing(void)
{
}

BOOL	return_false(void)
{
	return FALSE;
}
