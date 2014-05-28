#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>


#define SHARE_KEY 1234
#define SHARED_DATA_SIZE 128
#define SHARE_PATH "test.shm"


struct shared_data {
	char data[SHARED_DATA_SIZE];
	int size;
};

static void loop() {
	do {
		sleep(1);
	} while (1);
}


int main(int argc, char** argv)
{
	int shmid;
	struct shared_data* pdata = NULL;
#if 0
	key_t key = ftok(SHARE_PATH, 0);
#else
	key_t key = (key_t)SHARE_KEY;
#endif

	if (key < 0) {
		perror("error with key");
	}

	shmid = shmget(key, sizeof(struct shared_data), IPC_CREAT);
	if (shmid < 0) {
		perror("error when shmget");
	}

	if (argc > 1) {
		if (strcmp(argv[1], "create") == 0) {
#if 0
			struct shared_data *sdata = (struct shared_data*)malloc(sizeof(struct shared_data));
			sdata->size = 0;
			memset(sdata->data, 0x00, sizeof(sdata->data));

			pdata = shmat(shmid, sdata, SHM_RND);
#endif
			pdata = shmat(shmid, NULL, 0);

			printf("shmat %d size %d\n", shmid, (int)sizeof(struct shared_data));

			if (pdata == NULL || pdata == (void*)-1) {
				perror("error whtn shmat");
				printf("error when shmat %d\n", shmid);
				return 1;
			}

			memset(pdata->data, 0x00, sizeof(pdata->data));

			loop();

		} else if (strcmp(argv[1], "put") == 0) {
			pdata = shmat(shmid, NULL, 0);

			if (pdata == NULL || pdata == (void*)-1) {
				perror("error whtn shmat");
				printf("error when shmat %d\n", shmid);
				return 1;
			}

			strcpy(pdata->data, argv[2]);

			shmdt(pdata);
		}

	} else {
		// read
		pdata = shmat(shmid, NULL, 0);
		if (pdata == NULL || pdata == (void*)-1) {
			perror("error whtn shmat");
			printf("error when shmat %d\n", shmid);
			return 1;
		}

		printf("shared content:\n");
		printf("%s\n", pdata->data);
	}

	return 0;
}
