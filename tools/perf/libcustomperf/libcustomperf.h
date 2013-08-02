#ifndef _LIBCUSTOMPERF_H
#define _LIBCUSTOMPERF_H

#define TARGET_SOCK_FD 222
#define LEN_REG_LABEL 32

enum libcustomperf_messages {
	LIBCUSTOMPERF_INITIALIZE = 0,
	LIBCUSTOMPERF_START_MONITORING = 1,
	LIBCUSTOMPERF_STOP_MONITORING = 2,
	LIBCUSTOMPERF_SET_REGION = 3,
	LIBCUSTOMPERF_GET_REGION = 4,
	LIBCUSTOMPERF_UNSET_REGION = 5,
	LIBCUSTOMPERF_REGISTER_REGION = 6
};

int perf_init_communication(void);
int perf_start_monitoring(void);
int perf_stop_monitoring(void);
int perf_begin_region(int rd);
int perf_end_region(void);
int perf_get_region(int *rd);

#endif
