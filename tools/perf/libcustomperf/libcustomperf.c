#include "libcustomperf.h"
#include <unistd.h>
#include <stdbool.h>

#define SEND_CMD(c, r) \
  do { \
	if (write(TARGET_SOCK_FD, &c, sizeof(cmd)) == -1) \
		return -1; \
	if (read(TARGET_SOCK_FD, &r, sizeof(result)) == -1) \
		return -1; \
  } while (0)


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
	int cmd = LIBCUSTOMPERF_INITIALIZE;

	SEND_CMD(cmd, result);

	return result == LIBCUSTOMPERF_INITIALIZE;
}

int perf_start_monitoring()
{
	int result;
	int cmd = LIBCUSTOMPERF_START_MONITORING;

	SEND_CMD(cmd, result);

	return result == LIBCUSTOMPERF_START_MONITORING;
}

int perf_stop_monitoring()
{
	int result;
	int cmd = LIBCUSTOMPERF_STOP_MONITORING;

	SEND_CMD(cmd, result);

	return result == LIBCUSTOMPERF_STOP_MONITORING;
}

int perf_begin_region(int rd)
{
	int result;
	int cmd = LIBCUSTOMPERF_SET_REGION;

	if (write(TARGET_SOCK_FD, &cmd, sizeof(cmd)) == -1)
		return -1;

	if (write(TARGET_SOCK_FD, &rd, sizeof(rd)) == -1)
		return -1;

	if (read(TARGET_SOCK_FD, &result, sizeof(result)) == -1)
		return -1;


	return result == LIBCUSTOMPERF_SET_REGION;
}

int perf_end_region()
{
	return perf_begin_region(-1);
}

int perf_get_region(int *rd)
{
	int result;
	int cmd = LIBCUSTOMPERF_GET_REGION;


	if (write(TARGET_SOCK_FD, &cmd, sizeof(cmd)) == -1)
		return -1;

	if (read(TARGET_SOCK_FD, rd, sizeof(*rd)) == -1)
		return -1;

	if (read(TARGET_SOCK_FD, &result, sizeof(result)) == -1)
		return -1;

	return result == LIBCUSTOMPERF_GET_REGION;
}

int perf_register_region(char *label, int *rd)
{
	int result;
	int cmd = LIBCUSTOMPERF_REGISTER_REGION;


	if (write(TARGET_SOCK_FD, &cmd, sizeof(cmd)) == -1)
		return -1;

	if (write(TARGET_SOCK_FD, label, LEN_REG_LABEL) == -1)
		return -1;

	if (read(TARGET_SOCK_FD, rd, sizeof(*rd)) == -1)
		return -1;

	if (read(TARGET_SOCK_FD, &result, sizeof(result)) == -1)
		return -1;

	return result == LIBCUSTOMPERF_GET_REGION;
}
