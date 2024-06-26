#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jjy.h"

int test(time_t time, char *expect)
{
	struct tm *tm = localtime(&time);
	char actual[61];
	int i;
	for (i = 0; i < 60; i++) {
		t_jjy_bit bit = get_jjy_bit(tm, i);
		actual[i] = '0' + bit;
	}
	actual[i] = '\0';
	return strcmp(expect, actual) == 0;
}

int main(void)
{
	// Set time zone to JST
	// (https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html)
	setenv("TZ", "JST-9", 1);
	tzset();

	int result = 1;

	result &= test(         0, "200000000200000100120000000002000100000200111000021000000002"); // 1970-01-01T00:00:00Z
	result &= test( 946684800, "200000000200000100120000000002000100000200000000021100000002"); // 2000-01-01T00:00:00Z
	result &= test( 946684860, "200000001200000100120000000002000100010200000000021100000002"); // 2000-01-01T00:01:00Z
	result &= test( 946688400, "200000000200010000020000000002000100100200000000021100000002"); // 2000-01-01T01:00:00Z
	result &= test( 946688460, "200000001200010000020000000002000100110200000000021100000002"); // 2000-01-01T01:01:00Z
	result &= test( 978307140, "210101001200000100020000000002000100100200000000120010000002"); // 2000-12-31T23:59:00Z
	result &= test(2147483640, "200100100200010001020000000012100100000200011100020100000002"); // 2038-01-19T03:14:00Z
	
	printf("%s\n", result ? "OK" : "ERROR");
	
	return !result;
}
