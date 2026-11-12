#include <signal.h>
#include <stddef.h>

volatile sig_atomic_t signal_interrupt = 0;

void handler(int signal)
{
	(void)signal;
	signal_interrupt = 1;
}

int init_signal(void)
{
	struct sigaction sig = {0};

	sig.sa_handler = &handler;
	sig.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (1);
	return (0);
}
