#include "parse.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFF_LEN 4096

typedef struct {
	char *name;
	int (*t)();
} tester;

int main() {
	// The list of the tests
	tester tests[] = {
	    {"parse_command()", test_parse_command},
	    {"command_parse_int()", test_command_parse_int},
	    {"is_digit()", test_is_digit},
	    {"is_space()", test_is_space},
	};
	size_t testsLen = sizeof(tests) / sizeof(tester);

	// Capture stdout to a pipe.
	int realstdout = dup(STDOUT_FILENO);
	int fppipe[2];
	if (pipe(fppipe) != 0) {
		fprintf(stderr, "Create a pipe fail: %m\n");
		return 1;
	};
	if (dup2(fppipe[1], STDOUT_FILENO) == -1) {
		fprintf(stderr, "dup2() stdout into a pipe fail: %m\n");
		return 1;
	}
	close(fppipe[1]);
	fcntl(fppipe[0], F_SETFL, O_NONBLOCK);

	// Run the test
	char buff[BUFF_LEN];
	for (size_t i = 0; i < testsLen; i++) {
		dprintf(realstdout, "\e[1;34m=== %s", tests[i].name);
		if (tests[i].t()) {
			dprintf(realstdout, "\e[31m FAIL\e[0m\n");
			// Print stdout.
			fflush(stdout);
			char nooutput = 1;
			size_t readed = 0;
			while ((readed = read(fppipe[0], buff, BUFF_LEN)) != -1) {
				write(realstdout, buff, readed);
				nooutput = 0;
			}
			if (nooutput) {
				dprintf(realstdout, "\e[3mYou can stdout with function like "
				                    "printf to debug\e[0m\n");
			}
		} else {
			dprintf(realstdout, "\e[32m OK\e[0m\n");
			// Remove buffered stdout.
			while (read(fppipe[0], buff, BUFF_LEN) != -1)
				;
		}
	}

	return 0;
}
