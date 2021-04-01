#include "parse.h"
#include <string.h>

// Parse the command into cmd. Return 1 on error.
int parse_command(char *s, size_t len, command *cmd) {
	// Init cmd to zero value.
	*cmd = (command){};

	// Get status
	if (!strncmp(s, "exe:", 4)) {
		cmd->status = EXE;
	} else if (!strncmp(s, "ack:", 4)) {
		cmd->status = ACK;
	} else {
		return 1;
	}
	s += 4;

	// Length of readed bytes.
	size_t readed = 0;

	// Get the kind of command
	if (len > 6 && strncmp(s, "reset ", 6) == 0) {
		readed += 6;
		cmd->kind = RESET;
	} else if (len > 5 && strncmp(s, "stop ", 5) == 0) {
		readed += 5;
		cmd->kind = STOP;
	} else if (len > 5 && strncmp(s, "move ", 5) == 0) {
		readed += 5;
		cmd->kind = MOVE;
	} else if (len > 4 && strncmp(s, "axe ", 4) == 0) {
		readed += 4;
		cmd->kind = AXE;
	} else {
		return 1;
	}

	// Get the number arguments.
	readed += command_parse_int(s + readed, len - readed, &cmd->a);
	command_parse_int(s + readed, len - readed, &cmd->b);

	return 0;
}
int test_parse_command() {
	command cmd = {};
	return parse_command("exe:reset 42 93", 15, &cmd) != 0 ||
	       cmd.status != EXE || cmd.kind != RESET || cmd.a != 42 ||
	       cmd.b != 93;
}

// Parse a decimal integer and save it in in, from the string s of
// size s. Return the number of readed digits.
//
// Supported syntax: [ \t\n\r]*[+-]?\d*
int command_parse_int(char *s, size_t len, int *in) {
	size_t i;
	char isnegative = 0;
	*in = 0;
	for (i = 0; i < len && is_space(s[i]); i++)
		;
	if (i < len && s[i] == '-') {
		isnegative = 1;
		i++;
	} else if (i < len && s[i] == '+') {
		i++;
	}
	for (; i < len && is_digit(s[i]); i++) {
		*in = *in * 10 + s[i] - '0';
	}
	if (isnegative) {
		*in *= -1;
	}
	return i;
}
int test_command_parse_int() {
	int i1, i2, i3, i4, i5;
	return command_parse_int("36", 2, &i1) != 2 || i1 != 36 ||
	       command_parse_int("42 ", 3, &i2) != 2 || i2 != 42 ||
	       command_parse_int(" 95", 3, &i3) != 3 || i3 != 95 ||
	       command_parse_int("-10", 3, &i4) != 3 || i4 != -10 ||
	       command_parse_int("+10", 3, &i5) != 3 || i5 != +10;
}

// Return 0 if the file is not a digit.
int is_digit(char c) { return '0' <= c && c <= '9'; }
int test_is_digit() {
	return is_digit('0') != 1 || is_digit('5') != 1 ||
	       is_digit('9') != 1 || is_digit('A') != 0 ||
	       is_digit(' ') != 0 || is_digit('a') != 0;
}

// Return 0 if the file is a space: regular space return line,
// carrige return and tabulation.
int is_space(char c) {
	switch (c) {
	case ' ':
	case '\n':
	case '\t':
	case '\r':
		return 1;
	default:
		return 0;
	}
}
int test_is_space() {
	return is_space(' ') != 1 || is_space('\n') != 1 ||
	       is_space('\t') != 1 || is_space('\r') != 1 ||
	       is_space('0') != 0 || is_space('$') != 0 ||
	       is_space('a') != 0;
}
