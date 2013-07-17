#include "libcustomperf.h"
#include <unistd.h>
#include <stdbool.h>

int perf_send_command(int cmd)
{
	bool result = 1;
	if (write(TARGET_SOCK_FD, &cmd, sizeof(cmd)) == -1)
		return -1;
	if (read(TARGET_SOCK_FD, &result, sizeof(result)) == -1)
		return -1;

	return 0;
}

int perf_init_communication()
{
	int result;

	result = perf_send_command(LIBCUSTOMPERF_INITIALIZE);
	return result;
}

int perf_start_monitoring()
{
	int result;

	result = perf_send_command(LIBCUSTOMPERF_START_MONITORING);
	return result;
}

int perf_stop_monitoring()
{
	int result;

	result = perf_send_command(LIBCUSTOMPERF_STOP_MONITORING);
	return result;
}
