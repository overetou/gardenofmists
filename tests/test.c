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
	printf("[%s]\n", new_section);
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
		printf("s1 len = %u, s2 len = %u.\n%s\n-----\n%s\n", s1len, s2len, s1, s2);
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
	test_uint_eq(path_len("/this/is/an/absolute/gardenoftests"), 21);
	test_uint_eq(path_len("yo/my/gardenoftests"), 6);
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
	init_str("/user/oto/gardenofmists/", &(m.arg0));
	init_str("variables/téra.bin", &e1);
	proj_path(&e1, &m);
	test_strings_eq(m.realloc_string, "/user/oto/gardenofmists/variables/téra.bin");
	init_str("./", &(m.arg0));
	proj_path(init_str("yo", &e1), &m);
	test_strings_eq(m.realloc_string, "./yo");
	#endif
	free(m.realloc_string);
	m.realloc_string = NULL;
}

void	test_proj_variable_path()
{
	change_test_section("proj_variable_path");
	t_master m;
	t_const_str e1;
	t_const_str e2;

	m.realloc_string = NULL;
	#ifdef _WIN32
	#else
	init_str("/user/oto/gardenofmists/", &(m.arg0));
	init_str("variables/carcasson/", &e1);
	init_str("parkéba", &e2);
	proj_variable_path(&e1, (t_str*)(&e2), &m);
	test_strings_eq(m.realloc_string, "/user/oto/gardenofmists/variables/carcasson/parkéba");
	#endif
	free(m.realloc_string);
	m.realloc_string = NULL;
}

void	passing_tests()
{
	test_proj_path();
	test_proj_variable_path();
}

int main(void)
{
	test_path_len();
	(void)test_exit;
	(void)test_strings_eq;
	(void)passing_tests;//passing_tests();
	return 0;
}