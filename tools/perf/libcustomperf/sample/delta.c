#include <math.h>	/* for sin, exp etc.	   */
#include <stdio.h>      /* standard I/O		*/
#include <string.h>     /* for strcpy - 1 occurrence   */
#include <stdlib.h>     /* for exit   - 1 occurrence   */
#include <sys/time.h>
#include <libcustomperf.h>
#include <time.h>

int a_sleep(int x)
{
	int a = 123;

	for(int k=0; k < x; k++)
		for(int i=0; i < 500000000; i++)
			a++;

	return a;	
}


int main(int argc, char *argv[])
{
	int i;
	int perf_fd;


	perf_fd = perf_init_communication();

	printf("FD: %d\n", perf_fd);

	for(i = 0; i < 5; i++) {
		printf("i = %d\n", i);
		if(perf_fd)
			perf_start_monitoring(perf_fd);

		sleep(i);

		if(perf_fd)
			perf_stop_monitoring(perf_fd);
	}


	return 0;
}
