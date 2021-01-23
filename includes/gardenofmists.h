#ifndef GARDENOFMISTS
# define GARDENOFMISTS

# include <git2.h>
# include <stdio.h>

typedef struct s_master
{
} t_master;

void critical_test(char bool_val, const char *msg);
void	handle_git_error(const int error_code);

#endif
