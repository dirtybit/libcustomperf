#include <linux/perf_event.h>
#include <stdio.h>
#include <time.h>
#include "evlist.h"
#include "target.h"
#include "perf_comm.h"
#include "libcustomperf/libcustomperf.h"

pthread_t comm_thread;
pthread_attr_t comm_thread_attr;

void *perf_comm__handler(void *arg)
{
	int cmd = -918;
	char label[LEN_REG_LABEL];
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
			printf("perf_comm: init communication\n");
			break;
		case LIBCUSTOMPERF_START_MONITORING:
			perf_evlist__enable(evsel_list);
			printf("perf_comm: start monitoring\n");
			break;
		case LIBCUSTOMPERF_STOP_MONITORING:
			perf_evlist__disable(evsel_list);
			printf("perf_comm: stop monitoring\n");
			break;
		case LIBCUSTOMPERF_SET_REGION:
		{
			int rd;
			if (read(fd, &rd, sizeof(rd)) == -1) {
				perror("Can't read region descriptor");
				return NULL;
			}
			ioctl(-1, PERF_EVENT_IOC_SET_REGION, &rd);
			printf("perf_comm: set region\n");
			break;
		}
		case LIBCUSTOMPERF_UNSET_REGION:
			cmd = ioctl(-1, PERF_EVENT_IOC_UNSET_REGION, 0);
			printf("%d\n", cmd);
			printf("perf_comm: unset region\n");
			break;
		case LIBCUSTOMPERF_GET_REGION:
		{
			int rd;
			ioctl(-1, PERF_EVENT_IOC_GET_REGION, &rd);
			if (write(fd, &rd, sizeof(rd)) == -1) {
				perror("Can't write respond to workload");
				return NULL;
			}
			printf("perf_comm: get region\n");
			break;
		}
		case LIBCUSTOMPERF_REGISTER_REGION:
		{
			int rd;
			struct perf_region_definition *region;
			region = (struct perf_region_definition *) malloc(sizeof(*region));

			ioctl(-1, PERF_EVENT_IOC_REG_REGION, &rd);
			if (read(fd, label, LEN_REG_LABEL) == -1) {
				perror("Can't read region label");
				return NULL;
			}
			if (write(fd, &rd, sizeof(rd)) == -1) {
				perror("Can't write respond to workload");
				return NULL;
			}
			region->label = strndup(label, LEN_REG_LABEL);
			region->rd = rd;
			perf_target__add_region(handler_arg->target, region);
			printf("perf_comm: register region\n");
			break;
		}
		default:
			printf("perf_comm: nothing\n");
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
