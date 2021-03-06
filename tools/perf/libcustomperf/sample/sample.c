/*
 *     C/C++ Whetstone Benchmark Single or Double Precision
 *
 *     Original concept	Brian Wichmann NPL      1960's
 *     Original author	 Harold Curnow  CCTA     1972
 *     Self timing versions    Roy Longbottom CCTA     1978/87
 *     Optimisation control    Bangor University	1987/90
 *     C/C++ Version	   Roy Longbottom	  1996
 *
 ************************************************************
 *
 *     The program should run for about 100 seconds on PCs
 *     (adjustable in main - variable duration). This time
 *     is necessary because of the poor clock resolution.
 *     The original concept included such things as a given
 *     number of subroutine calls and divides which may be
 *     changed by optimisation. For comparison purposes the
 *     compiler and level of optimisation should be identified.
 *     Complier and option variables in main() should be used
 *     for this purpose.
 *	
 ************************************************************
 *
 *     The original benchmark had a single variable I which
 *     controlled the running time. Constants with values up
 *     to 899 were multiplied by I to control the number
 *     passes for each loop. It was found that large values
 *     of I could overflow index registers so an extra outer
 *     loop with a second variable J was added.
 *
 *     Self timing versions were produced during the early
 *     days. The 1978 changes supplied timings of individual
 *     loops and these were used later to produce MFLOPS and
 *     MOPS ratings.
 *
 *     1987 changes converted the benchmark to Fortran 77
 *     standards and removed redundant IF statements and
 *     loops to leave the 8 active loops N1 to N8. Procedure
 *     P3 was changed to use global variables to avoid over-
 *     optimisation with the first two statements changed from
 *     X1=X and Y1=Y to X=Y and Y=Z. A self time calibrating
 *     version for PCs was also produced, the facility being
 *     incorporated in this version.
 *
 *     This version has changes to avoid worse than expected
 *     speed ratings, due to underflow, and facilities to show
 *     that consistent numeric output is produced with varying
 *     optimisation levels or versions in different languages.
 *
 *     Some of the procedures produce ever decreasing numbers.
 *     To avoid problems, variables T and T1 have been changed
 *     from 0.499975 and 0.50025 to 0.49999975 and 0.50000025.
 *
 *     Each section now has its own double loop. Inner loops
 *     are run 100 times the loop constants. Calibration
 *     determines the number of outer loop passes. The
 *     numeric results produced in the main output are for
 *     one pass on the outer loop. As underflow problems were
 *     still likely on a processor 100 times faster than a 100
 *     MHZ Pentium, three sections have T=1.0-T inserted in the
 *     outer loop to avoid the problem. The two loops avoid
 *     index register overflows.
 *
 *     The first section is run ten times longer than required
 *     for accuracy in calculating MFLOPS. This time is divided
 *     by ten for inclusion in the MWIPS calculations.
 *
 *     This version has facilities for typing in details of the
 *     particular run. This information is appended to file
 *     Whets.txt along with the results. The input section can
 *     be avoided using a command line parameter N (for example
 *     Whets.exe N).  
 *
 *     Roy Longbottom  101323.2241@compuserve.com
 *
 ************************************************************
 *
 *     Whetstone benchmark results are available in whets.tbl
 *     from ftp.nosc.mil/pub/aburto. The results include
 *     further details of the benchmarks.
 *
 ************************************************************
 *
 *     Source code is available in C/C++, Fortran, Basic and
 *     Visual Basic in the same format as this version. Pre-
 *     compiled versions for PCs are also available via C++.
 *     These comprise optimised and non-optimised versions
 *     for DOS, Windows and NT.
 *
 *     This version compiles and runs correctly either as a
 *     C or CPP program with a WATCOM and Borland compiler.
 *
 ************************************************************
 *
 * Example of initial calibration display (Pentium 100 MHz)
 *
 * Single Precision C/C++ Whetstone Benchmark
 *
 * Calibrate
 *      0.17 Seconds	  1   Passes (x 100)
 *      0.77 Seconds	  5   Passes (x 100)
 *      3.70 Seconds	 25   Passes (x 100)
 *
 * Use 676  passes (x 100)
 *
 * 676 passes are used for an approximate duration of 100
 * seconds, providing an initial estimate of a speed rating
 * of 67.6 MWIPS.
 *
 * This is followed by the table of results as below. Input
 * statements are then supplied to type in the run details.
 *
 ************************************************************
 * 
 * Examples of results from file Whets.txt
 *
 * Whetstone Single  Precision Benchmark in C/C++
 *
 * Month run	 4/1996
 * PC model	  Escom
 * CPU		Pentium
 * Clock MHz	 100
 * Cache	     256K
 * Options	   Neptune chipset
 * OS/DOS	    Windows 95
 * Compiler	  Watcom C/C++ 10.5  Win386
 * OptLevel	  No optimisation
 * Run by	    Roy Longbottom
 * From	      UK
 * Mail	      101323.2241@compuserve.com
 *
 * Loop content		 Result	    MFLOPS     MOPS   Seconds
 *
 * N1 floating point    -1.12475025653839100      19.971	      0.274
 * N2 floating point    -1.12274754047393800      11.822	      3.240
 * N3 if then else	1.00000000000000000		11.659     2.530
 * N4 fixed point	12.00000000000000000		13.962     6.430
 * N5 sin,cos etc.	0.49904659390449520		2.097    11.310
 * N6 floating point     0.99999988079071040	3.360	     45.750
 * N7 assignments	3.00000000000000000		2.415    21.810
 * N8 exp,sqrt etc.      0.75110864639282230		1.206     8.790
 *
 * MWIPS					  28.462	    100.134
 *
 * Whetstone Single  Precision Benchmark in C/C++
 *
 * Compiler	  Watcom C/C++ 10.5  Win386
 * OptLevel	  -otexan -zp4 -om -fp5 -5r
 *
 * Loop content		 Result	    MFLOPS     MOPS    Seconds
 *
 * N1 floating point    -1.12475025653839100      26.751		0.478
 * N2 floating point    -1.12274754047393800      17.148		5.220
 * N3 if then else	1.00000000000000000		19.922      3.460
 * N4 fixed point	12.00000000000000000		15.978     13.130
 * N5 sin,cos etc.	0.49904659390449520		2.663     20.810
 * N6 floating point     0.99999988079071040      10.077	      35.650
 * N7 assignments	3.00000000000000000		22.877      5.380
 * N8 exp,sqrt etc.      0.75110864639282230		1.513     16.370
 *
 * MWIPS					  66.270	     100.498
 *
 *
 * Whetstone Double  Precision Benchmark in C/C++
 *
 * Compiler	  Watcom C/C++ 10.5 Win32NT 
 * OptLevel	  -otexan -zp4 -om -fp5 -5r
 *
 * Loop content		 Result	   MFLOPS      MOPS   Seconds
 *
 * N1 floating point    -1.12398255667391900     26.548		0.486
 * N2 floating point    -1.12187079889284400     16.542		5.460
 * N3 if then else	1.00000000000000000		19.647     3.540
 * N4 fixed point	12.00000000000000000		15.680    13.500
 * N5 sin,cos etc.	0.49902937281515140		3.019    18.520
 * N6 floating point     0.99999987890802820      9.977	      36.330
 * N7 assignments	3.00000000000000000		22.620     5.490
 * N8 exp,sqrt etc.      0.75100163018457870		1.493    16.740
 *
 * MWIPS					 67.156	     100.066
 *
 *  Note different numeric results to single precision. Slight variations
 *  are normal with different compilers and sometimes optimisation levels. 
 *
 **************************************************************************
 *
 *			Running Instructions
 *
 *      1.  Insert compiler name and optimisation details at COMPILER
 *	  For identification if executable files are used elsewhere
 *      2.  Insert timer routine at TIME to return seconds
 *      3.  Insert date routine at DATE for month and year
 *      4.  Compile and run for single precision results. Include run
 *	  time parameter N to bipass typing in hardware details etc.
 *      5.  Insert compiler macro definition DP for -dDP to run double
 *	  precision version (or change code at PRECISION)
 *      6.  Run with maximum and no optimisation (minimum debug)
 *      7.  Notify Roy Longbottom of other necessary changes
 *      8.  Send results file Whets.txt to Roy Longbottom - with one
 *	  sample of each run and system details fully completed
 *
 *      Roy Longbottom  101323.2241@compuserve.com    10 September 1996
 *
 **************************************************************************
 */
 

