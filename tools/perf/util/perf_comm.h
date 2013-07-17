#include <pthread.h>
#include "../perf.h"
#include "../builtin-record.h"

/* This needs to be changed */

struct perf_record;

void *perf_comm__handler(void *arg);
int perf_comm__start_handler(struct perf_record *rec);
int perf_comm__terminate_handler(void);
