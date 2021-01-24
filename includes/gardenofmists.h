#ifndef GARDENOFMISTS
# define GARDENOFMISTS

# include <git2.h>
# include <stdio.h>
# include <gtk/gtk.h>

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
	t_const_str	*arg0;
	char		*realloc_string;
	BOOL		dark_mode;
} t_master;

void critical_test(char bool_val, const char *msg);
void	handle_git_error(const int error_code);
UINT	path_len(const char *path);
void	proj_path(t_const_str *path_end, t_master *m);
void	proj_variable_path(t_const_str *folders, t_str *path_end, t_master *m);
void	init_str(const char *s, t_const_str *to_init);

#endif
