#include "libcustomperf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int perf_send_command(int fd, int cmd)
{
	int result = 1;
	if (write(fd, &cmd, sizeof(cmd)) == -1)
		return -1;
	if (read(fd, &result, sizeof(result)) == -1)
		return -1;

	return result == cmd;
}

int perf_init_communication()
{
	char *perf_comm_fd_env = getenv("PERF_COMM_FD");

	if(!perf_comm_fd_env)
		return -1;
	else
		return atoi(perf_comm_fd_env);
}

int perf_start_monitoring(int fd)
{
	int result;

	result = perf_send_command(fd, LIBCUSTOMPERF_START_MONITORING);
	return result;
}

int perf_stop_monitoring(int fd)
{
	int result;

	result = perf_send_command(fd, LIBCUSTOMPERF_STOP_MONITORING);
	return result;
}