#include <math.h>	/* for sin, exp etc.	   */
#include <stdio.h>      /* standard I/O		*/
#include <string.h>     /* for strcpy - 1 occurrence   */
#include <stdlib.h>     /* for exit   - 1 occurrence   */
#include <sys/time.h>
#include <libcustomperf.h>
#include <time.h>

#ifdef DP 
	#define SPDP double
	#define Precision "Double"
#else
	#define SPDP float
	#define Precision "Single"
#endif




void whetstones(long xtra, long x100, int calibrate, int profile);  
void pa(SPDP e[4], SPDP t, SPDP t2);
void po(SPDP e1[4], long j, long k, long l);
void p3(SPDP *x, SPDP *y, SPDP *z, SPDP t, SPDP t1, SPDP t2);
void pout(char title[22], float ops, int type, SPDP checknum, struct timeval time, int calibrate, int section);
  


static struct timeval loop_time[9];
static SPDP loop_mops[9];
static SPDP loop_mflops[9];
static SPDP TimeUsed;
static SPDP mwips;
static char  headings[9][18];
static SPDP Check;
static SPDP results[9];
static char this_month;
static int this_year;
  
#include <time.h>  /* for following time functions only */
SPDP what_time()
{		  
	SPDP secs;
	clock_t Time;
	Time = clock();
	secs = (SPDP)(Time) / (SPDP)(CLOCKS_PER_SEC);
	return secs;
}

     
void what_date()
{
	return;
}

