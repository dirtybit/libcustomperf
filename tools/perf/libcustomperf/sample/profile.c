#include <stdio.h>
#include <stdlib.h>
#include <libcustomperf.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int rc;
	int num_of_startstop;

	rc = perf_init();
	
	if(rc < 0)
		exit(1);

	printf("Profile\n");

	if(argc == 2)
		num_of_startstop = atoi(argv[1])/2;
		
	
	for(int i = 0; i < num_of_startstop; i++) {
		perf_start_monitoring();
		usleep(1000000);
		perf_stop_monitoring();
		usleep(1000000);
	}
	printf("Start/stop test %d times\n", num_of_startstop*2);

	perf_finalize();

	return 0;
}
