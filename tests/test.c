#include "../includes/gardenofmists.h"

UINT test_number;
const char *test_section;

t_master m;

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
	char *tmp = strnew("/user/oto/gardenofmists/");
	t_str e1;
	char *tmp2 = strnew("variables/téra.bin");

	m.realloc_string = NULL;
	#ifdef _WIN32
	#else
	init_str(tmp, &(m.program_path));
	init_str(tmp2, &e1);
	program_path((t_const_str*)(&e1));
	test_strings_eq(m.realloc_string, "/user/oto/gardenofmists/variables/téra.bin");
	init_str("./", &(m.program_path));
	program_path((t_const_str*)(init_str("yo", &e1)));
	test_strings_eq(m.realloc_string, "./yo");
	#endif
	free(m.realloc_string);
	m.realloc_string = NULL;
	free(tmp);
	free(tmp2);
}

void	test_proj_variable_path()
{
	change_test_section("proj_variable_path");
	t_const_str e1;
	t_const_str e2;

	m.realloc_string = NULL;
	#ifdef _WIN32
	#else
	init_str("/user/oto/gardenofmists/", &(m.program_path));
	init_str("variables/carcasson/", (t_str*)(&e1));
	init_str("parkéba", (t_str*)(&e2));
	proj_variable_path(&e1, (t_str*)(&e2));
	test_strings_eq(m.realloc_string, "/user/oto/gardenofmists/variables/carcasson/parkéba");
	#endif
	free(m.realloc_string);
	m.realloc_string = NULL;
}

void	passing_tests()
{
	test_proj_path();
	test_proj_variable_path();
	test_path_len();
}

void	test_get_proj_path()
{
	char	*candidate;

	change_test_section ("test_get_proj_path");
	candidate = get_proj_path();
	test_strings_eq(candidate, "/run/media/osc/DATA/Documents/code/unix/gardenofmists/");
	free(candidate);
}

int main(void)
{
	(void)test_exit;
	(void)passing_tests;passing_tests();
	test_get_proj_path();
	return 0;
}