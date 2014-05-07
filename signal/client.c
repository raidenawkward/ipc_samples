#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

#include "sigdef.h"

static int str2sig(const char* str)
{
	if (strcmp(str, "up") == 0) {
		return SIG_UP;
	} else if (strcmp(str, "down") == 0) {
		return SIG_DOWN;
	} else if (strcmp(str, "left") == 0) {
		return SIG_LEFT;
	} else if (strcmp(str, "right") == 0) {
		return SIG_RIGHT;
	} else {
		return SIG_UNKNOWN;
		//return SIGINT;
	}
}

static void send_sig(int pid, int sig)
{
	printf("sending sig %d to %d\n", sig, pid);
	kill(pid, sig);
}

int main(int argc, char** argv)
{
	int pid = -1;
	int i;

	if (argc <= 1)
		return -1;

	for (i = 1; i < argc; ++i) {
		if (i == 1) {
			pid = atoi(argv[i]);
			continue;
		}

		int sig = str2sig(argv[i]);
		send_sig(pid, sig);
	}

	return 0;
}
