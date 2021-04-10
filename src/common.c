#include "gardenofmists.h"
#include <libgen.h>

char	*strnew(const char *model)
{
	int l = strlen(model);
	char *new = malloc(l + 1);

	strncpy(new, model, l);
	new[l] = '\0';
	return new;
}

void	memcopy(char *dest, const char *src, const UINT len)
{
	UINT i = 0;

	while (i != len)
	{
		dest[i] = src[i];
		i++;
	}
}

t_str	*init_str(char *s, t_str *to_init)
{
	to_init->s = s;
	to_init->len = strlen(s);
	return to_init;
}


t_const_str	*init_const_str(const char *s, t_const_str *to_init)
{
	to_init->s = s;
	to_init->len = strlen(s);
	return to_init;
}

t_str	*init_str_with_len(char *s, UINT len, t_str *to_init)
{
	to_init->s = s;
	to_init->len = len;
	return to_init;
}

//Adds the given string to the path of the project.
void	proj_path(t_const_str *path_end)
{
	m.realloc_string = realloc(m.realloc_string, m.proj_path.len + path_end->len + 1);
	memcopy(m.realloc_string, m.proj_path.s, m.proj_path.len);
	memcopy(m.realloc_string + m.proj_path.len, path_end->s, path_end->len);
	m.realloc_string[m.proj_path.len + path_end->len] = '\0';
}

void	proj_variable_path(t_const_str *folders, t_str *path_end)
{
	m.realloc_string = realloc(m.realloc_string, (m.proj_path.len) + (folders->len) + (path_end->len) + 1);
	memcopy(m.realloc_string, m.proj_path.s, m.proj_path.len);
	memcopy(m.realloc_string + m.proj_path.len, folders->s, folders->len);
	memcopy(m.realloc_string + m.proj_path.len + folders->len, path_end->s, path_end->len);
	m.realloc_string[(m.proj_path.len) + (folders->len) + (path_end->len)] = '\0';
}

//Returns the length to last path separator character in the given string. (We know that the executable is named gardenofmists)
UINT	path_len(const char *path)
{
	UINT len = strlen(path);
	if (len >= 15)
		return len - 13;
	return 0;
}

char  *get_proj_path(void)
{
	char *path = malloc(PROJ_PATH_LEN);
	int dest_len = PROJ_PATH_LEN;
	ssize_t	actual_len;

	actual_len = readlink("/proc/self/exe", path, dest_len);
	critical_test(actual_len != -1 && actual_len <= PROJ_PATH_LEN - 1,
	"Could not read the location of the executable (must be < 80)");
	path[actual_len] = '\0';
	dirname(path);
	strcat(path, "/");
	return path;
}