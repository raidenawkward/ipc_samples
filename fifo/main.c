#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE_PATH "test.fifo"
#define FIFO_PERMISSION (S_IRWXU | S_IRWXG)


int main()
{
	int fd;
	int pid;

	if (mkfifo(FIFO_FILE_PATH, FIFO_PERMISSION)) {
		perror("error make fifo file");
		return -1;
	}

	pid = fork();
	if (pid < 0) {
		perror("error folk");
		return -1;
	}

	if (pid) {
		fd = open(FIFO_FILE_PATH, O_WRONLY);

		if (fd <= 0) {
			perror("error open file");
		}

		write(fd, "abcdefg", 1024);

	} else {

		char buf[32];
		memset(buf, 0x00, sizeof(buf));

		// wait parent for writing data
		sleep(1);

		fd = open(FIFO_FILE_PATH, O_RDONLY);

		if (fd <= 0) {
			perror("error open file");
		}

		read(fd, buf, sizeof(buf));
		printf("read from fifo:\n");
		printf("%s\n", buf);
	}

	close(fd);

	return 0;
}
