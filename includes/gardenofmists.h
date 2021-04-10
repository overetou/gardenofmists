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

typedef struct s_master
{
	t_str		proj_path;
	char		*realloc_string;
	BOOL		dark_mode;
	GtkBuilder	*builder;
} t_master;

extern t_master m;

//common
char	*strnew(const char *model);
void	critical_test(char bool_val, const char *msg);
t_str	*init_str(char *s, t_str *to_init);
t_const_str	*init_const_str(const char *s, t_const_str *to_init);
t_str	*init_str_with_len(char *s, UINT len, t_str *to_init);
//git
void	handle_git_error(const int error_code);
UINT	path_len(const char *path);
void	proj_path(t_const_str *path_end);
void	proj_variable_path(t_const_str *folders, t_str *path_end);
char	*get_proj_path(void);
//css
void	load_css(void);
//ui file
void	load_builder(void);
//notifications
void	display_error(const char *s);
void	display_notif(const char *msg);
#endif
