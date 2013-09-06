#include <math.h>	/* for sin, exp etc.	   */
#include <stdio.h>      /* standard I/O		*/
#include <string.h>     /* for strcpy - 1 occurrence   */
#include <stdlib.h>     /* for exit   - 1 occurrence   */
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <libcustomperf.h>
#include <time.h>
#include <fcntl.h>

int a_sleep(int x)
{
	int a = 123;

	for(int k=0; k < x; k++)
		for(int i=0; i < 500000000; i++)
			a++;

	return a;	
}

void __list_open_fds(void)
{
	int maxfd = 250, mask, fd, i;
		
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		return;
	else
		maxfd = fd;

	close(fd);
	for (i = 0; i < maxfd; i++) {
		if (dup2(i, fd) != -1) {
			fcntl(i, F_GETFD, &mask);
			printf("FD is open: %d\tCLOEXEC = %d\n", i, mask & FD_CLOEXEC);
			close(fd);
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	int rc;
	int maxfd = 250;

	/* printf("%s:%d\tAfter execvp in the workload\n", __FILE__, __LINE__);
	   __list_open_fds(); */
	
	rc = perf_init();
	if (rc == -1)
		exit(1);

	for(i = 1; i < 5; i++) {
		printf("i = %d\n", i);
		perf_start_monitoring();

		sleep(i);

		perf_stop_monitoring();
		
		sleep(i-1);
	}


	return 0;
}
