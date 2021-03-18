#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>

// The type of the command.
enum command_kind {
	ERROR, // Used if parse_command fail.
	RESET,
	STOP,
	MOVE,
	AXE,
};

// Define the status of the command, for execution or acknowledgement.
enum status_command {
	EXE, // Execution
	ACK, // Acknowledgment
};

// One command.
typedef struct {
	enum status_command status;
	enum command_kind kind;
	int a;
	int b;
} command;

int parse_command(char *s, size_t len, command *cmd);
int test_parse_command();
int command_parse_int(char *s, size_t len, int *in);
int test_command_parse_int();
int is_digit(char c);
int test_is_digit();
int is_space(char c);
int test_is_space();

#endif
