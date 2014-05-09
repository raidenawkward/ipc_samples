#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 1024
#define BACKLOG 9876
#define BUF_SIZE 1024

static char* remote_addr;

static void usage()
{
	printf("usage:\n");
	printf("b {remote ip}\n");
}

static display(const char* words)
{
	printf("%s\n", words);
}

static void process_send(const char* text)
{
	int sockfd;
	struct sockaddr_in addr_s;
	int ctrl_flag = 1;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("failed to create new socket");
		return;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &ctrl_flag, sizeof(ctrl_flag));

	memset(&addr_s, 0x00, sizeof (struct sockaddr_in));
	addr_s.sin_family = AF_INET;
	addr_s.sin_addr.s_addr = inet_addr(remote_addr);
	addr_s.sin_port = htons(PORT);

	if (connect(sockfd, (struct sockaddr*)(&addr_s), sizeof (struct sockaddr_in)) < 0) {
		printf("failed to connect to server %s\n", remote_addr);
		return;
	}

	write(sockfd, text, strlen(text));

	close(sockfd);
}

static void process_receive()
{
	int sockfd;
	struct sockaddr_in addr_s, addr_c;
	char buf[BUF_SIZE];
	int ctrl_flag = 1;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("failed to create new socket");
		return;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &ctrl_flag, sizeof(ctrl_flag));

	memset(&addr_s, 0x00, sizeof (struct sockaddr_in));
	addr_s.sin_family = AF_INET;
	addr_s.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_s.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr*)(&addr_s), sizeof(struct sockaddr_in)) < 0) {
		perror("error when bind");
		return;
	}

	if (listen(sockfd, BACKLOG) < 0) {
		perror("failed to listen");
		return;
	}

	while (1) {
		int sockaddr_len;
		int sock_client = accept(sockfd, (struct sockaddr*)(&addr_c), &sockaddr_len);
		int read_bytes;

		if (sock_client < 0) {
			continue;
		}

		memset(buf, 0x00, sizeof(buf));

		read_bytes = read(sock_client, buf, sizeof(buf));

		printf("received:\n");
		printf("%s\n", buf);
	}

	close(sockfd);
}

int main(int argc, char** argv)
{
	int pid;

	pid = fork();

	if (argc > 1) {
		remote_addr = (char*)malloc(strlen(argv[1]));
		strcpy(remote_addr, argv[1]);
	} else {
		usage();
		return 0;
	}

	if (pid < 0) {
		perror("error when create child process");
	}

	if (pid == 0) {
		process_receive();

	} else {
		char buf[BUF_SIZE];

		while (1) {
			memset(buf, 0x00, sizeof(buf));
			scanf("%s", buf);
			process_send(buf);
		}
	}

	free(remote_addr);

	return 0;
}
