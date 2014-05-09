#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msgdef.h"

static void news_received(const char* news)
{
	printf("news received:\n");
	printf("%s\n", news);
}

int main()
{
	int msgid;

	msgid = msgget((key_t)MSG_KEY, MSG_CREATE_FLAG);

	if (msgid < 0) {
		perror("failed when create msg");
		return -1;
	}

	while (1) {
		struct msg_buf recvbuf;
		size_t len = msgrcv(msgid, &recvbuf, BUF_SIZE, MSG_TYPE, MSG_NOERROR);
		if (len >= 0) {
			news_received(recvbuf.text);
		}
	}

	return 0;
}
