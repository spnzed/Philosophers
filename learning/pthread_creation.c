#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define BOLD "\033[1m"
#define GOLD "\033[0;33m"
#define RESET "\033[0m"

void foo(void)
{

}

void *thread_func(void *arg)
{
	printf ("Hello thread\n");
	return NULL;
}

void *print_background(void *arg)
{
	printf ("Printed from thread\n");
	sleep (5);
	return NULL;
}


#define BOLD_RED "\033[1;31m"
#define RESET    "\033[0m"

long get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void precise_usleep(long usec) {
    struct timeval start, current;
    long elapsed;
    long rem;

    gettimeofday(&start, NULL);
    do {
        gettimeofday(&current, NULL);
        elapsed = get_elapsed_time_microseconds(start, current);
        rem = usec - elapsed;

        if (rem > 1000) 
            usleep(rem / 2);
        
    } while (elapsed < usec);
}

int main(void) 
{
    struct timeval start;
    struct timeval end;
    long seconds;
    long microseconds;
    double elapsed;

    gettimeofday(&start, NULL);
    precise_usleep(500000);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    
    printf("Expected sleep duration: "BOLD_RED"\t0.5"RESET" seconds\n");
    printf("Actual sleep duration: "BOLD_RED"\t\t%f"RESET" seconds\n\n", elapsed);
    return (0);
}

// // Define ANSI escape sequences for colors and styles
// #define BOLD_CYAN "\033[1;36m"
// #define RESET "\033[0m"

// int main()
// {
//     struct timeval start, end;

//     gettimeofday(&start, NULL); // Get the current time before sleeping
//     usleep(500000);  // Expected sleep: 500 milliseconds (0.5 seconds)
//     gettimeofday(&end, NULL);  // Get the time after sleeping

//     long seconds = end.tv_sec - start.tv_sec;
//     long microseconds = end.tv_usec - start.tv_usec;

//     double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

//     printf("Expected sleep duration: "BOLD_CYAN"\t500 milliseconds\n"RESET);
//     printf("Actual sleep duration: "BOLD_CYAN"\t\t%.2f milliseconds\n\n"RESET, elapsedMilliseconds);

//     return 0;
// }

// int	main(void)
// {
// 	struct timespec start_ts, end_ts;
// 	double elapsed_usleep_us, elapsed_usleep_ns;
//     double elapsed_gettimeofday_us, elapsed_gettimeofday_ns;
//     double elapsed_foo_us, elapsed_foo_ns;

// 	//usleep
// 	clock_gettime(CLOCK_MONOTONIC, &start_ts);
// 	int i = 0;
// 	while (i < 100)
// 	{
// 		usleep(0);
// 		i++;
// 	}
// 	clock_gettime(CLOCK_MONOTONIC, &end_ts);
// 	elapsed_usleep_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
// 	elapsed_usleep_us = elapsed_usleep_ns / 1e3;
// 	//gettimeofday
// 	clock_gettime(CLOCK_MONOTONIC, &start_ts);
//     struct timeval tmp;
// 	i = 0;
//     while (i < 100)
// 	{
//         gettimeofday(&tmp, NULL);
// 		i++;
// 	}
//     clock_gettime(CLOCK_MONOTONIC, &end_ts);
//     elapsed_gettimeofday_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
//     elapsed_gettimeofday_us = elapsed_gettimeofday_ns / 1e3;
// 	//foo
//     clock_gettime(CLOCK_MONOTONIC, &start_ts);
// 	i = 0;
//     while (i < 100)
// 	{
//         foo();
// 		i++;
// 	}
//     clock_gettime(CLOCK_MONOTONIC, &end_ts);
//     elapsed_foo_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
//     elapsed_foo_us = elapsed_foo_ns / 1e3;
	
	
// 	printf("Time for %d calls to usleep(0):\t\t" BOLD "%.0f microseconds %.0f ns\n" RESET, 100, elapsed_usleep_us, elapsed_usleep_ns);
// 	printf("Time for %d calls to gettimeofday():\t\t" BOLD "%.0f microseconds\t %.0fns\n" RESET, 100, elapsed_gettimeofday_us, elapsed_gettimeofday_ns);
// 	printf("Time for %d calls to foo():\t\t\t" BOLD "%.0f microseconds\t%.0f ns\n\n" RESET, 100, elapsed_foo_us, elapsed_foo_ns);
// }

// int main ()
// {
// 	pthread_t	thread;

// 	if (pthread_create(&thread, NULL, print_background, NULL) != 0)
// 	{
// 		perror("Failed to create thread\n");
// 		return (1);
// 	}
// 	pthread_detach(thread);
// 	// pthread_join(thread, NULL);
// 	//printf ("Exit\n");
// 	usleep (100000);
// 	printf ("Printed from main\n");
// 	return (0);
// }