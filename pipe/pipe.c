#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE (1024)


static void child_answers(const char* whatmomsays)
{
	printf("child answers: yes mom, i will %s\n", whatmomsays);
}

int main()
{
	int pipefd[2];
	int pid = -1;
	char buf[BUF_SIZE];

	if (pipe(pipefd) < 0) {
		perror("error when creating pipe");
		return -1;
	}

	pid = fork();
	if (pid < 0) {
		perror("error when creating child process");
		return -1;
	}

	if (pid == 0) {
		close(pipefd[1]);

		while (1) {
			memset(buf, 0x00, BUF_SIZE);
			if (read(pipefd[0], buf, sizeof(buf)) > 0) {
				child_answers(buf);
			}
		}

	} else {
		close(pipefd[0]);

		while (1) {
			memset(buf, 0x00, BUF_SIZE);
			scanf("%s", buf);
			write(pipefd[1], buf, strlen(buf));
		}
	}

	return 0;
}
