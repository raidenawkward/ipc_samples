#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msgdef.h"


static void publish(int id, const char* news)
{
	struct msg_buf msgbuf;
	size_t len = strlen(news) + 1;

	msgbuf.type = MSG_TYPE;

	memset(msgbuf.text, 0x00, len);
	strcpy(msgbuf.text, news);

	//msgsnd(id, &msgbuf, len, MSG_NOERROR);
	msgsnd(id, &msgbuf, BUF_SIZE, MSG_NOERROR);
}

int main(int argc, char** argv)
{
	char buf[BUF_SIZE];
	int msgid = -1;

	msgid = msgget((key_t)MSG_KEY, MSG_CREATE_FLAG);

	if (msgid < 0) {
		perror("failed when create msg");
		return -1;
	}

	while (1) {
		memset(buf, 0x00, sizeof(buf));
		scanf("%s", buf);
		publish(msgid, buf);
	}

	return 0;
}
