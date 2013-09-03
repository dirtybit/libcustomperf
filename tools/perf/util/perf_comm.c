#include <stdio.h>
#include <time.h>
#include "cpumap.h"
#include "thread_map.h"
#include "evlist.h"
#include "evsel.h"
#include "perf_comm.h"
#include "libcustomperf/libcustomperf.h"

#define FD(e, x, y) (*(int *)xyarray__entry(e->fd, x, y))

pthread_t comm_thread;
pthread_attr_t comm_thread_attr;

void send_fds(int fd, struct perf_evlist *evlist, int pages)
{
	struct perf_evsel *evsel;
	int thread;
	int nr_threads = thread_map__nr(evlist->threads);
	int cntr_fd;
	
	if (write(fd, &pages, sizeof(pages)) == -1) {
		perror("Can't write num of fd to workload");
		return;
	}

	if (cpu_map__all(evlist->cpus)) {

		for (thread = 0; thread < nr_threads; thread++) {
			list_for_each_entry(evsel, &evlist->entries, node) {
				cntr_fd = FD(evsel, 0, thread);
				if (write(fd, &cntr_fd, sizeof(cntr_fd)) == -1) {
					perror("Can't write fd to workload");
					return;
				}
				else
					printf("FD written %d\n", cntr_fd);
			}
		}
	}
	else {
		int cpu;
		int nr_cpus = cpu_map__nr(evlist->cpus);

		for (cpu = 0; cpu < nr_cpus; cpu++) {
			for (thread = 0; thread < nr_threads; thread++) {
				list_for_each_entry(evsel, &evlist->entries, node) {
					cntr_fd = FD(evsel, cpu, thread);
					if (write(fd, &cntr_fd, sizeof(cntr_fd)) == -1) {
						perror("Can't write fd to workload");
						return;
					}
				}
			}
		}
	}

	cntr_fd = -1;
	if (write(fd, &cntr_fd, sizeof(cntr_fd)) == -1) {
		perror("Can't write fd to workload");
		return;
	}
}

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

		if (write(fd, &cmd, sizeof(cmd)) == -1) {
			perror("Can't write respond to workload");
			return NULL;
		}

		switch (cmd) {
		case LIBCUSTOMPERF_INITIALIZE:
			break;
		case LIBCUSTOMPERF_START_MONITORING:
			//perf_comm__read_counters(handler_arg->target, evsel_list, START);
			break;
		case LIBCUSTOMPERF_STOP_MONITORING:
			//perf_comm__read_counters(handler_arg->target, evsel_list, STOP);
			break;
		case LIBCUSTOMPERF_GET_FDS:
			send_fds(fd, evsel_list, handler_arg->pages);
			//perf_comm__read_counters(handler_arg->target, evsel_list, STOP);
			break;
		default:
			break;
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
