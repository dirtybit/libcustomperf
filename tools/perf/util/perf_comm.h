#include <pthread.h>
#include "../perf.h"
#include "util/evlist.h"
#include "util/target.h"

/* This needs to be changed */

struct perf_handler_arg {
	struct perf_evlist *evlist;
	struct perf_target *target;
};

void *perf_comm__handler(void *arg);
int perf_comm__start_handler(struct perf_handler_arg *arg);
int perf_comm__terminate_handler(void);
