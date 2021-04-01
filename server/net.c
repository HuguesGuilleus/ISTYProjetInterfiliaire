#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net.h"

// Event loop, open a UDP listener, parse each packet and send a
// response and to something according to the command.
int server(u_int16_t port) {
	struct sockaddr_in servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	// Connection
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}
	int rc = bind(sockfd, (const struct sockaddr *)&servaddr,
	              sizeof(servaddr));
	if (rc == -1) {
		perror("failed to bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	char buffer[250] = {};
	while (1) {
		// Read the request
		struct sockaddr remote_addr = {};
		socklen_t remote_len = sizeof(remote_addr);
		int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL,
		                 &remote_addr, &remote_len);

		n = main_action(buffer, n, 250);

		// Send a response
		int len = sendto(sockfd, buffer, n, 0, &remote_addr, remote_len);
		if (len == -1) {
			buffer[len] = '\0';
			fprintf(stderr, "Write '%s' fail: %m\n", buffer);
		}
	}

	close(sockfd);
	return 0;
}

// Take the buffer with a specific length and capacity, parse to a
// command then write the response and return its length.
int main_action(char *buffer, int len, int cap) {
	command cmd = {};

	if (parse_command(buffer, len, &cmd)) {
		memcpy(buffer, "err: parsed", 11);
		return 11;
	} else if (cmd.status != EXE) {
		memcpy(buffer, "err: expected exe command status", 32);
		return 32;
	}

	switch (cmd.kind) {
	case RESET:
		printf("todo RESET\n");
		break;
	case STOP:
		printf("todo STOP\n");
		break;
	case MOVE:
		printf("todo MOVE (%d, %d)\n", cmd.a, cmd.b);
		break;
	case AXE:
		printf("todo AXE (%d, %d)\n", cmd.a, cmd.b);
		break;
	case ERROR:
		break;
	}

	// Just change to make an aquittment
	memcpy(buffer, "ack:", 4);
	return len;
}
