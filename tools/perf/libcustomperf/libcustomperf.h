#ifndef _LIBCUSTOMPERF_H
#define _LIBCUSTOMPERF_H

#define TARGET_SOCK_FD 222

enum libcustomperf_messages {
	LIBCUSTOMPERF_INITIALIZE = 0,
	LIBCUSTOMPERF_START_MONITORING = 1,
	LIBCUSTOMPERF_STOP_MONITORING = 2
};

int perf_init_communication(void);
int perf_start_monitoring(int);
int perf_stop_monitoring(int);

#endif
