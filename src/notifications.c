#include "gardenofmists.h"

//The result must be true else the given message is displayed and the program ends.
void critical_test(char bool_val, const char *msg)
{
	if (bool_val)
		return ;
	display_error(msg);
}

void	display_notif(const char *msg)
{
	char *s;
	t_const_str logo_path;

	program_path(init_const_str("assets/logo.svg", &logo_path));
	#ifdef _WIN32
	#else
	s = malloc(m.program_path.len + 66 + strlen(msg));
	sprintf(s, "notify-send -i %s 'Garden of Mists' '%s'", m.realloc_string, msg);
	#endif
	system(s);
	free(s);
}

void	display_error(const char *s)
{
	display_notif(s);
	exit(0);
}