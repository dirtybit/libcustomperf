#ifndef _LIBCUSTOMPERF_H
#define _LIBCUSTOMPERF_H

#include "list.h"
#include "rdpmc.h"
#include <stdlib.h>

enum libcustomperf_messages {
	LIBCUSTOMPERF_INITIALIZE = 0,
	LIBCUSTOMPERF_START_MONITORING = 1,
	LIBCUSTOMPERF_STOP_MONITORING = 2,
	LIBCUSTOMPERF_GET_FDS = 3,
	LIBCUSTOMPERF_SEND_DELTAS = 4
};

enum delta_type {START, STOP, UNK};

struct perf_delta_point {
	enum delta_type type;
	struct timeval timestamp;
	u64 counter_value;
	struct list_head list;
};

struct perf_counter_mmap {
	int fd;
	void *mmap_base;
	struct perf_delta_point *deltas;
	struct list_head list;
};

int perf_init(void);
int perf_finalize(void);
void perf_start_monitoring(void);
void perf_stop_monitoring(void);

#endif