int num_of_startstop = 0;
int perf_comm_fd;

int main(int argc, char *argv[])
{
	int count = 10, calibrate = 1;
	long xtra=1;
	int endit, section;
	long x100 = 100;
	int duration = 100;
	char general[9][80] = {" "};

#if PROFILE
	perf_comm_fd = perf_init();
	
	if(perf_comm_fd < 0)
		exit(1);

	printf("Profile\n");
	perf_start_monitoring();
#endif

	if(argc == 2)
		num_of_startstop = atoi(argv[1]);
		
	
	printf("\n %s Precision C/C++ Whetstone Benchmark\n\n", Precision);

	printf("Calibrate\n");
	do
	{
		TimeUsed=0;
		whetstones(xtra,x100,calibrate, 0);
	    
		printf("%11.2f Seconds %10.0lf   Passes (x 100)\n",
				     TimeUsed,(SPDP)(xtra));
		calibrate = calibrate + 1;
		count = count - 1;
		if (TimeUsed > 2.0)
			count = 0;
		else
			xtra = xtra * 5;
	} while (count > 0);
	
	if (TimeUsed > 0)
		xtra = (long)((SPDP)(duration * xtra) / TimeUsed);
	if (xtra < 1)
		xtra = 1;
	
	calibrate = 0;
  

	xtra = 2000;

	printf("\nUse %ld  passes (x 100)\n", xtra);

	printf("\n	  %s Precision C/C++ Whetstone Benchmark",Precision);
	printf("\nLoop content		  Result	         MFLOPS "
				"     MOPS     Seconds\n\n");

	TimeUsed=0;
	whetstones(xtra,x100,calibrate, 1);

	printf("\nMWIPS	    ");
	if (TimeUsed>0)
		mwips=(float)(xtra) * (float)(x100) / (10 * TimeUsed);
	else
		mwips = 0;
	
	printf("%39.3f%19.3f\n\n",mwips,TimeUsed);
     
	if (Check == 0)
		printf("Wrong answer  ");
	
#ifdef PROFILE
	printf("Profile\n");
	perf_stop_monitoring();
	for(int i = 0; i < num_of_startstop; i++) {
		perf_start_monitoring();
		perf_stop_monitoring();
	}
	printf("Start/stop test %d times\n", num_of_startstop);
#endif

}


