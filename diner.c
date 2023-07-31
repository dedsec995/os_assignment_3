#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>

#define NUM_STOOLS 8

sem_t counter_seats;
pthread_mutex_t counter_mutex;
int num_patrons;
int patron_count = 0;
int total_wait_time = 0;

void *patron_thread(void *arg)
{
	int patron_id = *(int *)arg;
	int wait_time;

	// Try to acquire a seat
	sem_wait(&counter_seats);

	// Start eating
	pthread_mutex_lock(&counter_mutex);
	patron_count++;
	printf("Patron #%d is eating!", patron_id);
	pthread_mutex_unlock(&counter_mutex);

	// Simulate eating for a random amount of time (1 ms to 1000 ms)
	wait_time = rand() % 351 + 41;
	usleep(wait_time * 1000);

	// Record wait time
	total_wait_time += wait_time;

	// Finished eating, release the seat
	pthread_mutex_lock(&counter_mutex);
	patron_count--;
	printf("Patron #%d waited %d ms\n", patron_id, wait_time);
	pthread_mutex_unlock(&counter_mutex);

	sem_post(&counter_seats);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("You must input the number of patrons!\n");
		exit(-1);
	}
	num_patrons = atoi(argv[1]);

	// Initialize semaphore and mutex
	sem_init(&counter_seats, 0, NUM_STOOLS);
	pthread_mutex_init(&counter_mutex, NULL);

	// Create an array to store thread IDs
	pthread_t *threads = (pthread_t *)malloc(num_patrons * sizeof(pthread_t));

	// Create threads
	for (int i = 0; i < num_patrons; i++)
	{
		int *patron_id = (int *)malloc(sizeof(int));
		*patron_id = i + 1;
		pthread_create(&threads[i], NULL, patron_thread, (void *)patron_id);
	}

	// Wait for all threads to finish
	for (int i = 0; i < num_patrons; i++)
	{
		pthread_join(threads[i], NULL);
	}

	// Clean up
	free(threads);
	sem_destroy(&counter_seats);
	pthread_mutex_destroy(&counter_mutex);

	// Calculate and print average wait time
	printf("Average wait time: %d ms\n", total_wait_time / num_patrons);
	printf("num_patrons: %d\n", num_patrons);

	return 0;
}