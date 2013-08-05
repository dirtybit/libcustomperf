#include <stdio.h>
#include <time.h>
#include "evlist.h"
#include "perf_comm.h"
#include "libcustomperf/libcustomperf.h"

pthread_t comm_thread;
pthread_attr_t comm_thread_attr;

void *perf_comm__handler(void *arg)
{
	int cmd = -918;
	struct perf_handler_arg *handler_arg = (struct perf_handler_arg *) arg;
	struct perf_evlist *evsel_list = handler_arg->evlist;
	int fd = handler_arg->target->comm_sck;
	while (1) {
		if (read(fd, &cmd, sizeof(cmd)) == -1) {
			perror("Can't read command from the workload");
			return NULL;
		}

		switch (cmd) {
		case LIBCUSTOMPERF_INITIALIZE:
			break;
		case LIBCUSTOMPERF_START_MONITORING:
			perf_evlist__enable(evsel_list);
			break;
		case LIBCUSTOMPERF_STOP_MONITORING:
			perf_evlist__disable(evsel_list);
			break;
		default:
			break;
		}

		if (write(fd, &cmd, sizeof(cmd)) == -1) {
			perror("Can't write respond to workload");
			return NULL;
		}
	}
	return 0;
}

int perf_comm__start_handler(struct perf_handler_arg *arg)
{
	int rc;
	pthread_attr_init(&comm_thread_attr);

	rc = pthread_create(&comm_thread, &comm_thread_attr, perf_comm__handler, (void *)arg);
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		return -1;
	}
	return 0;
}

int perf_comm__terminate_handler(void)
{
	return 0;
}