int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
        long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * 
								t1->tv_sec);
        result->tv_sec = diff / 1000000;
        result->tv_usec = diff % 1000000;

        return (diff<0);
}

void timeval_print(struct timeval *tv)
{
        char buffer[30];
        time_t curtime;

        printf("%ld.%06ld", tv->tv_sec, tv->tv_usec);
        curtime = tv->tv_sec;
        strftime(buffer, 30, "%m-%d-%Y  %T", localtime(&curtime));
        printf(" = %s.%06ld\n", buffer, tv->tv_usec);
}



void whetstones(long xtra, long x100, int calibrate, int profile)
{
	long n1,n2,n3,n4,n5,n6,n7,n8,i,ix,n1mult;
	SPDP x,y,z;	      
	long j,k,l;
	SPDP e1[4];
	SPDP timea;
	SPDP timeb;
	struct timeval tvBegin, tvEnd, tvDiff;
			
	SPDP t =  0.49999975;
	SPDP t0 = t;	
	SPDP t1 = 0.50000025;
	SPDP t2 = 2.0;
		
	Check=0.0;
	
	n1 = 12*x100;
	n2 = 14*x100;
	n3 = 345*x100;
	n4 = 210*x100;
	n5 = 32*x100;
	n6 = 899*x100;
	n7 = 616*x100;
	n8 = 93*x100;
	n1mult = 10;

	/* Section 1, Array elements */

	e1[0] = 1.0;
	e1[1] = -1.0;
	e1[2] = -1.0;
	e1[3] = -1.0;
	gettimeofday(&tvBegin, NULL);

	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n1*n1mult; i++)
			{
				e1[0] = (e1[0] + e1[1] + e1[2] - e1[3]) * t;
				e1[1] = (e1[0] + e1[1] - e1[2] + e1[3]) * t;
				e1[2] = (e1[0] - e1[1] + e1[2] + e1[3]) * t;
				e1[3] = (-e1[0] + e1[1] + e1[2] + e1[3]) * t;
			}
			t = 1.0 - t;
		}
		t =  t0;		    
	}
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	pout("N1 floating point\0",(float)(n1*16)*(float)(xtra), 1,e1[3],tvDiff,calibrate,1);

	/* Section 2, Array as parameter */
	gettimeofday(&tvBegin, NULL);
	{
		for (ix=0; ix<xtra; ix++)
		{ 
			for(i=0; i<n2; i++)
			{
				pa(e1,t,t2);
			}
			t = 1.0 - t;
		}
		t =  t0;
	}
	
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	pout("N2 floating point\0",(float)(n2*96)*(float)(xtra), 1,e1[3],tvDiff,calibrate,2);

	/* Section 3, Conditional jumps */
	j = 1;
	gettimeofday(&tvBegin, NULL);

	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n3; i++)
			{
				if(j==1)
					j = 2;
				else
					j = 3;
				if(j>2)
					j = 0;
				else
					j = 1;
				if(j<1)
					j = 1;
				else
					j = 0;
			}
		}
	}
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	pout("N3 if then else  \0",(float)(n3*3)*(float)(xtra), 2,(SPDP)(j),tvDiff,calibrate,3);

	/* Section 4, Integer arithmetic */
	j = 1;
	k = 2;
	l = 3;

	gettimeofday(&tvBegin, NULL);
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n4; i++)
			{
				j = j *(k-j)*(l-k);
				k = l * k - (l-j) * k;
				l = (l-k) * (k+j);
				e1[l-2] = j + k + l;
				e1[k-2] = j * k * l;
			}
		}
	}

	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	x = e1[0]+e1[1];
	pout("N4 fixed point   \0",(float)(n4*15)*(float)(xtra), 2,x,tvDiff,calibrate,4);
     
	/* Section 5, Trig functions */
	x = 0.5;
	y = 0.5;
	
	gettimeofday(&tvBegin, NULL);

	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=1; i<n5; i++)
			{
				x = t*atan(t2*sin(x)*cos(x)/(cos(x+y)+cos(x-y)-1.0));
				y = t*atan(t2*sin(y)*cos(y)/(cos(x+y)+cos(x-y)-1.0));
			}
			t = 1.0 - t;
		}
		t = t0;
	}
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	
	pout("N5 sin,cos etc.  \0",(float)(n5*26)*(float)(xtra), 2,y,tvDiff,calibrate,5);
  
	/* Section 6, Procedure calls */
	x = 1.0;
	y = 1.0;
	z = 1.0;
	gettimeofday(&tvBegin, NULL);
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n6; i++)
			{
				p3(&x,&y,&z,t,t1,t2);
			}
		}
	}
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	
	pout("N6 floating point\0",(float)(n6*6)*(float)(xtra),
				1,z,tvDiff,calibrate,6);
  
	/* Section 7, Array refrences */
	j = 0;
	k = 1;
	l = 2;
	e1[0] = 1.0;
	e1[1] = 2.0;
	e1[2] = 3.0;
	gettimeofday(&tvBegin, NULL);
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0;i<n7;i++)
			{
				po(e1,j,k,l);
			}
		}
	}
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	pout("N7 assignments   \0",(float)(n7*3)*(float)(xtra), 2, e1[2],tvDiff,calibrate,7);
	
	/* Section 8, Standard functions */
	x = 0.75;
	
	gettimeofday(&tvBegin, NULL);
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n8; i++)
			{
				x = sqrt(exp(log(x)/t1));
			}
		}
	}
	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	pout("N8 exp,sqrt etc. \0",(float)(n8*4)*(float)(xtra), 2,x,tvDiff,calibrate,8);

	return;
}


