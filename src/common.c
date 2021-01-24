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

void	init_str(const char *s, t_const_str *to_init)
{
	to_init->s = s;
	to_init->len = strlen(s);
}

void	init_str_with_len(const char *s, UINT len, t_const_str *to_init)
{
	to_init->s = s;
	to_init->len = len;
}

//Adds the given string to the path of the project.
void	proj_path(t_const_str *path_end, t_master *m)
{
	//printf("trying to assemble: %s and %s\n", m->arg0.s, path_end->s);
	m->realloc_string = realloc(m->realloc_string, m->arg0.len + path_end->len + 1);
	//printf("Realloc a size of: %u.\n", m->arg0.len + path_end->len + 1);
	memcopy(m->realloc_string, m->arg0.s, m->arg0.len);
	//printf("Copied %u chars from %s\n", m->arg0.len, m->arg0.s);
	memcopy(m->realloc_string + m->arg0.len, path_end->s, path_end->len);
	//printf("Copied %u chars from %s\n", path_end->len, path_end->s);
	m->realloc_string[m->arg0.len + path_end->len] = '\0';
	//printf("added a 0 at %u. The result is: %s\n", m->arg0.len + path_end->len, m->realloc_string);
}

void	proj_variable_path(t_const_str *folders, t_str *path_end, t_master *m)
{
	m->realloc_string = realloc(m->realloc_string, m->arg0.len + folders->len + path_end->len + 1);
	memcopy(m->realloc_string, m->arg0.s, m->arg0.len);
	memcopy(m->realloc_string + m->arg0.len, folders->s, folders->len);
	memcopy(m->realloc_string + m->arg0.len + folders->len, path_end->s, path_end->len);
	m->realloc_string[m->arg0.len + folders->len + path_end->len + 1] = '\0';
}

//Returns the length to last path separator character in the given string.
UINT	path_len(const char *path)
{
	UINT path_len;
	UINT arg_len;

	arg_len = strlen(path);
	path_len = arg_len;
	while (path_len && path[path_len] != SLASH_C)
		path_len--;
	return path_len + 1;
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
