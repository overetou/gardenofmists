#include "gardenofmists.h"

void	memcopy(char *dest, const char *src, const UINT len)
{
	UINT i = 0;

	while (i != len)
	{
		dest[i] = src[i];
		i++;
	}
}

t_const_str	*init_str(const char *s, t_const_str *to_init)
{
	to_init->s = s;
	to_init->len = strlen(s);
	return to_init;
}

t_const_str	*init_str_with_len(const char *s, UINT len, t_const_str *to_init)
{
	to_init->s = s;
	to_init->len = len;
	return to_init;
}

//Adds the given string to the path of the project.
void	proj_path(t_const_str *path_end, t_master *m)
{
	m->realloc_string = realloc(m->realloc_string, m->arg0.len + path_end->len + 1);
	memcopy(m->realloc_string, m->arg0.s, m->arg0.len);
	memcopy(m->realloc_string + m->arg0.len, path_end->s, path_end->len);
	m->realloc_string[m->arg0.len + path_end->len] = '\0';
}

void	proj_variable_path(t_const_str *folders, t_str *path_end, t_master *m)
{
	m->realloc_string = realloc(m->realloc_string, m->arg0.len + folders->len + path_end->len + 1);
	memcopy(m->realloc_string, m->arg0.s, m->arg0.len);
	memcopy(m->realloc_string + m->arg0.len, folders->s, folders->len);
	memcopy(m->realloc_string + m->arg0.len + folders->len, path_end->s, path_end->len);
	m->realloc_string[m->arg0.len + folders->len + path_end->len + 1] = '\0';
}

//Returns the length to last path separator character in the given string. (We know that the executable is named gardenofmists)
UINT	path_len(const char *path)
{
	UINT len = strlen(path);
	if (len >= 15)
		return len - 13;
	return 0;
}

//The result must be true else the given message is displayed and the program ends.
void critical_test(char bool_val, const char *msg)
{
	if (bool_val)
		return ;
	puts("\nError:");
	puts(msg);
	exit(0);
}
