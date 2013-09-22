#include "rdpmc.h"
#include <linux/perf_event.h>
#include <stdio.h>

#define barrier() asm volatile("" ::: "memory")

/*
 * dirtybit:
 * Functions needed to read the PMC using mapped pages of counters.
 */

static u64 rdpmc(unsigned int counter)
{
	unsigned int low, high;

	asm volatile("rdpmc" : "=a" (low), "=d" (high) : "c" (counter));

	return low | ((u64)high) << 32;
}

u64 mmap_read_counter(void *addr)
{
	struct perf_event_mmap_page *pc = addr;
	u32 seq, idx;
	u64 count;

	do {
		seq = pc->lock;
		barrier();

		idx = pc->index;
		count = pc->offset;
		if (idx)
			count += rdpmc(idx - 1);

		barrier();
	} while (pc->lock != seq);


	return count;
}


