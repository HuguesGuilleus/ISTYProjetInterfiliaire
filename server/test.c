#include "parse.h"
#include <stdio.h>

typedef struct {
	char *name;
	int (*t)();
} tester;

int main() {
	tester tests[] = {
	    {"parse_command()", test_parse_command},
	    {"command_parse_int()", test_command_parse_int},
	    {"is_digit()", test_is_digit},
	    {"is_space()", test_is_space},
	};
	size_t testsLen = sizeof(tests) / sizeof(tester);

	for (size_t i = 0; i < testsLen; i++) {
		if (tests[i].t()) {
			printf("%s fail\n", tests[i].name);
		}
	}

	return 0;
}
