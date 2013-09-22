#ifndef _LIBCUSTOMPERF_H
#define _LIBCUSTOMPERF_H

#include "list.h"
#include "rdpmc.h"
#include <stdlib.h>

enum libcustomperf_messages {
	LIBCUSTOMPERF_GET_FDS = 0
};

enum delta_type {START, STOP, UNK};

struct perf_counter_mmap {
	int fd;
	void *mmap_base;
	u64 last_start;
	u64 accumulate;
	struct list_head list;
};

int perf_init(void);
void perf_start_monitoring(void);
void perf_stop_monitoring(void);

#endif
