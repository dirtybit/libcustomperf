#include "libcustomperf.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <unistd.h>

static struct perf_counter_mmap *counters;
static unsigned int pages;
static int sock_fd;

void perf_read_counters(enum delta_type type)
{
	struct perf_counter_mmap *counter;

	list_for_each_entry(counter, &counters->list, list) {
		u64 value = mmap_read_counter(counter->mmap_base);
		if (counter->fd == 7) {
			printf("Type: %d -  Value: %ld\n", type, value);
			if (type == START) {
				counter->last_start = value;
			} else if (type == STOP) {
				printf("Counter FD %d - Begin: %ld\tEnd: %ld\t", counter->fd, counter->last_start, value);
				value -= counter->last_start;
				printf("Delta %ld\n", value);
				counter->accumulate += value;
			}
		}
	}
}

int perf_send_command(int fd, int cmd)
{
	int result = -1;
	if (write(fd, &cmd, sizeof(cmd)) == -1){
		perror("Unable to send command");
		return -1;
	}

	if (read(fd, &result, sizeof(result)) == -1) {
		perror("Unable to read result");
		return -1;
	}

	return result == cmd;
}

int perf_get_cntr_fds(int fd)
{
	int cntr_fd = -1;
	struct perf_counter_mmap *counter;

	if (perf_send_command(fd, LIBCUSTOMPERF_GET_FDS) == 0)
	{
		perror("GET_FDS");
		return -1;
	}
	
	if (read(fd, &pages, sizeof(pages)) == -1)
	{
		perror("Read num pages");
		return -1;
	}

	while(1) {
		if (read(fd, &cntr_fd, sizeof(cntr_fd)) == -1)
			return -1;

		if (cntr_fd < 0)
			break;

		counter = (struct perf_counter_mmap *) malloc(sizeof(*counter));
		counter->fd = cntr_fd;
		counter->last_start = 0;
		counter->accumulate = 0;
		list_add(&counter->list, &counters->list);
	}

	return 0;
}

int perf_mmap_counters()
{
	struct perf_counter_mmap *counter;
	void *base;
	int page_size = sysconf(_SC_PAGE_SIZE);
	int prot = PROT_READ, mmap_len = (pages + 1) * page_size; //mask = pages * page_size - 1,

	list_for_each_entry(counter, &counters->list, list) {
		base = mmap(NULL, mmap_len, prot, MAP_SHARED, counter->fd, 0);
		if (base == MAP_FAILED) {
			perror("MMAP");
			counter->mmap_base = NULL;
			goto unmap;
		}

		counter->mmap_base = base;
	}

	return 0;

unmap:
	list_for_each_entry(counter, &counters->list, list) {
		if (counter->mmap_base != NULL) {
			munmap(counter->mmap_base, mmap_len);
			counter->mmap_base = NULL;
		}
	}

	return -1;
}

int perf_init()
{
	char *perf_comm_fd_env = getenv("PERF_COMM_FD");

	if(!perf_comm_fd_env)
		return -1;
	else
	{
		sock_fd = atoi(perf_comm_fd_env);
		counters = (struct perf_counter_mmap *) malloc(sizeof(*counters));
		INIT_LIST_HEAD(&counters->list);

		if (perf_get_cntr_fds(sock_fd) < 0)
			return -1;

		if (perf_mmap_counters() < 0)
			return -1;

		return 0;
	}
}

int perf_finalize()
{
	// TODO: This function communicates back the collected delta information to the perf.

	struct perf_counter_mmap *counter;

	list_for_each_entry(counter, &counters->list, list) {
		printf("Counter FD: %d\tValue: %ld\n", counter->fd, counter->accumulate);
	}

	return 0;
}

void perf_start_monitoring()
{
	perf_read_counters(START);
}

void perf_stop_monitoring()
{
	perf_read_counters(STOP);
}

