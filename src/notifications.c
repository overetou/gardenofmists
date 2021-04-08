#include "gardenofmists.h"

void	display_notif(const char *msg)
{
	char *s;
	t_const_str logo_path;

	proj_path(init_const_str("assets/logo.svg", &logo_path));
	#ifdef _WIN32
	#else
	s = malloc(m.proj_path.len + 66 + strlen(msg));
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