#ifndef GARDENOFMISTS
# define GARDENOFMISTS

# include <git2.h>
# include <gtk/gtk.h>
# include <fcntl.h>
# include <unistd.h>

# ifdef _WIN32
#  define MKDIR(x) mkdir(x)
#  define SLASH_C '\\'
#  define SLASH_S "\\"
# else
#  define MKDIR(x) mkdir(x, 0700)
#  define SLASH_C '/'
#  define SLASH_S "/"
# endif

# define UINT unsigned int
# define BOOL char

# define ED_SCREEN m.current_screen.editor
# define WELC_SCREEN m.current_screen.welcome
# define PROJ_PATH_LEN 80

typedef struct	s_str
{
	char	*s;
	UINT	len;
}				t_str;

typedef struct	s_const_str
{
	const char	*s;
	UINT		len;
}				t_const_str;

typedef struct	s_welc_screen
{
	GObject		*gobj;
	GObject		*new_proj_box_space;
	GObject		*projs_display_box;
	GObject		*proj_name_entry;
	char		**proj_string_list;
}				t_welc_screen;

typedef struct	s_ed_screen
{
}				t_ed_screen;

typedef union	u_screen
{
	t_ed_screen		editor;
	t_welc_screen	welcome;
}				t_screen;

typedef struct	s_win
{
	GObject		*gobj;
	int			handler_id;
	void		(*save_work_func)(void);
	char		(*unsaved_work_remains_func)(void);
	void		(*clean_before_quit_func)(void);
	BOOL		fullscreen;
	BOOL		can_show_creds;
}				t_win;

typedef struct	s_master
{
	t_str		proj_path;
	char		*realloc_string;
	BOOL		dark_mode;
	GtkBuilder	*builder;
	t_win		w;
	t_screen	current_screen;
}				t_master;

extern t_master m;

//common
char	*strnew(const char *model);
void	critical_test(char bool_val, const char *msg);
t_str	*init_str(char *s, t_str *to_init);
t_const_str	*init_const_str(const char *s, t_const_str *to_init);
t_str	*init_str_with_len(char *s, UINT len, t_str *to_init);
GList	*dive_through_children(int dive_nb, int *indexes_tab, GtkContainer *parent);
//generic actions
void	toggle_fullscreen(void);
void	quit_program(void);
void	show_shortcuts_and_creds(GtkButton *clicked, void *dummy);
//git
void	handle_git_error(const int error_code);
UINT	path_len(const char *path);
void	proj_path(t_const_str *path_end);
void	proj_variable_path(t_const_str *folders, t_str *path_end);
char	*get_proj_path(void);
//css
void	style_dialog(GtkDialog *popup);
void	style_dialog_button(GtkWidget *button);
void	load_css(void);
//ui file
void	load_builder(void);
void	load_window(void);
//notifications
void	display_error(const char *s);
void	display_notif(const char *msg);
//events
gboolean	handle_delete_event(GtkWidget *widget, GdkEvent *event, void *dummy);
char		on_window_keypress(GtkWidget *win, GdkEventKey *event);
void		do_nothing(void);
BOOL		return_false(void);
//welcome screen
void	free_welcome_screen(void);
void	load_welcome_screen(void);
#endif