void pa(SPDP e[4], SPDP t, SPDP t2)
{
	long j;
	for(j=0;j<6;j++)
	{
		e[0] = (e[0]+e[1]+e[2]-e[3])*t;
		e[1] = (e[0]+e[1]-e[2]+e[3])*t;
		e[2] = (e[0]-e[1]+e[2]+e[3])*t;
		e[3] = (-e[0]+e[1]+e[2]+e[3])/t2;
	}

	return;
}

void po(SPDP e1[4], long j, long k, long l)
{
	e1[j] = e1[k];
	e1[k] = e1[l];
	e1[l] = e1[j];
	return;
}

void p3(SPDP *x, SPDP *y, SPDP *z, SPDP t, SPDP t1, SPDP t2)
{
	*x = *y;
	*y = *z;
	*x = t * (*x + *y);
	*y = t1 * (*x + *y);
	*z = (*x + *y)/t2;
	return;
}

    void pout(char title[18], float ops, int type, SPDP checknum,
              struct timeval time, int calibrate, int section)
      {
        SPDP mops,mflops;

        Check = Check + checknum;
        loop_time[section] = time;
        strcpy (headings[section],title);
        TimeUsed =  TimeUsed + time.tv_sec;
        if (calibrate == 1)
     
          {
              results[section] = checknum;
          }
        if (calibrate == 0)
          {              
            printf("%s %24.17f    ",headings[section],results[section]);    
       
            if (type == 1)
             {
                if (time.tv_sec>0)
                 {
                    mflops = ops/(1000000L*time.tv_sec);
                 }
                else
                 {
                   mflops = 0;
                 }
                loop_mops[section] = 99999;
                loop_mflops[section] = mflops;
                printf(" %9.3f         %ld.%06ld\n",
                 loop_mflops[section], time.tv_sec, time.tv_usec);                
             }
            else
             {
                if (time.tv_sec>0)
                 {
                   mops = ops/(1000000L*time.tv_sec);
                 }
                else
                 {
                   mops = 0;
                 }
                loop_mops[section] = mops;
                loop_mflops[section] = 0;                 
                printf("           %9.3f %ld.%06ld\n",
		       loop_mops[section], time.tv_sec, time.tv_usec);
             }
          }
          
        return;
      }


 
