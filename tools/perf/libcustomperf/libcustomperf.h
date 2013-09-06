#ifndef _LIBCUSTOMPERF_H
#define _LIBCUSTOMPERF_H

#define TARGET_SOCK_FD 222

enum libcustomperf_messages {
	LIBCUSTOMPERF_INITIALIZE = 0,
	LIBCUSTOMPERF_START_MONITORING = 1,
	LIBCUSTOMPERF_STOP_MONITORING = 2,
	LIBCUSTOMPERF_GET_FDS = 3
};

int perf_init(void);
int perf_finalize(void);
void perf_start_monitoring(void);
void perf_stop_monitoring(void);

#endif
