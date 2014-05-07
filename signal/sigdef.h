#ifndef __SIG_DEFINE_H
#define __SIG_DEFINE_H

#include <signal.h>

enum e_sig {
	SIG_UP = SIGUSR1,
	SIG_DOWN,
	SIG_LEFT,
	SIG_RIGHT,
	SIG_UNKNOWN
};


#endif // __SIG_DEFINE_H
