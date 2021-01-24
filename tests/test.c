#include "../includes/gardenofmists.h"

UINT test_number;
const char *test_section;

static void	test_exit()
{
	puts("Critical test failed. Stopping now.\n");
	exit(0);
}

static void	change_test_section(const char *new_section)
{
	test_section = new_section;
	test_number = 1;
}

static void	test(const BOOL success)
{
	if (success)
		puts("Ok");
	else
		printf("In section [%s], test %u failed.\n", test_section, test_number);
	test_number++;
}

static BOOL test_strings_eq(const char *s1, const char *s2)
{
	UINT	i;
	UINT s1len = strlen(s1), s2len = strlen(s2);

	if (s1len != s2len)
	{
		test(FALSE);
		printf("s1 len = %u, s2 len = %u.\n", s1len, s2len);
		return TRUE;
	}
	i = 0;
	while (i != s1len)
	{
		if (s1[i] != s2[i])
		{
			test(FALSE);
			printf("On pos %u, s1 is '%c'(val=%d) and s2 is '%c'(val=%d).\n", i, s1[i], s1[i], s2[i], s2[i]);
			return TRUE;
		}
		i++;
	}
	test(TRUE);
	return FALSE;
}

static BOOL	test_uint_eq(const int u1, const int u2)
{
	if (u1 == u2)
	{
		test(TRUE);
		return FALSE;
	}
	test(FALSE);
	printf("Tested numbers did not match. %u != %u.\n", u1, u2);
	return(TRUE);
}

void	test_path_len()
{
	change_test_section("path_len");
	#ifdef _WIN32
	#else
	test_uint_eq(path_len("/this/is/an/absolute/path"), 21);
	test_uint_eq(path_len("yo/my/man"), 6);
	#endif
}

void	test_proj_path()
{
	change_test_section("proj_path");
	t_master m;
	t_const_str e1;

	m.realloc_string = NULL;
	#ifdef _WIN32
	#else
	init_str("/user/oto/gardenofmists/", m.arg0);
	init_str("variables/tera.bin", &e1);
	proj_path(&e1, &m);
	test_strings_eq(m.realloc_string, "/user/oto/gardenofmists/variables/tera.bin");
	#endif
	free(m.realloc_string);
}

void	passing_tests()
{
	test_path_len();
	test_proj_path();
}

int main(void)
{
	(void)test_exit;
	(void)test_strings_eq;
	(void)passing_tests;//passing_tests();
	return 0;
}