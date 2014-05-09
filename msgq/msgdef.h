#ifndef __MSGDEF_H
#define __MSGDEF_H

#define BUF_SIZE (128)

#define MSG_KEY 1111
#define MSG_TYPE 16
//#define MSG_CREATE_FLAG (0666 | IPC_CREAT)
#define MSG_CREATE_FLAG (IPC_CREAT)

struct msg_buf {
	long type;
	char text[BUF_SIZE];
};

#endif // __MSGDEF_H
