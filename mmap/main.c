#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define DATA_SIZE 10

struct passed_data {
	int size;
	char data[DATA_SIZE];
};

static void passed_data_print(const struct passed_data* d)
{
	int i;

	if (!d)
		return;

	for (i = 0; i < d->size; ++i) {
		printf("%c", d->data[i]);
	}

	printf("\n");
}

int main(int argc, char** argv)
{
	int pid;
	struct passed_data *data, *pubdata;
	int i;

	data = (struct passed_data*)malloc(sizeof(struct passed_data));
	memset(data, 0x00, sizeof(struct passed_data));

	pubdata = mmap(data,
					sizeof(struct passed_data),
					PROT_READ | PROT_WRITE,
					MAP_SHARED | MAP_ANONYMOUS,
					-1,
					0);

	if (argc > 1) {
		pubdata->size = atoi(argv[1]);
	} else {
		pubdata->size = DATA_SIZE;
	}

	for (i = 0; i < pubdata->size; ++i) {
		pubdata->data[i] = 'a';
	}

	pid = fork();
	if (pid < 0) {
		perror("error when create child process");
	}

	if (pid == 0) {
		while (1) {
			int i;
			//printf("in child:\n");

			char ch = pubdata->data[0] + 1;
			if (ch > 'z')
				ch = 'a';

			for (i = 0; i < pubdata->size; ++i) {
					pubdata->data[i] = ch;
			}

			passed_data_print(pubdata);

			sleep(2);
		}
	} else {
		int i = 0;
		while (1) {
			int i;
			//printf("in parent:\n");

			char ch = pubdata->data[0] + 1;
			if (ch > 'z')
				ch = 'a';

			for (i = 0; i < pubdata->size; ++i) {
					pubdata->data[i] = ch;
			}

			passed_data_print(pubdata);

			sleep(1);
			++i;
		}

		munmap(pubdata, sizeof(struct passed_data));
	}

	free(data);

	return 0;
}
