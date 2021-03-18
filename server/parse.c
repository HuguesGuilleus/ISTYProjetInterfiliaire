#include "parse.h"
#include <string.h>

// Parse the command into cmd. Return 1 on error.
int parse_command(char *s, size_t len, command *cmd) {
	*cmd = (command){};

	if(strncmp(s, "exe:", 4)){
		cmd->status = EXE;
	} else if(s, "ack:", 4) {
		cmd->status = ACK;
	} else {
		return 1;
	}

	size_t i = 4 ;
	
	if(strncmp(s+4, "reset ", 6) == 0) {
		i += 6;
		cmd->kind = RESET ;
	} else if(strncmp(s+4, "stop ", 5) == 0) {
		i += 5;
		cmd->kind =STOP;
	} else if(strncmp(s+4, "move ", 5) == 0) {
		i += 5;
		cmd->kind = MOVE;
	} else if(strncmp(s+4, "axe ", 4) == 0 ){
		i += 4;
		cmd->kind = AXE;
	} else {
		return 1;
	}
	
	return 0;
}
int test_parse_command(){
	command cmd = {};
	return parse_command("exe:reset 42 93", 15, &cmd) != 0 || 
		cmd.status != ACK ||
		cmd.kind != RESET ||
//		cmd.a != 42 ||
//		cmd.b != 93 ;
		0;
}

// Parse a decimal integer and save it in in, from the string s of size s.
// Return the number of readed digits.
int command_parse_int(char *s, size_t len, int *in) {
	size_t i;
	*in = 0;
	for(i = 0; i < len && is_digit(s[i]); i++){
		*in = *in * 10 + s[i]-'0'; 
	}
	return i;
}
int test_command_parse_int() {
	int i1, i2;
	return command_parse_int("36", 2, &i1) != 2 && i1 != 36 && 
		command_parse_int("42 ", 5, &i2) != 42 && i2 != 42;
}

// Return 0 if the file is not a digit.
int is_digit(char c) {
	return '0' <= c && c <= '9';
}
int test_is_digit() {
	return is_digit('0') != 1 ||
		 is_digit('5') != 1 ||
		 is_digit('9') != 1 ||
		 is_digit('A') != 0 ||
		 is_digit(' ') != 0 ||
		 is_digit('a') != 0; 
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
	return is_space(' ') != 1 ||
		 is_space('\n') != 1 ||
		 is_space('\t') != 1 ||
		 is_space('\r') != 1 ||
		 is_space('0') != 0 ||
		 is_space('$') != 0 ||
		 is_space('a') != 0;
}
