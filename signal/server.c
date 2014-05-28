#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "sigdef.h"

struct pos {
	int x;
	int y;
};

void pos_up(struct pos* p)
{
	if (!p)
		return;
	--p->y;
}

void pos_down(struct pos* p)
{
	if (!p)
		return;

	++p->y;
}

void pos_left(struct pos* p)
{
	if (!p)
		return;

	--p->x;
}

void pos_right(struct pos* p)
{
	if (!p)
		return;

	++p->x;
}

void pos_report(const struct pos* p)
{
	if (!p)
		return;

	printf("current pos: (%d,%d)\n", p->x, p->y);
}

void pos_init(struct pos* p)
{
	if (!p)
		return;

	p->x = 0;
	p->y = 0;
}

static struct pos position;

void sighandler(int sig)
{
	switch (sig) {
	case SIG_UP:
		pos_up(&position);
		break;
	case SIG_DOWN:
		pos_down(&position);
		break;
	case SIG_LEFT:
		pos_left(&position);
		break;
	case SIG_RIGHT:
		pos_right(&position);
		break;
	case SIG_UNKNOWN:
	case SIGINT:
		printf("exiting\n");
		//exit(0);
		break;
	default:
		break;
	}

	pos_report(&position);
}

static void loop()
{
	while(1) {
		sleep(1);
	}
}

int main()
{
	pos_init(&position);

	struct sigaction act;
	act.sa_handler = sighandler;
	sigemptyset(&act.sa_mask);
	//act.sa_flags = 0;

	sigaction(SIG_UP, &act, NULL);
	sigaction(SIG_DOWN, &act, NULL);
	sigaction(SIG_LEFT, &act, NULL);
	sigaction(SIG_RIGHT, &act, NULL);
	sigaction(SIG_UNKNOWN, &act, NULL);

	printf("server launched on pid %d\n", (int)getpid());
	loop();

	return 0;
}
