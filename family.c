#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>
#include<unistd.h>
unsigned int num_family_members;
sem_t *chopsticks;

void *family_member(void *arg) {
    int member_id = *((int *)arg);
    int left_chopstick = member_id;
    int right_chopstick = (member_id + 1) % num_family_members;
    while (1) {
        // Wait
        sleep(rand() % 5); // Let's wait

        // Get chopsticks
        sem_wait(&chopsticks[left_chopstick]);
        sem_wait(&chopsticks[right_chopstick]);
        // Eat
        printf("Family member #%d is eating!\n", member_id);
        sleep(rand() % 3); // Eat it up

        // Free chopsticks
        sem_post(&chopsticks[right_chopstick]);
        sem_post(&chopsticks[left_chopstick]);
    }

    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
	if(argc != 2){
		printf("You must input the number of family members!\n");
		exit(-1);
	}
	num_family_members = atoi(argv[1]);
	chopsticks = (sem_t *)malloc(sizeof(sem_t) * num_family_members);

    // Creating semaphores
    for (int i = 0; i < num_family_members; ++i) {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create threads for family members
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * num_family_members);
    int *thread_args = (int *)malloc(sizeof(int) * num_family_members);

    for (int i = 0; i < num_family_members; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, family_member, &thread_args[i]);
    }


    for (int i = 0; i < num_family_members; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Clean up Even thou its gonna run till sun burns out!!!!! Pro gamer ^_^
    free(chopsticks);
    free(threads);
    free(thread_args);

    return 0;
}