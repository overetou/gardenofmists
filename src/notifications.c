#include "gardenofmists.h"

void	display_notif(const char *msg, t_master *m)
{
	char *s;
	//t_const_str logo_path;

	printf("arg0 = %s\n", m->arg0.s);
	//proj_path(init_str("assets/logo.svg", &logo_path), m);
	printf("logo path = %s\n", m->realloc_string);
	#ifdef _WIN32
	#else
	s = malloc(m->arg0.len + 66 + strlen(msg));
	sprintf(s, "notify-send -i `pwd`/assets/logo.svg 'Garden of Mists' '%s'", msg);
	printf("About to process: %s\n", s);
	#endif
	system(s);
	free(s);
}

void	display_error(const char *s, t_master *m)
{
	display_notif(s, m);
	exit(0);
}