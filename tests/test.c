#include "gardenofmists.h"

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

static BOOL test_strings_eq(const char *s1, const UINT s1len, const char *s2, const UINT s2len)
{
	UINT	i;

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

int main(void)
{
	return 0;
}